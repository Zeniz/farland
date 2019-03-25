#pragma once
#include "skillNode.h"
class heal2 : public skillNode
{
private:
	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 2.f;

	const int AUG_X = 0;
	const int AUG_Y = -32;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 700;
	const int RANGE = 5;

	const float MANACOST = 20;

public:
	heal2();
	~heal2();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) override;
};

