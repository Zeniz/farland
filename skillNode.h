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

enum SKILL_KINDS {
	SKILL_KINDS_NONE = -1,
	SKILL_KINDS_ATK,
	SKILL_KINDS_HEAL,
	SKILL_KINDS_BUFF,
	SKILL_KINDS_RESUR,
};

class skillNode : public gameNode
{
protected:
	string _skillName;
	vPOINT _vAugIdx[SKILL_DIR_END];	//	LT, LB, RT, RB
	float _multiNumPhysic;
	float _multiNumMagic;

	SKILL_ATTR _attr;
	float _attrAdjustRatio;

	float _manaCost;
	int _castCountMax;

	
	int _range;

	SKILL_KINDS _skillKinds;

	int _duration;




public:
	skillNode();
	~skillNode();

	virtual HRESULT init() abstract;
	virtual void release() abstract;
	virtual void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) abstract;




	int getAugIdxSize(SKILL_DIR dir) { return _vAugIdx[dir].size(); }
	POINT getAugIdx(SKILL_DIR dir, int idx) { return _vAugIdx[dir][idx]; }
	float getMultiNumPhysic() { return _multiNumPhysic; }
	float getMultiNumMagic() { return _multiNumMagic; }
	SKILL_ATTR getAttr() { return _attr; }
	float getAttrAdjustRatio() { return _attrAdjustRatio; }
	int getCastCountMax() { return _castCountMax; }
	int getRange() { return _range; }
	string getSkillName() { return _skillName; }
	SKILL_KINDS getSkillKinds() { return _skillKinds; }
	float getManaCost() { return _manaCost; }
	int getDuration() { return _duration; }
	

};

