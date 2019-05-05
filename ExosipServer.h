#pragma once
#include <string>
#include <iostream>
#include "eXosip2\eXosip.h"
#include "Device.h"
#include "CommFactory.h"
#include "GetFactory.h"
#include "RecordControlFactory.h"
#include "AlarmControlFactory.h"
#include "CameraControlFactory.h"
#include "DeviceControlFactory.h"
#include "RequestFactory.h"
#include "InviteFactory.h"
#include "registfactory.h"
#include <map>
#include <memory>
#include <thread>
#include <QThread>

//����һ�������
#define NONCE "9bd055"
//Ĭ�ϼ����㷨
#define ALGORITHTHM "MD5"
#define UNINITIAL -1
class ExosipServer
{
	friend RecordControlFactory;
	friend AlarmControlFactory;
	friend CameraControlFactory;
	friend DeviceControlFactory;
	friend RequestFactory;
	friend InviteFactory;
    friend RegistFactory;
public:
	~ExosipServer();
	static ExosipServer *GetTheServer();
	int ServerInit();
	int ServerListen(int m = 0, int s = 1000);
	bool PlayBackConected();
	int RunListenThread();
	GetFactory *m_factory = nullptr;
	//CommFactory *m_comm = nullptr;
    int m_expires = 3600;
private:
	int SendRegisteAnswer();
	int SendACK();
	//static int ListenThread();
	std::string GetFormatHeader();
	std::string GetFromHeader(std::string id = "defualt");
	std::string GetToHeader(std::string id = "defualt");
	std::string GetRouteHeade(std::string id = "defualt", std::string ip = "127.0.0.1", std::string port = "5060");

	std::map<std::string, Device*> DeviceMap;//�洢�豸��map��keyֵΪ�豸�ı�ţ�valueΪDevice
	Device *m_tmpDevice = nullptr;//����ע����豸��ʱ�ԵĴ洢������
	DeviceInfo *m_serverInfo = nullptr; //�洢����������Ϣ
	eXosip_t *m_server = nullptr;
	eXosip_event_t *m_event = nullptr;//���������¼�
	int m_videoDid = -1;//�洢�㲥��������Ӧ���¼�
    std::thread *m_listenThread = NULL;
    //static ExosipServer *TheExosipServer;
    static void ListenThread();
	
    ExosipServer(std::string ip = "192.168.1.220", std::string port = "8880", int iport = 8880, std::string domain = "3402000000", std::string id = "34020000001110000001");
	ExosipServer(const ExosipServer &server);
	ExosipServer &operator=(const ExosipServer &server);
public:
	enum RETURNVALUE
	{
		INIT_SUCCESS = 101, //��ʼ��sip�������ɹ�
		INIT_FAIL,			//��ʼ��sip������ʧ��
		SEND_ANSWER_SUCCESS,
		REGISTE_SUCCESS,
		CONTROL_SUCCESS,
		INVITE_SUCCESS,
		DEVICE_CATALOG,
		DEVICE_INFO,
        SEND_DEVINFO,
		DEVICE_STATUS,
		DEVICE_START,
		KEEP_ALIVE
	};
	enum CONTROLCOMM {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		ZOOMLARGE,
		ZOOMLITTLE,
		STOP_CONTROL,
		RECORD,
		STOP_RECORD,
		RECORD_QUERY,
		ALARM,
		DEPLOY,
		CANCLE_DEPLOY,
		ALARM_RET,
		PLAY_LIVE,
		PLAYBACK,
		DOWNLOAD,
		PLAY,
		PAUSE,
		FASTPLAY,
        SLOWPLAY,
        REGIST,
        CANCLE_REGIST,
        BYE
	};

};

