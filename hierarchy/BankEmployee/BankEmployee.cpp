#include "BankEmployee.h"
#include "Application.h"
#include <iostream>

BankEmployee::BankEmployee(const MyString& firstName, const MyString& surname,
                           const MyString& EGN, unsigned age, const MyString& password)
        : User(firstName, surname, EGN, age, password) {}

void BankEmployee::show_tasks() const {
    std::cout << "Tasks:\n";
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        std::cout << "Task ID: " << tasks[i].taskId << ", Type: " <<
        static_cast<int>(tasks[i].type) <<
        ", Details: " << tasks[i].details.c_str() << "\n";
    }
}

void BankEmployee::view(const MyString& taskId) const {
    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].taskId == id) {
            std::cout << "Viewing Task ID: " << tasks[i].taskId << "\n";
            std::cout << "Type: " << static_cast<int>(tasks[i].type) << "\n";
            std::cout << "Details: " << tasks[i].details.c_str() << "\n";
            return;
        }
    }
    std::cout << "Task not found.\n";
}

void BankEmployee::approve(const MyString& taskId) {
    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].taskId == id) {
            Task& task = tasks[i];
            Application& app = Application::getInstance();

            switch (task.type) {
                case TaskType::OPEN:
                    app.openAccount(task.details, task.client->getId());
                    break;
                case TaskType::CLOSE:
                    app.closeAccount(task.details, task.client->getId());
                    break;
                case TaskType::CHANGE: {
                    // For change, details should include both current and new bank info
                    MyString currentBank = ...; // extract current bank from details
                    MyString newBank = ...; // extract new bank from details
                    app.changeAccountBank(currentBank, newBank, task.client->getId());
                    break;
                }
                default:
                    std::cout << "Unknown task type.\n";
                    return;
            }

            app.addMessageToClient(task.client->getId(), "Your request has been approved.");
            tasks.popAt(i);
            std::cout << "Task approved.\n";
            return;
        }
    }
    std::cout << "Task not found.\n";
}

void BankEmployee::disapprove(const MyString& taskId, const MyString& message) {
    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].taskId == id) {
            Task& task = tasks[i];
            Application& app = Application::getInstance();

            app.addMessageToClient(task.client->getId(), "Your request has been disapproved. Reason: " + message);
            tasks.popAt(i);
            std::cout << "Task disapproved.\n";
            return;
        }
    }
    std::cout << "Task not found.\n";
}


void BankEmployee::validate(const MyString& taskId) {
    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].taskId == id && tasks[i].type == TaskType::CHANGE) {
            Task& task = tasks[i];
            Application& app = Application::getInstance();

            MyString currentBank = ...; // extract current bank from details
            Bank* bank = app.findBank(currentBank);
            if (bank && bank->findUser(task.client->getUsername())) {
                std::cout << "Task validated.\n";
            } else {
                std::cout << "Validation failed. Account not found in the specified bank.\n";
            }
            return;
        }
    }
    std::cout << "Task not found or invalid task type.\n";
}

void BankEmployee::addTask(const Task& task) {
    tasks.pushBack(task);
}

size_t BankEmployee::getTaskCount() const {
    return tasks.getSize();
}
