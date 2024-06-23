#include "Application.h"
#include <iostream>
#include "DoubleToString.h"

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

bool Application::validate(const MyString& taskId) const {
    BankEmployee* leastBusyEmployee = getLeastBusyEmployee();
    return leastBusyEmployee -> validate(taskId);

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
        Task task(TaskType::CLOSE, findClientById(clientId), "Close account request",
                  static_cast<unsigned>(leastBusyEmployee->getTaskCount() + 1));
        leastBusyEmployee->addTask(task);
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

const BankEmployee* Application::getLeastBusyEmployee(const MyString& bankName) const {


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
        Task task(TaskType::CHANGE, findClientById(clientId), "Change account bank request",
                  static_cast<unsigned>(leastBusyEmployee->getTaskCount() + 1));
        leastBusyEmployee->addTask(task);
        std::cout << "Task assigned to employee.\n";
    } else {
        std::cout << "No employees available to handle the task.\n";
    }
}

double Application::checkAccountBalance (const MyString& bankName, const MyString& accountNumber, int clientId) {
    Bank* bank = findBank(bankName);
    return bank->checkBalance(accountNumber);
}

void Application::list(const MyString &bankName, int clientId) {
    Client* client = findClientById(clientId);

    client->list(bankName);
}

void Application::listAccounts(const MyString& bankName, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) {
        std::cout << "Bank not found.\n";
        return;
    }
    Vector<MyString> accounts = bank->listAccounts(clientId);
    for (size_t i = 0; i < accounts.getSize(); ++i) {
        std::cout << accounts[i].c_str() << "\n";
    }
}

void Application::sendCheck(double sum, const MyString& verificationCode, const MyString& egn) {
    User* user = userManager.findUserByEgn(egn);
    if (!user) {
        std::cout << "User not found.\n";
        return;
    }

    Client* client = dynamic_cast<Client*>(user);
    if (!client) {
        std::cout << "User is not a client.\n";
        return;
    }

    MyString str = doubleToString(sum, 5);
    client->addMessage("Check received: $" + str + " with code " + verificationCode.c_str());
}

void Application::approveTask(const MyString& taskId, int employeeId) {
    // Find the employee
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getId() == employeeId) {
            // Find the task within the employee's task list
            for (size_t j = 0; j < employees[i].getTaskCount(); ++j) {
                MyString str = toString(employees[i].getTasks()[j].taskId);

                if (taskId == str) {
                    // Approve the task
                    employees[i].getTasks()[j].approve();
                    return;
                }
            }
        }
    }
    std::cout << "Task or employee not found.\n";
}

void Application::disapproveTask(const MyString& taskId, const MyString& message, int employeeId) {
    // Find the employee
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getId() == employeeId) {
            // Find the task within the employee's task list
            for (size_t j = 0; j < employees[i].getTaskCount(); ++j) {

                MyString str = toString(employees[i].getTasks()[j].taskId);

                if (taskId == str) {
                    // Disapprove the task
                    employees[i].getTasks()[j].reject(message);
                    return;
                }
            }
        }
    }
    std::cout << "Task or employee not found.\n";
}

void Application::validateTask(const MyString& taskId, int employeeId) {
    // Find the employee
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getId() == employeeId) {
            // Find the task within the employee's task list
            for (size_t j = 0; j < employees[i].getTaskCount(); ++j) {
                MyString str = toString(employees[i].getTasks()[j].taskId);
                if (str == taskId) {
                    // Validate the task
                    if (employees[i].validate(taskId)) {
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

void Application::signupExternalEmployee(const MyString& firstName, const MyString& surname,
                                         const MyString& EGN, unsigned age, const MyString& password) {
    ExternalEmployee employee(firstName, surname, EGN, age, password);
    companyEmployees.pushBack(employee);
}

ExternalEmployee* Application::findExternalEmployeeById(int employeeId) {
    for (size_t i = 0; i < companyEmployees.getSize(); ++i) {
        if (companyEmployees[i].getId() == employeeId) {
            return &companyEmployees[i];
        }
    }
    return nullptr;
}
