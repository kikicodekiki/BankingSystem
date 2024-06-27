#pragma once

#include "Task.h"
#include "Bank.h"

class Bank;

class BankEmployee : public User {
public:
    BankEmployee()= default;
    BankEmployee(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age,
                 const MyString& password, Bank* bank);

    void show_tasks() const ;
    void view(const MyString& taskId) const ;
    void approve(const MyString& taskId) ;
    void disapprove(const MyString& taskId, const MyString& message) ;
    bool validate(const MyString& taskId) const ;

    void addTask(const Task& task);
    size_t getTaskCount() const;

    Bank* getCurrentBank () const {return bank;}

    ~BankEmployee() = default;

    Vector<Task> getTasks ()  {
        return tasks;
    }
    const Vector<Task>& getTasks() const { return tasks; }

    void help() const;

    User* clone() const override{
        return new BankEmployee(*this);
    }

private:
    Vector<Task> tasks;
    Bank* bank = nullptr; //does not own the bank object
};
