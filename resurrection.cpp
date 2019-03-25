#include "stdafx.h"
#include "resurrection.h"


resurrection::resurrection()
{
}


resurrection::~resurrection()
{
}

HRESULT resurrection::init()
{
	_skillName.clear();
	_skillName = "resurrection";

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

	_skillKinds = SKILL_KINDS::SKILL_KINDS_RESUR;

	EFFECTMANAGER->addEffect("resurrection", "images/skillEffect/resurrection.png", 5185, 448, 305, 448, 1, 0.167f, 2);


	return S_OK;
}

void resurrection::release()
{
}

void resurrection::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir

	pos.x += AUG_X;
	pos.y += AUG_Y - zLvl * TILESIZE_HEI / 2;
	EFFECTMANAGER->play("resurrection", pos.x, pos.y);
}
