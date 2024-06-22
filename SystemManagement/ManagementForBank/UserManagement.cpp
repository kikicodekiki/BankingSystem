#include "UserManagement.h"

void UserManagement::addUser(Polymorphic_Ptr<User> user) {
    users.pushBack(std::move(user));
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
