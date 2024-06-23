#include "TaskState.h"
#include "Task.h"
#include "Application.h"
#include <iostream>

void Approved::approve(Task& task) {
    Application& app = Application::getInstance();
    switch (task.type) {
        case TaskType::OPEN: {
            app.openAccount(task.bank->getName(), task.client->getId());
            break;
        }
        case TaskType::CLOSE: {
            app.closeAccount(task.bank->getName(), task.accountNumber, task.client->getId());
            break;
        }
        case TaskType::CHANGE:{
            MyString newBank;

            do {
                std::cout << "Enter the name of the new bank: \n";
                std::cin >> newBank;
            } while (!newBank.c_str());

            app.changeAccountBank(newBank, task.bank ->getName(),
                                  task.accountNumber, task.client->getId() );
            break;
        }
        default: {
            std::cout << "Unknown task type.\n";
            return;
        }
    }
    app.addMessageToClient(task.client->getId(), "Your request has been approved.");
}

void Approved::reject(Task& task, const MyString& message) {
    std::cout << "Cannot reject an already approved task.\n";
}
