
#include "Employee.h"
#include <assert.h>

void Employee::addTask (const Task& task) {
    tasks.pushBack(task);
}
size_t Employee::getNumberOfTasks () const {
    return tasks.getSize();
}
const Task& Employee::getTaskAtIndex (size_t index) const {
    assert (index < tasks.getSize());

    return tasks[index];
}
Task& Employee::getTaskAtIndex (size_t index) {
    assert (index < tasks.getSize());

    return tasks[index];
}

void Employee::saveToFile(std::ofstream& ofs) const  {
    User::saveToFile(ofs);

    bankName.saveToFile(ofs);

    int tasksCount = tasks.getSize();

    ofs.write(reinterpret_cast<const char*>(&tasksCount), sizeof(tasksCount) );
    for (int i = 0; i < tasksCount; i++) {
        tasks[i].saveToFile(ofs);
    }

}
void Employee:: readFromFile(std::ifstream& ifs)  {
    User::readFromFile(ifs);

    bankName.readFromFile(ifs);

    int tasksCount = 0;

    ifs.read(reinterpret_cast< char*>(&tasksCount), sizeof tasksCount);

    for (int i = 0; i < tasksCount; i++) {
        tasks[i].readFromFile(ifs);
    }
}

void Employee::view (size_t index) const {
    for (int i = 0; i < tasks.getSize(); i++) {
         std::cout << "Task №" << i << ": ";
         tasks[i].viewTask();
         std::cout << '\n';
    }
}

void Employee::whoAmI () const {
    User::whoAmI();
    std::cout<< "And you work in: " << bankName << '\n';
}

void Employee::approveTask(size_t taskId) {
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].getId() == taskId) {
            tasks[i].approve();
            return;
        }
    }
    throw std::runtime_error("Task not found.");
}

void Employee::disapproveTask(size_t taskId, const MyString& message) {
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].getId() == taskId) {
            tasks[i].reject(message);
            return;
        }
    }
    throw std::runtime_error("Task not found.");
}

void Employee::validateTask(size_t taskId) {
    for (size_t i = 0; i < tasks.getSize(); ++i) {
        if (tasks[i].getId() == taskId) {
            tasks[i].validate();
            return;
        }
    }
    throw std::runtime_error("Task not found.");
}

void Employee::help() const {
    // implementation
}
