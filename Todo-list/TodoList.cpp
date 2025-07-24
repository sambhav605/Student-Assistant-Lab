#include "TodoList.h"
#include<iostream>
#include <fstream>
#include <sstream> // to do the string operations 
#include <iomanip>
#include <ctime>

/**
 * @brief Constructs a Task object with an ID and description.
 * 
 * Initializes the task with the given ID and description, and
 * sets the timestamp to the current date and time.
 * 
 * @param taskId The unique identifier for the task.
 * @param desc The description text of the task.
 */
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

/**
 * @brief Constructs a TaskManager object with a given filename.
 * 
 * Initializes the task manager with the specified filename for
 * loading and saving tasks. Sets the initial task ID counter to 1.
 * 
 * @param file The filename to be used for task persistence.
 *TaskManager:: TaskManager(const std::string& file)
{
    filename = file;
    nextId = 1;
}

/**
 * @brief Retrieves the current date and time as a formatted string.
 * 
 * Gets the system's current time and converts it to a human-readable
 * timestamp string. The trailing newline character from ctime() output
 * is removed before returning.
 * 
 * @return std::string The current timestamp in a readable format.
 */std::string TaskManager::getCurrentTimestamp(){
    std::time_t now =  time(0);
    char* timeStr = std::ctime(&now);
    std::string result = std::string(timeStr);
    result.pop_back();
    return result;
}

/**
 * @brief Displays the main menu for the TODO List Manager.
 * 
 * This function prints the main options that the user can choose from,
 * including adding a task, viewing tasks, deleting a task, or exiting the program.
 * It does not take any parameters and does not return a value.
 */
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

/**
 * @brief Adds a new task to the task list.
 * 
 * Creates a new Task object with a unique ID and the provided description,
 * adds it to the task list, and then saves the updated list to a file.
 * Also displays confirmation and timestamp of the added task.
 * 
 * @param description The description of the task to be added.
 */
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

/**
 * @brief Loads tasks from a file into the task list.
 * 
 * Reads each line from the specified file, parses task information (ID, 
 * description, and timestamp), and reconstructs the tasks. Updates the
 * task list and sets the next available task ID based on the highest 
 * loaded ID.
 * 
 * If the file does not exist or is empty, it initializes the task list
 * as empty and prints a message to the console.
 */
void TaskManager::loadFromFile()
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout<<" No existing task file found. Starting with empty list." << std::endl;
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

    std::cout << " Loaded " << tasks.size() << " tasks from file." << std::endl;
}

/**
 * @brief Saves all current tasks to a file.
 * 
 * Writes each task's ID, description, and timestamp to the specified file,
 * using a pipe (`|`) as a delimiter between fields. Overwrites any existing
 * file content with the updated task list.
 * 
 * If the file cannot be opened, an error message is displayed.
 */void TaskManager::saveToFile()
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

/**
 * @brief Checks if the task list is empty.
 * 
 * @return true If there are no tasks in the list.
 * @return false If there is at least one task.
 */ 
bool TaskManager::isEmpty() {
    return tasks.empty();
}

/**
 * @brief Returns the total number of tasks currently stored.
 * 
 * @return int The count of tasks in the task list.
 */
int TaskManager:: getTaskCount()
{
    // here we used the explicit type conversion to convert from unsigned int to regular int
    return static_cast<int>(tasks.size());
}

/**
 * @brief The main program loop that runs the TODO List Manager.
 * 
 * Loads existing tasks from file and repeatedly displays the main menu,
 * processes user input for adding, viewing, deleting tasks, or exiting.
 * Handles input validation and ensures tasks are saved before exit.
 */void TaskManager::run()
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
