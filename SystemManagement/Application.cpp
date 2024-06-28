#include "Application.h"
#include "DoubleToString.h"

#include <stdexcept>
#include <iostream>

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

void Application::login(const MyString& username, const MyString& password) {
    for (size_t i = 0; i < clients.getSize(); ++i) {
        if (clients[i].authenticate(username, password)) {
            logged = &clients[i];
            type = UserType::Client;
            return;
        }
    }
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].authenticate(username, password)) {
            logged = &employees[i];
            type = UserType::Employee;
            return;
        }
    }
    for (size_t i = 0; i < externalEmployees.getSize(); ++i) {
        if (externalEmployees[i].authenticate(username, password)) {
            logged = &externalEmployees[i];
            type = UserType::ExternalEmployee;
            return;
        }
    }
    throw std::runtime_error("Invalid username or password.");
}

void Application::signup(const UserType& userType,
                         const MyString& firstName,
                         const MyString& surname, const MyString& EGN,
                         const MyString& password, size_t age, const MyString& bankName,
                         const MyString& address) {
    switch (userType) {
        case UserType::Client:
            clients.pushBack(Client(firstName, surname, EGN, age, password, address));
            break;
        case UserType::Employee:
            employees.pushBack(Employee(firstName, surname, EGN, age, password, bankName));
            break;
        case UserType::ExternalEmployee:
            externalEmployees.pushBack(ExternalEmployee(firstName, surname, EGN, age, password));
            break;
        default:
            throw std::runtime_error("Invalid user type.");
    }
}

void Application::createBank(const MyString& bankName) {
    for (size_t i = 0; i < banks.getSize(); ++i) {
        if (banks[i].getBankName() == bankName) {
            throw std::runtime_error("Bank already exists.");
        }
    }
    banks.pushBack(Bank(bankName));
}

void Application::logout() {
    logged = nullptr;
    type = UserType::DEFAULT;
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

double Application::checkAccountBalance(const MyString& bankName, const MyString& accountNumber, int clientId) {
    const Bank* bank = findBank(bankName);
    if (!bank) throw std::runtime_error("Bank not found.");
    return bank->checkBalance(std::stoul(accountNumber.c_str()));
}

void Application::openAccount(const MyString& bankName, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) throw std::runtime_error("Bank not found.");
    bank->createAccount(logged->getFullName());
}

void Application::closeAccount(const MyString& bankName, const MyString& accountNumber, int clientId) {
    Bank* bank = findBank(bankName);
    if (!bank) throw std::runtime_error("Bank not found.");
    bank->closeAccount(logged->getFullName(), std::stoul(accountNumber.c_str()));
}

void Application::changeAccountBank(const MyString& newBankName, const MyString& currBank, const MyString& accNum, int clientId) {

}

void Application::list(const MyString& bankName, int clientId) {
    const Bank* bank = findBank(bankName);
    if (!bank) throw std::runtime_error("Bank not found.");
    const Vector<Pair<MyString, Account>>& accounts = bank->getBankAccounts();
    for (size_t i = 0; i < accounts.getSize(); ++i) {
        if (accounts[i].getLhs() == logged->getFullName()) {
            std::cout << "Account Number: " << accounts[i].getRhs().getAccountNumber() << ", Balance: " << accounts[i].getRhs().getBalance() << "\n";
        }
    }
}

void Application::sendCheck(double sum, const MyString& verificationCode, const MyString& egn) {
    BankCheck check(verificationCode.c_str(), sum);
    Client* client = findClientByEgn(egn);
    if (client) {
        client->addCheck(check);
    } else {
        throw std::runtime_error("Client not found.");
    }
}

void Application::approveTask(size_t taskId, int employeeId) {
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getId() == employeeId) {
            employees[i].approveTask(taskId);
            return;
        }
    }
    throw std::runtime_error("Employee not found.");
}

void Application::disapproveTask(size_t taskId, const MyString& message, int employeeId) {
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getId() == employeeId) {
            employees[i].disapproveTask(taskId, message);
            return;
        }
    }
    throw std::runtime_error("Employee not found.");
}

void Application::validateTask(size_t taskId, int employeeId) {
    for (size_t i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getId() == employeeId) {
            employees[i].validateTask(taskId);
            return;
        }
    }
    throw std::runtime_error("Employee not found.");
}

void Application::redeemCheck(const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode, int clientId) {
    Client* client = dynamic_cast<Client*>(logged);
    if (client) {
        double sum = client->getCheckSum(verificationCode);
        Bank* bank = findBank(bankName);
        if (bank) {
            bank->deposit(std::stoul(accountNumber.c_str()), client->getFullName(), sum);
        } else {
            throw std::runtime_error("Bank not found.");
        }
    } else {
        throw std::runtime_error("Logged user is not a client.");
    }
}

Bank* Application::findBank(const MyString& bankName) {
    for (size_t i = 0; i < banks.getSize(); ++i) {
        if (banks[i].getBankName() == bankName) {
            return &banks[i];
        }
    }
    return nullptr;
}

const Bank* Application::findBank(const MyString& bankName) const {
    for (size_t i = 0; i < banks.getSize(); ++i) {
        if (banks[i].getBankName() == bankName) {
            return &banks[i];
        }
    }
    return nullptr;
}

Client* Application::findClientByEgn(const MyString& egn) {
    for (size_t i = 0; i < clients.getSize(); ++i) {

        MyString parseEGN = parseEgn(clients[i].getEgn());

        if (parseEGN == egn) {
            return &clients[i];
        }
    }
    return nullptr;
}

Employee* Application::getLeastBusyEmployee(const MyString& bankName) {
    Bank* bank = findBank(bankName);
    if (!bank) throw std::runtime_error("Bank not found.");
    return bank->getLeastBusyEmployee();
}
