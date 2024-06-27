#pragma once
#include "User.h"

#include "Vector.h"
#include "MyString.h"
#include <fstream>

class Client : public User {
public:
    Client() = default;
    Client(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age,
           const MyString& password, const MyString& address);
    Client(MyString&& firstName, MyString&& surname, MyString&& EGN, unsigned age,
           MyString&& password, MyString&& address);

    void check_avl(const MyString& bankName, const MyString& accountNumber) const ;
    void open(const MyString& bankName) ;
    void close(const MyString& bankName, const MyString& accountNumber) ;
    void redeem(const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode) ;
    void change(const MyString& newBankName, const MyString& currBank, const MyString& accNum) ;
    void list(const MyString& bankName) const ;
    void messages() const;

    void addAccount(const MyString& accountName);
    void addMessage(const MyString& message);

//    void saveToFile(std::ofstream& ofs) const ;
//    void readFromFile(std::ifstream& ifs) ;

    void help() const ;

    User* clone() const override {
        return new Client(*this);
    }

    Vector<MyString> getAccounts() const;
private:
    MyString address;
    //tuk trqbva da e vektor ot bank accounts
    Vector<MyString> messageInbox;
};

