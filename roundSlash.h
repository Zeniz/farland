#pragma once
#include "skillNode.h"
class roundSlash : public skillNode
{
private:

	const float MULTI_NUM = 0.9f;

	const int AUG_X = 0;
	const int AUG_Y = -50;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;

public:
	roundSlash();
	~roundSlash();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;

};

