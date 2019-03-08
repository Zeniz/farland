#pragma once

#include "objects.h"
#include "tileNode.h"
#include "enemy.h"

typedef vector<enemy*> vEnemy;



class charSkills;
class charStatePattern;

enum class CHAR_DIR {
	NONE = -1,
	LT,
	RT,
	LB,
	RB,

	CHAR_DIR_END,
};

enum class CHAR_STATE {
	NONE = -1,
	IDLE,
	MOVE,
	CASTING,
	DEAD,
	GETHIT,
	STONE,
	FROZEN,
	GETHIT2,
	BLOCK,

	BASIC_ATK,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4,

	CHAR_STATE_END,
};

enum class CUR_SKILL {
	NONE = -1,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4,

	CUR_SKILL_END,
};

enum class CHAR_NAME {
	NONE = -1,
	LEON,
	CAREN,

};

enum class CHAR_PORTRAIT_KINDS {
	NONE = -1,
	BASIC,
	UPSET,
	JOYFUL,
	CRYING,
	NOTICED,
	SURPRISED,
	EMBRASSED,
	GETDMG,
	DEAD,

	CHAR_PORTRAIT_END,

};

enum class ORDER_KINDS {
	NONE = -1,
	STAY,
	MOVE,
	ATK,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4,

};

enum CHAR_VALUE_CURAUG {
	CURAUG_NONE = -1,
	CUR,
	AUG,
	CURAUG_END,

};

enum CHAR_VALUE_KINDS {
	CHAR_VALUE_NONE = -1,
	MAX_HP,	CUR_HP,	REGEN_HP,
	MAX_MP, CUR_MP, REGEN_MP,
	
	MOVE_SPD,
	CASTING_SPD,

	ATK,	DEF,
	M_ATK,	M_DEF,


	KINDS_END,
};

class Character : public objects
{
protected:
	//	<objects> : public
	//	image* _img;
	//	int _frameX;
	//	int _frameY;
	//	
	//	POINTFLOAT _pos;
	//	RECT _rc;
	//	int _zLevel;
	//	OBJ_KINDS _objKinds;

	animation* _ani;
	bool _isStateChanged;
	TILE* _frontTile;
	TILE* _curTile;
	TILE* _targetTile;
	POINT mapIdx;		//	추가됨. 초기화되지않음.
	vvMap* _vvMap;
	vEnemy* _vEnemy;

	float _charValue[CHAR_VALUE_CURAUG::CURAUG_END][CHAR_VALUE_KINDS::KINDS_END];

	//{
	//	float _maxHp, _curHp, _regenHp;
	//	float _maxMp, _curMp, _regenMp;
	//	float _moveSpd;
	//	float _castingSpd;
	//	float _atk;
	//	float _def;
	//	float _magicAtk;
	//	float _magicDef;
	//
	//	float _augMaxHp;
	//	float _augMaxMp;
	//	float _augRegenHp;
	//	float _augRegenMp;
	//	float _augMoveSpd;
	//	float _augCastSpd;
	//	float _augAtk;
	//	float _augDef;
	//	float _augMagicAtk;
	//	float _augMagicDef;
	//}
	
	bool _isMoveOrderMode;		//	추가됨. 초기화되지않음.===========


	POINTFLOAT _moveVec;
	POINTFLOAT _probePos;
	

	CHAR_NAME _name;
	CHAR_DIR _dir;
	CHAR_STATE _state;
	//charStatePattern* _statePattern;
	
	charStatePattern* _arrStatePattern[static_cast<const int>(CHAR_STATE::CHAR_STATE_END)];

	CHAR_PORTRAIT_KINDS _portraitKinds;
	POINT _portraitFrameIdx;

	CUR_SKILL _curSkill;
	charSkills* _arySkill[static_cast<const int>(CUR_SKILL::CUR_SKILL_END)];


	list<ORDER_KINDS> _lOrderList;
	list<ORDER_KINDS>::iterator _liOrderList;
	list<POINT> _lWayIdxList;
	list<POINT>::iterator _liWayIdxList;


	

public:
	Character();
	~Character();

	HRESULT init();
	virtual void update() abstract;
	void aniRender();

	virtual void InitObjectiveValDefault(POINT mapIdx)		abstract;
	virtual void InitCharacteristicValDefault()				abstract;
	virtual void InitCharacteristicAugValDefault()			abstract;

	void InitObjectiveVal(image* img, POINTFLOAT pos, int zlvl, animation* ani, TILE* curTile);
	void InitCharacteristicVal(float maxHp, float curHp, float regenHp,
		float maxMp, float curMp, float regenMp,
		float moveSpd, float castSpd,
		float atk, float def, float mAtk, float mDef,
		CHAR_NAME charName, CHAR_DIR charDir, CHAR_STATE charState
	);
	void InitCharacteristicAugVal(float augMaxHp, float augCurHp, float augRegenHp,
		float augMaxMp, float augCurMp, float augRegenMp,
		float augMoveSpd, float augCastSpd,
		float augAtk, float augDef, float augMAtk, float augMDef
	);
	

	void InitCharacteristicAugVal();	//	증가치 null


	TILE* getCurTile() { return _curTile; }
	void setCurTile(TILE* curTile) { _curTile = curTile; }

	list<POINT>* getWaylistAddr() { return &_lWayIdxList; }

	
	void LinkToArrStatePattern(charStatePattern* addrCharStatePattern) {
		_arrStatePattern[0] = addrCharStatePattern;
	}
	void LinkToVvMap(vvMap* vvMapAddr) {
		_vvMap = vvMapAddr;
	}
	void LinkToVEnemy(vEnemy* vEnemyAddr) {
		_vEnemy = vEnemyAddr;
	}
};

