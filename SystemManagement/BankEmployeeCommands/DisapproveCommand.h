#pragma once
#include "BankEmployeeCommand.h"
#include "MyString.h"
#include "Application.h"

class DisapproveTaskCommand : public BankEmployeeCommand {
public:
    DisapproveTaskCommand(const MyString& taskId, const MyString& message, int employeeId)
            : BankEmployeeCommand(employeeId), taskId(taskId), message(message) {}

    void execute() override {
        Application::getInstance().disapproveTask(taskId, message, employeeId);
    }
private:
    MyString taskId;
    MyString message;
};
