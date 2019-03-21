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


	_multiNum = MULTI_NUM;
	_attr = ATTR;
	_attrAdjustRatio = ATTR_ADJUST_RATIO;

	_castCountMax = CASTCOUNT_MAX;
	_range = RANGE;

	EFFECTMANAGER->addEffect("meteor", "images/skillEffect/meteor.png", 8338, 490, 758, 490, 1, 0.167f, 6);


	return S_OK;
}

void meteor::release()
{
}

void meteor::StartSkillEffect(POINT curMapIdx, int dir)
{
	POINTFLOAT pos = ConvertIdxToPosFloat(curMapIdx.x, curMapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	// Adjust Pos by Dir

	pos.x -= AUG_X;
	pos.y -= 50;
	EFFECTMANAGER->play("meteor", pos.x, pos.y);
}
