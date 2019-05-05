#include "RecordControlFactory.h"
#include "eXosip2\eXosip.h"
#include "ExosipServer.h"
#include <iostream>
using namespace std;
RecordControlFactory::RecordControlFactory()
{
}


RecordControlFactory::~RecordControlFactory()
{
}

int RecordControlFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
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

	if (controlComm == server->RECORD)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Control>\r\n"
			"<CmdType>DeviceControl</CmdType>\r\n"
			"<SN>17</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<RecordCmd>Record</RecordCmd>\r\n"
			"</Control>\r\n", id.c_str());
	}
	else if (controlComm == server->STOP_RECORD)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Control>\r\n"
			"<CmdType>DeviceControl</CmdType>\r\n"
			"<SN>17</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<RecordCmd>StopRecord</RecordCmd>\r\n"
			"</Control>\r\n", id.c_str());
	}
	else if (controlComm == server->RECORD_QUERY)
	{
		sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
			"<Query>\r\n"
			"<CmdType>RecordInfo</CmdType>\r\n"
			"<SN>17430</SN>\r\n"
			"<DeviceID>%s</DeviceID>\r\n"
			"<StartTime>2010-11-11T19:46:17</StartTime>\r\n"
			"<EndTime>2010-11-12T19:46:17</EndTime>\r\n"
			"<FilePath>64010000002100000001</FilePath>\r\n"
			"<Address>Address1</Address>\r\n"
			"<Secrecy>0</Secrecy>\r\n"
			"<Type>time</Type>\r\n"
			"<RecorderID>64010000003000000001</RecorderID>\r\n"
			"</Query>\r\n", id.c_str());
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
