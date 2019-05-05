#include "CameraControlFactory.h"
#include "ExosipServer.h"
#include <iostream>
#include <string>
using namespace std;


CameraControlFactory::CameraControlFactory()
{
}


CameraControlFactory::~CameraControlFactory()
{
}

int CameraControlFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
{
	ExosipServer *Server = ExosipServer::GetTheServer();
	int ret = -1;
	char command[64] = "";
	char xml_body[1024] = "";
	if (Server->DeviceMap.find(id) == Server->DeviceMap.end())
	{
		cout << "Device Not exist: " << id << endl;
	}

	osip_message_t *msg = nullptr;
	eXosip_lock(Server->m_server);
	ret = eXosip_message_build_request(Server->m_server, &msg, "MESSAGE", Server->GetToHeader(id).c_str(), Server->GetFromHeader().c_str(), Server->GetRouteHeade(id, ip, port).c_str());
	if (ret != OSIP_SUCCESS)
		goto RESULT;
	osip_message_set_content_type(msg, "Application/MANSCDP+xml");

	switch (controlComm) {
	case ExosipServer::LEFT:
		sprintf(command, "A50F01021F0000D6");
		break;
	case ExosipServer::RIGHT:
		sprintf(command, "A50F01011F0000D5");
		break;
	case ExosipServer::UP:
		sprintf(command, "A50F0108001F00DC");
		break;
	case ExosipServer::DOWN:
		sprintf(command, "A50F0104001F00D8");
		break;
	case ExosipServer::ZOOMLARGE:
		sprintf(command, "A50F0110000010D5");
		break;
	case ExosipServer::ZOOMLITTLE:
		sprintf(command, "A50F0120000010E5");
		break;
	case ExosipServer::STOP_CONTROL:
		sprintf(command, "A50F0100000000B5");
		break;
	default:
		sprintf(command, "A50F01021F0000D6");
	}

	sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
		"<Control>\r\n"
		"<CmdType>DeviceControl</CmdType>\r\n"
		"<SN>11</SN>\r\n"
		"<DeviceID>34020000001320000001</DeviceID>\r\n"
		"<PTZCmd>%s</PTZCmd>"
		"</Control>\r\n", command);
	osip_message_set_body(msg, xml_body, strlen(xml_body));

	ret = eXosip_message_send_request(Server->m_server, msg);
	if (ret > 0)
		ret = Server->CONTROL_SUCCESS;
	else
		cout << "send control fail" << ret << endl;

RESULT:
	//osip_message_free(msg);
	eXosip_unlock(Server->m_server);
	return ret;
}
