#pragma once
#include <fstream>
class IUser {
public:
//    virtual void exit() = 0;
    virtual void whoAmI() const = 0;
    virtual void help() const = 0;

    virtual void saveToFile(std::ofstream ofs) const = 0;
    virtual void readFromFile(std::ifstream& ifs) = 0;

    virtual ~IUser() = default;
};
