#pragma once
#include "IExternalCompanyEmployee.h"
#include "User.h"
#include "Pair.h"



struct BankCheck{
    Pair<char[3], double> check;
};



class ExternalCompanyEmployee : public User, public virtual IExternalEmployee{
public :
    void send_check (double sum, const MyString& bankName, const MyString& EGN) override;
private:

};
