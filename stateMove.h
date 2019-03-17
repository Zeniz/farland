#pragma once
#include "charStatePattern.h"
class stateMove : public charStatePattern
{
public:
	stateMove();
	~stateMove();
public:
	void onIdle(Character* character) override;
	void onMove(Character* character) override;
	void onCast(Character* character) override;
	void onDead(Character* character) override;
	void onGetHit(Character* character) override;
	void onStone(Character* character) override;
	void onFrozen(Character* character) override;
	void onGetHit2(Character* character) override;
	void onBlock(Character* character) override;

	void onBasicAtk(Character* character) override;
	void onSkillOne(Character* character) override;
	void onSkillTwo(Character* character) override;
	void onSkillThree(Character* character) override;
	void onSkillFour(Character* character) override;

	void update(Character* character) override;


	
	void CalDirFunc(Character* character);
	void CalTileForRender(Character* character);
};

