#pragma once
#include "gameNode.h"
class enemyHpBar : public gameNode
{
private:
	image* _barImg[2];
	float _hpRatio;

	float* _curHp;
	float* _maxHp;

	POINTFLOAT* _centerPos;

	POINT _augPosForRender;

public:
	enemyHpBar();
	~enemyHpBar();

	HRESULT init();
	HRESULT init(float* curHpAddr, float* maxHpAddr, POINTFLOAT* centerPos, POINT augPosForRender);
	void release();
	void update();
	void render();
	
};

