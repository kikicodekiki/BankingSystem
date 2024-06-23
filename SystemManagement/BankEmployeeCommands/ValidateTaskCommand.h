#pragma once
#include "BankEmployeeCommand.h"
#include "MyString.h"
#include "Application.h"

class ValidateTaskCommand : public BankEmployeeCommand {
public:
    ValidateTaskCommand(const MyString& taskId, int employeeId) :
            BankEmployeeCommand(employeeId), taskId(taskId) {}


    void execute () override {
        Application::getInstance().validateTask(taskId, employeeId);
    }
private:
    MyString taskId;
};
