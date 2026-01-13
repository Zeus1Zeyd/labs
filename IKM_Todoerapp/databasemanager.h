#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>
#include <QVariantList>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool connectToDatabase();

    // для работы с задачами
    Q_INVOKABLE QVariantList getAllTasks(int userId = 1);
    Q_INVOKABLE bool addTask(const QString &title, const QString &description,
                             const QString &dueDate, int priority,
                             const QVariantList &tagIds, int userId = 1);
    Q_INVOKABLE bool updateTaskStatus(int taskId, int statusId);
    Q_INVOKABLE bool deleteTask(int taskId);
    Q_INVOKABLE bool updateTask(int taskId, const QString &title,
                                const QString &description, const QString &dueDate,
                                int priority);
    Q_INVOKABLE bool updateTaskWithTags(int taskId, const QString &title,
                                        const QString &description, const QString &dueDate,
                                        int priority, const QVariantList &tagIds);

    // для работы с тегами
    Q_INVOKABLE QVariantList getAllTags();
    Q_INVOKABLE QVariantList getTaskTags(int taskId);

    // для работы с пользователями
    Q_INVOKABLE int getCurrentUserId() const { return m_currentUserId; }
    Q_INVOKABLE void setCurrentUserId(int userId) { m_currentUserId = userId; }
    Q_INVOKABLE bool createUser(const QString &name, const QString &email);
    Q_INVOKABLE int loginUser(const QString &name);
    Q_INVOKABLE int registerUser(const QString &name, const QString &email);
    Q_INVOKABLE QString getCurrentUserName();

private:
    QSqlDatabase m_database;
    int m_currentUserId;

    bool executeQuery(QSqlQuery &query);
    bool initializeDefaultUser();
};

#endif
