#include "stdafx.h"
#include "timeDelayUI.h"


timeDelayUI::timeDelayUI()
{
}


timeDelayUI::~timeDelayUI()
{
}

HRESULT timeDelayUI::init()
{
	IMAGEMANAGER->addFrameImage("timeDelayBox", L"images/UI/timeDelay/timeDelayBox.png", 176, 30, 4, 1);
	_boxImg = IMAGEMANAGER->findImage("timeDelayBox");
	_isCharStop = false;
	_isMobStop = false;
	_isPause = false;

	_stdElapsedTime = 0.f;
	_curElapsedTime = 0.f;

	_timeDelayRatio = 1.0f;




	return S_OK;
}

void timeDelayUI::release()	
{
}

void timeDelayUI::update()
{
	if (_timeDelayRatio != 0) {
		_stdElapsedTime = TIMEMANAGER->getElapsedTime() / _timeDelayRatio;
	}
	_curElapsedTime += TIMEMANAGER->getElapsedTime();

	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		_isPause = !_isPause;
		if(_isCharSlowMode)		_isCharStop = _isPause;
		if (_isMobSlowMode)		_isMobStop = _isPause;

	}

	if (!_isPause) {
		if (KEYMANAGER->isOnceKeyDown(VK_OEM_PLUS)) {
			_timeDelayRatio += TIME_RATIO_DELTA;
			if (_timeDelayRatio > 1.0f)
				_timeDelayRatio = 1.0f;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_OEM_MINUS)) {
			_timeDelayRatio -= TIME_RATIO_DELTA;
			if (_timeDelayRatio <= 0.f)
				_timeDelayRatio = 0.1f;
		}
	}

	

	if (!_isPause) {
		//	여태까지 지난 시간이, 기준시간보다 많이 지났다-> play해야한다.
		if (_curElapsedTime >= _stdElapsedTime - TIME_ERROR) {
			_curElapsedTime = 0.f;
			_isCharStop = false;
			_isMobStop = false;
		}
		//	아니라면, stop해라.
		else {
			if (_isCharSlowMode) {
				_isCharStop = true;
			}
			if (_isMobSlowMode) {
				_isMobStop = true;
			}
		}
	}
	




}

void timeDelayUI::render()
{
	wstring str;
	WCHAR append[32];
	

	if (_isPause) {
		str = L"Paused";
	}
	else {
		str = L"x ";
		swprintf_s(append, L"%.1f", _timeDelayRatio);
		str += append;
	}
	
	
	_boxImg->renderABS(1424, 0, 1.0f);
	//_buttonImg->render(1424, 0, 1.0f);
	D2DMANAGER->drawTextD2D(
		D2DMANAGER->createBrush(0xFFFFFF, 1.0f),
		L"consolas",
		15.f,
		str.c_str(),
		1540 + CAMERA2D->getCamPosX() ,7.f + CAMERA2D->getCamPosY());


}
