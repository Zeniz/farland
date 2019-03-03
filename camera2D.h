#pragma once
#include "singletonBase.h"

enum cameraState
{
	PLAYER_CAMERA,
	EVENT_CAMERA,
	CAMERA_STATE_MAX
};



class camera2D : public singletonBase<camera2D>
{
public:
	


private:

	POINT _maxMapPoint;
	POINT _camPos[cameraState::CAMERA_STATE_MAX];
	
	cameraState _state;
	int _shakeCount;
	int _shakeValue;

	const int CAM_MOVESPD = 5;
	
public:
	camera2D();
	~camera2D();

	HRESULT init();
	HRESULT init(POINT maxPoint);
	HRESULT init(POINT maxPoint, cameraState camState);
	void release();
	void update();

	int getCamPosX() { return _camPos[_state].x; }
	int getCamPosY() { return _camPos[_state].y; }

	void setFocusOn(POINT focusPos, cameraState camState) { _camPos[camState] = focusPos; }
	void setMapSize(int maxXPoint, int maxYPoint);
	void setState(cameraState state) { _state = state; }
	void ShakeYourBodyBabe(int shakeValue, int shakeCount);

	

};

