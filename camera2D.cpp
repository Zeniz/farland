#include "stdafx.h"
#include "camera2D.h"


camera2D::camera2D()
{
}


camera2D::~camera2D()
{
}

HRESULT camera2D::init()
{
	//포지션 제로 초기화

	_maxMapPoint = { 0,0 };
	for (int i = 0; i < cameraState::CAMERA_STATE_MAX; i++) {
		_camPos[i] = { 0,0 };
	}
	_state = PLAYER_CAMERA;
	
	_shakeValue = 0;
	_shakeCount = 0;

	

	return S_OK;
}

HRESULT camera2D::init(POINT maxPoint)
{
	//포지션 제로 초기화 및 맥스 세팅
	
	_maxMapPoint = maxPoint;
	for (int i = 0; i < cameraState::CAMERA_STATE_MAX; i++) {
		_camPos[i] = { 0,0 };
	}
	_state = PLAYER_CAMERA;

	_shakeValue = 0;
	_shakeCount = 0;
	return S_OK;
}

HRESULT camera2D::init(POINT maxPoint, cameraState camState)
{
	//포지션 제로 초기화 및 맥스 세팅

	_maxMapPoint = maxPoint;
	for (int i = 0; i < cameraState::CAMERA_STATE_MAX; i++) {
		_camPos[i] = { 0,0 };
	}
	_state = camState;

	_shakeValue = 0;
	_shakeCount = 0;
	return S_OK;
}

void camera2D::release()
{
}

void camera2D::update()
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_camPos[_state].x -= CAM_MOVESPD;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_camPos[_state].x += CAM_MOVESPD;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		_camPos[_state].y -= CAM_MOVESPD;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_camPos[_state].y += CAM_MOVESPD;
	}

}


void camera2D::setMapSize(int maxXPoint, int maxYPoint)
{
	_maxMapPoint.x = maxXPoint;
	_maxMapPoint.y = maxYPoint;
}

void camera2D::ShakeYourBodyBabe(int shakeValue, int shakeCount)
{
	_shakeValue = shakeValue;
	_shakeCount = shakeCount;
}

