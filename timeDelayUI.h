#pragma once
#include "UIObjects.h"
class timeDelayUI : public UIObjects
{
private:
	image* _boxImg;
	
	
	bool _isPause;

	bool _isCharStop;
	bool _isMobStop;
	bool _isCharSlowMode;
	bool _isMobSlowMode;

	float _stdElapsedTime;	//	1프레임이 지나갈수있는 기준시
	float _curElapsedTime;	//	누적된 시간
	
	float _timeDelayRatio;	//	몇배속으로 느리게 만들것?




	const float TIME_ERROR = 0.004f;		//	1프레임 = 0.016666초
	const float TIME_RATIO_DELTA = 0.1f;	//	한번 속도조절할떄마다의 속도비율 변화크기


public:
	timeDelayUI();
	~timeDelayUI();

	HRESULT init()	override;
	void release()	override;
	void update()	override;
	void render()	override;

	bool getIsCharStop() { 
		return _isCharStop; 
	}
	void setIsCharStop(bool value) { _isCharStop = value; }
	bool getIsMobStop() { return _isMobStop; }
	void setIsMobStop(bool value) { _isMobStop = value; }

	bool getIsCharSlowMode() { return _isCharSlowMode; }
	void setIsCharSlowMode(bool value) { _isCharSlowMode = value; }
	bool getIsMobSlowMode() { return _isMobSlowMode; }
	void setIsMobSlowMode(bool value) { _isMobSlowMode = value; }


	float getStdElapsedTime() { return _stdElapsedTime; }
	void setStdElapsedTime(float stdTime) { _stdElapsedTime = stdTime; }
	float getCurElapsedTime() { return _curElapsedTime; }
	void setCurElapsedTime(float accumedTime) { _curElapsedTime = accumedTime; }
	void augCurElapsedTime(float augTime) { _curElapsedTime += augTime; }

	float getTimeDelayRatio() { return _timeDelayRatio; }
	void setTimeDelayRatio(float delayRatio) { _timeDelayRatio = delayRatio; }
	

};

