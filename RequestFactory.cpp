#include "RequestFactory.h"
#include "eXosip2\eXosip.h"
#include "ExosipServer.h"
#include <iostream>
using namespace std;


RequestFactory::RequestFactory()
{
}


RequestFactory::~RequestFactory()
{
}

int RequestFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
{
	int ret = -1;
	char body[2048] = "";
    osip_message_t *msg = nullptr;
	ExosipServer *server = ExosipServer::GetTheServer();
	if (!server->PlayBackConected())
		goto RESULT;

	if (controlComm == server->PLAY)
	{
        sprintf(body, "PLAY RTSP/1.0\r\n"
			"CSeq: 2\r\n"
			"Scale: 1.0\r\n"
            "Range: npt=15-20\r\n");
	}
	else if (controlComm == server->PAUSE)
	{
        sprintf(body, "PAUSE RTSP/1.0\r\n"
			"CSeq: 1\r\n"
            "PauseTime: 15\r\n");
	}
	else if (controlComm == server->FASTPLAY)
	{
		sprintf(body, "PLAY RTSP/1.0\r\n"
			"CSeq: 3\r\n"
			"Scale: 2.0\r\n"
			"Range: npt=0-20\r\n");
	}
	else if (controlComm == server->SLOWPLAY)
	{
		sprintf(body, "PLAY RTSP/1.0\r\n"
			"CSeq: 2\r\n"
			"Scale: 0.5\r\n"
			"Range: npt=0-20\r\n");
	}
    else if(controlComm == server->BYE)
    {
        cout << "bye build" << endl;
        eXosip_lock(server->m_server);
        ret = eXosip_call_build_request(server->m_server, server->m_videoDid, "BYE", &msg);
        if(ret >= 0)
        {
            cout << "bye build ok" << endl;
            ret = eXosip_call_send_request(server->m_server, server->m_videoDid, msg);
            if (ret >= 0)
                cout << " send success" << endl;


        }
        else
            cout << "bye fail" << endl;
        eXosip_unlock(server->m_server);
        return ret;
    }
	else
	{
		sprintf(body, "PLAY RTSP/1.0\r\n"
			"CSeq: 2\r\n"
			"Scale: 1.0\r\n"
			"Range: npt=15-20\r\n");
	}



	eXosip_lock(server->m_server);
	ret = eXosip_call_build_info(server->m_server, server->m_videoDid, &msg);

    //test
    cout << "video did: " << server->m_videoDid<< endl;

	if (ret != OSIP_SUCCESS)
	{
		cout << "invite initial fail" << endl;
		goto RESULT;
	}
	osip_message_set_content_type(msg, "Application/MANSRTSP");
    if(osip_message_set_body(msg, body, strlen(body)) >= 0)
        cout << "set body ok " << endl;
    else
        cout << "set body fail" << endl;
	ret = eXosip_call_send_request(server->m_server, server->m_videoDid, msg);
	if (ret >= 0)
		cout << " send success" << endl;

RESULT:
	eXosip_unlock(server->m_server);
	return ret;
}
