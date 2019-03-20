#include "stdafx.h"
#include "slashOne.h"


slashOne::slashOne()
{
}


slashOne::~slashOne()
{
}

HRESULT slashOne::init()
{
	_skillName.clear();
	_skillName = "slashOne";

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, 0));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, -1));
	_vAugIdx[SKILL_DIR_LT].push_back(PointMake(-1, +1));

	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(0, +1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(-1, +1));
	_vAugIdx[SKILL_DIR_LB].push_back(PointMake(+1, +1));

	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(0, -1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(-1, -1));
	_vAugIdx[SKILL_DIR_RT].push_back(PointMake(+1, -1));

	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, 0));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, -1));
	_vAugIdx[SKILL_DIR_RB].push_back(PointMake(+1, +1));

	_multiNum = MULTI_NUM;

	EFFECTMANAGER->addEffect("slash1LB", "images/skillEffect/slash1LB.png", 2984, 352, 373, 352, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("slash1LT", "images/skillEffect/slash1LT.png", 2984, 352, 373, 352, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("slash1RB", "images/skillEffect/slash1RB.png", 2984, 352, 373, 352, 1, 0.167f, 2);
	EFFECTMANAGER->addEffect("slash1RT", "images/skillEffect/slash1RT.png", 2984, 352, 373, 352, 1, 0.167f, 2);
	
	return S_OK;
}

void slashOne::release()
{
}

void slashOne::StartSkillEffect(POINT curMapIdx, int dir)
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
		EFFECTMANAGER->play("slash1LT", pos.x, pos.y);
		break;

	case SKILL_DIR_LB:
		pos.x -= AUG_X;
		pos.y += AUG_Y;
		EFFECTMANAGER->play("slash1LB", pos.x, pos.y);
		break;

	case SKILL_DIR_RT:
		pos.x += AUG_X;
		pos.y -= 50;
		EFFECTMANAGER->play("slash1RT", pos.x, pos.y);
		break;

	case SKILL_DIR_RB:
		pos.x += AUG_X;
		pos.y += AUG_Y;
		EFFECTMANAGER->play("slash1RB", pos.x, pos.y);
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
	
}

