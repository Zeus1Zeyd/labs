#include "taskmodel.h"

TaskModel::TaskModel(DatabaseManager *dbManager, QObject *parent)
    : QObject(parent)
    , m_dbManager(dbManager)
{
    // НЕ загружаем задачи при создании, дождемся входа пользователя
    refreshTags();
}

QString TaskModel::currentUserName() const
{
    return m_dbManager->getCurrentUserName();
}

void TaskModel::setCurrentUser(int userId)
{
    m_dbManager->setCurrentUserId(userId);
    refreshTasks();
    emit currentUserNameChanged();
}

void TaskModel::refreshTasks()
{
    m_tasks = m_dbManager->getAllTasks(m_dbManager->getCurrentUserId());
    emit tasksChanged();
}

void TaskModel::refreshTags()
{
    m_tags = m_dbManager->getAllTags();
    emit tagsChanged();
}

bool TaskModel::addTask(const QString &title, const QString &description,
                        const QString &dueDate, int priority, const QVariantList &tagIds)
{
    bool success = m_dbManager->addTask(title, description, dueDate, priority, tagIds,
                                        m_dbManager->getCurrentUserId());
    if (success) {
        refreshTasks();
    }
    return success;
}

bool TaskModel::completeTask(int taskId)
{
    bool success = m_dbManager->updateTaskStatus(taskId, 2);
    if (success) {
        refreshTasks();
    }
    return success;
}

bool TaskModel::uncompleteTask(int taskId)
{
    bool success = m_dbManager->updateTaskStatus(taskId, 1);
    if (success) {
        refreshTasks();
    }
    return success;
}

bool TaskModel::deleteTask(int taskId)
{
    bool success = m_dbManager->deleteTask(taskId);
    if (success) {
        refreshTasks();
    }
    return success;
}

bool TaskModel::updateTask(int taskId, const QString &title,
                           const QString &description, const QString &dueDate,
                           int priority, const QVariantList &tagIds)
{
    bool success = m_dbManager->updateTaskWithTags(taskId, title, description, dueDate, priority, tagIds);
    if (success) {
        refreshTasks();
    }
    return success;
}

QVariantList TaskModel::filterTasksByStatus(const QString &status)
{
    QVariantList filtered;

    for (const QVariant &taskVar : m_tasks) {
        QVariantMap task = taskVar.toMap();
        if (task["statusName"].toString() == status) {
            filtered.append(task);
        }
    }

    return filtered;
}

QVariantMap TaskModel::getTaskById(int taskId)
{
    for (const QVariant &taskVar : m_tasks) {
        QVariantMap task = taskVar.toMap();
        if (task["taskId"].toInt() == taskId) {
            return task;
        }
    }
    return QVariantMap();
}
