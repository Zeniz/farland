#include "stdafx.h"
#include "bossAtk2.h"


bossAtk2::bossAtk2()
{
}


bossAtk2::~bossAtk2()
{
}

HRESULT bossAtk2::init()
{
	_skillName.clear();
	_skillName = "bossAtk2";

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	//	LT : y -1~1, x 0 ~ -3
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j > -4; j--) {
			_vAugIdx[SKILL_DIR_LT].push_back(PointMake(j, i));
		}
	}

	//	LB : x -1~1, y 0 ~ 3
	for (int i = 0; i < 4; i++) {
		for (int j = -1; j < 2; j++) {
			_vAugIdx[SKILL_DIR_LB].push_back(PointMake(j, i));
		}
	}

	//	RT : x -1~1, y 0 ~ -3
	for (int i = 0; i > -4; i--) {
		for (int j = -1; j < 2; j++) {
			_vAugIdx[SKILL_DIR_RT].push_back(PointMake(j, i));
		}
	}

	//	RB : x 0~3, y -1 ~ 1
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			_vAugIdx[SKILL_DIR_RB].push_back(PointMake(j, i));
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


	EFFECTMANAGER->addEffect("bossAtk2LB", "images/skillEffect/bossAtk2LB.png", 9852, 821, 821, 821, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("bossAtk2LT", "images/skillEffect/bossAtk2LT.png", 9852, 821, 821, 821, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("bossAtk2RB", "images/skillEffect/bossAtk2RB.png", 9852, 821, 821, 821, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("bossAtk2RT", "images/skillEffect/bossAtk2RT.png", 9852, 821, 821, 821, 1, 0.167f, 2);

	return S_OK;
}

void bossAtk2::release()
{
}

void bossAtk2::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir
	switch (dir)
	{
	case SKILL_DIR_NONE:
		break;
	case SKILL_DIR_LT:
		pos.x += AUG_X;
		pos.y -= AUG_Y / 4 + zLvl * TILESIZE_HEI / 2;
		EFFECTMANAGER->play("bossAtk2LT", pos.x, pos.y);
		break;

	case SKILL_DIR_LB:
		pos.x += AUG_X;
		pos.y -= AUG_Y + zLvl * TILESIZE_HEI / 2;
		EFFECTMANAGER->play("bossAtk2LB", pos.x, pos.y);
		break;

	case SKILL_DIR_RT:
		pos.x -= AUG_X;
		pos.y -= AUG_Y / 4 + zLvl * TILESIZE_HEI / 2;

		EFFECTMANAGER->play("bossAtk2RT", pos.x, pos.y);
		break;

	case SKILL_DIR_RB:
		pos.x -= AUG_X;
		pos.y -= AUG_Y + zLvl * TILESIZE_HEI / 2;
		EFFECTMANAGER->play("bossAtk2RB", pos.x, pos.y);
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
}
