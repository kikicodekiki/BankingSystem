#pragma once
#include "System.h"
#include "Application.h"
#include <iostream>
#include <sstream>



class Run {
public:
    static void start() {
        Application& app = Application::getInstance();
        std::string line;

        while (std::getline(std::cin, line)) {
            std::istringstream iss(line);
            std::string command;
            iss >> command;

            if (command == "create_bank") {
                std::string bankName;
                iss >> bankName;
                app.createBank(bankName.c_str());
            } else if (command == "signup") {
                signup();
            } else if (command == "login") {
                login();
            } else if (command == "exit") {
                app.logout();
            } else {
                Vector<MyString> args;
                std::string arg;
                while (iss >> arg) {
                    args.pushBack(arg.c_str());
                }
                System::executeCommand(command.c_str(), args);
            }
        }
    }

private:
    static void signup() {
        Application& app = Application::getInstance();
        std::string firstName, surname, egn, password, bankName, address;
        int age;
        UserType role;

        std::cout << "Name: ";
        std::cin >> firstName;
        std::cout << "Surname: ";
        std::cin >> surname;
        std::cout << "EGN: ";
        std::cin >> egn;
        std::cout << "Age: ";
        std::cin >> age;
        std::cout << "Role: ";
        std::string roleStr;
        std::cin >> roleStr;
        if (roleStr == "Client") {
            role = UserType::Client;
            std::cout << "Address: ";
            std::cin >> address;
        } else if (roleStr == "Employee") {
            role = UserType::Employee;
            std::cout << "Bank associated: ";
            std::cin >> bankName;
        } else if (roleStr == "Third-party employee") {
            role = UserType::ExternalEmployee;
        }
        std::cout << "Password: ";
        std::cin >> password;

        app.signup(role, firstName.c_str(), surname.c_str(), egn.c_str(), age, bankName.c_str(), address.c_str());
    }

    static void login() {
        Application& app = Application::getInstance();
        std::string username, password;

        std::cout << "Name: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        app.login(username.c_str(), password.c_str());
    }
};
