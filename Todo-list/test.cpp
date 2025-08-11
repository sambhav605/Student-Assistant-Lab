#include <iostream>
#include <sqlite3.h>
#include "../studentValidation/UserAuth.h"
#include "TodoList.h"
#include<string>
int main() {
    sqlite3 *db;
    if (sqlite3_open("student.db", &db)) {
        std::cerr << "Can't open database\n";
        return 1;
    }
    std::string password;
    std::string username;
    UserAuth auth(db);
    int userId = -1;
    while (userId == -1) {
        int choice;
        std::cout << "\n1. Login\n2. Register\nChoose: ";
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            std::cout<<"enter username and password";
            std::cin>>username>>password;
            userId = auth.loginUser(username,password);
        } else if (choice == 2) {
            std::cout<<"enter username and password";
            std::cin>>username>>password;
            auth.registerUser(username,password);
        }
    }

    TodoList todo(db, userId);
    int choice;
    while (true) {
        std::cout << "\n--- TODO LIST ---\n";
        std::cout << "1. Add Work\n";
        std::cout << "2. Remove Work\n";
        std::cout << "3. View Work\n";
        std::cout << "4. Exit\n";
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
            todo.removeTask(id);
        }
        else if (choice == 3) {
            todo.viewTasks();
        }
        else if (choice == 4) {
            break;
        }
    }

    sqlite3_close(db);
    return 0;
}
