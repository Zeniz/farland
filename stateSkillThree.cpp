#include "stdafx.h"
#include "stateSkillThree.h"


stateSkillThree::stateSkillThree()
{
}


stateSkillThree::~stateSkillThree()
{
}

void stateSkillThree::onIdle(Character * character)
{
}

void stateSkillThree::onMove(Character * character)
{
}

void stateSkillThree::onCast(Character * character)
{
}

void stateSkillThree::onDead(Character * character)
{
}

void stateSkillThree::onGetHit(Character * character)
{
}

void stateSkillThree::onStone(Character * character)
{
}

void stateSkillThree::onFrozen(Character * character)
{
}

void stateSkillThree::onGetHit2(Character * character)
{
}

void stateSkillThree::onBlock(Character * character)
{
}

void stateSkillThree::onBasicAtk(Character * character)
{
}

void stateSkillThree::onSkillOne(Character * character)
{
}

void stateSkillThree::onSkillTwo(Character * character)
{
}

void stateSkillThree::onSkillThree(Character * character)
{
}

void stateSkillThree::onSkillFour(Character * character)
{
}

void stateSkillThree::update(Character * character)
{
	//	프레임이 끝나면, 공격적용!
	if (character->_ani->isLastFrame()) {
		vEnemy* _vEnemy = character->_vEnemy;
		character->_coolDownTimer[0][ORDER_KINDS::SKILL3] = 0;

		(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
			character->_charValue[0][CHAR_VALUE_KINDS::ATK] * character->SKILL3_MULTI +
			character->_charValue[1][CHAR_VALUE_KINDS::ATK] * character->SKILL3_MULTI);


		//	공격적용 후, 오더 삭제후 idle로 돌아감
		if (character->_lOrderList.size() != 0) {
			character->_lOrderList.pop_front();
		}
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}
}
