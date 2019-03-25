#include "stdafx.h"
#include "buff1.h"


buff1::buff1()
{
}


buff1::~buff1()
{
}

HRESULT buff1::init()
{
	_skillName.clear();
	_skillName = "buff1";

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	for (int i = 0; i < 4; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				_vAugIdx[i].push_back(PointMake(j, k)); // 3x3
			}
		}
	}


	_multiNumPhysic = MULTI_NUM_PHYSIC;
	_multiNumMagic = MULTI_NUM_MAGIC;
	_attr = ATTR;
	_attrAdjustRatio = ATTR_ADJUST_RATIO;

	_castCountMax = CASTCOUNT_MAX;
	_range = RANGE;
	_manaCost = this->MANACOST;
	_duration = this->DURATION;


	_skillKinds = SKILL_KINDS::SKILL_KINDS_BUFF;

	IMAGEMANAGER->addFrameImage("buff1", L"images/skillEffect/buff1.png", 2260, 102, 20, 1);
	KEYANIMANAGER->addAnimationType("buff1");
	int buffAniAry[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("buff1", "buff1", "buff1",
		buffAniAry, 20, 15, true);
	

	return S_OK;
}

void buff1::release()
{
}

void buff1::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
}
