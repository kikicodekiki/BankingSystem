
#include "ExternalEmployee.h"



ExternalEmployee::ExternalEmployee(const MyString &firstName, const MyString &lastName,
                                   const MyString &EGN, size_t age,
                                   const MyString &password) :
        User(firstName, lastName, EGN, age, password){}


ExternalEmployee::ExternalEmployee(MyString &&firstName, MyString &&lastName,
                                   MyString &EGN, size_t age,
                                   MyString &&password) :
        User(std::move(firstName), std::move(lastName), std::move(EGN), age, std::move(password)){}


void ExternalEmployee::help() const {
    //implementation
}


void ExternalEmployee:: saveToFile(std::ofstream& ofs) const {
    //implementation
}
void ExternalEmployee::readFromFile(std::ifstream& ifs){
    //implementation
}


