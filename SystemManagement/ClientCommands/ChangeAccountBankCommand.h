#pragma once
#include "ClientCommand.h"
#include "MyString.h"
#include "Application.h"

class ChangeAccountBankCommand : public ClientCommand {
public:
    ChangeAccountBankCommand(const MyString& newBankName, const MyString& currBank, const MyString& accNum, int clientId)
            : ClientCommand(clientId), newBankName(newBankName), currBank(currBank), accNum(accNum) {}


    void execute() override {
        Application::getInstance().changeAccountBank(newBankName, currBank, accNum, clientId);
    }
private:
    MyString newBankName;
    MyString currBank;
    MyString accNum;
};
