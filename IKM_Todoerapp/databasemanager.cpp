#include "databasemanager.h"
#include <QDebug>
#include <QDateTime>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
    , m_currentUserId(1)
{
}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

bool DatabaseManager::connectToDatabase()
{
    m_database = QSqlDatabase::addDatabase("QPSQL");

    m_database.setHostName("localhost");
    m_database.setPort(5432);
    m_database.setDatabaseName("todo");
    m_database.setUserName("postgres");
    m_database.setPassword("1234");

    if (!m_database.open()) {
        qCritical() << "Database connection failed:" << m_database.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully!";

    // initializeDefaultUser();

    return true;
}

bool DatabaseManager::executeQuery(QSqlQuery &query)
{
    if (!query.exec()) {
        qWarning() << "Query execution failed:" << query.lastError().text();
        qWarning() << "Query:" << query.lastQuery();
        return false;
    }
    return true;
}

QVariantList DatabaseManager::getAllTasks(int userId)
{
    QVariantList tasks;

    QSqlQuery query(m_database);
    query.prepare(R"(
        SELECT
            t.task_id, t.title, t.description, t.created_at,
            t.due_at, t.completed_at, t.status_id, t.priority,
            ts.status_name,
            ARRAY_AGG(tg.tag_id) FILTER (WHERE tg.tag_id IS NOT NULL) as tag_ids,
            ARRAY_AGG(tg.tag_name) FILTER (WHERE tg.tag_name IS NOT NULL) as tag_names,
            ARRAY_AGG(tg.color) FILTER (WHERE tg.color IS NOT NULL) as tag_colors
        FROM tasks t
        LEFT JOIN task_statuses ts ON t.status_id = ts.status_id
        LEFT JOIN task_tags tt ON t.task_id = tt.task_id
        LEFT JOIN tags tg ON tt.tag_id = tg.tag_id
        WHERE t.user_id = :userId
        GROUP BY t.task_id, ts.status_name
        ORDER BY t.created_at DESC
    )");

    query.bindValue(":userId", userId);

    if (!executeQuery(query)) {
        return tasks;
    }

    while (query.next()) {
        QVariantMap task;
        task["taskId"] = query.value("task_id").toInt();
        task["title"] = query.value("title").toString();
        task["description"] = query.value("description").toString();
        task["createdAt"] = query.value("created_at").toDateTime();
        task["dueAt"] = query.value("due_at").toDateTime();
        task["completedAt"] = query.value("completed_at").toDateTime();
        task["statusId"] = query.value("status_id").toInt();
        task["statusName"] = query.value("status_name").toString();
        task["priority"] = query.value("priority").toInt();

        // Обработка массивов тегов (PostgreSQL возвращает их как строку)
        QString tagIdsStr = query.value("tag_ids").toString();
        QString tagNamesStr = query.value("tag_names").toString();
        QString tagColorsStr = query.value("tag_colors").toString();

        QVariantList tagsList;
        if (!tagNamesStr.isEmpty() && tagNamesStr != "{}") {
            // Простая обработка массивов PostgreSQL
            tagNamesStr.remove("{").remove("}");
            tagColorsStr.remove("{").remove("}");
            QStringList names = tagNamesStr.split(",");
            QStringList colors = tagColorsStr.split(",");

            for (int i = 0; i < names.size(); ++i) {
                QVariantMap tag;
                tag["name"] = names[i];
                tag["color"] = (i < colors.size()) ? colors[i] : "#CCCCCC";
                tagsList.append(tag);
            }
        }
        task["tags"] = tagsList;

        tasks.append(task);
    }

    return tasks;
}

bool DatabaseManager::addTask(const QString &title, const QString &description,
                              const QString &dueDate, int priority,
                              const QVariantList &tagIds, int userId)
{
    m_database.transaction();

    QSqlQuery query(m_database);
    query.prepare(R"(
        INSERT INTO tasks (user_id, title, description, due_at, priority, status_id)
        VALUES (:userId, :title, :description, :dueAt, :priority, 1)
        RETURNING task_id
    )");

    query.bindValue(":userId", userId);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":dueAt", dueDate.isEmpty() ? QVariant() : QDateTime::fromString(dueDate, Qt::ISODate));
    query.bindValue(":priority", priority);

    if (!executeQuery(query)) {
        m_database.rollback();
        return false;
    }

    query.next();
    int taskId = query.value(0).toInt();

    // добавление тегов
    for (const QVariant &tagIdVar : tagIds) {
        QSqlQuery tagQuery(m_database);
        tagQuery.prepare("INSERT INTO task_tags (task_id, tag_id) VALUES (:taskId, :tagId)");
        tagQuery.bindValue(":taskId", taskId);
        tagQuery.bindValue(":tagId", tagIdVar.toInt());

        if (!executeQuery(tagQuery)) {
            m_database.rollback();
            return false;
        }
    }

    m_database.commit();
    return true;
}

bool DatabaseManager::updateTaskStatus(int taskId, int statusId)
{
    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE tasks
        SET status_id = :statusId,
            completed_at = CASE WHEN :statusId = 2 THEN NOW() ELSE NULL END
        WHERE task_id = :taskId
    )");

    query.bindValue(":statusId", statusId);
    query.bindValue(":taskId", taskId);

    return executeQuery(query);
}

bool DatabaseManager::deleteTask(int taskId)
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM tasks WHERE task_id = :taskId");
    query.bindValue(":taskId", taskId);

    return executeQuery(query);
}

