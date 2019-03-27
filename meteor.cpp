#include "stdafx.h"
#include "meteor.h"


meteor::meteor()
{
}


meteor::~meteor()
{
}

HRESULT meteor::init()
{
	_skillName.clear();
	_skillName = "meteor";

	SOUNDMANAGER->addSound("meteor", "sounds/effectSound/meteorSound2.mp3", false, false);

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

	EFFECTMANAGER->addEffect("meteor", "images/skillEffect/meteor.png", 8338, 490, 758, 490, 1, 0.167f, 6);


	return S_OK;
}

void meteor::release()
{
}

void meteor::StartSkillEffect(POINT curMapIdx, int dir, int zLvl)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir

	pos.x += AUG_X;
	pos.y += AUG_Y;
	EFFECTMANAGER->play("meteor", pos.x, pos.y);

	for (int i = 0; i < 3; i++) {
		pos = ConvertIdxToPosFloat(curMapIdx.x + RND->getFromIntTo(-2, 3), curMapIdx.y + RND->getFromIntTo(-3, 4), TILESIZE_WID, TILESIZE_HEI);
		pos.x += AUG_X;
		pos.y += AUG_Y - zLvl * TILESIZE_HEI / 2;
		EFFECTMANAGER->play("meteor", pos.x, pos.y);
	}
	SOUNDMANAGER->play("meteor", OPTIONMANAGER->getRatioValue(OPTION_KINDS::EFFECT_SOUND));
	
}
