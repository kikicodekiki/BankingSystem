
#include "User.h"



#include "MyString.h"
#include "Vector.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

int User::currId = 1;

User::User(const MyString& name, const MyString& surname, const MyString& EGN, size_t age, const MyString& password)
        : name(name), surname(surname), age(age) {
    setEGN(EGN);
    setPassword(password);
    id = currId++;
}

void User::whoAmI() const {
    std::cout << "Name: " << name.c_str() << " " << surname.c_str() << "\n";
    std::cout << "EGN: ";
    for (size_t i = 0; i < EGN_SIZE; ++i) {
        std::cout << EGN[i];
    }
    std::cout << "\nAge: " << age << "\n";
}

bool User::authenticate(const MyString& username, const MyString& password) const {
    return (name + " " + surname) == username && this->password == password;
}

void User::saveToFile(std::ofstream& ofs) const {
    name.saveToFile(ofs);

    surname.saveToFile(ofs);

    ofs.write((const char*)&EGN, sizeof(EGN));
    ofs.write((const char*)&age, sizeof(age));

    password.saveToFile(ofs);
}

void User::readFromFile(std::ifstream& ifs) {
    name.readFromFile(ifs);

    surname.readFromFile(ifs);

    ifs.read((char*)&EGN, sizeof(EGN));
    ifs.read((char*)&age, sizeof(age));

    password.readFromFile(ifs);
}

void User::setEGN(const MyString& EGN) {
    if (EGN.getSize() != EGN_SIZE) {
        throw std::invalid_argument("EGN must be exactly 10 digits long.");
    }
    for (size_t i = 0; i < EGN_SIZE; ++i) {
        this->EGN[i] = EGN[i] - '0';
    }
}

void User::setPassword(const MyString& password) {
    if (password == (name + surname)) {
        throw std::invalid_argument("The password should differ from your username.");
    }
    this->password = password;
}

MyString User::getFullName() const {
    return name + " " + surname;
}
