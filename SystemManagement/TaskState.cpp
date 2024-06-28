#include "TaskState.h"
#include "Task.h"
#include "Application.h"

void Approved::approve(Task& task) {

}

void Approved::reject(Task& task, const MyString& message) {

}

void Approved::validate(Task& task) {

}

void Rejected::approve(Task& task) {
    // Can't approve a rejected task, do nothing or throw an error
}

void Rejected::reject(Task& task, const MyString& message) {
    // Already rejected, do nothing or throw an error
}

void Rejected::validate(Task& task) {
    // Task is already rejected, validation logic can be skipped or throw an error
}

void NeedsApproval::approve(Task& task) {
    // Move to approved state
    task.setState(new Approved());
}

void NeedsApproval::reject(Task& task, const MyString& message) {
    // Move to rejected state
    task.setState(new Rejected());
}


void NeedsApproval::validate(Task& task) {
    Application& app = Application::getInstance();


    Bank* bank = app.findBank(task.bankName);
    if (!bank) {
        std::cerr << "Validation failed: Bank does not exist." << std::endl;
        task.setState(new Rejected());
        return;
    }


    bool accountExists = false;
    const Vector<Pair<MyString, Account>>& accounts = bank->getBankAccounts();
    for (size_t i = 0; i < accounts.getSize(); ++i) {
        if (accounts[i].getRhs().getAccountNumber() == std::stoul(task.accountNumber.c_str())) {
            accountExists = true;
            break;
        }
    }

    if (!accountExists) {
        std::cerr << "Validation failed: Account number does not exist." << std::endl;
        task.setState(new Rejected());
        return;
    }

    std::cout << "Validation passed: Task approved." << std::endl;
    task.setState(new Approved());
}

