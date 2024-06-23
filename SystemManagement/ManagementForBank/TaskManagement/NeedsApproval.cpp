#include "Task.h"
#include "TaskState.h"
#include "Application.h"
#include "BankEmployee.h"
#include <iostream>

void NeedsApproval::approve(Task& task) {
    Application& app = Application::getInstance();
    if (task.type == TaskType::CHANGE) {
        Bank* currentBank = app.findBank(task.bank->getName());
        if (currentBank) {
            BankEmployee* leastBusyEmployee = currentBank->getLeastBusyEmployee();
            if (leastBusyEmployee) {
                leastBusyEmployee->addTask(task);
                std::cout << "Task forwarded to another employee for validation.\n";
                return;
            }
        }
    }
    task.setState(new Approved());
}

void NeedsApproval::reject(Task& task, const MyString& message) {
    task.setState(new Rejected());
    Application::getInstance().addMessageToClient(task.client->getId(),
                                                  "Your request has been rejected. Reason: " + message);
}
