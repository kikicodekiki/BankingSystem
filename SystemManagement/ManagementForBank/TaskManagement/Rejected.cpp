#include "TaskState.h"
#include "Task.h"
#include <iostream>

void Rejected::approve(Task& task) {
    std::cout << "Cannot approve a rejected task.\n";
}

void Rejected::reject(Task& task, const MyString& message) {
    std::cout << "Task is already rejected.\n";
}
