#include "Task.h"
#include "TaskState.h"

Task::Task(const TaskType &t,const MyString& clientName, const MyString& bankName, const MyString &accNum,
           const MyString &d, unsigned int id) : type(t), clientName(clientName),
                                                                   bankName(bankName),
                                                 accountNumber(accNum), details(d), taskId(id),
                                                 state(new NeedsApproval()) {}

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

void Task::readFromFile(std::ifstream& ifs) {
    // Implementation
}

void Task::validate() {
    // Implementation
}

void Task::saveToFile(std::ofstream& ofs) const {
    // Implementation
}

void Task::viewTask() const {
    // Implementation
}

