#pragma once
#include "skillNode.h"
class meteor : public skillNode
{
private:

	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 2.3f;

	const int AUG_X = 175;
	const int AUG_Y = -200;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

	const int CASTCOUNT_MAX = 1600;
	const int RANGE = 12;

	const float MANACOST = 80;

public:
	meteor();
	~meteor();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

