#pragma once
#include "charStatePattern.h"
class stateGetHit2 : public charStatePattern
{
public:
	stateGetHit2();
	~stateGetHit2();
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

	void update(Character* character) override;
};

