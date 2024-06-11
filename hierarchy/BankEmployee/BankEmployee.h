#pragma once
#include "MyString.h"
#include "IBankEmployee.h"
#include "User.h"

#include "Vector.h"
#include "Client.h"

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

class BankEmployee : public User, public virtual IBankEmployee {
public:
    BankEmployee( const MyString& firstName, const MyString& surname, const MyString& EGN,
                  unsigned age, const MyString& password) :
                  User(firstName,surname,EGN,age,password) {}
private:

    //сравняваме спрямо това чий сайз е най-малкия -> той изпълнява поръчката
    Vector<Task> tasks;
    size_t taskCounter = 0;

};


