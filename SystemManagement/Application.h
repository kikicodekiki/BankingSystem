#pragma once

//#include "User.h"
#include "Vector.h"
//#include "Client.h"
//#include "BankEmployee.h"
//#include "ExternalEmployee.h"
#include "UserManagement.h"
//#include "Bank.h"
#include "DoubleToString.h"
//#include "Task.h"
#include "PolymorphicPtr.h"
#include "MyString.h"

enum class TaskType;
enum class UserType {
    Client,
    Employee,
    ExternalEmployee,
    DEFAULT
};
//class UserManagement;
class ExternalEmployee;
class Client;
class BankEmployee;
class Bank;
class User;

class Application {

private:
    User* logged = nullptr;
    UserType type = UserType::DEFAULT;

    UserManagement userManager;
    Vector<Bank> banks;
    Vector<Polymorphic_Ptr<Client>> clients;
    Vector<Polymorphic_Ptr<BankEmployee>> employees;

    Application() = default;

public:
    static Application& getInstance();

    void login(const MyString& username, const MyString& password);
    void signup(const UserType& userType, const MyString& firstName,
                const MyString& surname, const MyString& EGN,const MyString& password,
                size_t age, const MyString& bankName = "", const MyString& address = "");

    void createBank(const MyString& bankName);
    void logout();

    const User* getLoggedUser() const;
    User* getLoggedUser();
    UserType getLoggedType() const;

    void changeAccountBank(const MyString& newBankName, const MyString& currBank,
                           const MyString& accNum, int clientId);
    void closeAccount(const MyString& bankName, const MyString& accountNumber, int clientId);
    void openAccount(const MyString& bankName, int clientId);

   // void executeCommand(const MyString& command, const Vector<MyString>& args);

    void addMessageToClient(int clientId, const MyString& message);
    Bank* findBank(const MyString& bankName);
    const Bank* findBank(const MyString& bankName) const;

    Client* findClientById(int clientId);
    BankEmployee* getLeastBusyEmployee(const MyString& bankName);
//    const BankEmployee* getLeastBusyEmployee(const MyString& bankName) const;

    double checkAccountBalance(const MyString& bankName, const MyString& accountNumber, int clientId);

    void list(const MyString& bankName, int clientId);

    void listAccounts(const MyString& bankName, int clientId);
    void sendCheck(double sum, const MyString& verificationCode, const MyString& egn);
    void approveTask(const MyString& taskId, int employeeId);
    void disapproveTask(const MyString& taskId, const MyString& message, int employeeId);
    void validateTask(const MyString& taskId, int employeeId);

    void redeemCheck(const MyString& bankName,
                     const MyString& accountNumber, const MyString& verificationCode,
                     int clientId);

    BankEmployee*assignTaskToLeastBusyEmployee(TaskType taskType, int clientId, const MyString& taskDetails);
    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;

};


