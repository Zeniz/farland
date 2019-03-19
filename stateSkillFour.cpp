 #include "stdafx.h"
#include "stateSkillFour.h"


stateSkillFour::stateSkillFour()
{
}


stateSkillFour::~stateSkillFour()
{
}

void stateSkillFour::onIdle(Character * character)
{
}

void stateSkillFour::onMove(Character * character)
{
}

void stateSkillFour::onCast(Character * character)
{
}

void stateSkillFour::onDead(Character * character)
{
}

void stateSkillFour::onGetHit(Character * character)
{
}

void stateSkillFour::onStone(Character * character)
{
}

void stateSkillFour::onFrozen(Character * character)
{
}

void stateSkillFour::onGetHit2(Character * character)
{
}

void stateSkillFour::onBlock(Character * character)
{
}

void stateSkillFour::onBasicAtk(Character * character)
{
}

void stateSkillFour::onSkillOne(Character * character)
{
}

void stateSkillFour::onSkillTwo(Character * character)
{
}

void stateSkillFour::onSkillThree(Character * character)
{
}

void stateSkillFour::onSkillFour(Character * character)
{
	
}

void stateSkillFour::update(Character * character)
{
	//	프레임이 끝나면, 공격적용!
	if (character->_ani->isLastFrame()) {
		vEnemy* _vEnemy = character->_vEnemy;
		character->_coolDownTimer[0][ORDER_KINDS::SKILL4] = 0;

		(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
			-(character->_charValue[0][CHAR_VALUE_KINDS::ATK] * character->SKILL4_MULTI +
			character->_charValue[1][CHAR_VALUE_KINDS::ATK] * character->SKILL4_MULTI));
		(*_vEnemy)[character->_targetEnemyIdx]->setState(E_STATE::E_STUNNED);


		//	공격적용 후, 오더 삭제후 idle로 돌아감
		if (character->_lOrderList.size() != 0) {
			character->_lOrderList.pop_front();
		}
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}
}
