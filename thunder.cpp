#include "stdafx.h"
#include "thunder.h"


thunder::thunder()
{
}


thunder::~thunder()
{
}

HRESULT thunder::init()
{
	_skillName.clear();
	_skillName = "thunder";
	SOUNDMANAGER->addSound("thunder", "sounds/effectSound/thunder.wav", false, false);

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

	EFFECTMANAGER->addEffect("thunder", "images/skillEffect/thunder.png", 2667, 306, 381, 306, 1, 0.167f, 2);


	return S_OK;
}

void thunder::release()
{
}

void thunder::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir

	pos.x += AUG_X;
	pos.y += AUG_Y - zLvl * TILESIZE_HEI / 2;
	EFFECTMANAGER->play("thunder", pos.x, pos.y);
	SOUNDMANAGER->play("thunder", OPTIONMANAGER->getRatioValue(OPTION_KINDS::EFFECT_SOUND));
}
