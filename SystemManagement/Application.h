#pragma once
#include "Vector.h"
#include "TaskType.h"
#include "User.h"
#include "Bank.h"
#include "Client.h"
#include "Employee.h"
#include "ExternalEmployee.h"

enum class UserType {
    Client,
    Employee,
    ExternalEmployee,
    DEFAULT
};

class Application {
public:
    static Application& getInstance();

    void login(const MyString& username, const MyString& password);
    void signup(const UserType& userType, const MyString& firstName, const MyString& surname, const MyString& EGN, const MyString& password, size_t age, const MyString& bankName = "", const MyString& address = "");
    void createBank(const MyString& bankName);
    void logout();
    const User* getLoggedUser() const;
    User* getLoggedUser();
    UserType getLoggedType() const;

    double checkAccountBalance(const MyString& bankName, const MyString& accountNumber, int clientId);

    void openAccount(const MyString& bankName, int clientId);
    void closeAccount(const MyString& bankName, const MyString& accountNumber, int clientId);
    void changeAccountBank(const MyString& newBankName, const MyString& currBank, const MyString& accNum, int clientId);


    void list(const MyString& bankName, int clientId);
    void sendCheck(double sum, const MyString& verificationCode, const MyString& egn);
    void approveTask(size_t taskId, int employeeId);
    void disapproveTask(size_t taskId, const MyString& message, int employeeId);

    void validateTask(size_t taskId, int employeeId);
    void redeemCheck(const MyString& bankName, const MyString& accountNumber,
                     const MyString& verificationCode, int clientId);

    Bank* findBank(const MyString& bankName);
    const Bank* findBank(const MyString& bankName) const;

private:
    User* logged = nullptr;
    UserType type = UserType::DEFAULT;

    Vector<Bank> banks;
    Vector<Client> clients;
    Vector<Employee> employees;
    Vector<ExternalEmployee> externalEmployees;

    Application() = default;
    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;


    Client* findClientByEgn(const MyString& egn);
    Employee* getLeastBusyEmployee(const MyString& bankName);
};


