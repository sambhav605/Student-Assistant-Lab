#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <sqlite3.h>

struct TaskStats {
    int totalTasks;
    int completedTasks;
    int pendingTasks;
    int highPriorityTasks;
    int mediumPriorityTasks;
    int lowPriorityTasks;
};
class TodoList {
public:
    TodoList(sqlite3 *db, int userId);
    void addTask(const std::string &task);
    void removeTask(int id);
    void markTaskDone(int id);
    void viewTasks();
    // Statistics and analytics
    TaskStats getStatistics();
    void displayStatistics();
    bool exportToCSV(const std::string& filename);
private:
    sqlite3 *db;
    int userId;
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif