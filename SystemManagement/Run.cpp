#include "Run.h"
#include "Application.h"
#include <iostream>

void Run::run() {
    std::cout << "Welcome to the Banking System!\n";
    while (true) {
        std::cout << "Enter a command (type 'help' for a list of commands): ";
        MyString command;
        std::cin >> command;

        if (command == "exit") {
            break;
        } else if (command == "create_bank") {
            MyString bankName;
            std::cin >> bankName;
            createBank(bankName);
        } else if (command == "signup") {
            signup();
        } else if (command == "login") {
            login();
        } else {
            executeCommand(command);
        }
    }
}

void Run::createBank(const MyString& name) {
    Application::getInstance().createBank(name);
}

void Run::signup() {
    UserType userType;
    MyString firstName, surname, egn, bankName, address, password;
    unsigned age;

    std::cout << "Name: ";
    std::cin >> firstName;
    std::cout << "Surname: ";
    std::cin >> surname;
    std::cout << "EGN: ";
    std::cin >> egn;
    std::cout << "Age: ";
    std::cin >> age;
    std::cout << "Role (Client, Employee, Third-party): ";
    MyString role;
    std::cin >> role;

    if (role == "Client") {
        userType = UserType::Client;
    } else if (role == "Employee") {
        userType = UserType::Employee;
        std::cout << "Bank associated: ";
        std::cin >> bankName;
    } else if (role == "Third-party") {
        userType = UserType::ExternalEmployee;
    } else {
        std::cout << "Invalid role!\n";
        return;
    }

    std::cout << "Password: ";
    std::cin >> password;

    Application::getInstance().signup(userType, firstName, surname, egn, password, age, bankName, address);
}

void Run::login() {
    MyString username, password;
    std::cout << "Name: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    Application::getInstance().login(username, password);
}

void Run::executeCommand(const MyString& command) {
    Vector<MyString> args;
    MyString arg;
    while (std::cin.peek() != '\n' && std::cin >> arg) {
        args.pushBack(arg);
    }
    Application::getInstance().executeCommand(command, args);
}

void Run::showHelp() const {
    std::cout << "Available commands:\n";
    std::cout << "create_bank <bank_name>\n";
    std::cout << "signup\n";
    std::cout << "login\n";
    std::cout << "exit\n";
    std::cout << "other commands like open, close, check_avl, redeem, etc.\n";
}
