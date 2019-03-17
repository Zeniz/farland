#include "stdafx.h"
#include "stateBlock.h"


stateBlock::stateBlock()
{
}


stateBlock::~stateBlock()
{
}

void stateBlock::onIdle(Character * character)
{
}

void stateBlock::onMove(Character * character)
{
}

void stateBlock::onCast(Character * character)
{
}

void stateBlock::onDead(Character * character)
{
}

void stateBlock::onGetHit(Character * character)
{
}

void stateBlock::onStone(Character * character)
{
}

void stateBlock::onFrozen(Character * character)
{
}

void stateBlock::onGetHit2(Character * character)
{
}

void stateBlock::onBlock(Character * character)
{
}

void stateBlock::onBasicAtk(Character * character)
{
}

void stateBlock::onSkillOne(Character * character)
{
}

void stateBlock::onSkillTwo(Character * character)
{
}

void stateBlock::onSkillThree(Character * character)
{
}

void stateBlock::onSkillFour(Character * character)
{
}

void stateBlock::update(Character * character)
{
	//	현재 홀딩만 하고 있다면,
	if (character->_lOrderList.size() == 1) {
		if (character->_holdCounter < character->_holdCounterMax) {
			character->_holdCounter++;
		}
		else {
			character->_holdCounter = 0;
			character->HoldRegenFunc();
		}

	}
	//	다른 명령이 들어왔다면,
	if (character->_lOrderList.begin()->kinds != ORDER_KINDS::HOLD) {
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
		if ((character->_lOrderList.begin()->kinds) == ORDER_KINDS::HOLD)
			character->_lOrderList.pop_front();
	}

}
