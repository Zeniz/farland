#include "stdafx.h"
#include "doubleSlash.h"


doubleSlash::doubleSlash()
{
}


doubleSlash::~doubleSlash()
{
}

HRESULT doubleSlash::init()
{
	_skillName.clear();
	_skillName = "doubleSlash";

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, 0));

	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(0, +1));

	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(0, -1));

	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, 0));

	_multiNum = MULTI_NUM;

	EFFECTMANAGER->addEffect("doubleSlashLB", "images/skillEffect/doubleSlashLB.png", 2448, 280, 306, 280, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("doubleSlashLT", "images/skillEffect/doubleSlashLT.png", 2448, 280, 306, 280, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("doubleSlashRB", "images/skillEffect/doubleSlashRB.png", 2448, 280, 306, 280, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("doubleSlashRT", "images/skillEffect/doubleSlashRT.png", 2448, 280, 306, 280, 1, 0.167f, 2);

	return S_OK;
}

void doubleSlash::release()
{
}

void doubleSlash::StartSkillEffect(POINT curMapIdx, int dir)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir
	switch (dir)
	{
	case SKILL_DIR_NONE:
		break;
	case SKILL_DIR_LT:
		pos.x -= AUG_X;
		pos.y -= 50;
		EFFECTMANAGER->play("doubleSlashLT", pos.x, pos.y);
		break;

	case SKILL_DIR_LB:
		pos.x -= AUG_X;
		pos.y += AUG_Y;
		EFFECTMANAGER->play("doubleSlashLB", pos.x, pos.y);
		break;

	case SKILL_DIR_RT:
		pos.x += AUG_X;
		pos.y -= 50;
		EFFECTMANAGER->play("doubleSlashRT", pos.x, pos.y);
		break;

	case SKILL_DIR_RB:
		pos.x += AUG_X;
		pos.y += AUG_Y;
		EFFECTMANAGER->play("doubleSlashRB", pos.x, pos.y);
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
}
