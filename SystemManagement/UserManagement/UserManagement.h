#pragma once
#include "IUserManagment.h"
#include "PolymorphicPtr.h"
#include "User.h"
#include "Vector.h"
#include "MyString.h"
#include "Client.h"
#include "BankEmployee.h"
class UserManagement : public IUserManagement {
public:
    void addUser(Polymorphic_Ptr<User> user) override;

    Polymorphic_Ptr<User> findUser(const MyString& egn) const override;
    Polymorphic_Ptr<User> findUserByEgnArray ( const size_t egn[EGN_SIZE] )const override;
    Client* findClientById (int clientId) ;

    BankEmployee* findLeastBusyEmployee();
    const BankEmployee* findLeastBusyEmployee() const;

    Vector<Polymorphic_Ptr<User>> getUsers() const {
        return users;
    }

private:
    Vector<Polymorphic_Ptr<User>> users;

    int clientsCount = 0;
    int employeesCount = 0;

    int findUserIndex(const MyString& EGN) const;
};
