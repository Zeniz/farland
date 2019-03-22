#pragma once
#include "skillNode.h"
class thunder : public skillNode
{
private:
	
	const float MULTI_NUM_PHYSIC = 0.f;
	const float MULTI_NUM_MAGIC = 1.0f;

	const int AUG_X = 10;
	const int AUG_Y = -125;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_STUN;
	const float ATTR_ADJUST_RATIO = 6.f;

	const int CASTCOUNT_MAX = 800;
	const int RANGE = 5;

	const float MANACOST = 30;
public:
	thunder();
	~thunder();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

