#include "ExosipServer.h"
#include <iostream>
#include <winsock.h>
using namespace std;

void ExosipServer::ListenThread()
{
    ExosipServer::GetTheServer()->ServerListen();
}

ExosipServer::ExosipServer(std::string ip, std::string port, int iport, std::string domain, std::string id)
{
    if (m_serverInfo == nullptr)
    {
        m_serverInfo = new DeviceInfo;//初始化服务器信息
        m_serverInfo->m_Ip = ip;
        m_serverInfo->m_domain = domain;
        m_serverInfo->m_Port = port;
        m_serverInfo->m_iPort = iport;
        m_serverInfo->m_ID = id;
        m_serverInfo->m_passwd = "12345678";
        m_serverInfo->m_authAlgorithm = "MD5";
    }
}
ExosipServer::ExosipServer(const ExosipServer & server)
{
}
ExosipServer & ExosipServer::operator=(const ExosipServer & server)
{
    return *this;
}
ExosipServer::~ExosipServer()
{

    if (m_serverInfo != nullptr)
    {
        delete m_serverInfo;
        m_serverInfo = nullptr;
    }
    if (m_server != nullptr)
    {
        eXosip_quit(m_server);
        m_server = nullptr;
    }
    if (m_factory != nullptr)
    {
        delete m_factory;
        m_factory = nullptr;
    }
    if (m_listenThread != nullptr)
    {
        delete m_listenThread;
        m_listenThread = nullptr;
    }
}

ExosipServer * ExosipServer::GetTheServer()
{
    static ExosipServer server;
    return &server;
}

int ExosipServer::ServerInit()
{
    int ret = INIT_FAIL;

    m_server = eXosip_malloc();
    if (eXosip_init(m_server) == OSIP_SUCCESS && m_serverInfo != nullptr)
    {
        eXosip_set_option(m_server, EXOSIP_OPT_SET_IPV4_FOR_GATEWAY, m_serverInfo->m_Ip.c_str());
        if (eXosip_listen_addr(m_server, IPPROTO_UDP, nullptr, m_serverInfo->m_iPort, AF_INET, 0) == OSIP_SUCCESS)
        {
            ret = INIT_SUCCESS;
            m_factory = new GetFactory();
            m_listenThread = new thread(ListenThread);
        }

        else
        {
            eXosip_quit(m_server);
            //osip_free(m_server);
            m_server = nullptr;
        }
    }
    else
    {
        eXosip_quit(m_server);
        //osip_free(m_server);
        m_server = nullptr;
    }

    return ret;
}

