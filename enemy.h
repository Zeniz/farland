#pragma once
#include "objects.h"
#include "tileNode.h"



enum E_IMGNUM {
	E_IMG_NONE = -1,
	
	MOB_SKEL,



	E_IMG_END,
};


static string _enemyImgKey[E_IMG_END] = {
	"mobSkel",
};
//	맵 에디터용...맵 에디터에 넣을까?
static struct tagEnemySpriteInfoForMapEditor {
	POINT tileCenterPosAtSprite;
	RECT sampleRc;
	POINT mobTileSize;
	
	E_IMGNUM imgNum;
	image* sampleImg;

	int zLvl;
	
};

static tagEnemySpriteInfoForMapEditor _enemyInfo[E_IMG_END];



class enemy : public objects
{
public:
	//	 : public <objects>
	//image* _img;
	//int _frameX;
	//int _frameY;
	//
	//POINTFLOAT _pos;
	//RECT _rc;
	//int _zLevel;

	enum E_DIR {
		DIR_NONE = -1,
		DIR_LT = 0,
		DIR_RT,
		DIR_RB,
		DIR_LB,

		DIR_END,
	};

	enum E_ATTR {
		ATTR_NONE = -1,
		FIRE,
		ICE,
		THUNDER,
		WIND,
		EARTH,


		ATTR_END,
	};

	enum E_STATUS {
		STATUS_NONE = -1,
		IDLE,
		DEAD,
		GETDMG,
		STONED,
		FROZEN,
		GETCRIDMG,
		STUNNED,
		DEF,
		MOVE,


		ATK1,
		ATK2,
		ATK3,


		SKILL1_CAST,
		SKILL1_SHOT,
		SKILL2_CAST,
		SKILL2_SHOT,
		SKILL3_CAST,
		SKILL3_SHOT,
		SKILL4_CAST,
		SKILL4_SHOT,

		STATUS_END,
		
	};

	float _curHp;
	float _maxHp;
	float _curMp;
	float _maxMp;

	POINT _mapIdx;
	E_IMGNUM _imgNum;

	animation* _ani[E_DIR::DIR_END][E_STATUS::STATUS_END];
	float _attrValue[ATTR_END];				//	속성점수.


	TILE _curTile;
	

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//	float getCurHp() { return _curHp; }
	//	void setCurHp(float curHp) { _curHp = curHp; }
	//	float getMaxHp() { return _maxHp; }
	//	void setMaxHp(float maxHp) { _maxHp = maxHp; }
	//	float getCurMp() { return _curMp; }
	//	void setCurMp(float curMp) { _curMp = curMp; }
	//	float getMaxMp() { return _maxMp; }
	//	void setMaxMp(float maxMp) { _maxMp = maxMp; }
	//	POINT getMapIdx() { return _mapIdx; }
	//	void setMapIdx(POINT mapIdx) { _mapIdx = mapIdx; }



	void setMobPosbyIdx(int mapIdxX, int mapIdxY) {
		_mapIdx.x = mapIdxX;
		_mapIdx.y = mapIdxY;
		_pos = ConvertIdxToPosFloat(_mapIdx.x, _mapIdx.y, TILESIZE_WID, TILESIZE_HEI);

	}
	void setCurHpByDmg(float dmg) { _curHp -= dmg; }
	void setCurMpBySkill(float usedMp) { _curMp -= usedMp; }



};


