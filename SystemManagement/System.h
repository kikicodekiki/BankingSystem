#pragma once
#include "Application.h"
#include "CheckBalannceCommand.h"
#include "OpenAccountCommand.h"
#include "CloseAccountCommand.h"
#include "ListAccountCommands.h"
class System {
public:
    static void executeCommand (const MyString& command, const Vector<MyString> args) {

        Application& app = Application::getInstance();

        if (command == "check_avl" && args.getSize() == 2) {
            CheckBalanceCommand checkBalanceCmd(args[0], args[1], app.getLoggedUser()->getId());
            checkBalanceCmd.execute();
        } else if (command == "open" && args.getSize() == 1) {
            OpenAccountCommand openAccountCmd(args[0], app.getLoggedUser()->getId());
            openAccountCmd.execute();
        } else if (command == "close" && args.getSize() == 2) {
            CloseAccountCommand closeAccountCmd(args[0], args[1], app.getLoggedUser()->getId());
            closeAccountCmd.execute();
        } else if (command == "list" && args.getSize() == 1) {
            ListAccountCommand listAccountsCmd(args[0], app.getLoggedUser()->getId());
            listAccountsCmd.execute();
        } else {
            std::cout << "Unknown command or incorrect arguments.\n";
        }
    }
};
