#pragma once
#include "MyString.h"
#include <fstream>

const size_t EGN_SIZE = 10;


class User {
public:
    User() = default;
    User(const MyString& name, const MyString& surname, const MyString& EGN, size_t age, const MyString& password);
    virtual ~User() = default;

    virtual void whoAmI() const;
    bool authenticate(const MyString& username, const MyString& password) const;
    MyString getFullName () const;

    virtual void saveToFile(std::ofstream& ofs) const;
    virtual void readFromFile(std::ifstream& ifs);
    virtual User* clone() const = 0;

    virtual void help() const = 0;

    int getId ()const {return id;}

    const size_t* getEgn() const {return EGN;}

protected:
    MyString name;
    MyString surname;
    size_t EGN[EGN_SIZE];
    size_t age = 1;
    MyString password;
    int id = 0;
    static int currId;

    void setEGN(const MyString& EGN);
    void setPassword(const MyString& password);
};
