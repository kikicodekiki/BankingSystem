#pragma once
#include "MyString.h"
#include "IUser.h"
#include <fstream>

constexpr size_t EGN_SIZE = 10;

class User: public virtual IUser {
public :
    User() = default;
    User (const MyString& name, const MyString& surname,
          const MyString& EGN, size_t age,
          const MyString& password);
    User (MyString&& name, MyString&& surname,
          MyString&& EGN, size_t age,
          MyString&& password);

    virtual ~User() = default;

    void whoAmI() const override;

    bool authenticate (const MyString& username, const MyString& password) const;

    void saveToFile(std::ofstream& ofs) const override;
    void readFromFile(std::ifstream& ifs) override;

    virtual User* clone () const = 0;

    const size_t* getEgn() const {return EGN;}
    MyString getFullName () const;
    int getId () const {return id;}

protected:

    MyString name;
    MyString surname;
    size_t EGN[EGN_SIZE];
    size_t age = 1;
    MyString password;

    static int currId;

    int id;

    void setEGN (const MyString& EGN);
    void setPassword(const MyString& password);

};
