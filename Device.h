#pragma once
#include "eXosip2\eXosip.h"
#include <iostream>
#include <string>
struct DeviceInfo
{
	std::string m_Ip; //�豸��ip
	std::string m_Port; //�豸�Ķ˿ں�
	int m_iPort;
	std::string m_ID;	//�豸��ID
	std::string m_domain; //�豸������
	bool isAuthNull;
	//authorization��Ϣ
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
	DeviceInfo *GetDeviceInfo();//��ȡ�豸����Ϣ
	int SetDeviceBaseInfo(osip_message_t *msg);//�����豸����Ϣ
	int SetDeviceAuthInfo(osip_authorization_t *auth);
	int SetDeviceInfo(osip_message_t *msg);
	bool isAuthNull();

	~Device();
private:
	DeviceInfo *m_Info = nullptr;//�豸����Ϣ
};

