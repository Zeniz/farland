#pragma once
#include "skillNode.h"
class roundSlash : public skillNode
{
private:

	const float MULTI_NUM_PHYSIC = 0.9f;
	const float MULTI_NUM_MAGIC = 0.f;

	const int AUG_X = 64;
	const int AUG_Y = 32;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 100;
	const int RANGE = 1;

	const float MANACOST = 30;

public:
	roundSlash();
	~roundSlash();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) override;

};

