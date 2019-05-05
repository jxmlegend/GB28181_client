#pragma once
#include <string>
class CommFactory
{
public:
	CommFactory();
    virtual int SendComm(std::string id, int controlComm, std::string ip = "192.168.1.220", std::string port = "5060", int expires = 3600) = 0;
	virtual ~CommFactory() = 0;
};

