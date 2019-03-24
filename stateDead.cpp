#include "stdafx.h"
#include "stateDead.h"


stateDead::stateDead()
{
}


stateDead::~stateDead()
{
}

void stateDead::onIdle(Character * character)
{
}

void stateDead::onMove(Character * character)
{
}

void stateDead::onCast(Character * character)
{
}

void stateDead::onDead(Character * character)
{
}

void stateDead::onGetHit(Character * character)
{
}

void stateDead::onStone(Character * character)
{
}

void stateDead::onFrozen(Character * character)
{
}

void stateDead::onGetHit2(Character * character)
{
}

void stateDead::onBlock(Character * character)
{
}

void stateDead::onBasicAtk(Character * character)
{
}

void stateDead::onSkillOne(Character * character)
{
}

void stateDead::onSkillTwo(Character * character)
{
}

void stateDead::onSkillThree(Character * character)
{
}

void stateDead::onSkillFour(Character * character)
{
}

void stateDead::update(Character * character)
{
	character->_portraitKinds = CHAR_PORTRAIT_KINDS::DEAD;
}
