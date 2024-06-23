#pragma once
#include "ICommand.h"
#include "ApproveTaskCommand.h"
#include "ChangeAccountBankCommand.h"
#include "CheckBalannceCommand.h"
#include "CloseAccountCommand.h"
#include "DisapproveTaskCommand.h"
#include "OpenAccountCommand.h"
#include "SendCheckCommand.h"
#include "ValidateTaskCommand.h"
#include "RedeemCheckCommand.h"

class CommandFactory {
public:
    static ICommand* createApproveTaskCommand(const MyString& taskId, int employeeId) {
        return new ApproveTaskCommand(taskId, employeeId);
    }

    static ICommand* createChangeAccountBankCommand(const MyString& newBankName, const MyString& currBank, const MyString& accNum, int clientId) {
        return new ChangeAccountBankCommand(newBankName, currBank, accNum, clientId);
    }

    static ICommand* createCheckBalanceCommand(const MyString& bankName, const MyString& accountNumber, int clientId) {
        return new CheckBalanceCommand(bankName, accountNumber, clientId);
    }

    static ICommand* createCloseAccountCommand(const MyString& bankName, const MyString& accountNumber, int clientId) {
        return new CloseAccountCommand(bankName, accountNumber, clientId);
    }

    static ICommand* createDisapproveTaskCommand(const MyString& taskId, const MyString& message, int employeeId) {
        return new DisapproveTaskCommand(taskId, message, employeeId);
    }

    static ICommand* createOpenAccountCommand(const MyString& bankName, int clientId) {
        return new OpenAccountCommand(bankName, clientId);
    }

    static ICommand* createSendCheckCommand(double sum, const MyString& EGN, const MyString& bankName, int employeeId) {
        return new SendCheckCommand(sum, EGN, bankName, employeeId);
    }

    static ICommand* createValidateTaskCommand(const MyString& taskId, int employeeId) {
        return new ValidateTaskCommand(taskId, employeeId);
    }

    static ICommand* createRedeemCheckCommand (const MyString& bankName, const MyString& accountNumber,
                                               const MyString& verificationCode, int clientId ) {
        return new RedeemCheckCommand(bankName,accountNumber,verificationCode,clientId);
    }
};
