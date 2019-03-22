#include "stdafx.h"
#include "heal2.h"


heal2::heal2()
{
}


heal2::~heal2()
{
}

HRESULT heal2::init()
{
	_skillName.clear();
	_skillName = "heal2";

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

	_skillKinds = SKILL_KINDS::SKILL_KINDS_HEAL;

	EFFECTMANAGER->addEffect("heal2", "images/skillEffect/heal2.png", 6593, 250, 347, 250, 1, 0.167f, 2);


	return S_OK;
}

void heal2::release()
{
}

void heal2::StartSkillEffect(POINT curMapIdx, int dir)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir

	pos.x += AUG_X;
	pos.y += AUG_Y;
	EFFECTMANAGER->play("heal2", pos.x, pos.y);
}
