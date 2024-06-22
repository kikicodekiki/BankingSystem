#include "Application.h"
#include <iostream>

Application& Application::getInstance() {
    static Application app;
    return app;
}

void Application::createBank(const MyString& bankName) {
    banks.pushBack(Bank(bankName));
    std::cout << "Bank " << bankName.c_str() << " created.\n";
}

void Application::logout() {
    if (logged) {
        std::cout << logged->getFullName().c_str() << " logged out.\n";
        logged = nullptr;
        type = UserType::DEFAULT;
    } else {
        std::cout << "No user is currently logged in.\n";
    }
}

const User* Application::getLoggedUser() const {
    return logged;
}

User* Application::getLoggedUser() {
    return logged;
}

UserType Application::getLoggedType() const {
    return type;
}

Bank* Application::findBank(const MyString& bankName) {
    for (size_t i = 0; i < banks.getSize(); i++) {
        if (banks[i].getName() == bankName) {
            return &banks[i];
        }
    }
    return nullptr;
}

Client* Application::findClientById(int clientId) {
    for (size_t i = 0; i < clients.getSize(); i++) {
        if(clients[i].getId() == clientId) {
            return &clients[i];
        }
    }
    return nullptr;
}

void Application::addMessageToClient(int clientId, const MyString &message) {
    Client* client = findClientById(clientId);
    if (client) {
        client->addMessage(message);
    }
}

void Application::openAccount(const MyString& bankName, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        //throw std::runtime_error("Bank not found.\n")
        std::cout << "Bank not found.\n";
        return;
    }

    // Find the least busy employee
    BankEmployee* leastBusyEmployee = nullptr;
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (!leastBusyEmployee || employees[i].getTaskCount() < leastBusyEmployee->getTaskCount()) {
            leastBusyEmployee = &employees[i];
        }
    }

    if (leastBusyEmployee) {
        Task task(TaskType::OPEN, findClientById(clientId), "Open account request",
                  static_cast<unsigned>(leastBusyEmployee->getTaskCount() + 1));
        leastBusyEmployee->addTask(task);
        std::cout << "Task assigned to employee.\n";
    } else {
        //throw std::runtime_error("No employees available to handle the task.\n");
        std::cout << "No employees available to handle the task.\n";
    }
}

//tuk da opravq abstrakciqta!!!!!!

void Application::closeAccount(const MyString& bankName, const MyString& accountNumber, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        std::cout << "Bank not found.\n";
        return;
    }

    // Find the least busy employee
    BankEmployee* leastBusyEmployee = nullptr;
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (!leastBusyEmployee || employees[i].getTaskCount() < leastBusyEmployee->getTaskCount()) {
            leastBusyEmployee = &employees[i];
        }
    }

    if (leastBusyEmployee) {
        Task task(TaskType::CLOSE, findClientById(clientId), "Close account request", static_cast<unsigned>(leastBusyEmployee->getTaskCount() + 1));
        leastBusyEmployee->addTask(task);
        std::cout << "Task assigned to employee.\n";
    } else {
        std::cout << "No employees available to handle the task.\n";
    }
}

void Application::changeAccountBank(const MyString& newBankName, const MyString& currBank, const MyString& accNum, int clientId) {
    Bank* oldBank = findBank(currBank);
    Bank* newBank = findBank(newBankName);

    if (!oldBank || !newBank) {
        std::cout << "One or both banks not found.\n";
        return;
    }

    //otdelna funciq!!!!!!!!!!!!!
    // Find the least busy employee
    BankEmployee* leastBusyEmployee = nullptr;
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (!leastBusyEmployee || employees[i].getTaskCount() < leastBusyEmployee->getTaskCount()) {
            leastBusyEmployee = &employees[i];
        }
    }

    //otdelna funckiq!!!!!!
    if (leastBusyEmployee) {
        Task task(TaskType::CHANGE, findClientById(clientId), "Change account bank request", static_cast<unsigned>(leastBusyEmployee->getTaskCount() + 1));
        leastBusyEmployee->addTask(task);
        std::cout << "Task assigned to employee.\n";
    } else {
        std::cout << "No employees available to handle the task.\n";
    }
}
