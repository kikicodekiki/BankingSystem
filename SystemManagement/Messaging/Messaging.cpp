#pragma once
#include "Messaging.h"

void Messaging::sendMessage(const MyString& userEgn, const MyString& message) {
    int index = findUserMessagesIndex(userEgn);
    if (index == -1) {
        userEgns.pushBack(userEgn);
        Vector<MyString> messages;
        messages.pushBack(message);
        userMessages.pushBack(messages);
    } else {
        userMessages[index].pushBack(message);
    }
}

Vector<MyString> Messaging::getMessages(const MyString& userEgn) const {
    int index = findUserMessagesIndex(userEgn);
    if (index == -1) {
        return Vector<MyString>();
    }
    return userMessages[index];
}

int Messaging::findUserMessagesIndex(const MyString& userEgn) const {
    for (size_t i = 0; i < userEgns.getSize(); ++i) {
        if (userEgns[i] == userEgn) {
            return i;
        }
    }
    return -1;
}
