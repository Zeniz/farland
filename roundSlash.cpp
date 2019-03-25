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

	for (int i = 0; i < 4; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				switch (i)
				{
				case SKILL_DIR::SKILL_DIR_LT:
					_vAugIdx[i].push_back(PointMake(j+1, k));
					break;
				case SKILL_DIR::SKILL_DIR_LB:
					_vAugIdx[i].push_back(PointMake(j, k-1));
					break;
				case SKILL_DIR::SKILL_DIR_RT:
					_vAugIdx[i].push_back(PointMake(j, k+1));
					break;
				case SKILL_DIR::SKILL_DIR_RB:
					_vAugIdx[i].push_back(PointMake(j - 1, k));
					break;
				default:
					break;
				}
				
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

	EFFECTMANAGER->addEffect("roundSlash", "images/skillEffect/roundSlash.png", 5152, 191, 644, 191, 1, 0.167f, 2);
	

	return S_OK;
}

void roundSlash::release()
{
}

void roundSlash::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir
	switch (dir)
	{
		//	 자신위치 y -> -50
	case SKILL_DIR_NONE:
		break;
	case SKILL_DIR_LT:
		pos.x += AUG_X;
		pos.y += -25 - zLvl * TILESIZE_HEI / 2;
		
		break;
	case SKILL_DIR_LB:
		pos.x += AUG_X;
		pos.y -= AUG_Y * 3 + zLvl * TILESIZE_HEI / 2;
		
		break;
	case SKILL_DIR_RT:
		pos.x -= AUG_X;
		pos.y += -25 - zLvl * TILESIZE_HEI / 2;
		
		break;
	case SKILL_DIR_RB:
		pos.x -= AUG_X;
		pos.y -= AUG_Y * 3 + zLvl * TILESIZE_HEI / 2;
		
		break;
	case SKILL_DIR_END:
		break;
	default:
		break;
	}
	EFFECTMANAGER->play("roundSlash", pos.x, pos.y);
}
