#include "BankEmployee.h"
#include "Application.h"
#include <iostream>
#include "TaskState.h"

BankEmployee::BankEmployee(const MyString& firstName, const MyString& surname,
                           const MyString& EGN, unsigned age, const MyString& password, Bank* bank)
        : User(firstName, surname, EGN, age, password), bank(bank){ //will directly call for the bank as we
    //cannot have an initialization without first having created a bank
}

void BankEmployee::show_tasks() const {
    std::cout << "Tasks:\n";
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        std::cout << "Task ID: " << tasks[i].taskId << ", Type: " <<
        static_cast<int>(tasks[i].type) << std::endl;
    }
}

void BankEmployee::view(const MyString& taskId) const {
    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].taskId == id) {
            std::cout << "Viewing Task ID: " << tasks[i].taskId << "\n";
            std::cout << "Type: " << static_cast<int>(tasks[i].type) << "\n";
            return;
        }
    }
    std::cout << "Task not found.\n";
}

void BankEmployee::approve(const MyString& taskId) {
    unsigned id = std::stoul(taskId.c_str());

    for (size_t i = 0; i < tasks.getSize(); i++) {
        if (tasks[i].taskId == id) {
            tasks[i].approve();
            Application& app = Application::getInstance();
            app.addMessageToClient(tasks[i].client ->getId(),
                                   "Your task with ID " + taskId + " has been approved by "
                                   + getFullName());
            return;
        }
    }

    std::cout << "Task not found. \n";
}

void BankEmployee::disapprove(const MyString& taskId, const MyString& message) {
    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].taskId == id) {
            tasks[i].reject(message);
            Application& app = Application::getInstance();
            app.addMessageToClient(tasks[i].client->getId(),
                                   "Your task with ID " + taskId +" has been disapproved by " + getFullName() +
                                   ". Reason: " + message);
            return;
        }
    }
    std::cout << "Task not found.\n";
}


bool BankEmployee::validate(const MyString& taskId) const {

    unsigned id = std::stoul(taskId.c_str());
    for (size_t i = 0; i < tasks.getSize(); i++) {
        if (tasks[i].taskId == id && tasks[i].type == TaskType::CHANGE) {
            // validate if the client data matches with the account details in the current bank
            return bank->validateClientData(tasks[i].client, tasks[i].accountNumber);
        }
    }
    std::cout << "Task not found or not a change task.\n";
    return false;

}

void BankEmployee::addTask(const Task& task) {
    tasks.pushBack(task);
}

size_t BankEmployee::getTaskCount() const {
    return tasks.getSize();
}

void BankEmployee::help() const {
    std::cout << "Available commands:\n";
    std::cout << "show_tasks - Show all tasks assigned to this employee\n";
    std::cout << "view [task_id] - View details of a specific task\n";
    std::cout << "approve [task_id] - Approve a specific task\n";
    std::cout << "disapprove [task_id] [message] - Disapprove a specific task with a reason\n";
    std::cout << "validate [task_id] - Validate a change task\n";
}

