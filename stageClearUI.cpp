#include "stdafx.h"
#include "stageClearUI.h"


stageClearUI::stageClearUI()
{
}


stageClearUI::~stageClearUI()
{
}

HRESULT stageClearUI::init()
{
	_clearImg = IMAGEMANAGER->addImage("clearImg", L"images/UI/stageUI/stageClearImg.png", 942, 442);
	_failImg = IMAGEMANAGER->addImage("failImg", L"images/UI/stageUI/stageFailImg.png", 942, 442);
	_clearRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _clearImg->GetWidth(), _clearImg->GetHeight());
	_isClear = false;
	_isGameOver = false;


	return S_OK;
}

void stageClearUI::release()
{
}

void stageClearUI::update()
{
	if (!_isClear) {
		if (_vpEnemy->size() == 0) {
			_isClear = true;
		}
		bool isAlive = false;
		for (int i = 0; i < _vpChara->size(); i++) {
			if ((*_vpChara)[i]->_charValue[CUR][CHAR_VALUE_KINDS::CUR_HP] > 0) {
				isAlive = true;
			}
		}
		if (!isAlive) {
			_isGameOver = true;
		}
	}
	

	else if (_isClear) {
		if (PtInRect(&_clearRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {


				SCENEMANAGER->changeScene(_nextStage.c_str());
			}
		}
	}
	if (_isGameOver) {
		if (PtInRect(&_clearRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SCENEMANAGER->changeScene("gameover");
			}
		}
	}
	
}

void stageClearUI::render()
{
	if (_isClear) {
		_clearImg->renderABS(_clearRc.left, _clearRc.top, 1.0f);
	}
	else if (_isGameOver) {
		_failImg->renderABS(_clearRc.left, _clearRc.top, 1.0f);
	}
}

void stageClearUI::CalNextStage(string curStageName)
{
	_curStage = curStageName.c_str();

	if (curStageName == "stage1") {
		_nextStage = "bossStage";
	}
	if (curStageName == "bossStage") {
		_nextStage = "mainmenu";
	}
}
