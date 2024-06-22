#pragma once
enum class TaskType {
    OPEN,
    CLOSE,
    CHANGE,

    Default
};

struct Task {
    TaskType type = TaskType::Default;
    const Client* client = nullptr;
    MyString details;
    unsigned taskId = 0;

    Task () = default;
    Task (const TaskType& t, const Client* c, const MyString& d, unsigned id ) :
            type(t), client(c), details(d), taskId(id) {}
    ~Task() {
        delete client;
    }
};
