#pragma once
#include "ClientCommand.h"
#include "ICommand.h"
#include "Application.h"

class CheckBalanceCommand : public ClientCommand {
public:
    CheckBalanceCommand(const MyString& bankName, const MyString& accountNumber, int clientId)
            : ClientCommand(clientId), bankName(bankName), accountNumber(accountNumber) {}

    void execute() override {
        Application& app = Application::getInstance();

    }
private:
    MyString bankName;
    MyString accountNumber;
};
