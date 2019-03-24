#include "stdafx.h"
#include "bossAtk1.h"


bossAtk1::bossAtk1()
{
}


bossAtk1::~bossAtk1()
{
}

HRESULT bossAtk1::init()
{
	_skillName.clear();
	_skillName = "bossAtk1";

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	for (int i = 0; i < 4; i++) {
		for (int j = -2; j < 3; j++) {
			for (int k = -2; k < 3; k++) {
				_vAugIdx[i].push_back(PointMake(j, k)); // 5x5
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

	_skillKinds = SKILL_KINDS::SKILL_KINDS_ATK;

	EFFECTMANAGER->addEffect("bossAtk1LB", "images/skillEffect/bossAtk1LB.png", 10465, 619, 805, 619, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("bossAtk1LT", "images/skillEffect/bossAtk1LT.png", 10465, 619, 805, 619, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("bossAtk1RB", "images/skillEffect/bossAtk1RB.png", 10465, 619, 805, 619, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("bossAtk1RT", "images/skillEffect/bossAtk1RT.png", 10465, 619, 805, 619, 1, 0.167f, 2);

	return S_OK;
}

void bossAtk1::release()
{
}

void bossAtk1::StartSkillEffect(POINT curMapIdx, int dir)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir
	switch (dir)
	{
	case SKILL_DIR_NONE:
		break;
	case SKILL_DIR_LT:
		pos.x += AUG_X;
		pos.y -= AUG_Y / 4;
		EFFECTMANAGER->play("bossAtk1LT", pos.x, pos.y);
		break;

	case SKILL_DIR_LB:
		pos.x += AUG_X;
		pos.y -= AUG_Y;
		EFFECTMANAGER->play("bossAtk1LB", pos.x, pos.y);
		break;

	case SKILL_DIR_RT:
		pos.x -= AUG_X;
		pos.y -= AUG_Y / 4;

		EFFECTMANAGER->play("bossAtk1RT", pos.x, pos.y);
		break;

	case SKILL_DIR_RB:
		pos.x -= AUG_X;
		pos.y -= AUG_Y;
		EFFECTMANAGER->play("bossAtk1RB", pos.x, pos.y);
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
}
