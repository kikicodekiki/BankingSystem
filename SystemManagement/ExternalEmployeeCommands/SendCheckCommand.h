#pragma once
#include "ExternalEmployeeCommand.h"
#include "Application.h"
#include "BankCheck.h"

class SendCheckCommand : public ExternalEmployeeCommand {
public:
    SendCheckCommand(double sum, const MyString& EGN, const MyString& bankName, int employeeId) :
            ExternalEmployeeCommand(employeeId), sum(sum), EGN(EGN), bankName(bankName) {}


    void execute () override {
        const char* code = BankCheck::generateVerificationCode();

        BankCheck check(code, sum);
        Application& app = Application::getInstance();
        Bank* bank = app.findBank(bankName);
        if (bank) {
            bank ->issueCheck(EGN, check);
        } else {
            throw std::runtime_error("Bank not found. \n");
        }


    }

private:
    double sum;
    MyString EGN;
    MyString bankName;
};
