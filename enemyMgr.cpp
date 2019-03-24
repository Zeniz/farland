#include "stdafx.h"
#include "enemyMgr.h"


enemyMgr::enemyMgr()
{
}


enemyMgr::~enemyMgr()
{
}

HRESULT enemyMgr::init()
{
	_vEnemy.clear();

	return S_OK;
}

void enemyMgr::release()
{
}

void enemyMgr::update()
{
	for (int i = 0; i < _vEnemy.size(); i++) {
		_vEnemy[i]->update();
		if (_vEnemy[i]->_deleteDelayCount > _vEnemy[i]->DELETE_DELAY_MAX) {
			_vEnemy[i]->release();
			_vEnemy.erase(_vEnemy.begin() + i);
			i--;
		}
	}
}

void enemyMgr::render(int idxX, int idxY)
{
	for (int i = 0; i < _vEnemy.size(); i++) {
		if (_vEnemy[i]->getTileForRender()->_mapIdx.x == idxX &&
			_vEnemy[i]->getTileForRender()->_mapIdx.y == idxY) {
			_vEnemy[i]->render();
		}
	}
}

/*
void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++) {
		_vEnemy[i]->render();
	}
	
}
*/

enemy* enemyMgr::MakeNewEnemy(ENEMY_NAME mobName)
{
	enemy* tmpEnemy = nullptr;
	switch (mobName)
	{
	case ENEMY_NAME::E_NAME_NONE:
		break;
	case ENEMY_NAME::MOB_SKEL:
		tmpEnemy = new skeleton;
		tmpEnemy->init();
		break;

	case ENEMY_NAME::MOB_KAISER:
		tmpEnemy = new charKaiser;
		tmpEnemy->init();
		break;


	case ENEMY_NAME::E_NAME_END:
		break;
	default:
		break;
	}
	
	tmpEnemy->LinkToMap(_vvMap);
	tmpEnemy->LinkToVChara(_vChara);



	return tmpEnemy;

}

void enemyMgr::AddEnemy(enemy * enemy)
{
	_vEnemy.push_back(enemy);
}


