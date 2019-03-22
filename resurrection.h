#pragma once
#include "skillNode.h"
class resurrection : public skillNode
{
private:
	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 0.f;

	const int AUG_X = 0;
	const int AUG_Y = -96;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 1200;
	const int RANGE = 5;

	const float MANACOST = 60;

public:
	resurrection();
	~resurrection();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

