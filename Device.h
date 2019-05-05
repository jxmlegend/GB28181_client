#pragma once
#include "eXosip2\eXosip.h"
#include <iostream>
#include <string>
struct DeviceInfo
{
	std::string m_Ip; //设备的ip
	std::string m_Port; //设备的端口号
	int m_iPort;
	std::string m_ID;	//设备的ID
	std::string m_domain; //设备的域名
	bool isAuthNull;
	//authorization信息
	std::string m_authUserName;
	std::string m_authAlgorithm;
	std::string m_authrealm;
	std::string m_authnonce;
	std::string m_authResponse;
	std::string m_authUri;
    std::string m_passwd;

};
class Device
{
public:
	Device();
	DeviceInfo *GetDeviceInfo();//获取设备的信息
	int SetDeviceBaseInfo(osip_message_t *msg);//设置设备的信息
	int SetDeviceAuthInfo(osip_authorization_t *auth);
	int SetDeviceInfo(osip_message_t *msg);
	bool isAuthNull();

	~Device();
private:
	DeviceInfo *m_Info = nullptr;//设备的信息
};

