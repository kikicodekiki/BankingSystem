#pragma once
#include "ICommand.h"
#include "MyString.h"


class BankEmployeeCommand : public ICommand {
public:
    BankEmployeeCommand(int employeeId) : employeeId(employeeId) {}
protected:
    int employeeId;
};
