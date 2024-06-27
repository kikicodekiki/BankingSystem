#pragma once
//#include "IUserManagment.h"
#include "PolymorphicPtr.h"
#include "User.h"
#include "Vector.h"
#include "MyString.h"
#include "Client.h"
//#include "BankEmployee.h"
#include <fstream>

class BankEmployee;

class UserManagement {
public:
    void addUser(Polymorphic_Ptr<User> user) ;

    Polymorphic_Ptr<User> findUser(const MyString& egn) const ;
    Polymorphic_Ptr<User> findUserByEgnArray ( const size_t egn[EGN_SIZE] )const ;
    Client* findClientById (int clientId) ;
    User* findUserByEgn (const MyString& egn);

    BankEmployee* findLeastBusyEmployee();
    const BankEmployee* findLeastBusyEmployee() const;

    Vector<Polymorphic_Ptr<User> > getUsers() const {
        return users;
    }

//    void saveToFile (std::ofstream& ofs) const;
//    void readFromFile (std::ifstream& ifs);


private:
    Vector<Polymorphic_Ptr<User> > users;

    int clientsCount = 0;
    int employeesCount = 0;

    int findUserIndex(const MyString& EGN) const;
};
