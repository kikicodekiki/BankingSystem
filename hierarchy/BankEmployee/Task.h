#pragma once
#include "MyString.h"
#include "Vector.h"
#include "TaskState.h"
#include <fstream>
#include "TaskType.h"


class Application;


class Task {
public:
    TaskType type = TaskType::Default;
    MyString clientName ;
    MyString bankName;
    unsigned taskId = 0;
    TaskState* state = nullptr;
    MyString accountNumber;
    MyString details;

    Task() = default;
    Task(const TaskType& t, const MyString& clientName, const MyString& bankName,
         const MyString& accNum, const MyString& d, unsigned id);
    ~Task();

    Task (const Task& other) = default;

    void saveToFile (std::ofstream& ofs ) const;
    void readFromFile (std::ifstream& ifs);

    void approve();
    void reject(const MyString& message);
    void setState(TaskState* newState);

    void viewTask () const;

    int getId () const {return taskId;}

    void validate();

private:
    void cleanupState();
};
