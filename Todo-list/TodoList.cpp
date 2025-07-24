#include "TodoList.h"
#include<iostream>
#include <fstream>
#include <sstream> // to do the string operations 
#include <iomanip>
#include <ctime>

// Task Constructor Implementation
Task :: Task(int taskId, const std::string& desc)
{
    id = taskId;
    description = desc;

    // Get the current timestamp 
    std:: time_t now = time(0); // Get current time as seconds
    char* timeStr = ctime(&now);
    timestamp = std::string(timeStr);
    timestamp.pop_back();
}

// TaskManager Constructor 
TaskManager:: TaskManager(const std::string& file)
{
    filename = file;
    nextId = 1;
}

// functions to get the current timeStamp 
std::string TaskManager::getCurrentTimestamp(){
    std::time_t now =  time(0);
    char* timeStr = std::ctime(&now);
    std::string result = std::string(timeStr);
    result.pop_back();
    return result;
}

// Display the main menu 
void TaskManager::displayMenu()
{
    std::cout << "\n==================================" << std::endl;
    std::cout << "       TODO LIST MANAGER" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "1. Add New Task" << std::endl;
    std::cout << "2. View All Tasks" << std::endl;
    std::cout << "3. Delete Task" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "==================================" << std::endl;
}

// Add a new Task 
void TaskManager::addTask(const std::string& description)
{
    Task newTask(nextId, description);
    tasks.push_back(newTask);
    nextId++;

    std::cout << "✓ Task added successfully!" << std::endl;
    std::cout << "Task: " << description << std::endl;
    std::cout << "Added at: " << newTask.timestamp << std::endl;

    saveToFile(); // Auto saves after adding
}

// Load Tasks from file 
void TaskManager::loadFromFile()
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout<<"📁 No existing task file found. Starting with empty list." << std::endl;
        return ;
    }
    std::string line;
    int maxId = 0;

    while(std::getline(file,line))
    {
        if(line.empty())
            continue;
        
        std::stringstream ss(line);//created stringstream object to breakdown the string
        std::string idStr, desc , timestamp;
        if (std::getline(ss, idStr, '|') && 
            std::getline(ss, desc, '|') && 
            std::getline(ss, timestamp))
        {
            int id = std::stoi(idStr); // converts the string ID to an integer
            
            // Create task object manually 
            Task task(id,desc);
            task.timestamp = timestamp; // override with saved timestamp 

            tasks.push_back(task);

            // Track the highest ID for nextId
            if( id>maxId)
            {
                maxId = id;
            }
            
        }
    }
    nextId = maxId + 1;
    file.close();

    std::cout << "📂 Loaded " << tasks.size() << " tasks from file." << std::endl;
}

//Save tasks to file 
void TaskManager::saveToFile()
{
    std::ofstream file(filename);
    if(!file.is_open())
    {
        std::cout << " Error: Could not save tasks to file!" << std::endl;
        return;
    }
    
    // here we used const auto& to avoid copy between the elements of the vector
    for(const auto& task : tasks)
    {
        file << task.id << "|" << task.description << "|" << task.timestamp<< std::endl;
    }
    file.close();
}

// to view tasks 
void TaskManager::viewTasks(){
    std::cout<<"this is view tasks function";
}
void TaskManager::deleteTask(int taskNumber)
{
    std::cout<<"this is the simple delete task function";
}
//Check if task list is empty 
bool TaskManager::isEmpty() {
    return tasks.empty();
}
// Get total number of tasks 
int TaskManager:: getTaskCount()
{
    // here we used the explicit type conversion to convert from unsigned int to regular int
    return static_cast<int>(tasks.size());
}

// Main program loop - THE HEART OF THE PROGRAM!
void TaskManager::run()
{
    std::cout << " Welcome to TODO List Manager!" << std::endl;
    std::cout << "Loading your tasks..." << std::endl;
    
    loadFromFile();

    int choice;
    std::string taskDescription;
    int taskNum;

    do{
        displayMenu();
        std::cout<<"Enter your choice (1-4)";
        std::cin>>choice;

        switch(choice)
        {
            case 1: // Add Task
                std::cout << "\n ADD NEW TASK" << std::endl;
                std::cout << "Enter task description: ";
                std::cin.ignore(); // Clear the newline from previous input
                std::getline(std::cin, taskDescription);
                if (!taskDescription.empty()) {
                    addTask(taskDescription);
                } else {
                    std::cout << " Task description cannot be empty!" << std::endl;
                }
                break;
            case 2: // View Tasks
                viewTasks();
                break;
            case 3: // Delete Task
                std::cout << "\n  DELETE TASK" << std::endl;
                viewTasks(); // Show current tasks first
                
                if (!isEmpty()) {
                    std::cout << "Enter task number to delete: ";
                    std::cin >> taskNum;
                    deleteTask(taskNum);
                }
                break;
            case 4: // Exit
                std::cout << "\n Saving your tasks..." << std::endl;
                saveToFile();
                std::cout << " Thank you for using TODO List Manager!" << std::endl;
                std::cout << "Your tasks have been saved to: " << filename << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please select 1-4." << std::endl;
                break;
        }
        // Pause before showimg the menu again 
        if(choice != 4)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }while( choice!=4);
}
