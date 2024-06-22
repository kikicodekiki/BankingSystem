#include "Client.h"
#include "Application.h"

Client ::Client (const MyString& firstName, const MyString& surname,
         const MyString& EGN, unsigned age, const MyString& password,
         const MyString& address) : User(firstName, surname, EGN, age, password ),
                                    address(address) {}

Client ::Client (MyString&& firstName, MyString&& surname, MyString&& EGN, unsigned age,
        MyString&& password, MyString&& address) : User(std::move(firstName),
                                                        std::move(surname),
                                                        std::move(EGN),
                                                        std::move(age),
                                                        std::move(password) ),
                                                        address(std::move(address)) {}

void Client::check_avl (const MyString& bankName, const MyString& accountNumber) const {
    Application& app = Application::getInstance();
    app.checkAccountBalance(bankName, accountNumber, id);
}

void Client::open (const MyString& bankName) {
    Application& app = Application::getInstance();
    app.openAccount(bankName, id);
}

void Client::close (const MyString& bankName, const MyString& accountNumber) {
    Application& app = Application::getInstance();
    app.closeAccount(bankName, accountNumber, id);
}

void Client::redeem (const MyString& bankName, const MyString& accountNumber, const MyString& verificationCode) {
    Application& app = Application::getInstance();
    app.redeemCheck(bankName,accountNumber,verificationCode, id);
}

void Client::change (const MyString& newBankName, const MyString& currBank, const MyString& accNum) {
    Application& app = Application::getInstance();
    app.changeAccountBank(newBankName, currBank, accNum, id);
}

void Client::list(const MyString& bankName) const {
    Application& app = Application::getInstance();
    app.listAccounts(bankName, id);
}

void Client::messages() const {
    for (size_t i = 0; i < messageInbox.getSize(); ++i) {
        std::cout << messageInbox[i] << std::endl;
    }
}

void Client::help() const {
    std::cout << "Available commands: check_avl, open, close, redeem, change, list, messages\n" ;
}

void Client::addAccount(const MyString& accountName) {
    bankAccounts.pushBack(accountName);
}

//void saveToFile(std::ofstream& ofs) const override;
//void readFromFile(std::ifstream& ifs) override;
