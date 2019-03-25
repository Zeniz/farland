#include "stdafx.h"
#include "bossBuff.h"


bossBuff::bossBuff()
{
}


bossBuff::~bossBuff()
{
}

HRESULT bossBuff::init()
{
	_skillName.clear();
	_skillName = "bossBuff";

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

	IMAGEMANAGER->addFrameImage("bossBuff", L"images/skillEffect/bossBuff.png", 6912, 263, 16, 1);
	KEYANIMANAGER->addAnimationType("bossBuff");
	int buffAniAry[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("bossBuff", "bossBuff", "bossBuff",
		buffAniAry, 16, 15, true);


	return S_OK;
}

void bossBuff::release()
{
}

void bossBuff::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
}
