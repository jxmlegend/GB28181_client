#include "DeviceControlFactory.h"
#include "eXosip2\eXosip.h"
#include "ExosipServer.h"
#include <iostream>
using namespace std;



DeviceControlFactory::DeviceControlFactory()
{
}


DeviceControlFactory::~DeviceControlFactory()
{
}

int DeviceControlFactory::SendComm(std::string id, int controlComm, std::string ip, std::string port, int expires)
{
    ExosipServer *Server = ExosipServer::GetTheServer();
    int ret = -1;
    char xml_body[1024] = "";
    if (Server->DeviceMap.find(id) == Server->DeviceMap.end())
    {
        cout << "Device Not exist: " << id << endl;
    }

    osip_message_t *msg = nullptr;
    eXosip_lock(Server->m_server);
    cout << "ip: " << ip << endl;
    ret = eXosip_message_build_request(Server->m_server, &msg, "MESSAGE", Server->GetToHeader(id).c_str(), Server->GetFromHeader().c_str(), Server->GetRouteHeade(id, ip, port).c_str());
    if (ret != OSIP_SUCCESS)
        goto RESULT;
    osip_message_set_content_type(msg, "Application/MANSCDP+xml");

    if (controlComm == Server->DEVICE_CATALOG)
    {
        sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
                          "<Query>\r\n"
                          "<CmdType>Catalog</CmdType>\r\n"
                          "<SN>248</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "</Query>\r\n", id.c_str());
    }
    else if (controlComm == Server->DEVICE_INFO)
    {
        sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
                          "<Query>\r\n"
                          "<CmdType>DeviceInfo</CmdType>\r\n"
                          "<SN>17430</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "</Query>\r\n", id.c_str());
    }
    else if (controlComm == Server->DEVICE_STATUS)
    {
        sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
                          "<Query>\r\n"
                          "<CmdType>DeviceStatus</CmdType>\r\n"
                          "<SN>248</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "</Query>\r\n", id.c_str());
    }
    else if (controlComm == Server->DEVICE_START)
    {
        sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
                          "<Control>\r\n"
                          "<CmdType>DeviceControl</CmdType>\r\n"
                          "<SN>17298</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "<TeleBoot>Boot</TeleBoot>\r\n"
                          "</Control>\r\n", id.c_str());
    }
    else if (controlComm == Server->KEEP_ALIVE)
    {
        sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
                          "<Notify>\r\n"
                          "<CmdType>Keepalive</CmdType>\r\n"
                          "<SN>43</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "<Status>OK</Status>\r\n"
                          "</Notify>\r\n", id.c_str());
    }
    else if(controlComm == Server->SEND_DEVINFO)
    {
        sprintf(xml_body, "<?xml version=\"1.0\"?>\r\n"
                          "<Response>\r\n"
                          "<CmdType>DeviceInfo</CmdType>\r\n"
                          "<SN>17430</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "<DeviceName>HTIPC</DeviceName>\r\n"
                          "<Result>OK</Result>\r\n"
                          "<Manufacturer>Happtimesoft</Manufacturer>\r\n"
                          "<Model>HTIPC</Model>\r\n"
                          "<Firmwave>V1.0</Firmwave>\r\n"
                          "<Channel>1</Channel>\r\n"
                          "</Response>\r\n"
                          "\r\n"
                , Server->m_serverInfo->m_ID.c_str());
    }
    else
    {
    }


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
