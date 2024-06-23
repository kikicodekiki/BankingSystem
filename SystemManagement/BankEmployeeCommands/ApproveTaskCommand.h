#pragma once
#include "BankEmployeeCommand.h"
#include "Application.h"


class ApproveTaskCommand : public BankEmployeeCommand {
public:
    ApproveTaskCommand(const MyString& taskId, int employeeId) :
            BankEmployeeCommand(employeeId), taskId(taskId) {}


    void execute () override {
        Application::getInstance().approveTask(taskId, employeeId);
    }
private:
    MyString taskId;
};
