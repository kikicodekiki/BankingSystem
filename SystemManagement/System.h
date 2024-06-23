#pragma once
#include "CommandFactory.h"
#include "Application.h"

class System {
public:
    static void executeCommand(const MyString& command, const Vector<MyString>& args) {
        Application& app = Application::getInstance();
        ICommand* cmd = nullptr;

        if (app.getLoggedType() == UserType::Client) {
            if (command == "check_avl" && args.getSize() == 2) {
                cmd = CommandFactory::createCheckBalanceCommand(args[0], args[1], app.getLoggedUser()->getId());
            } else if (command == "open" && args.getSize() == 1) {
                cmd = CommandFactory::createOpenAccountCommand(args[0], app.getLoggedUser()->getId());
            } else if (command == "close" && args.getSize() == 2) {
                cmd = CommandFactory::createCloseAccountCommand(args[0], args[1], app.getLoggedUser()->getId());
            } else if (command == "change" && args.getSize() == 3) {
                cmd = CommandFactory::createChangeAccountBankCommand(args[0], args[1], args[2], app.getLoggedUser()->getId());
            } else if (command == "redeem" && args.getSize() == 3) {
                cmd = CommandFactory::createRedeemCheckCommand(args[0], args[1], args[2], app.getLoggedUser()->getId());
            }
        } else if (app.getLoggedType() == UserType::Employee) {
            if (command == "approve" && args.getSize() == 1) {
                cmd = CommandFactory::createApproveTaskCommand(args[0], app.getLoggedUser()->getId());
            } else if (command == "disapprove" && args.getSize() == 2) {
                cmd = CommandFactory::createDisapproveTaskCommand(args[0], args[1], app.getLoggedUser()->getId());
            } else if (command == "validate" && args.getSize() == 1) {
                cmd = CommandFactory::createValidateTaskCommand(args[0], app.getLoggedUser()->getId());
            }
        } else if (app.getLoggedType() == UserType::ExternalEmployee) {
            if (command == "send_check" && args.getSize() == 3) {
                double sum = std::stod(args[0].c_str());
                cmd = CommandFactory::createSendCheckCommand(sum, args[1], args[2], app.getLoggedUser()->getId());
            }
        }

        if (cmd) {
            cmd->execute();
            delete cmd;
        } else {
            std::cout << "Unknown command or incorrect arguments.\n";
        }
    }
};
