#pragma once
#include "User.h"
#include "Vector.h"
#include "Client.h"
#include "BankEmployee.h"
//#include "ExternalCompanyEmployee.h"
#include "Bank.h"

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
    void signup(const UserType& userType, const MyString& firstName,
                const MyString& surname, const MyString& EGN, unsigned age,
                const MyString& bankName = "", const MyString& address = "");

    void createBank(const MyString& bankName);
    void logout();

    const User* getLoggedUser() const;
    User* getLoggedUser();
    UserType getLoggedType() const;

    void changeAccountBank(const MyString& newBankName, const MyString& currBank,
                                        const MyString& accNum, int clientId);
    void closeAccount (const MyString& bankName, const MyString& accountNumber, int clientId);
    void openAccount(const MyString& bankName, int clientId);

    void executeCommand(const MyString& command, const Vector<MyString>& args);

    void addMessageToClient(int clientId, const MyString& message);

private:
    User* logged = nullptr;
    UserType type = UserType::DEFAULT;

    Vector<Client> clients;
    Vector<BankEmployee> employees;
    //Vector<ExternalCompanyEmployee> companyEmployees;
    Vector<Bank> banks;

    Application() = default;
    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;

    Bank* findBank(const MyString& bankName);
    Client* findClientById(int clientId);
};
