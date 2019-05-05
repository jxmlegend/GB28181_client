#include "Device.h"
using namespace std;


Device::Device()
{
	if (m_Info == nullptr)
		m_Info = new DeviceInfo();
}

DeviceInfo * Device::GetDeviceInfo()
{
	// TODO: 在此处插入 return 语句
	return m_Info;
}

int Device::SetDeviceBaseInfo(osip_message_t *msg)
{
	int ret = -1;
	osip_contact_t *contact = nullptr;
	if (msg == nullptr || m_Info == nullptr)
		goto RESULT;

	osip_message_get_contact(msg, 0, &contact);
	m_Info->m_domain = string(msg->from->url->host);
	m_Info->m_ID = string(msg->from->url->username);
	m_Info->m_Port = string(contact->url->port);
	m_Info->m_iPort = -1;
	m_Info->m_Ip = string(contact->url->host);
	m_Info->isAuthNull = true;
	osip_contact_free(contact);
RESULT:

	return ret;
}

int Device::SetDeviceAuthInfo(osip_authorization_t *auth)
{
	//设置authorization信息
	if (auth == nullptr || m_Info == nullptr)
		goto RESULT;

	m_Info->m_authAlgorithm = auth->algorithm;
	m_Info->m_authnonce = auth->nonce;
	m_Info->m_authrealm = auth->realm;
	m_Info->m_authResponse = auth->response;
	m_Info->m_authUri = auth->uri;
	m_Info->m_authUserName = auth->username;
	m_Info->isAuthNull = false;

RESULT:
	return 0;
}

int Device::SetDeviceInfo(osip_message_t * msg)
{
	int ret = -1;
	osip_authorization_t *auth = nullptr;
	if (msg == nullptr)
		goto RESULT;

	ret = SetDeviceBaseInfo(msg);
	osip_message_get_authorization(msg, 0, &auth);
	if (auth != nullptr)
	{
		SetDeviceAuthInfo(auth);
	}

RESULT:
	return ret;
}

bool Device::isAuthNull()
{
	return m_Info->isAuthNull;
}

Device::~Device()
{

}

