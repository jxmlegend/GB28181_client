#include "GetFactory.h"
#include "RecordControlFactory.h"
#include "AlarmControlFactory.h"
#include "CameraControlFactory.h"
#include "DeviceControlFactory.h"
#include "RequestFactory.h"
#include "InviteFactory.h"
#include "registfactory.h"

GetFactory::GetFactory()
{
}


GetFactory::~GetFactory()
{
	if (cameraControl != nullptr)
	{
		delete cameraControl;
		cameraControl = nullptr;
	}
	if (recordControl != nullptr)
	{
		delete recordControl;
		recordControl = nullptr;
	}
	if (alarmControl != nullptr)
	{
		delete alarmControl;
		alarmControl = nullptr;
	}
	if (deviceControl != nullptr)
	{
		delete deviceControl;
		deviceControl = nullptr;
	}
	if (requestControl != nullptr)
	{
		delete requestControl;
		requestControl = nullptr;
	}
	if (invite != nullptr)
	{
		delete invite;
		invite = nullptr;
	}
}

CommFactory * GetFactory::GetCameraControlFactory()
{
	if(cameraControl == nullptr)
		cameraControl = new CameraControlFactory();
	return cameraControl;
}

CommFactory * GetFactory::GetRecordControlFactory()
{
	if (recordControl == nullptr)
		recordControl = new RecordControlFactory();
	return recordControl;
}

CommFactory * GetFactory::GetAlarmControlFactory()
{
	if (alarmControl == nullptr)
		alarmControl = new AlarmControlFactory();
	return alarmControl;
}

CommFactory * GetFactory::GetDeviceControlFactory()
{
	if (deviceControl == nullptr)
		deviceControl = new DeviceControlFactory();
	return deviceControl;
}

CommFactory * GetFactory::GetRequestFactory()
{
	if (requestControl == nullptr)
		requestControl = new RequestFactory();
	return requestControl;
}

CommFactory * GetFactory::GetInviteFactory()
{
	if (invite == nullptr)
		invite = new InviteFactory();
	return invite;
}
CommFactory * GetFactory::GetRegistFactory()
{
    if (regist == nullptr)
        regist = new RegistFactory();
    return regist;
}
