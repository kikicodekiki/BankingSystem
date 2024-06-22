#pragma once
#include "User.h"
#include "Vector.h"
#include "Client.h"
#include "BankEmployee.h"
#include "ExternalCompanyEmployee.h"
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
    void login(MyString&& username, MyString&& password);

    void signup(const UserType& userType, const MyString& firstName,
                const MyString& surname, const MyString& EGN, unsigned age,
                const MyString& address = " ");

    void create_bank (const MyString& bankName);
    void create_bank (MyString&& bankName);

    void addClient (const Client& client);
    void addBankEmployee (const BankEmployee& bank);
    void addExternalCompanyEmployee (const ExternalCompanyEmployee& extEmp);

    void addClient (Client&& client);
    void addBankEmployee (BankEmployee&& bank);
    void addExternalCompanyEmployee (ExternalCompanyEmployee&& extEmp);

    void logout();

    const User* getLoggedUser() const;
    User* getLoggedUser();
    UserType getLoggedType();

    void executeCommand(const MyString& command, const Vector<MyString>& args);

    void exit_app() const;


private:

    User* logged = nullptr;
    UserType type = UserType::DEFAULT;

    Vector<Client> clients;
    Vector<BankEmployee> employees;
    Vector<ExternalCompanyEmployee> companyEmployees;
    Vector <Bank> banks;

    Application() = default;
    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;
};
