#pragma once
#include "ICommand.h"



class ClientCommand : public ICommand {
public:
    ClientCommand(int clientId) : clientId(clientId) {}
protected:
    int clientId;
};
