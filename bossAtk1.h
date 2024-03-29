#pragma once
#include "skillNode.h"
class bossAtk1 : public skillNode
{
private:

	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 1.5f;

	const int AUG_X = 10;
	const int AUG_Y = -50;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 500;		//	600����
	const int RANGE = 5;
	const float MANACOST = 30;


public:
	bossAtk1();
	~bossAtk1();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) override;
};

