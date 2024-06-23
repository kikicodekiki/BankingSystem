#include "Task.h"
#include "TaskState.h"
#include "NeedsApproval.h"

Task::Task(const TaskType& t, const Client* c, const MyString& accNum, const MyString& d, unsigned id)
        : type(t), client(c), accountNumber(accNum), details(d), taskId(id), state(new NeedsApproval()) {}


Task::~Task() {
    delete state;
}

void Task::approve() {
    if (state) {
        state->approve(*this);
    }
}

void Task::reject(const MyString& message) {
    if (state) {
        state->reject(*this, message);
    }
}

void Task::setState(TaskState* newState) {
    cleanupState();
    state = newState;
}

void Task::cleanupState() {
    if (state) {
        delete state;
        state = nullptr;
    }
}
