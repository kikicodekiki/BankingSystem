#include "Application.h"

Application& Application::getInstance() {
    static Application app;
    return app;
}

void Application::create_bank (const MyString& bankName) {
    Bank bank = Bank(bankName);
    banks.pushBack(bank);
}
void create_bank (MyString&& bankName);

void addClient (const Client& client);
void addBankEmployee (const BankEmployee& bank);
void addExternalCompanyEmployee (const ExternalCompanyEmployee& extEmp);

void addClient (Client&& client);
void addBankEmployee (BankEmployee&& bank);
void addExternalCompanyEmployee (ExternalCompanyEmployee&& extEmp);
