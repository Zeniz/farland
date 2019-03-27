#pragma once
#include "gameNode.h"
#include "tileNode.h"


#include "CharMgr.h"
#include "enemyMgr.h"

#include "mapLoader.h"

#include "UIMgr.h"

class bossStage : public gameNode
{
private:
	image* _bgImg;
	//	===	기본적으로 필요한 것들 ===	//
	vvMap _vvMap;
	POINT _tileNum;

	vEnemy _vEnemy;

	CharMgr* _charMgr;
	enemyMgr* _enemyMgr;

	mapLoader* _mapLoader;

	POINT _clipMapIdx[2];
	const int CLIP_TILENUM_WID = 60;
	const int CLIP_TILENUM_HEI = 60;


	UIMgr* _UIMgr;
	unsigned char _selectedUI;


public:
	bossStage();
	~bossStage();

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
	void ObjRender(int idx, int idxY);
};

