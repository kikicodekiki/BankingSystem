#pragma once
#include "User.h"
#include "IClient.h"
#include "Vector.h"
#include "MyString.h"
#include <fstream>

class Client : public User, public virtual IClient {
public:
    Client(const MyString& firstName, const MyString& surname, const MyString& EGN, unsigned age,
           const MyString& password, const MyString& address);
    Client(MyString&& firstName, MyString&& surname, MyString&& EGN, unsigned age,
           MyString&& password, MyString&& address);

    void check_avl(const MyString& bankName, const MyString& accountNumber) const override;
    void open(const MyString& bankName) override;
    void close(const MyString& bankName, const MyString& accountNumber) override;
    void redeem(const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode) override;
    void change(const MyString& newBankName, const MyString& currBank, const MyString& accNum) override;
    void list(const MyString& bankName) const override;
    void messages() const override;

    void addAccount(const MyString& accountName);
    void addMessage(const MyString& message);

    void saveToFile(std::ofstream& ofs) const override;
    void readFromFile(std::ifstream& ifs) override;

    void help() const override;

    User* clone() const override {
        return new Client(*this);
    }
    Vector<MyString> getAccounts() const;
private:
    MyString address;
    Vector<MyString> bankAccounts;
    Vector<MyString> messageInbox;
};
