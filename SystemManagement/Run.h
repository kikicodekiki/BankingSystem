#pragma once
#include "Application.h"
#include "MyString.h"
#include "Vector.h"
#include <iostream>

class Run {
public:
    void run();
private:
    void createBank(const MyString& name);
    void signup();
    void login();
    void executeCommand(const MyString& command);
    void showHelp() const;
};
