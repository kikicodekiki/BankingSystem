#include "Application.h"
#include "BankEmployee.h"
#include "Client.h"
#include "Bank.h"
#include "UserManagement.h"
#include "ExternalEmployee.h"
#include "User.h"
#include <iostream>


Application& Application::getInstance() {
    static Application app;
    return app;
}

void Application::createBank(const MyString& bankName) {
    if (findBank(bankName) == nullptr) {
        banks.pushBack(Bank(bankName));
        std::cout << "Bank " << bankName.c_str() << " created.\n";
    } else {
        std::cout << "Bank already exists.\n";
    }
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

const Bank* Application::findBank(const MyString& bankName) const {
    for (size_t i = 0; i < banks.getSize(); i++) {
        if (banks[i].getName() == bankName) {
            return &banks[i];
        }
    }
    return nullptr;
}

Client* Application::findClientById(int clientId) {
    for (size_t i = 0; i < clients.getSize(); i++) {
        if(clients[i]->getId() == clientId) {
            return clients[i].get();
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
        std::cout << "Bank not found.\n";
        return;
    }

    BankEmployee* leastBusyEmployee = assignTaskToLeastBusyEmployee(TaskType::OPEN, clientId, "Open account request");
    if (leastBusyEmployee) {
        std::cout << "Task assigned to employee.\n";
    } else {
        std::cout << "No employees available to handle the task.\n";
    }
}
void Application::closeAccount(const MyString& bankName, const MyString& accountNumber, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        std::cout << "Bank not found.\n";
        return;
    }

    BankEmployee* leastBusyEmployee = assignTaskToLeastBusyEmployee(TaskType::CLOSE, clientId, "Close account request");
    if (leastBusyEmployee) {
        std::cout << "Task assigned to employee.\n";
    } else {
        std::cout << "No employees available to handle the task.\n";
    }
}
BankEmployee* Application::getLeastBusyEmployee(const MyString& bankName) {

    Bank* bank = findBank(bankName);
    BankEmployee* myEmployee = dynamic_cast<BankEmployee*>(bank->getLeastBusyEmployee());
    return myEmployee;

}

void Application::changeAccountBank(const MyString& newBankName, const MyString& currBank, const MyString& accNum, int clientId) {
    Bank* oldBank = findBank(currBank);
    Bank* newBank = findBank(newBankName);

    if (!oldBank || !newBank) {
        std::cout << "One or both banks not found.\n";
        return;
    }

    BankEmployee* leastBusyEmployee = assignTaskToLeastBusyEmployee(TaskType::CHANGE, clientId, "Change account bank request");
    if (leastBusyEmployee) {
        // Perform the actual account transfer
        if (oldBank->transferAccount(accNum, newBankName, accNum)) {
            Client* client = findClientById(clientId);
            if (client) {
                client->addAccount(accNum);
                client->addMessage("Account transferred to " + newBankName + " successfully.");
                std::cout << "Account transferred successfully.\n";
            }
        } else {
            std::cout << "Account transfer failed.\n";
        }
    } else {
        std::cout << "No employees available to handle the task.\n";
    }
}

double Application::checkAccountBalance(const MyString& bankName, const MyString& accountNumber, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        std::cout << "Bank not found.\n";
        return -1;
    }
    return bank->checkBalance(accountNumber);
}

void Application::list(const MyString& bankName, int clientId) {
    Client* client = findClientById(clientId);
    if (client) {
        client->list(bankName);
    }
}

void Application::listAccounts(const MyString& bankName, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        std::cout << "Bank not found.\n";
        return;
    }
    Vector<MyString> accounts = bank->listAllAccounts(clientId);
    for (size_t i = 0; i < accounts.getSize(); ++i) {
        std::cout << accounts[i].c_str() << "\n";
    }
}

void Application::sendCheck(double sum, const MyString& verificationCode, const MyString& egn) {
    Polymorphic_Ptr<User> user = userManager.findUser(egn);
    if (!user) {
        std::cout << "User not found.\n";
        return;
    }

    Client* client = dynamic_cast<Client*>(user.get());
    if (!client) {
        std::cout << "User is not a client.\n";
        return;
    }

    MyString str = doubleToString(sum, 5);
    client->addMessage("Check received: $" + str + " with code " + verificationCode.c_str());
}

