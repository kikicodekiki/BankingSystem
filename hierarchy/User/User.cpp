#pragma once
#include "User.h"
#include "MyString.h"
#include "Vector.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

int User::currId = 1;

static Vector<unsigned> parseMyStringToUnsignedArr(const MyString& str) {
    Vector<unsigned> result;

    const char* cstr = str.c_str();
    char* end = nullptr;

    while (*cstr != '\0') {
        unsigned value = std::strtoul(cstr, &end, 10);

        if (cstr == end) {
            break;
        }

        result.pushBack(value);

        cstr = end;

        while (*cstr == ' ') {
            ++cstr;
        }
    }

    return result;
}

void User::setEGN(const MyString& EGN) {
    Vector<unsigned> parseEGN = parseMyStringToUnsignedArr(EGN);

    if (parseEGN.getSize() != EGN_SIZE) {
        throw std::invalid_argument("EGN must be exactly 10 digits long\n");
    }

    for (size_t i = 0; i < EGN_SIZE; ++i) {
        this->EGN[i] = parseEGN[i];
    }
}

void User::setPassword(const MyString& password) {
    if (password == (name + surname)) {
        throw std::invalid_argument("The password should differ from your username");
    }

    this->password = password;
}

User::User (const MyString& name, const MyString& surname,
      const MyString& EGN, size_t age,
      const MyString& password) : name(name), surname(surname), age(age){

    setEGN(EGN);
    setPassword(password);
    id = currId++;
}


User :: User (MyString&& name, MyString&& surname,
        MyString&& EGN, size_t age,
        MyString&& password) : name (std::move(name)), surname(std::move(surname)), age(age){
    setEGN(std::move(EGN));
    setPassword(std::move(password));
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
    return getFullName() == username && this->password == password;
}

MyString User::getFullName() const {
    return name + " " + surname;
}


void User::saveToFile(std::ofstream& ofs) const {
    ofs << name << '\n' << surname << '\n' << age << '\n' << password << '\n';
    for (size_t i = 0; i < EGN_SIZE; ++i) {
        ofs << EGN[i];
    }
    ofs << '\n';
}
