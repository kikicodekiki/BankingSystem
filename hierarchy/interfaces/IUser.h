#pragma once

class IUser {
public:
    virtual void exit() = 0;
    virtual void whoAmI() const = 0;
    virtual void help() const = 0;

    virtual ~IUser() = default;
};
