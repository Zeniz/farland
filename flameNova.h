#pragma once
#include "skillNode.h"
class flameNova : public skillNode
{
private:

	const float MULTI_NUM = 0.9f;

	const int AUG_X = 0;
	const int AUG_Y = 0;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 1000;
	const int RANGE = 1;

public:
	flameNova();
	~flameNova();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

