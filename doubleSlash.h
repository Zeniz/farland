#pragma once
#include "skillNode.h"
class doubleSlash : public skillNode
{
private:

	const float MULTI_NUM_PHYSIC = 2.3f;
	const float MULTI_NUM_MAGIC = 0.f;

	const int AUG_X = 50;
	const int AUG_Y = 100;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 80;
	const int RANGE = 1;

	const float MANACOST = 50;

public:
	doubleSlash();
	~doubleSlash();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) override;
};

