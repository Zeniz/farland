#include "stdafx.h"
#include "enemyHpBar.h"


enemyHpBar::enemyHpBar()
{
	IMAGEMANAGER->addFrameImage("mobHpbar", L"images/mob/mobHpBar.png", 96, 20, 1, 2);
	_barImg[0] = IMAGEMANAGER->findImage("mobHpbar");
	_barImg[1] = IMAGEMANAGER->findImage("mobHpbar");
	_hpRatio = 0.f;
}


enemyHpBar::~enemyHpBar()
{
}

HRESULT enemyHpBar::init()
{
	_hpRatio = NULL;
	_curHp = nullptr;
	_maxHp = nullptr;

	return S_OK;
}

HRESULT enemyHpBar::init(float * curHpAddr, float * maxHpAddr, POINTFLOAT* centerPos, POINT augPosForRender)
{
	_curHp = curHpAddr;
	_maxHp = maxHpAddr;
	_centerPos = centerPos;
	_augPosForRender = augPosForRender;



	return S_OK;
}

void enemyHpBar::release()
{
}

void enemyHpBar::update()
{
	_hpRatio = (*_curHp) / (*_maxHp);
}

void enemyHpBar::render()
{
	_barImg[0]->frameRender(_centerPos->x + _augPosForRender.x - _barImg[0]->GetFrameWidth() / 2,
		_centerPos->y + _augPosForRender.y - _barImg[0]->GetFrameHeight() / 2,
		0, 0,
		1.0f);
	
	_barImg[1]->frameRender(_centerPos->x + _augPosForRender.x - _barImg[0]->GetFrameWidth() / 2,
		_centerPos->y + _augPosForRender.y - _barImg[0]->GetFrameHeight() / 2,
		(_barImg[0]->GetFrameWidth()-2) * _hpRatio,
		_barImg[0]->GetFrameHeight(),
		0,1,
		1.0f);
}
