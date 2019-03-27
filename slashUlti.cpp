#include "stdafx.h"
#include "slashUlti.h"


slashUlti::slashUlti()
{
}


slashUlti::~slashUlti()
{
}

HRESULT slashUlti::init()
{
	_skillName.clear();
	_skillName = "roundSlash";
	SOUNDMANAGER->addSound("slashUlti", "sounds/effectSound/swordSound1.mp3", false, false);

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, -1));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, 0));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, +1));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(0, -1));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(0, 0));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(0, +1));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(+1, -1));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(+1, 0));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(+1, +1));

	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(-1, -1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(-1, 0));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(-1, +1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(0, -1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(0, 0));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(0, +1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(+1, -1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(+1, 0));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(+1, +1));

	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(-1, -1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(-1, 0));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(-1, +1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(0, -1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(0, 0));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(0, +1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(+1, -1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(+1, 0));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(+1, +1));

	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(-1, -1));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(-1, 0));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(-1, +1));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(0, -1));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(0, 0));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(0, +1));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, -1));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, 0));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, +1));


	_multiNumPhysic = MULTI_NUM_PHYSIC;
	_multiNumMagic = MULTI_NUM_MAGIC;
	_attr = ATTR;
	_attrAdjustRatio = ATTR_ADJUST_RATIO;

	_castCountMax = CASTCOUNT_MAX;
	_range = RANGE;
	_manaCost = this->MANACOST;

	_skillKinds = SKILL_KINDS::SKILL_KINDS_ATK;

	EFFECTMANAGER->addEffect("slashUlti", "images/skillEffect/slashUlti.png", 6890, 334, 530, 334, 1, 0.167f, 2);


	return S_OK;
}

void slashUlti::release()
{
}

void slashUlti::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir
	switch (dir)
	{
	case SKILL_DIR_NONE:
		break;
	case SKILL_DIR_LT:	case SKILL_DIR_LB:
	case SKILL_DIR_RT:	case SKILL_DIR_RB:
		pos.x += AUG_X;
		pos.y += AUG_Y - zLvl * TILESIZE_HEI / 2;
		EFFECTMANAGER->play("slashUlti", pos.x, pos.y);
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
	SOUNDMANAGER->play("slashUlti");
}
