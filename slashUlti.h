#pragma once
#include "skillNode.h"
class slashUlti : public skillNode
{
private:

	const float MULTI_NUM_PHYSIC = 1.5f;
	const float MULTI_NUM_MAGIC = 0.5f;

	const int AUG_X = 32;
	const int AUG_Y = -64;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_STUN;
	const float ATTR_ADJUST_RATIO = 1.f;

	const int CASTCOUNT_MAX = 150;
	const int RANGE = 1;

	const float MANACOST = 70;

public:
	slashUlti();
	~slashUlti();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir, int zLvl) override;
};

