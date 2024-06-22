#pragma once
#include "IBankEmployee.h"
#include "Task.h"

class BankEmployee : public User, public virtual IBankEmployee {
public:
    BankEmployee(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age, const MyString& password);

    void show_tasks() const override;
    void view(const MyString& taskId) const override;
    void approve(const MyString& taskId) override;
    void disapprove(const MyString& taskId, const MyString& message) override;
    void validate(const MyString& taskId) override;

    void addTask(const Task& task);
    size_t getTaskCount() const;

private:
    Vector<Task> tasks;
};