bool DatabaseManager::updateTask(int taskId, const QString &title,
                                 const QString &description, const QString &dueDate,
                                 int priority)
{
    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE tasks
        SET title = :title,
            description = :description,
            due_at = :dueAt,
            priority = :priority
        WHERE task_id = :taskId
    )");

    query.bindValue(":taskId", taskId);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":dueAt", dueDate.isEmpty() ? QVariant() : QDateTime::fromString(dueDate, Qt::ISODate));
    query.bindValue(":priority", priority);

    return executeQuery(query);
}

QVariantList DatabaseManager::getAllTags()
{
    QVariantList tags;

    QSqlQuery query(m_database);
    query.prepare("SELECT tag_id, tag_name, color FROM tags ORDER BY tag_name");

    if (!executeQuery(query)) {
        return tags;
    }

    while (query.next()) {
        QVariantMap tag;
        tag["tagId"] = query.value("tag_id").toInt();
        tag["name"] = query.value("tag_name").toString();
        tag["color"] = query.value("color").toString();
        tags.append(tag);
    }

    return tags;
}

QVariantList DatabaseManager::getTaskTags(int taskId)
{
    QVariantList tags;

    QSqlQuery query(m_database);
    query.prepare(R"(
        SELECT t.tag_id, t.tag_name, t.color
        FROM tags t
        INNER JOIN task_tags tt ON t.tag_id = tt.tag_id
        WHERE tt.task_id = :taskId
    )");

    query.bindValue(":taskId", taskId);

    if (!executeQuery(query)) {
        return tags;
    }

    while (query.next()) {
        QVariantMap tag;
        tag["tagId"] = query.value("tag_id").toInt();
        tag["name"] = query.value("tag_name").toString();
        tag["color"] = query.value("color").toString();
        tags.append(tag);
    }

    return tags;
}

bool DatabaseManager::createUser(const QString &name, const QString &email)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO users (name, email) VALUES (:name, :email) RETURNING user_id");
    query.bindValue(":name", name);
    query.bindValue(":email", email);

    if (!executeQuery(query)) {
        return false;
    }

    query.next();
    m_currentUserId = query.value(0).toInt();
    return true;
}

bool DatabaseManager::updateTaskWithTags(int taskId, const QString &title,
                                         const QString &description, const QString &dueDate,
                                         int priority, const QVariantList &tagIds)
{
    m_database.transaction();

    QSqlQuery query(m_database);
    query.prepare(R"(
        UPDATE tasks
        SET title = :title,
            description = :description,
            due_at = :dueAt,
            priority = :priority
        WHERE task_id = :taskId
    )");

    query.bindValue(":taskId", taskId);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":dueAt", dueDate.isEmpty() ? QVariant() : QDateTime::fromString(dueDate, Qt::ISODate));
    query.bindValue(":priority", priority);

    if (!executeQuery(query)) {
        m_database.rollback();
        return false;
    }

    // удаляем старые связи с тегами
    QSqlQuery deleteTagsQuery(m_database);
    deleteTagsQuery.prepare("DELETE FROM task_tags WHERE task_id = :taskId");
    deleteTagsQuery.bindValue(":taskId", taskId);

    if (!executeQuery(deleteTagsQuery)) {
        m_database.rollback();
        return false;
    }

    // добавляем новые теги
    for (const QVariant &tagIdVar : tagIds) {
        QSqlQuery tagQuery(m_database);
        tagQuery.prepare("INSERT INTO task_tags (task_id, tag_id) VALUES (:taskId, :tagId)");
        tagQuery.bindValue(":taskId", taskId);
        tagQuery.bindValue(":tagId", tagIdVar.toInt());

        if (!executeQuery(tagQuery)) {
            m_database.rollback();
            return false;
        }
    }

    m_database.commit();
    return true;
}

int DatabaseManager::loginUser(const QString &name)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT user_id FROM users WHERE name = :name");
    query.bindValue(":name", name);

    if (executeQuery(query) && query.next()) {
        int userId = query.value(0).toInt();
        m_currentUserId = userId;
        qDebug() << "User logged in:" << name << "ID:" << userId;
        return userId;
    }

    return -1;
}

int DatabaseManager::registerUser(const QString &name, const QString &email)
{
    QSqlQuery query(m_database);

    // проверка есть ли такой пользователь
    query.prepare("SELECT user_id FROM users WHERE name = :name");
    query.bindValue(":name", name);

    if (executeQuery(query) && query.next()) {
        qWarning() << "User with this name already exists";
        return -1;
    }

    // есть ли с таким email
    if (!email.isEmpty()) {
        query.prepare("SELECT user_id FROM users WHERE email = :email");
        query.bindValue(":email", email);

        if (executeQuery(query) && query.next()) {
            qWarning() << "User with this email already exists";
            return -1;
        }
    }

    // создаем нового пользователя
    query.prepare(R"(
        INSERT INTO users (name, email, created_at)
        VALUES (:name, :email, NOW())
        RETURNING user_id
    )");

    query.bindValue(":name", name);
    query.bindValue(":email", email);

    if (!executeQuery(query)) {
        return -1;
    }

    if (query.next()) {
        int userId = query.value(0).toInt();
        m_currentUserId = userId;
        qDebug() << "User registered:" << name << "ID:" << userId << "Email:" << email;
        return userId;
    }

    return -1;
}

QString DatabaseManager::getCurrentUserName()
{
    QSqlQuery query(m_database);
    query.prepare("SELECT name FROM users WHERE user_id = :userId");
    query.bindValue(":userId", m_currentUserId);

    if (executeQuery(query) && query.next()) {
        return query.value(0).toString();
    }

    return "Пользователь";
}
