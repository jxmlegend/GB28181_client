#pragma once
#include "CommFactory.h"
class DeviceControlFactory :
	public CommFactory
{
public:
	DeviceControlFactory();
	~DeviceControlFactory();

	// ͨ�� CommFactory �̳�
    virtual int SendComm(std::string id, int controlComm, std::string ip = "192.168.1.220", std::string port = "5060", int expires = 3600) override;
};

