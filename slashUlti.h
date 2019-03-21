#pragma once
#include "skillNode.h"
class slashUlti : public skillNode
{
private:

	const float MULTI_NUM = 1.5f;

	const int AUG_X = 50;
	const int AUG_Y = -50;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_STUN;
	const float ATTR_ADJUST_RATIO = 1.f;

public:
	slashUlti();
	~slashUlti();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

