#include "stdafx.h"
#include "stateSkillTwo.h"


stateSkillTwo::stateSkillTwo()
{
}


stateSkillTwo::~stateSkillTwo()
{
}

void stateSkillTwo::onIdle(Character * character)
{
}

void stateSkillTwo::onMove(Character * character)
{
}

void stateSkillTwo::onCast(Character * character)
{
}

void stateSkillTwo::onDead(Character * character)
{
}

void stateSkillTwo::onGetHit(Character * character)
{
}

void stateSkillTwo::onStone(Character * character)
{
}

void stateSkillTwo::onFrozen(Character * character)
{
}

void stateSkillTwo::onGetHit2(Character * character)
{
}

void stateSkillTwo::onBlock(Character * character)
{
}

void stateSkillTwo::onBasicAtk(Character * character)
{
}

void stateSkillTwo::onSkillOne(Character * character)
{
}

void stateSkillTwo::onSkillTwo(Character * character)
{
}

void stateSkillTwo::onSkillThree(Character * character)
{
}

void stateSkillTwo::onSkillFour(Character * character)
{
}

void stateSkillTwo::update(Character * character)
{
	//	�������� ������, ��������!
	if (character->_ani->isLastFrame()) {
		vEnemy* _vEnemy = character->_vEnemy;
		character->_coolDownTimer[0][ORDER_KINDS::SKILL2] = 0;

		(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
			-(character->_charValue[0][CHAR_VALUE_KINDS::ATK] * character->SKILL2_MULTI +
			character->_charValue[1][CHAR_VALUE_KINDS::ATK] * character->SKILL2_MULTI));


		//	�������� ��, ���� ������ idle�� ���ư�
		if (character->_lOrderList.size() != 0) {
			character->_lOrderList.pop_front();
		}
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}
}
