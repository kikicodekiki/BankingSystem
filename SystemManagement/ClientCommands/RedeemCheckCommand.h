#pragma once
#include "ClientCommand.h"
#include "Application.h"


class RedeemCheckCommand : public ClientCommand {
public:
    RedeemCheckCommand(const MyString& bankName, const MyString& accountNumber,
                       const MyString& verificationCode, int clientId)
            : ClientCommand(clientId), bankName(bankName),
            accountNumber(accountNumber), verificationCode(verificationCode) {}
    void execute() override {
        Application::getInstance().redeemCheck(bankName, accountNumber, verificationCode, clientId);
    }
    ICommand* clone() const override {
        return new RedeemCheckCommand(*this);
    }

private:

    MyString bankName;
    MyString accountNumber;
    MyString verificationCode;

};
