#include "User.h"
#include "Vector.h"

#include <iostream>

int User::currId = 1;

static Vector<unsigned> parseMyStringToUnsignedArr (const MyString& str) {
    Vector<unsigned> result;

    const char* cstr = str.c_str();
    char* end = nullptr;

    while (*cstr != '\0') {
        unsigned value = std::strtoul(cstr, &end, 10);

        if (cstr == end) {break;}

        result.pushBack(value);

        cstr = end;

        while (*cstr == ' ') {
            ++cstr;
        }
    }

    return result;
}

void User::setEGN (const MyString& EGN) {
    Vector<unsigned> parseEGN = parseMyStringToUnsignedArr(EGN);

    if (parseEGN.getSize() != 10) {
        throw std::invalid_argument("EGN must be exactly 10 digits long");
    }

    for (size_t i = 0; i < 10; i++) {
        this->EGN[i] = parseEGN[i];
    }
}

void User::setPassword(const MyString& password) {
    if (password == (firstName+surname)) {
        throw std::invalid_argument("The password should differ from your username");
    }

    this-> password = password;
}


User::User (const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age,
            const MyString& password ) : firstName(firstName), surname(surname)  {

    setEGN(EGN);

    this -> age = age;

    setPassword(password);

    id = currId++;

}

User::User(MyString&& firstName, MyString&& surname, MyString&& EGN, unsigned age, MyString&& password)
        : firstName(std::move(firstName)), surname(std::move(surname)), age(age), password(std::move(password))
        {
           id = currId++;
           setEGN(std::move(EGN));
}

void User ::whoAmI() const {
    std::cout << "You are: " << firstName << " " << surname << "\n";
}
