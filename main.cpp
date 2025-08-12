#include "studentValidation/UserAuth.h"
#include "assigments/Assignments.h"
#include "todo-list/TodoList.h"
#include "utility/utils.h"
#include "calender/calender.h"
#include "routine/Routine.h"
#include "PomodoroTimer/PomodoroTimer.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <set>
#include <string>
#include <limits>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

int main()
{
    sqlite3 *db;
    Utility utils;
    if (sqlite3_open("student.db", &db) != SQLITE_OK)
    {
        utils.printErrorMessage("Failed to open database");
        return 1;
    }

    UserAuth auth(db);
    Assignment assignment(db);
    Routine routine(db);

    utils.printWelcomeBanner();

    utils.printSectionHeader("USER REGISTRATION", "[+]");

    std::string username, password;
    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (auth.registerUser(username, password))
        utils.printSuccessMessage("Registration completed successfully!");
    else
        utils.printErrorMessage("Registration failed! Username might already exist.");

    std::cout << std::endl;

    utils.printSectionHeader("USER LOGIN", "[>]");

    utils.printInputPrompt("Enter Username: ", "[USER]");
    std::cin >> username;
    std::cin.ignore();

    password = auth.getHiddenPassword("[PASS] Enter Password: ");

    if (!auth.loginUser(username, password))
    {
        utils.printErrorMessage("Login failed! Invalid credentials.");
        sqlite3_close(db);
        return 1;
    }

    utils.printSuccessMessage("Welcome back, " + username + "! Login successful.");

    int user_id = auth.getUserId(username);
    if (user_id == -1)
    {
        utils.printErrorMessage("Failed to retrieve user information");
        sqlite3_close(db);
        return 1;
    }

    TodoList todo(db, user_id);

    int choice;
    do
    {
        std::cout << CYAN << "\n                MAIN MENU\n" << RESET;
        utils.printLine('-', 50, BLUE);
        std::cout << " 1. [+] Add New Assignment\n";
        std::cout << " 2. [*] View All Assignments\n";
        std::cout << " 3. [@] View Assignment Calendar\n";
        std::cout << " 4. [T] Todo List\n";
        std::cout << " 5. [R] Manage Routine\n";
        std::cout << " 6. [P] Pomodoro Timer\n";
        std::cout << " 7. [X] Exit System\n";
        utils.printLine('-', 50, BLUE);
        std::cout << " >> Enter your choice (1-7): ";

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            utils.printErrorMessage("Invalid input! Please enter a number between 1-7.");
            continue;
        }
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            utils.printSectionHeader("ADD NEW ASSIGNMENT", "[+]");
            std::string title, description, due_date;
            utils.printInputPrompt("Assignment Title: ", "[TITLE]");
            std::getline(std::cin, title);
            utils.printInputPrompt("Description: ", "[DESC]");
            std::getline(std::cin, description);
            utils.printInputPrompt("Due Date (YYYY-MM-DD): ", "[DATE]");
            std::getline(std::cin, due_date);

            if (assignment.addAssignment(user_id, title, description, due_date))
                utils.printSuccessMessage("Assignment added successfully!");
            else
                utils.printErrorMessage("Failed to add assignment.");
            break;
        }

        case 2:
        {
            utils.printSectionHeader("YOUR ASSIGNMENTS", "[*]");
            auto assignments = assignment.getAssignments(user_id);
            if (assignments.empty())
                utils.printInfoMessage("No assignments found.");
            else
            {
                std::cout << BLUE << "[COUNT] " << RESET << "Total: " << YELLOW << assignments.size() << RESET << "\n";
                utils.printLine('-', 60, BLUE);
                for (size_t i = 0; i < assignments.size(); i++)
                {
                    const auto &a = assignments[i];
                    std::cout << YELLOW << "Assignment #" << (i + 1) << RESET << "\n";
                    std::cout << CYAN << " ID: " << RESET << a.id << "\n";
                    std::cout << CYAN << " Title: " << RESET << a.title << "\n";
                    std::cout << CYAN << " Description: " << RESET << a.description << "\n";
                    std::cout << CYAN << " Due Date: " << RESET << a.due_date << "\n";
                    if (i < assignments.size() - 1)
                        utils.printLine('.', 40, BLUE);
                }
            }
            utils.printLine('=', 60, MAGENTA);
            break;
        }

        case 3:
        {
            auto assignments = assignment.getAssignments(user_id);
            printCalendarWithAssignments(assignments, utils);
            break;
        }

        case 4:
        {
            utils.clearScreen();
            int tChoice;
            while (true)
            {
                utils.printSectionHeader("TODO LIST", "[T]");
                std::cout << CYAN << "1. Add Work\n2. Remove Work\n3. View Work\n4. Mark Task Done\n5. Back to Main Menu" << RESET << "\n";
                std::cout << "Choose: ";
                std::cin >> tChoice;
                std::cin.ignore();

                if (tChoice == 1)
                {
                    std::string task;
                    std::cout << "Enter task: ";
                    std::getline(std::cin, task);
                    todo.addTask(task);
                }
                else if (tChoice == 2)
                {
                    int id;
                    std::cout << "Enter task ID to remove: ";
                    std::cin >> id;
                    todo.removeTask(id);
                }
                else if (tChoice == 3)
                {
                    todo.viewTasks();
                }
                else if (tChoice == 4)
                {
                    int id;
                    std::cout << "Enter task ID to mark done: ";
                    std::cin >> id;
                    std::cin.ignore();
                    todo.markTaskDone(id);
                }
                else if (tChoice == 5)
                    break;
            }
            break;
        }

        case 5:
        {
            utils.clearScreen();
            int rChoice;
            while (true)
            {
                utils.printSectionHeader("ROUTINE MANAGEMENT", "[R]");
                std::cout << CYAN << "1. Add Routine\n2. View Routines\n3. Update Routine\n4. Delete Routine\n5. Back" << RESET << "\n";
                std::cout << "Choose: ";
                std::cin >> rChoice;
                std::cin.ignore();

                if (rChoice == 1)
                {
                    std::string day, start, end, subject;
                    std::cout << "Day: "; std::getline(std::cin, day);
                    std::cout << "Start Time: "; std::getline(std::cin, start);
                    std::cout << "End Time: "; std::getline(std::cin, end);
                    std::cout << "Subject: "; std::getline(std::cin, subject);
                    if (routine.addRoutine(user_id, day, start, end, subject))
                        utils.printSuccessMessage("Routine added.");
                    else
                        utils.printErrorMessage("Failed to add routine.");
                }
                else if (rChoice == 2)
                {
                    auto routines = routine.getRoutines(user_id);
                    if (routines.empty())
                        utils.printInfoMessage("No routines found.");
                    else
                        for (const auto &r : routines)
                            std::cout << YELLOW << "ID: " << r.id << RESET << " | " << r.day << " | " << r.start_time << "-" << r.end_time << " | " << r.subject << "\n";
                }
                else if (rChoice == 3)
                {
                    int id;
                    std::string day, start, end, subject;
                    std::cout << "ID: "; std::cin >> id; std::cin.ignore();
                    std::cout << "New Day: "; std::getline(std::cin, day);
                    std::cout << "New Start: "; std::getline(std::cin, start);
                    std::cout << "New End: "; std::getline(std::cin, end);
                    std::cout << "New Subject: "; std::getline(std::cin, subject);
                    if (routine.updateRoutine(id, day, start, end, subject))
                        utils.printSuccessMessage("Updated.");
                    else
                        utils.printErrorMessage("Failed to update.");
                }
                else if (rChoice == 4)
                {
                    int id;
                    std::cout << "ID: "; std::cin >> id; std::cin.ignore();
                    if (routine.deleteRoutine(id))
                        utils.printSuccessMessage("Deleted.");
                    else
                        utils.printErrorMessage("Failed to delete.");
                }
                else if (rChoice == 5)
                    break;
            }
            break;
        }

        case 6:
        {
            utils.clearScreen();
            utils.printSectionHeader("POMODORO TIMER", "[P]");

            int workMin, breakMin;
            std::cout << "Enter work duration (minutes): ";
            std::cin >> workMin;
            std::cout << "Enter break duration (minutes): ";
            std::cin >> breakMin;
            std::cin.ignore();

            PomodoroTimer pomodoro(workMin, breakMin);

            pomodoro.setWorkStartCallback([&]() {
                utils.printInfoMessage("Work phase started! Stay focused.");
            });
            pomodoro.setBreakStartCallback([&]() {
                utils.printInfoMessage("Break time! Relax.");
            });
            pomodoro.setTimerUpdateCallback([&](int remaining) {
                int m = remaining / 60, s = remaining % 60;
                std::cout << "\rTime Left: " << m << "m " << s << "s   " << std::flush;
            });

            pomodoro.start();

            while (pomodoro.isRunning())
            {
                pomodoro.update();
            }

            break;
        }

        case 7:
        {
            utils.printSectionHeader("GOODBYE!", "[X]");
            utils.printSuccessMessage("Thank you for using the system!");
            break;
        }

        default:
            utils.printErrorMessage("Invalid choice! Please select 1-7.");
        }

        if (choice != 7)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            utils.clearScreen();
        }

    } while (choice != 7);

    sqlite3_close(db);
    return 0;
}
