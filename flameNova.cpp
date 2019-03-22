#include "stdafx.h"
#include "flameNova.h"


flameNova::flameNova()
{
}


flameNova::~flameNova()
{
}

HRESULT flameNova::init()
{
	_skillName.clear();
	_skillName = "flameNova";

	for (int i = 0; i < SKILL_DIR::SKILL_DIR_END; i++) {
		_vAugIdx[i].clear();
	}

	for (int i = 0; i < 4; i++) {
		for (int j = -2; j < 3; j++) {
			for (int k = -2; k < 3; k++) {
				_vAugIdx[i].push_back(PointMake(j, k));	// 5x5
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

	EFFECTMANAGER->addEffect("flameNova", "images/skillEffect/flameNova.png", 8715, 326, 415, 326, 1, 0.167f, 2);
	


	return S_OK;
}

void flameNova::release()
{
}

void flameNova::StartSkillEffect(POINT curMapIdx, int dir)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir

	pos.x += AUG_X;
	pos.y += AUG_Y;
	
	EFFECTMANAGER->play("flameNova", pos.x, pos.y);
}
