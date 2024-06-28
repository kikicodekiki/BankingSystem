#pragma once

#include "MyString.h"


class Task;

class TaskState {
public:
    virtual void approve(Task& task) = 0;
    virtual void reject(Task& task, const MyString& message) = 0;
    virtual void validate(Task& task) = 0;
    virtual ~TaskState() = default;
};

class Approved : public TaskState {
public:
    void approve(Task& task) override;
    void reject(Task& task, const MyString& message) override;
    void validate(Task& task) override;
};

class Rejected : public TaskState {
public:
    void approve(Task& task) override;
    void reject(Task& task, const MyString& message) override;
    void validate(Task& task) override;
};

class NeedsApproval : public TaskState {
public:
    void approve(Task& task) override;
    void reject(Task& task, const MyString& message) override;
    void validate(Task& task) override;
};
