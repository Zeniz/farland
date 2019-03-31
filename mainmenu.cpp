#include "stdafx.h"
#include "mainmenu.h"


mainmenu::mainmenu()
{
}


mainmenu::~mainmenu()
{
}

HRESULT mainmenu::init()
{
	CAMERA2D->setFocusOn({ 0,0 }, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);


	IMAGEMANAGER->addFrameImage("mainmenuBg", L"images/title/titleImg.png", 1600, 900, 1, 1);
	IMAGEMANAGER->addFrameImage("newgameButton", L"images/title/newgameButton.png", 341, 106, 1, 2);
	IMAGEMANAGER->addFrameImage("mapToolButton", L"images/title/mapToolButton.png", 302, 106, 1, 2);
	IMAGEMANAGER->addFrameImage("exitButton", L"images/title/exitButton.png", 166, 102, 1, 2);
	
	SOUNDMANAGER->addSound("mainmenuBGM", "sounds/mainmenuBGM.mid", true, true);


	_bgImg = IMAGEMANAGER->findImage("mainmenuBg");
	_bgAlpha = 0.f;

	_buttons[NEWGAME].img = IMAGEMANAGER->findImage("newgameButton");
	_buttons[MAPTOOL].img = IMAGEMANAGER->findImage("mapToolButton");
	_buttons[EXIT].img = IMAGEMANAGER->findImage("exitButton");

	int buttonYGap = (BUTTON_END_Y - BUTTON_START_Y) / BUTTON_END;

	for (int i = 0; i < BUTTON_KINDS::BUTTON_END; i++) {
		_buttons[i].pos.y = BUTTON_START_Y + buttonYGap * i;
		_buttons[i].pos.x = BUTTON_START_X;
		_buttons[i].rc = RectMakeCenter(
			_buttons[i].pos.x,
			_buttons[i].pos.y,
			_buttons[i].img->GetFrameWidth(),
			_buttons[i].img->GetFrameHeight()
		);
		_buttons[i].frameX = 0;
		_buttons[i].frameY = 0;
	}
	
	POINT camPos = { 0, 0 };
	CAMERA2D->setFocusOn(camPos, cameraState::EVENT_CAMERA);

	_isTitleAlphaFin = false;

	

	return S_OK;
}

void mainmenu::release()
{
	SOUNDMANAGER->stop("mainmenuBGM");
}

void mainmenu::update()
{
	OPTIONMANAGER->update();
	if (!SOUNDMANAGER->isPlaySound("mainmenuBGM")) {
		SOUNDMANAGER->play("mainmenuBGM", OPTIONMANAGER->getRatioValue(OPTION_KINDS::BGM_VOLUME));
	}
	
	



	if (!_isTitleAlphaFin) {
		_bgAlpha += ALPHA_AUGSPD;
		if (_bgAlpha >= 1.0f) {
			_bgAlpha = 1.0f;
			_isTitleAlphaFin = true;
		}
	}

	else {
		for (int i = 0; i < BUTTON_END; i++) {
			_buttons[i].frameY = 0;
			if (PtInRect(&_buttons[i].rc, PointMake(_ptMouse.x, _ptMouse.y))) {
				_buttons[i].frameY = 1;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					switch (i)
					{
					case NEWGAME:
						SCENEMANAGER->changeScene("stage1");
						break;
					case MAPTOOL:
						SCENEMANAGER->changeScene("mapEditor");
						break;
					case EXIT:
						PostQuitMessage(NULL);
						break;

					default:
						break;
					}
				}
			}

		}
	}
}

void mainmenu::render()
{
	_bgImg->frameRender(0, 0, 0, 0, _bgAlpha);

	if (_isTitleAlphaFin) {
		for (int i = 0; i < BUTTON_END; i++) {
			_buttons[i].img->frameRender(
				_buttons[i].rc.left,
				_buttons[i].rc.top,
				_buttons[i].frameX,
				_buttons[i].frameY,
				1.0f);
		}
	}
	
	OPTIONMANAGER->render();
}
