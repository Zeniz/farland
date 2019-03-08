#pragma once
#include "gameNode.h"
#include "character.h"

class Character;

class charStatePattern abstract
{
public:

	virtual void onIdle(Character* character) abstract;
	virtual void onMove(Character* character) abstract;
	virtual void onCast(Character* character) abstract;
	virtual void onDead(Character* character) abstract;
	virtual void onGetHit(Character* character) abstract;
	virtual void onStone(Character* character) abstract;
	virtual void onFrozen(Character* character) abstract;
	virtual void onGetHit2(Character* character) abstract;
	virtual void onBlock(Character* character) abstract;

	virtual void update(Character* character) abstract;




};

