#include <iostream>
#include <sqlite3.h>
#include "studentValidation/UserAuth.h"
#include "Todo-list/TodoList.h"
#include<string>

const std::string RESET   = "\033[0m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string RED     = "\033[31m";

int main() {
    sqlite3 *db;
    if (sqlite3_open("todo.db", &db)) {
        std::cerr << "Can't open database\n";
        return 1;
    }

    UserAuth auth(db);
    int userId = -1;
    while (userId == -1) {
        int choice;
        std::cout << "\n1. Login\n2. Register\nChoose: ";
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            std::string username;
            std::string password;
            std::cout<<"enter the username and password";
            std::cin>>username>>password;
            userId = auth.loginUser(username,password);
        } else if (choice == 2) {
            std::string username;
            std::string password;
            std::cout<<"enter the username and password";
            std::cin>>username>>password;
            auth.registerUser(username,password);
        } else {
            std::cout << "Invalid choice\n";
        }
    }

    TodoList todo(db, userId);

    int choice;
    while (true) {
        std::cout << YELLOW << "\n--- TODO LIST ---\n";
        std::cout << GREEN <<"1. Add Task\n";
        std::cout << RED << "2. Remove Task\n";
        std::cout << "3. View Tasks\n";
        std::cout << "4. Mark Task Done\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string task;
            std::cout << "Enter task: ";
            std::getline(std::cin, task);
            todo.addTask(task);
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter task ID to remove: ";
            std::cin >> id;
            std::cin.ignore();
            todo.removeTask(id);
        }
        else if (choice == 3) {
            todo.viewTasks();
        }
        else if (choice == 4) {
            int id;
            std::cout << "Enter task ID to mark done: ";
            std::cin >> id;
            std::cin.ignore();
            todo.markTaskDone(id);
        }
        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "Invalid choice\n";
        }
    }

    sqlite3_close(db);
    return 0;
}
