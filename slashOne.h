#pragma once
#include "skillNode.h"
class slashOne : public skillNode
{
private:

	const float MULTI_NUM_PHYSIC = 1.5f;
	const float MULTI_NUM_MAGIC = 0.f;
	//const int AUG_X = 373 / 2;
	//const int AUG_Y = 352 / 2;
	const int AUG_X = 50;
	const int AUG_Y = 50;

	const SKILL_ATTR ATTR = SKILL_ATTR::SKILL_ATTR_NONE;
	const float ATTR_ADJUST_RATIO = 0.f;
	
	const int CASTCOUNT_MAX = 50;
	const int RANGE = 1;

	const float MANACOST = 20;

public:
	slashOne();
	~slashOne();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;

};

