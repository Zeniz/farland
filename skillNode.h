#pragma once
#include "gameNode.h"
#include <vector>


//class enemy;
//class character;
//
//typedef vector<enemy*> vEnemy;
//typedef vector<character*> vChara;

typedef vector<POINT> vPOINT;

enum SKILL_DIR {
	SKILL_DIR_NONE = -1,
	SKILL_DIR_LT,
	SKILL_DIR_LB,
	SKILL_DIR_RT,
	SKILL_DIR_RB,

	SKILL_DIR_END,
};

enum SKILL_ATTR {
	SKILL_ATTR_NONE = 0,
	SKILL_ATTR_STUN,
	SKILL_ATTR_FROZEN,
	SKILL_ATTR_STONE,

};

class skillNode : public gameNode
{
protected:
	string _skillName;
	vPOINT _vAugIdx[SKILL_DIR_END];	//	LT, LB, RT, RB
	float _multiNum;

	SKILL_ATTR _attr;
	float _attrAdjustRatio;

	int _castCountMax;

	int _range;




public:
	skillNode();
	~skillNode();

	virtual HRESULT init() abstract;
	virtual void release() abstract;
	virtual void StartSkillEffect(POINT curMapIdx, int dir) abstract;




	int getAugIdxSize(SKILL_DIR dir) { return _vAugIdx[dir].size(); }
	POINT getAugIdx(SKILL_DIR dir, int idx) { return _vAugIdx[dir][idx]; }
	float getMultiNum() { return _multiNum; }
	SKILL_ATTR getAttr() { return _attr; }
	float getAttrAdjustRatio() { return _attrAdjustRatio; }
	int getCastCountMax() { return _castCountMax; }
	int getRange() { return _range; }
	

};

