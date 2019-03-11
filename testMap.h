#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "enemy.h"
#include "skeleton.h"

#include "CharMgr.h"

#include "mapLoader.h"


#include "MaskTile.h"



class testMap : public gameNode
{
private:
	//	===	기본적으로 필요한 것들 ===	//
	vvMap _vvMap;
	POINT _tileNum;
	vObj _vObj;
	vEnemy _vEnemy;
	
	CharMgr* _charMgr;
	mapLoader* _mapLoader;

	POINT _clipMapIdx[2];
	const int CLIP_TILENUM_WID = 60;
	const int CLIP_TILENUM_HEI = 60;
	
	
	MaskTile* _maskTile;

	

	



public:
	testMap();
	~testMap();


	HRESULT init();
	void release();
	void update();
	void render();

	//	===	기본적으로 필요한 것들 ===

	void SetClipRangeFunc();		//	클리핑잡아줌.

	
	void FloorTileRender();
	void ZTileRender(int idxX, int idxY);
	void PlayerRender(int idxX, int idxY);
	void EnemyRender(int idxX, int idxY, int& enemyCount);
	void ObjRender(int idx, int idxY, int& objCount);


};