int ExosipServer::ServerListen(int m, int s)
{
    int ret = -1;
    bool flag = true;
    int regist_id = -1;
    osip_www_authenticate_t *pauth = nullptr;
    osip_message_t *pregist = nullptr;
    osip_message_t *msg = nullptr;
    osip_body_t *msg_body = nullptr;
    if (m_server == nullptr)
        goto RESULT;


    while (flag)
    {
        if(m_server == nullptr)
            cout << "server is null" << endl;
        m_event = eXosip_event_wait(m_server, m, s);

        if (m_event == nullptr)
        {
            cout << "time out..." << endl;
            continue;
        }
        cout << "let's go..." << endl;
        eXosip_lock(m_server);
        cout << "we come!" << endl;
        switch (m_event->type)
        {
        case EXOSIP_REGISTRATION_SUCCESS:
            cout << "EXOSIP_REGISTRATION_SUCCESS" << endl;
            break;
        case EXOSIP_CALL_INVITE:
            cout << "EXOSIP_CALL_INVITE" << endl;
            eXosip_call_build_answer(m_server, m_event->tid, 200, &msg);
            eXosip_call_send_answer(m_server, m_event->tid, 200, msg);
            break;
        case EXOSIP_REGISTRATION_FAILURE:
            //接收到401回复
            //获取authInfo
            cout << "regist 401 fail:line: " << __LINE__ << endl;
            if(m_event->response == nullptr)
            {
                cout << "response is null" << endl;
                break;
            }
            osip_message_get_www_authenticate(m_event->response, 0, &pauth);
            if(pauth == nullptr)
            {
                cout << "get auth fail" << endl;
                break;
            }
            m_serverInfo->m_authrealm = osip_www_authenticate_get_realm(pauth);
            ret = eXosip_add_authentication_info(m_server, m_serverInfo->m_ID.c_str(), m_serverInfo->m_ID.c_str(), m_serverInfo->m_passwd.c_str(),
                                           m_serverInfo->m_authAlgorithm.c_str(), m_serverInfo->m_authrealm.c_str());
            if(ret < 0)
            {
                cout << "add auth info fail" << __LINE__ << endl;
            }
            else
            {
                cout << "add auth info success " << endl;
            }
            regist_id = eXosip_register_build_register(m_server, m_event->rid, m_expires, &pregist);
            if(regist_id < 0)
            {
                cout << "regist build faile" << __LINE__ << endl;
            }
            else
            {
                if(eXosip_register_send_register(m_server, m_event->rid, pregist) >= 0)
                {
                    cout << "send rgister ok" << endl;
                }
                else
                    cout << "send regist fail" << __LINE__ << endl;
            }
            break;
        case EXOSIP_MESSAGE_NEW://收到一条新的message，判断其是否是registe请求
            //PrintMsg(m_event->request);
            if (!strcmp(m_event->request->cseq->method, "REGISTER"))//这是一条注册请求
            {
                //将请求注册的设备信息，存储
                if (m_tmpDevice != nullptr)
                {
                    delete m_tmpDevice;
                    m_tmpDevice = nullptr;
                }
                m_tmpDevice = new Device();
                m_tmpDevice->SetDeviceInfo(m_event->request);
                ret = SendRegisteAnswer();
            }
            else
            {
                cout << "EXOSIP_MESSAGE_NEW" << endl;
                osip_message_get_body(m_event->request, 0, &msg_body);
                cout << msg_body->body << endl;
                eXosip_message_build_answer(m_server, m_event->tid, 200, &msg);
                eXosip_message_send_answer(m_server, m_event->tid, 200, msg);
            }
            break;
        case EXOSIP_MESSAGE_ANSWERED:
            cout << "Get Message Answered" << endl;
            if (m_event->response->status_code == 200)
                cout << "get 200 msg answered" << endl;
            break;
        case EXOSIP_CALL_ANSWERED:
            cout << "Get Call Answer" << endl;
            if (!strcmp(m_event->response->cseq->method, "INVITE") && m_event->response->status_code == 200)
            {
                cout << "get 200 invite response" << endl;
                SendACK();
                ret = INVITE_SUCCESS;
            }
            break;
        case EXOSIP_CALL_ACK:
            cout << "EXOSIP_CALL_ACK" << endl;
            break;
        case EXOSIP_CALL_MESSAGE_ANSWERED:
            cout << "call message answer status: " << m_event->response->status_code << endl;
            break;
        case EXOSIP_CALL_MESSAGE_NEW:
            cout << "EXOSIP_CALL_MESSAGE_NEW" << endl;
            break;
        case EXOSIP_CALL_CLOSED:
            cout << "EXOSIP_CALL_CLOSED" << endl;
            m_videoDid = -1;
            break;
        case EXOSIP_CALL_RELEASED:
            cout << "EXOSIP_CALL_RELEASED" << endl;
            break;
        case EXOSIP_MESSAGE_REQUESTFAILURE:
            cout << "EXOSIP_MESSAGE_REQUESTFAILURE" << endl;
            break;
        default:
            cout << "Event type: " << m_event->type << endl;
            break;
        }
        eXosip_unlock(m_server);
    }

RESULT:
    return ret;
}
bool ExosipServer::PlayBackConected()
{
    bool ret = false;
    eXosip_lock(m_server);
    if (m_videoDid != UNINITIAL)
    {
        cout << "did exit" << endl;
        ret = true;
    }
    else
    {
        cout << "did no exit" << endl;
        ret = false;
    }
    eXosip_unlock(m_server);
    return ret;
}
int ExosipServer::RunListenThread()
{
    m_listenThread->detach();
    return 0;
}
int ExosipServer::SendRegisteAnswer()
{

    int ret = -1;
    int status = -1;
    osip_message_t *answer = nullptr;
    DeviceInfo *info = nullptr;
    if (m_tmpDevice->isAuthNull())
        status = 401;
    else
        status = 200;

    eXosip_lock(m_server);

    if (eXosip_message_build_answer(m_server, m_event->tid, status, &answer) == OSIP_SUCCESS)
    {
        info = m_tmpDevice->GetDeviceInfo();
        if (status == 401)
        {
            string authHead = "";
            authHead += "Digest realm=\"";
            authHead += info->m_ID;
            authHead += "\",nonce=\"";
            authHead += NONCE;
            authHead += "\",algorithm=\"";
            authHead += ALGORITHTHM;
            authHead += "\"";
            osip_message_set_header(answer, "WWW-Authenticate", authHead.c_str());
            //osip_message_set_www_authenticate(answer, authHead.c_str());
            cout << "send 401 unathorization" << endl;
        }
        else if (status == 200)
        {
            osip_message_set_contact(answer, GetFormatHeader().c_str());//<sip:id@ip:port>;expires=
            osip_message_set_date(answer, "2019-04-27");
            osip_message_set_expires(answer, "3600");
        }
        else
        {
        }

        ret = eXosip_message_send_answer(m_server, m_event->tid, status, answer);
    }
    else
    {
        ret = eXosip_message_send_answer(m_server, m_event->tid, 400, nullptr);
    }

    eXosip_unlock(m_server);

    if (ret == OSIP_SUCCESS && status == 200)
    {
        ret = REGISTE_SUCCESS;
        osip_header_t *dst = nullptr;
        osip_message_get_expires(m_event->request, 0, &dst);
        if (!strcmp(dst->hvalue, "0"))
        {
            //删除设备
            if (DeviceMap.find(m_tmpDevice->GetDeviceInfo()->m_ID) != DeviceMap.end())
            {
                DeviceMap.erase(m_tmpDevice->GetDeviceInfo()->m_ID);
                cout << "Delete Device: " << m_tmpDevice->GetDeviceInfo()->m_ID << endl;
            }
            else
                cout << "No Device: " << m_tmpDevice->GetDeviceInfo()->m_ID << endl;
            delete m_tmpDevice;
            m_tmpDevice = nullptr;
        }
        else
        {
            //设备插入map中
            DeviceMap.insert(pair<string, Device*>(m_tmpDevice->GetDeviceInfo()->m_ID, m_tmpDevice));
            cout << "Add Device: " << m_tmpDevice->GetDeviceInfo()->m_ID << endl;
            m_tmpDevice = nullptr;
        }

    }
    else if (ret == OSIP_SUCCESS)
        ret = SEND_ANSWER_SUCCESS;

    return ret;
}

