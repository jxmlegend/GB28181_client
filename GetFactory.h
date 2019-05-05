#pragma once
#include "CommFactory.h"
class GetFactory
{
private:
	CommFactory *cameraControl = nullptr;
	CommFactory *recordControl = nullptr;
	CommFactory *alarmControl = nullptr;
	CommFactory *deviceControl = nullptr;
	CommFactory *requestControl = nullptr;
	CommFactory *invite = nullptr;
    CommFactory *regist = nullptr;
public:
	GetFactory();
	~GetFactory();
	CommFactory *GetCameraControlFactory();
	CommFactory *GetRecordControlFactory();
	CommFactory *GetAlarmControlFactory();
	CommFactory *GetDeviceControlFactory();
	CommFactory *GetRequestFactory();
	CommFactory *GetInviteFactory();
    CommFactory *GetRegistFactory();
};

