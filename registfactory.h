#ifndef REGISTFACTORY_H
#define REGISTFACTORY_H
#include "CommFactory.h"

class RegistFactory : public CommFactory
{
public:
    RegistFactory();
    int SendComm(std::string id, int controlComm, std::string ip = "127.0.0.1", std::string port = "5060", int expires = 3600);
    ~RegistFactory();
};

#endif // REGISTFACTORY_H
