#pragma once
#include "PolymorphicPtr.h"
#include "User.h"


class IUserManagement {
public:

    virtual void addUser(Polymorphic_Ptr<User> user) = 0;
    virtual Polymorphic_Ptr<User> findUser (const MyString& EGN) const = 0;

    virtual ~IUserManagement() = default;
};