int ExosipServer::SendACK()
{
    int ret = -1;
    osip_message_t *ack = nullptr;
    eXosip_lock(m_server);

    ret = eXosip_call_build_ack(m_server, m_event->did, &ack);
    if (ret == OSIP_SUCCESS)
    {
        if (eXosip_call_send_ack(m_server, m_event->did, ack) >= 0)
        {
            cout << "send ack" << endl;
            m_videoDid = m_event->did;
        }

    }

    eXosip_unlock(m_server);
    return ret;
}



std::string ExosipServer::GetFormatHeader()
{
    string contact;
    contact += "<sip:";
    contact += m_serverInfo->m_ID;
    contact += "@";
    contact += m_serverInfo->m_Ip;
    contact += ":";
    contact += m_serverInfo->m_Port;
    contact += ">";
    return contact;
}

std::string ExosipServer::GetFromHeader(std::string id)
{
    string contact;
    if (id == "defualt")
    {
        contact += "sip:";
        contact += m_serverInfo->m_ID;
        contact += "@";
        contact += m_serverInfo->m_domain;
        contact += ":";
        contact += m_serverInfo->m_Port;

    }
    else
    {
        contact += "sip:";
        contact += id;
        contact += "@";
        contact += m_serverInfo->m_domain;
        contact += ":";
        contact += m_serverInfo->m_Port;
    }
    cout << "From:" << contact << endl;
    return contact;
}

std::string ExosipServer::GetToHeader(std::string id)//用来寻找设备信息的
{
    string contact;
    //根据id寻找设备，就先这么将就着吧
    contact += "sip:";
    contact += id;
    contact += "@";
    contact += m_serverInfo->m_Ip;
    contact += ":";
    contact += "5060";
    cout << "To:" << contact << endl;
    return contact;
}

std::string ExosipServer::GetRouteHeade(std::string id, std::string ip, std::string port)
{
    string contact;
    //根据id寻找设备，就先这么将就着吧
    contact += "sip:";
    contact += id;
    contact += "@";
    contact += ip;
    contact += ":";
    contact += port;
    cout << "ip: " << ip << endl;
    cout << "Route:" << contact << endl;
    return contact;

}
