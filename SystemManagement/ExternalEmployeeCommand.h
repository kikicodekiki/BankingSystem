#pragma once
#include "ICommand.h"
#include "Application.h"


class ExternalEmployeeCommand : public ICommand {
public:
    ExternalEmployeeCommand(int employeeId) : employeeId(employeeId) {}
protected:
    int employeeId;
};
