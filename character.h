#pragma once

#include "objects.h"
#include "tileNode.h"
#include "enemy.h"
#include "charStatePattern.h"


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

enum ORDER_KINDS {
	NONE = -1,
	MOVE,
	HOLD,
	ATTACK,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4,
	ORDER_END,

};

struct tagOrderInfo {
	ORDER_KINDS kinds;
	POINT targetMapIdx;

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
	MAX_SP, CUR_SP, REGEN_SP,
	
	MOVE_SPD,
	CASTING_SPD,

	ATK,	DEF,
	M_ATK,	M_DEF,


	KINDS_END,
};



class Character : public objects
{
public:
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
	TILE* _tileForRender;
	TILE* _targetTile;
	POINT mapIdx;		//	�߰���. �ʱ�ȭ��������.
	vvMap* _vvMap;
	vEnemy* _vEnemy;

	float _charValue[CHAR_VALUE_CURAUG::CURAUG_END][CHAR_VALUE_KINDS::KINDS_END];
	float _coolDownTimer[2][ORDER_KINDS::ORDER_END];

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
	
	bool _isMoveOrderMode;		//	�߰���. �ʱ�ȭ��������.===========


	POINTFLOAT _moveVec;
	POINTFLOAT _probePos;
	

	CHAR_NAME _name;
	CHAR_DIR _dir;
	CHAR_STATE _state;
	CHAR_STATE _preState;
	//charStatePattern* _statePattern;
	
	charStatePattern* _curState;
	charStatePattern* _arrStatePattern[static_cast<const int>(CHAR_STATE::CHAR_STATE_END)];

	CHAR_PORTRAIT_KINDS _portraitKinds;
	POINT _portraitFrameIdx;

	CUR_SKILL _curSkill;
	charSkills* _arySkill[static_cast<const int>(CUR_SKILL::CUR_SKILL_END)];


	list<tagOrderInfo> _lOrderList;
	list<tagOrderInfo>::iterator _liOrderList;
	list<POINT> _lWayIdxList;
	list<POINT>::iterator _liWayIdxList;

	RECT screenRc;		//	�����ڿ��� ����
	ORDER_KINDS _mode;		//	���� ������ ���� ����
	bool _isOrderFin;

	bool _isSelectedChar;	//	���� ���õ� ĳ�����ΰ�?
	int _holdCounter;
	int _holdCounterMax;

	int _targetEnemyIdx;		//	���ݴ���� �ε���
	int _aStarCount;			//	aStar��˻� ī��Ʈ
	int _basicAtkCount;			
	//bool _isOnMove;				//	atk�Ϸ� �̵����ΰ�?
	bool _isOnAtking;				//	�����Ϸ� �������ΰ�?
	int _castingCount;
	

	const int CAST1COUNT_MAX = 120;			//	ĳ���ÿ� �ɸ��� �ð�
	const int CAST2COUNT_MAX = 120;
	const int CAST3COUNT_MAX = 120;
	const int CAST4COUNT_MAX = 120;

	const float SKILL1_MULTI = 1.5;			//	��ų ���
	const float SKILL2_MULTI = 1.5;			//	��ų ���
	const float SKILL3_MULTI = 1.5;			//	��ų ���
	const float SKILL4_MULTI = 1.5;			//	��ų ���

	const float FLOAT_ERROR = 1.f;			//	�����̵���, ���� �ٷ�����ִ� ũ��.
	const int ASTAR_COUNT_MAX = 60;
	const int BASIC_ATK_COUNT_MAX = 60;

	//	UI�������, ȭ�鳻 ��Ʈ �����ʿ�.(�ȱ׷� Ŭ���Ҷ� �������� ���ϰԵǼ� out of range ���Ե�)
	//	����, �� ���� UI�� �־������.
	const int UI_START_X = 0;
	const int UI_START_Y = 900;
	const int UI_WID = 0;
	const int UI_HEI = 0;
	
	const int DEF_MAX = 50;
	const float DEFRATIO_MAX = 0.90;

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

	

	

	void InitCharacteristicAugVal();	//	����ġ null

	
	void MoveFunc();		//	�̰žȾ�. -> stateMove������
	//	======== �������� ���°� ===========
	//setAni()�� ���������� �ؾ���.
	void MakeIdleByEndAni();
	void CoolDownFunc();
	void SetModeFunc();
	void MakeOrder();
	void HoldRegenFunc();
	bool MakeClickedEnemyIdx();



	TILE* getCurTile() { return _curTile; }
	void setCurTile(TILE* curTile) { _curTile = curTile; }
	TILE* getTileforRender() { return _tileForRender; }
	void setTileforRender(TILE* tileforRender) { _tileForRender = tileforRender; }
	TILE* getTartgetTile() { return _targetTile; }
	void setTargetTile(TILE* targetTile) { _targetTile = targetTile; }

	bool getIsSelectedChar() { return _isSelectedChar; }
	void setIsSelectedChar(bool value) { _isSelectedChar = value; }

	float* getCharValueCur() { return _charValue[CUR]; }
	float* getCharValueAug() { return _charValue[CUR]; }

	void setCurHpAug(float augVal) { 
		float def = _charValue[0][CHAR_VALUE_KINDS::DEF] + _charValue[1][CHAR_VALUE_KINDS::DEF];
		if (_state == CHAR_STATE::BLOCK) {
			def *= 2;
		}
			
		float defRatio = (def / DEF_MAX);
		if (defRatio > DEFRATIO_MAX)
			defRatio = DEFRATIO_MAX;
		_charValue[0][CHAR_VALUE_KINDS::CUR_HP] += augVal * (1-defRatio);
		_preState = _state;
		_state = CHAR_STATE::GETHIT;
		_isStateChanged = true;
		_curState = _arrStatePattern[static_cast<const int>(_state)];
	}
	void setCurMpAug(float augVal) { _charValue[0][CHAR_VALUE_KINDS::CUR_MP] += augVal; }
	void setCurSpAug(float augVal) { _charValue[0][CHAR_VALUE_KINDS::CUR_SP] += augVal; }
	
	
	

	ORDER_KINDS getModeKinds() { return _mode; }


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


