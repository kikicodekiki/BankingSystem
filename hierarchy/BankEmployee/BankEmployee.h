#pragma once
#include "IBankEmployee.h"
#include "Task.h"
#include "Bank.h"

class BankEmployee : public User, public virtual IBankEmployee {
public:
    BankEmployee(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age,
                 const MyString& password, Bank* bank);

    void show_tasks() const override;
    void view(const MyString& taskId) const override;
    void approve(const MyString& taskId) override;
    void disapprove(const MyString& taskId, const MyString& message) override;
    bool validate(const MyString& taskId) const override;

    void addTask(const Task& task);
    size_t getTaskCount() const;

    Bank* getCurrentBank () const {return bank;}

    ~BankEmployee() = default;


    void help() const override;

    User* clone() const override {
        return new BankEmployee(*this);
    }

private:
    Vector<Task> tasks;
    Bank* bank = nullptr; //does not own the bank object
};
