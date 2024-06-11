#pragma once
#include "IUser.h"
#include "MyString.h"

class User : public virtual IUser  {
public:

    User (const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age, const MyString& password );
    void whoAmI() const override;
    void exit() override;

    //not overriding the help function
private:
    MyString firstName;
    MyString surname;
    MyString password;

    unsigned EGN[10]; //will be string in the constructor

    unsigned age;

    void setEGN ();


};
