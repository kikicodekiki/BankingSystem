#pragma once
#include "ICommand.h"
#include "Application.h"
#include "ClientCommand.h"

class CloseAccountCommand : public ClientCommand {
public:
    CloseAccountCommand(const MyString& bankName, const MyString& accountNumber, int clientId)
            : ClientCommand(clientId), bankName(bankName), accountNumber(accountNumber) {}

    void execute() override  {
        Application::getInstance().closeAccount(bankName, accountNumber, clientId);
    }
    ICommand* clone() const override {
        return new CloseAccountCommand(*this);
    }
private:
    MyString bankName;
    MyString accountNumber;
};
