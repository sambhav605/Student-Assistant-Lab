#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <string>
#include <ctime>

// created the struct task to store the id , description and timestamp
struct Task{
    int id;
    std::string description;
    std::string timestamp;
    
    // created the constructor
    Task(int taskId, const std::string& desc);
};
class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;
    std:: string filename;

    std::string getCurrentTimestamp();
    void displayMenu();

public:
    // Constructor
    TaskManager(const std::string& file ="tasks.txt");

    //Core functionality
    void addTask(const std::string& description);
    void viewTasks();
    void deleteTask(int taskNumber);

    // File Operations
    void loadFromFile();
    void saveToFile();

    // function to run the program 
    void run();

    // Utility functions 
    int getTaskCount();
    bool isEmpty();
};
#endif