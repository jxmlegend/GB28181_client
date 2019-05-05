#include "InviteFactory.h"
#include "eXosip2\eXosip.h"
#include "ExosipServer.h"
#include <iostream>
using namespace std;


InviteFactory::InviteFactory()
{
}


InviteFactory::~InviteFactory()
{
}

int InviteFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
{
	ExosipServer *server = ExosipServer::GetTheServer();
	int ret = -1;
	char body[2048] = "";
	string comm;
	if (controlComm == server->PLAY_LIVE)
	{
		comm = "Play";
	}
	else if (controlComm == server->PLAYBACK)
	{
		comm = "Playback";
	}
    else if (controlComm == server->DOWNLOAD)
	{
		comm = "Download";
	}
	else
	{
		goto RESULT;
	}

	sprintf(body, "v=0\r\n"
		"o=%s 0 0 IN IP4 127.0.0.1\r\n"
		"s=%s\r\n"
		"u=%s:3\r\n"
		"c=IN IP4 %s\r\n"
		"t=1314378296 1314378896\r\n"
		"m=video %s RTP/AVP 96 98 97\r\n"
		"a=recvonly\r\n"
		"a=rtpmap:96 PS/90000\r\n"
		"a=rtpmap:98 H264/90000\r\n"
        "a=rtpmap:97 MPEG4/90000\r\n", server->m_serverInfo->m_ID.c_str(), comm.c_str(), id.c_str(), ip.c_str(), "5000");

	osip_message_t *msg = nullptr;
	eXosip_lock(server->m_server);
	ret = eXosip_call_build_initial_invite(server->m_server, &msg, server->GetToHeader(id).c_str(), server->GetFromHeader().c_str(), server->GetRouteHeade(id, ip, port).c_str(), "");
	//int eXosip_call_build_initial_invite (struct eXosip_t *excontext, osip_message_t ** invite, const char *to, const char *from, const char *route, const char *subject);
	if (ret != OSIP_SUCCESS)
	{
		cout << "invite initial fail" << endl;
		goto RESULT;
	}
	osip_message_set_content_type(msg, "application/sdp");
	osip_message_set_body(msg, body, strlen(body));
	ret = eXosip_call_send_initial_invite(server->m_server, msg);

RESULT:
	eXosip_unlock(server->m_server);
	return ret;

}
