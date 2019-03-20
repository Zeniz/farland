#pragma once
#include "skillNode.h"
class doubleSlash : public skillNode
{
private:

	const float MULTI_NUM = 2.3f;

	const int AUG_X = 0;
	const int AUG_Y = 0;

public:
	doubleSlash();
	~doubleSlash();

	HRESULT init() override;
	void release() override;
	void StartSkillEffect(POINT curMapIdx, int dir) override;
};

