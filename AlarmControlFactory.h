#pragma once
#include "CommFactory.h"
class AlarmControlFactory :
	public CommFactory
{
public:
	AlarmControlFactory();
	~AlarmControlFactory();

	// ͨ�� CommFactory �̳�
	virtual int SendComm(std::string id, int controlComm, std::string ip = "127.0.0.1", std::string port = "5060", int expires = 3600) override;
};