void Application::approveTask(const MyString& taskId, int employeeId) {
    for (size_t i = 0; i < employees.getSize(); ++i) {

        if (employees[i]->getId() == employeeId) {

            for (size_t j = 0; j < employees[i]->getTaskCount(); ++j) {

                MyString str = toString(employees[i]->getTasks()[j].taskId);

                if (taskId == str) {
                    employees[i]->getTasks()[j].approve();
                    return;
                }
            }
        }
    }
    std::cout << "Task or employee not found.\n";
}

void Application::disapproveTask(const MyString& taskId, const MyString& message, int employeeId) {
    for (size_t i = 0; i < employees.getSize(); ++i) {

        if (employees[i]->getId() == employeeId) {

            for (size_t j = 0; j < employees[i]->getTaskCount(); ++j) {

                MyString str = toString(employees[i]->getTasks()[j].taskId);

                if (taskId == str) {
                    employees[i]->getTasks()[j].reject(message);
                    return;
                }
            }
        }
    }
    std::cout << "Task or employee not found.\n";
}

void Application::validateTask(const MyString& taskId, int employeeId) {
    for (size_t i = 0; i < employees.getSize(); ++i) {

        if (employees[i]->getId() == employeeId) {

            for (size_t j = 0; j < employees[i]->getTaskCount(); ++j) {

                MyString str = toString(employees[i]->getTasks()[j].taskId);

                if (str == taskId) {

                    if (employees[i]->validate(taskId)) {
                        std::cout << "Task validated successfully.\n";

                    } else {
                        std::cout << "Task validation failed.\n";
                    }
                    return;
                }
            }
        }
    }
    std::cout << "Task or employee not found.\n";
}

void Application::redeemCheck(const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        std::cout << "Bank not found.\n";
        return;
    }
    double amount = bank->redeemCheck(accountNumber, verificationCode);
    if (amount < 0) {
        std::cout << "Invalid check or verification code.\n";
    } else {
        std::cout << "Check redeemed successfully. Amount: $" << amount << "\n";
    }
}

void Application::signup(const UserType& userType, const MyString& firstName,
                         const MyString& surname, const MyString& EGN, const MyString& password,
                         size_t age, const MyString& bankName, const MyString& address) {
    switch (userType) {
        case UserType::Client: {
            if (banks.empty())
                userManager.addUser(Polymorphic_Ptr<User>(new Client(firstName, surname, EGN,
                                                                     age,password, address)));
            break;
        }
        case UserType::Employee:
        {
            Bank* bank = findBank(bankName);
            if (!bank) {
                std::cout << "Bank not found.\n";
                return;
            }
            userManager.addUser(Polymorphic_Ptr<User>(new BankEmployee(firstName, surname, EGN, age, address, bank)));
        }
            break;
        case UserType::ExternalEmployee:
            userManager.addUser(Polymorphic_Ptr<User>(new ExternalEmployee(firstName, surname, EGN, age, address)));
            break;
        default:
            std::cout << "Invalid user type.\n";
            break;
    }
}

void Application::login(const MyString& username, const MyString& password) {
    for (size_t i = 0; i < userManager.getUsers().getSize(); i++) {
        if (userManager.getUsers()[i]->authenticate(username, password)) {
            logged = userManager.getUsers()[i].get();
            if (dynamic_cast<Client*>(logged)) {
                type = UserType::Client;
            } else if (dynamic_cast<BankEmployee*>(logged)) {
                type = UserType::Employee;
            } else if (dynamic_cast<ExternalEmployee*>(logged)) {
                type = UserType::ExternalEmployee;
            } else {
                type = UserType::DEFAULT;
            }
            std::cout << "Login successful.\n";
            return;
        }
    }
    std::cout << "Invalid username or password.\n";
}

BankEmployee* Application::assignTaskToLeastBusyEmployee(TaskType taskType, int clientId, const MyString& taskDetails) {
    BankEmployee* leastBusyEmployee = nullptr;
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (!leastBusyEmployee || employees[i]->getTaskCount() < leastBusyEmployee->getTaskCount()) {
            leastBusyEmployee = employees[i].get();
        }
    }

    if (leastBusyEmployee) {
        Task task(taskType, findClientById(clientId), "", taskDetails, static_cast<unsigned>(leastBusyEmployee->getTaskCount() + 1));
        leastBusyEmployee->addTask(task);
    }

    return leastBusyEmployee;
}
