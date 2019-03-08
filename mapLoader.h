#pragma once
#include "tileNode.h"
#include "aStarTileNode.h"
#include "enemy.h"
#include "skeleton.h"
typedef vector<enemy*> vEnemy;

class mapLoader
{
private:




public:
	mapLoader();
	~mapLoader();



	void LoadMap(int mapIdx, vvMap* vvMapAddr, POINT* tileNum, vObj* vObjAddr, vEnemy* vEnemyAddr);

};

