#include "stdafx.h"
#include "stateSkillOne.h"


stateSkillOne::stateSkillOne()
{
}


stateSkillOne::~stateSkillOne()
{
}

void stateSkillOne::onIdle(Character * character)
{
}

void stateSkillOne::onMove(Character * character)
{
}

void stateSkillOne::onCast(Character * character)
{
}

void stateSkillOne::onDead(Character * character)
{
}

void stateSkillOne::onGetHit(Character * character)
{
}

void stateSkillOne::onStone(Character * character)
{
}

void stateSkillOne::onFrozen(Character * character)
{
}

void stateSkillOne::onGetHit2(Character * character)
{
}

void stateSkillOne::onBlock(Character * character)
{
}

void stateSkillOne::onBasicAtk(Character * character)
{
}

void stateSkillOne::onSkillOne(Character * character)
{
}

void stateSkillOne::onSkillTwo(Character * character)
{
}

void stateSkillOne::onSkillThree(Character * character)
{
}

void stateSkillOne::onSkillFour(Character * character)
{
}

void stateSkillOne::update(Character * character)
{
	//	프레임이 끝나면, 공격적용!
	if (character->_ani->isLastFrame()) {
		SKILLMANAGER->FindSkill(character->_skillName[(int)SKILL_NUM::SKILL1])->StartSkillEffect(
			character->mapIdx, (int)character->_dir);
		


		vEnemy* _vEnemy = character->_vEnemy;
		character->_coolDownTimer[0][ORDER_KINDS::SKILL1] = 0;

		(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
			-(character->_charValue[0][CHAR_VALUE_KINDS::ATK]* character->SKILL1_MULTI +
			character->_charValue[1][CHAR_VALUE_KINDS::ATK]* character->SKILL1_MULTI));


		//	공격적용 후, 오더 삭제후 idle로 돌아감
		if (character->_lOrderList.size() != 0) {
			character->_lOrderList.pop_front();
		}
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}
	
}
