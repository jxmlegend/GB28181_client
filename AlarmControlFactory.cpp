#include "AlarmControlFactory.h"
#include "eXosip2\eXosip.h"
#include "ExosipServer.h"
#include <iostream>
using namespace std;


AlarmControlFactory::AlarmControlFactory()
{
}


AlarmControlFactory::~AlarmControlFactory()
{
}

int AlarmControlFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
{
	int ret = -1;
	char xml_body[1024] = "";
	ExosipServer *server = ExosipServer::GetTheServer();
	if (server->DeviceMap.find(id) == server->DeviceMap.end())
	{
		cout << "Device Not exist: " << id << endl;
	}

	osip_message_t *msg = nullptr;
	eXosip_lock(server->m_server);
	ret = eXosip_message_build_request(server->m_server, &msg, "MESSAGE", server->GetToHeader(id).c_str(), server->GetFromHeader().c_str(), server->GetRouteHeade(id, ip, port).c_str());
	if (ret != OSIP_SUCCESS)
		goto RESULT;
	osip_message_set_content_type(msg, "Application/MANSCDP+xml");

	if (controlComm == server->DEPLOY)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Control>\r\n"
			"<CmdType>DeviceControl</CmdType>\r\n"
			"<SN>17294</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<GuardCmd>SetGuard</GuardCmd>\r\n"
			"</Control>\r\n", id.c_str());
	}
	else if (controlComm == server->ALARM)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Notify>\r\n"
			"<CmdType>Alarm</CmdType>\r\n"
			"<SN>1</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<AlarmPriority>4</AlarmPriority>\r\n"
			"<AlarmTime>2009-12-04T16:23:32</AlarmTime>\r\n"
			"<AlarmMethod>2</AlarmMethod>\r\n"
			"</Notify>\r\n", id.c_str());
	}
	else if (controlComm == server->CANCLE_DEPLOY)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Control>\r\n"
			"<CmdType>DeviceControl</CmdType>\r\n"
			"<SN>17294</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<GuardCmd>ResetGuard</GuardCmd>\r\n"
			"</Control>\r\n", id.c_str());
	}
	else if (controlComm == server->ALARM_RET)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Control>\r\n"
			"<CmdType>DeviceControl</CmdType>\r\n"
			"<SN>17438</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<AlarmCmd>ResetAlarm</AlarmCmd>\r\n"
			"<Info>\r\n"
			"<AlarmMethod>2</AlarmMethod>\r\n"
			"</Info>\r\n"
			"</Control>\r\n", id.c_str());
	}
	else
	{
	}


	osip_message_set_body(msg, xml_body, strlen(xml_body));

	ret = eXosip_message_send_request(server->m_server, msg);
	if (ret > 0)
		ret = server->CONTROL_SUCCESS;
	else
		cout << "send control fail" << ret << endl;

RESULT:
	//osip_message_free(msg);
	eXosip_unlock(server->m_server);
	return ret;
}
