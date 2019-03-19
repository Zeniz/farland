#include "stdafx.h"
#include "stateGetHit.h"


stateGetHit::stateGetHit()
{
}


stateGetHit::~stateGetHit()
{
}

void stateGetHit::onIdle(Character* character)
{
}

void stateGetHit::onMove(Character* character)
{
}

void stateGetHit::onCast(Character* character)
{
}

void stateGetHit::onDead(Character* character)
{
}

void stateGetHit::onGetHit(Character* character)
{
}

void stateGetHit::onStone(Character* character)
{
}

void stateGetHit::onFrozen(Character* character)
{
}

void stateGetHit::onGetHit2(Character* character)
{
}

void stateGetHit::onBlock(Character* character)
{
}

void stateGetHit::onBasicAtk(Character * character)
{
}

void stateGetHit::onSkillOne(Character * character)
{
}

void stateGetHit::onSkillTwo(Character * character)
{
}

void stateGetHit::onSkillThree(Character * character)
{
}

void stateGetHit::onSkillFour(Character * character)
{
}

void stateGetHit::update(Character* character)
{
	character->_portraitKinds = CHAR_PORTRAIT_KINDS::GETDMG;
	if (!character->_ani->isPlay()) {
		character->_state = character->_preState;
		character->_isStateChanged = true;
		character->_curState = character->_arrStatePattern[static_cast<const int>(character->_state)];		
	}
}
