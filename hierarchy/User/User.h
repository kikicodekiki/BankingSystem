#pragma once
#include "IUser.h"
#include "MyString.h"

class User : public virtual IUser  {
public:

    User (const MyString& firstName, const MyString& surname, const MyString& EGN,
          unsigned age, const MyString& password );
    User(MyString&& firstName, MyString&& lastName, MyString&& EGN,
         unsigned age, MyString&& password);

    User() = default;

    void whoAmI() const override;

    virtual void saveToFile(std::ofstream& ofs) const = 0;
    virtual void readFromFile(std::ifstream& ifs) = 0 ;

    virtual ~User() = default;
//    void exit() override;

    //not overriding the help function

protected:
    static int currId;

    int id = 0;

    MyString firstName;
    MyString surname;
    MyString password;

    unsigned EGN[10]; //will be string in the constructor

    unsigned age = 1;

    void setEGN (const MyString& EGN);
    void setPassword(const MyString& password);

};
