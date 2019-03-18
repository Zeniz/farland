#pragma once
#include "tileNode.h"
#include "aStarTileNode.h"
#include "enemyForMapEditor.h"
#include "enemy.h"
#include "skeleton.h"
typedef vector<enemy*> vEnemy;

class mapLoader
{
private:




public:
	mapLoader();
	~mapLoader();



	void LoadMap(int mapIdx, vvMap* vvMapAddr, POINT* tileNum, vEnemy* vEnemyAddr);

};

