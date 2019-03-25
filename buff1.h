#pragma once
#include "skillNode.h"
class buff1 : public skillNode
{
private:
	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 1.5f;

	const int AUG_X = 0;
	const int AUG_Y = 0;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 1000;
	const int RANGE = 5;

	const float MANACOST = 30;
	const int DURATION = 2000;
public:
	buff1();
	~buff1();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) override;
	int getDuration() { return DURATION; }
};

