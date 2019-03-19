#pragma once
#include "objects.h"
#include "eStatePattern.h"
#include "tileNode.h"
#include "enemyForMapEditor.h"
#include "enemyHpBar.h"

class Character;
typedef vector<Character*> vChara;



enum E_STATS {
	E_STATS_NONE = -1,
	E_CURHP,
	E_MAXHP,
	E_CURMP,
	E_MAXMP,
	E_MOVESPD,
	E_CASTSPD,

	E_ATK,
	E_DEF,
	E_MATK,
	E_MDEF,

	E_STATS_END,
};


static string _enemyImgKey[ENEMY_NAME::E_NAME_END] = {
	"mobSkel",
};


//=============================================



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

enum E_STATE {
	E_STATUS_NONE = -1,
	E_IDLE,
	E_DEAD,
	E_GETDMG,
	E_STONED,
	E_FROZEN,
	E_GETCRIDMG,
	E_STUNNED,
	E_BLOCK,
	E_MOVE,


	E_ATK1,
	E_ATK2,
	E_ATK3,


	E_SKILL1_CAST,
	E_SKILL1_SHOT,
	E_SKILL2_CAST,
	E_SKILL2_SHOT,
	E_SKILL3_CAST,
	E_SKILL3_SHOT,
	E_SKILL4_CAST,
	E_SKILL4_SHOT,

	E_STATUS_END,

};

struct tagEOrderInfo {
	E_STATE kinds;
	POINT targetMapIdx;
};
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



	


	float _statValue[E_STATS::E_STATS_END];


	E_DIR _dir;
	E_ATTR _attr;
	E_STATE _state;
	E_STATE _preState;


	POINT _mapIdx;
	ENEMY_NAME _name;
	
	
	eStatePattern _pattern;

	TILE* _pCurTile;
	TILE* _tileForRender;
	POINTFLOAT _moveVec;
	POINTFLOAT _probePos;
	//POINT mapIdx;


	animation* _ani;
	float _attrValue[ATTR_END];				//	속성점수.
	int _zLevel;

	bool _isNotice;

	//	맵에디터용 ㅠㅠ
	POINT _tileCenterPosAtSprite;
	POINT _mobTileSize;
	
	RECT _sampleRc;
	image* _sampleImg;
	
	// =============

	list<POINT> _lWayIdxList;
	//list<tagEOrderInfo> _lOrderList;
	TILE _curTile;
	bool _isStateChanged;
	bool _isAtkFin;
	int _abnormalConditionCount;


	int _targetCharIdx;
	int _moveTileCount;
	int _atkCount;
	int _deleteDelayCount;

	RECT _targetedRc;
	
	vvMap* _vvMap;
	vChara* _vChara;
	enemyHpBar* _hpBar;


	const int STUNNED_COUNTMAX = 240;
	const int ATKCOUNT_MAX = 120;
	const int MOVETILECOUNT_MAX = 2;
	const float FLOAT_ERROR = 1.f;

	const int LEN_TO_TOP_FROM_CENTERPOS = 120;
	const int LEN_TO_BOTTOM_FROM_CENTERPOS = 30;
	const int WID_FROM_CENTERPOS = 50;
	const int DELETE_DELAY_MAX = 300;


public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void InitObjectiveValDefault(POINT mapIdx)	abstract;
	virtual void InitCharacteristicValDefault()			abstract;

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
	/*
	bool operator <(enemy obj) {
		if (this->_mapIdx.y < obj._mapIdx.y) {
			return this->_mapIdx.y < obj._mapIdx.y;
		}
		else {
			return this->_mapIdx.x < obj._mapIdx.x;
		}
	}
	*/
	void setMobPosbyIdx(int mapIdxX, int mapIdxY) {
		_mapIdx.x = mapIdxX;
		_mapIdx.y = mapIdxY;
		_pos = ConvertIdxToPosFloat(_mapIdx.x, _mapIdx.y, TILESIZE_WID, TILESIZE_HEI);

	}
	

	void setEnemyInfo(POINT tileCenterPosAtSprite,
		RECT sampleRc, POINTFLOAT pos, POINT mobTileSize, ENEMY_NAME name,
		int zlvl, POINT mapIdx, RECT rc) {

		this->_tileCenterPosAtSprite = tileCenterPosAtSprite;
		this->_sampleRc = sampleRc;
		this->_pos = pos;
		this->_mobTileSize = mobTileSize;
		this->_name = name;
		this->_img = IMAGEMANAGER->findImage(_enemyImgKey[this->_name].c_str());
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

	void patternUpdate();
	void MakeIdleByEndAni();
	void ChkDead();
	void NoticeFunc(int noticeRange);

	
	void setCurHpAug(float augVal) {
		_statValue[E_STATS::E_CURHP] += augVal;
		if (_statValue[E_STATS::E_CURHP] > _statValue[E_STATS::E_MAXHP])
			_statValue[E_STATS::E_CURHP] = _statValue[E_STATS::E_MAXHP];
		if (_statValue[E_STATS::E_CURHP] < 0)
			_statValue[E_STATS::E_CURHP] = 0;
		_preState = _state;
		_state = E_STATE::E_GETDMG;
		_isStateChanged = true;
	}

	void setState(E_STATE state) {
		_preState = _state;
		_state = state;
		_isStateChanged = true;
	}

	void setHpBar(POINT augPos);


	TILE* getCurTile() { return _pCurTile; }
	TILE* getTileForRender() { return _tileForRender; }
	Character* getChara(int idx) { return (*_vChara)[idx]; }





	void LinkToMap(vvMap* vvMapAddr) { _vvMap = vvMapAddr; }
	void LinkToVChara(vChara* vCharaAddr) { _vChara = vCharaAddr; }
};

bool compareEnemy(enemy* e1, enemy* e2);
