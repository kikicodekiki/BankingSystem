#pragma once
#include "MyString.h"
#include "User.h"
#include "Task.h"
#include "Vector.h"



class Employee : public User {
public:
    Employee() = default;

    Employee(const MyString& name, const MyString& surname,
             const MyString& EGN, size_t age,
             const MyString& password, const MyString& bankName ) :
             User(name,surname,EGN,age,password ) , bankName(bankName){}

    void addTask (const Task& task);
    size_t getNumberOfTasks () const;
    const Task& getTaskAtIndex (size_t index) const;
    Task& getTaskAtIndex (size_t index);

    void saveToFile(std::ofstream& ofs) const override;
    void readFromFile(std::ifstream& ifs) override;

    void view (size_t index) const;
    void help() const override;
    void whoAmI () const override;

    User* clone () const {
        return new Employee(*this);
    }


    void approveTask(size_t taskId);
    void disapproveTask(size_t taskId, const MyString& message);
    void validateTask(size_t taskId);

private:
    MyString bankName;
    Vector<Task> tasks;
};
