#pragma once
#include "Task.h"

class TaskState {
public:
    virtual void approve(Task& task) = 0;
    virtual void reject(Task& task, const MyString& message) = 0;
    virtual ~TaskState() = default;
};

class NeedsApproval : public TaskState {
public:
    void approve(Task& task) override;
    void reject(Task& task, const MyString& message) override;
};

class Approved : public TaskState {
public:
    void approve(Task& task) override;
    void reject(Task& task, const MyString& message) override;
};

class Rejected : public TaskState {
public:
    void approve(Task& task) override;
    void reject(Task& task, const MyString& message) override;
};
