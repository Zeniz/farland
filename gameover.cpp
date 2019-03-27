#include "stdafx.h"
#include "gameover.h"


gameover::gameover()
{
}


gameover::~gameover()
{
}

HRESULT gameover::init()
{
	
	_bgImg = IMAGEMANAGER->addFrameImage("gameoverBG", L"images/gameover/gameoverImg.png", 1600, 900, 1, 1);
	
	_retry.img =IMAGEMANAGER->addFrameImage("retryTxt", L"images/gameover/retryTxt.png", 214, 102, 1, 2);
	_mainmenu.img = IMAGEMANAGER->addFrameImage("mainmenuTxt", L"images/gameover/mainmenuTxt.png", 347, 104, 1, 2);

	_retry.rc = RectMake(425, 670, _retry.img->GetFrameWidth(), _retry.img->GetFrameHeight());
	_mainmenu.rc = RectMake(925, 670, _mainmenu.img->GetFrameWidth(), _mainmenu.img->GetFrameHeight());

	_retry.frameY = 0;
	_mainmenu.frameY = 0;

	_alpha = 0.f;
	_isAlphaFin = false;


	return S_OK;
}

void gameover::release()
{
}

void gameover::update()
{
	if (!_isAlphaFin) {
		_alpha += ALPHA_AUG;
		if (_alpha >= 1.0f) {
			_alpha = 1.0f;
			_isAlphaFin = true;
		}
	}

	//	alpha increase Func Ended
	else {
		_retry.frameY = 0;
		_mainmenu.frameY = 0;
		if (PtInRect(&_retry.rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			_retry.frameY = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SCENEMANAGER->changeScene(SCENEMANAGER->getPreSceneName().c_str());
			}
		}
		else if (PtInRect(&_mainmenu.rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			_mainmenu.frameY = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SCENEMANAGER->changeScene("mainmenu");
			}
		}
	}


}

void gameover::render()
{
	_bgImg->renderABS(0, 0, _alpha);

	_retry.img->frameRenderABS(_retry.rc.left, _retry.rc.top, 0, _retry.frameY, _alpha);
	_mainmenu.img->frameRenderABS(_mainmenu.rc.left, _mainmenu.rc.top, 0, _mainmenu.frameY, _alpha);
}
