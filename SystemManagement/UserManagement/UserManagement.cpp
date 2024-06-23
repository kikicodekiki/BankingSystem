#include "UserManagement.h"

void UserManagement::addUser(Polymorphic_Ptr<User> user) {
    if(dynamic_cast<Client*>(user.get())) {
        users.pushBack(std::move(user));
        clientsCount++;
    }

    else if(dynamic_cast<BankEmployee*>(user.get())) {
        users.pushBack(std::move(user));
        employeesCount++;
    }
}


Polymorphic_Ptr<User> UserManagement::findUser(const MyString& egn) const {
    int index = findUserIndex(egn);
    if (index != -1) {
        return users[index];
    }
    return nullptr;
}

int UserManagement::findUserIndex(const MyString& egn) const {
    for (size_t i = 0; i < users.getSize(); ++i) {

        const size_t* userEgn = users[i]->getEgn();
        bool match = true;

        for (size_t j = 0; j < 10; ++j) {
            if (userEgn[j] != egn[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;
}

Polymorphic_Ptr<User> UserManagement::findUserByEgnArray ( const size_t egn[EGN_SIZE] )const {
    for (size_t i = 0; i < users.getSize(); ++i) {
        const size_t* userEgn = users[i]->getEgn();
        bool match = true;
        for (size_t j = 0; j < EGN_SIZE; ++j) {
            if (userEgn[j] != egn[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return users[i];
        }
    }
    return nullptr;
}

BankEmployee* UserManagement::findLeastBusyEmployee() {
    BankEmployee* leastBusyEmployee = nullptr;

    for (size_t i = 0; i < users.getSize(); i++) {
        BankEmployee* employee = dynamic_cast<BankEmployee*>(users[i].get());
        if (employee) {
            if (!leastBusyEmployee || employee->getTaskCount() < leastBusyEmployee->getTaskCount()) {
                leastBusyEmployee = employee;
            }
        }
    }
    return leastBusyEmployee;
}

const BankEmployee* UserManagement::findLeastBusyEmployee() const {

    return const_cast<UserManagement*>(this)->findLeastBusyEmployee();
}

Client* UserManagement::findClientById (int clientId)  {
    for (size_t i = 0; i < users.getSize(); ++i) {
        Client* client = dynamic_cast<Client*>(users[i].get());
        if (client && client->getId() == clientId) {
            return client;
        }
    }
    return nullptr;
}
