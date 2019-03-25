#include "stdafx.h"
#include "flameBurst.h"


flameBurst::flameBurst()
{
}


flameBurst::~flameBurst()
{
}

HRESULT flameBurst::init()
{
	_skillName.clear();
	_skillName = "flameBurst";

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

	_skillKinds = SKILL_KINDS::SKILL_KINDS_ATK;

	EFFECTMANAGER->addEffect("flameBurst", "images/skillEffect/flameBurst.png", 3376, 355, 422, 355, 1, 0.167f, 2);
	

	return S_OK;
}

void flameBurst::release()
{
}

void flameBurst::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir
	
	pos.x += AUG_X;
	pos.y += AUG_Y - zLvl * TILESIZE_HEI/2;
	EFFECTMANAGER->play("flameBurst", pos.x, pos.y);
	
}
