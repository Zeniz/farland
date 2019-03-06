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
	POINTFLOAT pos;
	RECT rc;
	POINT mobTileSize;
	

	E_IMGNUM imgNum;
	image* sampleImg;

	int zLvl;
	POINT mapIdx;
	
	void init() {
		tileCenterPosAtSprite = { NULL,NULL };
		sampleRc = { NULL,NULL,NULL,NULL };
		mobTileSize = { NULL ,NULL };
		imgNum = E_IMG_NONE;
		sampleImg = nullptr;
		mapIdx = { NULL, NULL };
	}
	
	int getPixPosToLeft() {
		return tileCenterPosAtSprite.x - sampleRc.left;
	}
	int getPixPosToTop() {
		return tileCenterPosAtSprite.y - sampleRc.top;
	}
	int getWid() {
		return sampleRc.right - sampleRc.left;
	}
	int getHei() {
		return sampleRc.bottom - sampleRc.top;
	}


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

	//	맵에디터용 ㅠㅠ
	POINT _tileCenterPosAtSprite;
	POINT _mobTileSize;
	int _zLevel;
	RECT _sampleRc;
	image* _sampleImg;
	


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

	bool operator <(enemy obj) {
		if (this->_mapIdx.y < obj._mapIdx.y) {
			return this->_mapIdx.y < obj._mapIdx.y;
		}
		else {
			return this->_mapIdx.x < obj._mapIdx.x;
		}
	}

	void setMobPosbyIdx(int mapIdxX, int mapIdxY) {
		_mapIdx.x = mapIdxX;
		_mapIdx.y = mapIdxY;
		_pos = ConvertIdxToPosFloat(_mapIdx.x, _mapIdx.y, TILESIZE_WID, TILESIZE_HEI);

	}
	void setCurHpByDmg(float dmg) { _curHp -= dmg; }
	void setCurMpBySkill(float usedMp) { _curMp -= usedMp; }

	tagEnemySpriteInfoForMapEditor getEnemyInfo() {
		tagEnemySpriteInfoForMapEditor tmpEnemyInfo;


		tmpEnemyInfo.tileCenterPosAtSprite = this->_tileCenterPosAtSprite;
		tmpEnemyInfo.sampleRc = this->_sampleRc;
		tmpEnemyInfo.pos = this->_pos;		// 다 먹여주고 맵 세이버/로드 적용시작
		tmpEnemyInfo.mobTileSize = this->_mobTileSize;
		tmpEnemyInfo.imgNum = this->_imgNum;
		tmpEnemyInfo.sampleImg = IMAGEMANAGER->findImage("mobSprite");
		tmpEnemyInfo.zLvl = this->_zLevel;
		tmpEnemyInfo.mapIdx = this->_mapIdx;
		tmpEnemyInfo.rc = this->_rc;

		return tmpEnemyInfo;

	}
	void setEnemyInfo(POINT tileCenterPosAtSprite,
		RECT sampleRc, POINTFLOAT pos, POINT mobTileSize, E_IMGNUM imgNum,
		int zlvl, POINT mapIdx, RECT rc) {

		this->_tileCenterPosAtSprite = tileCenterPosAtSprite;
		this->_sampleRc = sampleRc;
		this->_pos = pos;
		this->_mobTileSize = mobTileSize;
		this->_imgNum = imgNum;
		this->_img = IMAGEMANAGER->findImage(_enemyImgKey[this->_imgNum]);
		this->_zLevel = zlvl;
		this->_mapIdx = mapIdx;
		this->_rc = rc;
		this->_sampleImg = IMAGEMANAGER->findImage("mobSprite");

	}

	int getWid() {
		return _sampleRc.right - _sampleRc.left;
	}
	int getHei() {
		return _sampleRc.bottom - _sampleRc.top;
	}

};

bool compareEnemy(enemy* e1, enemy* e2);
