#include "stdafx.h"
#include "enemy.h"

bool compareEnemy(enemy* e1, enemy* e2) {
	if (e1->_mapIdx.y != e2->_mapIdx.y) {
		return (e1->_mapIdx.y < e2->_mapIdx.y);
	}
	else {
		return (e1->_mapIdx.x < e2->_mapIdx.x);
	}

};

enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}
