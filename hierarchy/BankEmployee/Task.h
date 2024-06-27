#pragma once
#include "User.h"
#include "MyString.h"
#include "Vector.h"
#include "TaskState.h"
#include "Client.h"

#include "Bank.h"

enum class TaskType {
    OPEN,
    CLOSE,
    CHANGE,
    Default
};

class Task {

public:
    TaskType type = TaskType::Default;
    const Client* client = nullptr;
    Bank * bank = nullptr;
    unsigned taskId = 0;
    TaskState* state = nullptr;
    MyString accountNumber;
    MyString details;

    Task() = default;
    Task(const TaskType& t, const Client* c, const MyString& accNum, const MyString& d, unsigned id);
    ~Task();

    void approve();
    void reject(const MyString& message);
    void setState(TaskState* newState);

private:
    void cleanupState();
};
