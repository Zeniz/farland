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
		if (_vEnemy[i]->getTileForRender()->_idx.x == idxX &&
			_vEnemy[i]->getTileForRender()->_idx.y == idxY) {
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

enemy* enemyMgr::MakeNewEnemy(E_IMGNUM mobKind)
{
	enemy* tmpEnemy = nullptr;
	switch (mobKind)
	{
	case E_IMG_NONE:
		break;
	case MOB_SKEL:
		tmpEnemy = new skeleton;
		tmpEnemy->init();
		break;
	case E_IMG_END:
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


