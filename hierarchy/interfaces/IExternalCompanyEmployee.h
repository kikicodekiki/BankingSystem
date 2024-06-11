#pragma once
#include "MyString.h"
class IExternalEmployee {
public :
    virtual void send_check (double sum, const MyString& bankName, const MyString& EGN) = 0;
    virtual ~IExternalEmployee() = 0;
};
