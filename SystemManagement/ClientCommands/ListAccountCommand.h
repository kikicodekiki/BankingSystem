#pragma once
#include "ICommand.h"
#include "Application.h"
#include "ClientCommand.h"

class ListAccountCommand : public ClientCommand {
public:
    ListAccountCommand(const MyString& bankName, int clientId)
            : ClientCommand(clientId), bankName(bankName) {}

    void execute() override {
        Application::getInstance().list(bankName, clientId);
    }
private:
    MyString bankName;
};
