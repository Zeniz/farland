#include "stdafx.h"
#include "roundSlash.h"


roundSlash::roundSlash()
{
}


roundSlash::~roundSlash()
{
}

HRESULT roundSlash::init()
{
	_skillName.clear();
	_skillName = "roundSlash";

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


	_multiNum = MULTI_NUM;
	_attr = ATTR;
	_attrAdjustRatio = ATTR_ADJUST_RATIO;

	EFFECTMANAGER->addEffect("roundSlash", "images/skillEffect/roundSlash.png", 5152, 191, 644, 191, 1, 0.167f, 2);
	

	return S_OK;
}

void roundSlash::release()
{
}

void roundSlash::StartSkillEffect(POINT curMapIdx, int dir)
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
		pos.y += AUG_Y;
		EFFECTMANAGER->play("roundSlash", pos.x, pos.y);
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
}
