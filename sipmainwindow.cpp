#include "sipmainwindow.h"
#include "ui_sipmainwindow.h"

SIPMAINWINDOW::SIPMAINWINDOW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SIPMAINWINDOW)
{
    server = ExosipServer::GetTheServer();
    server->ServerInit();
    server->RunListenThread();
    ui->setupUi(this);
}

SIPMAINWINDOW::~SIPMAINWINDOW()
{
    delete ui;
}

void SIPMAINWINDOW::on_btnPlayBack_clicked()
{
    server->m_factory->GetInviteFactory()->SendComm("34010000001310000001", ExosipServer::PLAYBACK);
}

void SIPMAINWINDOW::on_btnPlay_clicked()
{
    server->m_factory->GetRequestFactory()->SendComm("34010000001310000001", ExosipServer::PLAY);
}

void SIPMAINWINDOW::on_btnLeft_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::LEFT);
}

void SIPMAINWINDOW::on_btnPause_clicked()
{
    server->m_factory->GetRequestFactory()->SendComm("34010000001310000001", ExosipServer::PAUSE);
}

void SIPMAINWINDOW::on_btnFastPlay_clicked()
{
    server->m_factory->GetRequestFactory()->SendComm("34010000001310000001", ExosipServer::FASTPLAY);
}

void SIPMAINWINDOW::on_btnSlowPlay_clicked()
{
    server->m_factory->GetRequestFactory()->SendComm("34010000001310000001", ExosipServer::SLOWPLAY);
}

void SIPMAINWINDOW::on_btnLive_clicked()
{
    server->m_factory->GetInviteFactory()->SendComm("34010000001310000001", ExosipServer::PLAY_LIVE);
}

void SIPMAINWINDOW::on_btnUp_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::UP);
}

void SIPMAINWINDOW::on_btnDown_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::DOWN);
}

void SIPMAINWINDOW::on_btnRight_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::RIGHT);
}

void SIPMAINWINDOW::on_btnZoomLarge_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::ZOOMLARGE);
}

void SIPMAINWINDOW::on_btnZoomLittle_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::ZOOMLITTLE);
}

void SIPMAINWINDOW::on_btnStop_clicked()
{
    server->m_factory->GetCameraControlFactory()->SendComm("34010000001310000001", ExosipServer::STOP_CONTROL);
}

void SIPMAINWINDOW::on_btnRecord_clicked()
{
    server->m_factory->GetRecordControlFactory()->SendComm("34010000001310000001", ExosipServer::RECORD);
}

void SIPMAINWINDOW::on_btnStopRecord_clicked()
{
    server->m_factory->GetRecordControlFactory()->SendComm("34010000001310000001", ExosipServer::STOP_RECORD);
}

void SIPMAINWINDOW::on_btnSearchRecord_clicked()
{
    server->m_factory->GetRecordControlFactory()->SendComm("34010000001310000001", ExosipServer::RECORD_QUERY);
}

void SIPMAINWINDOW::on_btnSetGuard_clicked()
{
    server->m_factory->GetAlarmControlFactory()->SendComm("34010000001310000001", ExosipServer::DEPLOY);
}

void SIPMAINWINDOW::on_btnAlarm_clicked()
{
    server->m_factory->GetAlarmControlFactory()->SendComm("34010000001310000001", ExosipServer::ALARM);
}

void SIPMAINWINDOW::on_btnResetGuard_clicked()
{
    server->m_factory->GetAlarmControlFactory()->SendComm("34010000001310000001", ExosipServer::CANCLE_DEPLOY);
}

void SIPMAINWINDOW::on_btnResetAlarm_clicked()
{
    server->m_factory->GetAlarmControlFactory()->SendComm("34010000001310000001", ExosipServer::ALARM_RET);
}

void SIPMAINWINDOW::on_btnCatalog_clicked()
{
    server->m_factory->GetDeviceControlFactory()->SendComm("34010000001310000001", ExosipServer::DEVICE_CATALOG);
}

void SIPMAINWINDOW::on_btnDeviceInfo_clicked()
{
    server->m_factory->GetDeviceControlFactory()->SendComm("34010000001310000001", ExosipServer::DEVICE_INFO);
}

void SIPMAINWINDOW::on_btnDeviceStart_clicked()
{
    server->m_factory->GetDeviceControlFactory()->SendComm("34010000001310000001", ExosipServer::DEVICE_START);
}

void SIPMAINWINDOW::on_btnKeepLive_clicked()
{
    server->m_factory->GetDeviceControlFactory()->SendComm("34020000002000000001", ExosipServer::KEEP_ALIVE);
}

void SIPMAINWINDOW::on_btnDeviceStatus_clicked()
{
    server->m_factory->GetDeviceControlFactory()->SendComm("34010000001310000001", ExosipServer::DEVICE_STATUS);
}

void SIPMAINWINDOW::on_btnRegist_clicked()
{
    server->m_factory->GetRegistFactory()->SendComm("34020000002000000001", ExosipServer::REGIST, "192.168.1.220");
}

void SIPMAINWINDOW::on_btnCancleRegist_clicked()
{
    server->m_factory->GetRegistFactory()->SendComm("34020000001320000001", ExosipServer::CANCLE_REGIST, "192.168.1.220");
}

void SIPMAINWINDOW::on_btnBye_clicked()
{
    server->m_factory->GetRequestFactory()->SendComm("34010000001310000001", ExosipServer::BYE);
}

void SIPMAINWINDOW::on_btnDownload_clicked()
{
    server->m_factory->GetInviteFactory()->SendComm("34010000001310000001", ExosipServer::DOWNLOAD);
}

void SIPMAINWINDOW::on_btnSendDevInfo_clicked()
{
    //server->m_factory->GetDeviceControlFactory()->SendComm("34020000002000000001", ExosipServer::SEND_DEVINFO);
    server->m_factory->GetRequestFactory()->SendComm("34020000002000000001", ExosipServer::SEND_DEVINFO2);
}
