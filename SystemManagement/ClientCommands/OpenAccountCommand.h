#pragma once
#include "ICommand.h"
#include "Application.h"
#include "ClientCommand.h"

class OpenAccountCommand : public ClientCommand {
public:
    OpenAccountCommand(const MyString& bankName, int clientId)
            : ClientCommand(clientId), bankName(bankName) {}

    void execute () override {
        Application::getInstance().openAccount(bankName, clientId);
    }
private:
    MyString bankName;

};
