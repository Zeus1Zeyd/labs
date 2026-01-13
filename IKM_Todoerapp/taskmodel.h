#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QObject>
#include <QVariantList>
#include "databasemanager.h"

class TaskModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList tasks READ tasks NOTIFY tasksChanged)
    Q_PROPERTY(QVariantList tags READ tags NOTIFY tagsChanged)
    Q_PROPERTY(QString currentUserName READ currentUserName NOTIFY currentUserNameChanged)

public:
    explicit TaskModel(DatabaseManager *dbManager, QObject *parent = nullptr);

    QVariantList tasks() const { return m_tasks; }
    QVariantList tags() const { return m_tags; }
    QString currentUserName() const;

    Q_INVOKABLE void refreshTasks();
    Q_INVOKABLE void refreshTags();
    Q_INVOKABLE bool addTask(const QString &title, const QString &description,
                             const QString &dueDate, int priority, const QVariantList &tagIds);
    Q_INVOKABLE bool completeTask(int taskId);
    Q_INVOKABLE bool uncompleteTask(int taskId);
    Q_INVOKABLE bool deleteTask(int taskId);
    Q_INVOKABLE bool updateTask(int taskId, const QString &title,
                                const QString &description, const QString &dueDate,
                                int priority, const QVariantList &tagIds);
    Q_INVOKABLE QVariantList filterTasksByStatus(const QString &status);
    Q_INVOKABLE QVariantMap getTaskById(int taskId);
    Q_INVOKABLE void setCurrentUser(int userId);

signals:
    void tasksChanged();
    void tagsChanged();
    void currentUserNameChanged();

private:
    DatabaseManager *m_dbManager;
    QVariantList m_tasks;
    QVariantList m_tags;
};

#endif
