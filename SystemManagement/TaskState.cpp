#include "TaskState.h"
#include "Application.h"
#include "BankEmployee.h"
#include <iostream>

void NeedsApproval::approve(Task& task) {
    // This will handle the initial approval and forwarding process
    Application& app = Application::getInstance();
    if (task.type == TaskType::CHANGE) {
        // Forward task to another employee for validation
        Bank* currentBank = app.findBank(task.details); // assuming task.details contains currentBank info
        if (currentBank) {
            BankEmployee* leastBusyEmployee = app.getLeastBusyEmployee();
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
    Application::getInstance().addMessageToClient(task.client->getId(), "Your request has been rejected. Reason: " + message);
}

void Approved::approve(Task& task) {
    // Handle final approval and task completion
    Application& app = Application::getInstance();
    switch (task.type) {
        case TaskType::OPEN:
            app.openAccount(task.details, task.client->getId());
            break;
        case TaskType::CLOSE:
            app.closeAccount(task.details, task.client->getId());
            break;
        case TaskType::CHANGE:

            app.changeAccountBank(currentBank, newBank, task.client->getId());
            break;
        default:
            std::cout << "Unknown task type.\n";
            return;
    }

    app.addMessageToClient(task.client->getId(), "Your request has been approved.");
    task.setState(new Approved());
}

void Approved::reject(Task& task, const MyString& message) {
    std::cout << "Cannot reject an already approved task.\n";
}

void Rejected::approve(Task& task) {
    std::cout << "Cannot approve a rejected task.\n";
}

void Rejected::reject(Task& task, const MyString& message) {
    std::cout << "Task is already rejected.\n";
}
