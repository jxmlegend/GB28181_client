#include "registfactory.h"
#include "ExosipServer.h"
#include <iostream>
#include <string>
using namespace std;
RegistFactory::RegistFactory()
{

}

int RegistFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
{

    if(controlComm == ExosipServer::REGIST)
    {;}
    else
        expires = 0;
    ExosipServer *server = ExosipServer::GetTheServer();
    server->m_expires = expires;

    osip_message_t *m_register = NULL;
    int register_id = -1;

    char contact[100];
    memset(contact, 0, sizeof contact);
    sprintf(contact, "sip:%s@%s:%s", server->m_serverInfo->m_ID.c_str(), server->m_serverInfo->m_Ip.c_str(), server->m_serverInfo->m_Port.c_str());
    cout << "contact: " << contact << endl;

    eXosip_lock(server->m_server);
    register_id = eXosip_register_build_initial_register(server->m_server, server->GetFromHeader().c_str(),
                                                         server->GetToHeader(id).c_str(), contact, expires, &m_register);
    if(register_id < 0)
    {
        eXosip_unlock(server->m_server);
        cout << "register initial fail..." << register_id << endl;
        return -1;
    }
    else
    {
        cout << "register initial success..." << endl;
    }

    int ret = 0;
    ret = eXosip_register_send_register(server->m_server, register_id, m_register);
    if(ret != OSIP_SUCCESS)
    {
        cout << "send register fail" << endl;
    }
    else
    {
        cout << "send register success" << endl;
    }

    eXosip_unlock(server->m_server);
    return ret;

}
RegistFactory::~RegistFactory()
{

}
