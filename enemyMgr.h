#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "enemy.h"
#include "character.h"
#include "skeleton.h"
#include "charKaiser.h"

typedef vector<enemy*> vEnemy;
typedef vector<Character*> vChara;

class enemyMgr : public gameNode
{
private:
	vEnemy _vEnemy;

	vvMap* _vvMap;
	vChara* _vChara;
public:
	enemyMgr();
	~enemyMgr();

	HRESULT init();
	void release();
	void update();
	//void render();
	void render(int idxX, int idxY);

	//	종류별로 뉴 떄리고 주소 돌려줌
	enemy* MakeNewEnemy(ENEMY_NAME mobName);
	void AddEnemy(enemy* enemy);
	

	vEnemy* getVEnemy() { return &_vEnemy; }

	void LinkToMap(vvMap* vvMapAddr) { _vvMap = vvMapAddr; }
	//void LinkToCharMgr(CharMgr* charMgrAddr) { _charMgr = charMgrAddr; }
	void LinkToVChara(vChara* vCharaAddr) { _vChara = vCharaAddr; }
};

