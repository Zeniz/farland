#pragma once
#include "skillNode.h"
class heal1 : public skillNode
{
private:
	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 1.3f;

	const int AUG_X = 0;
	const int AUG_Y = -32;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 400;
	const int RANGE = 5;

	const float MANACOST = 10;

public:
	heal1();
	~heal1();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

