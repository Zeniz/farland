#include "stdafx.h"
#include "stateCast.h"


stateCast::stateCast()
{
}


stateCast::~stateCast()
{
}

void stateCast::onIdle(Character * character)
{
}

void stateCast::onMove(Character * character)
{
}

void stateCast::onCast(Character * character)
{
}

void stateCast::onDead(Character * character)
{
}

void stateCast::onGetHit(Character * character)
{
}

void stateCast::onStone(Character * character)
{
}

void stateCast::onFrozen(Character * character)
{
}

void stateCast::onGetHit2(Character * character)
{
}

void stateCast::onBlock(Character * character)
{
}

void stateCast::onBasicAtk(Character * character)
{
}

void stateCast::onSkillOne(Character * character)
{
}

void stateCast::onSkillTwo(Character * character)
{
}

void stateCast::onSkillThree(Character * character)
{
}

void stateCast::onSkillFour(Character * character)
{
}

void stateCast::update(Character * character)
{
	character->_castingCount+= character->_charValue[CUR][CASTING_SPD] + character->_charValue[AUG][CASTING_SPD];
	character->_portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
	string skillName;
	
	//	카렌 애니전환용
	if (character->_name == CHAR_NAME::CAREN) {
		if (character->_ani->isLastFrame()) {
			character->_isStateChanged = true;
			character->_isCastBegin = false;
		}
	}
	

	switch (character->_lOrderList.begin()->kinds)
	{
	case ORDER_KINDS::SKILL1:
		skillName = character->_skillName[(int)SKILL_NUM::SKILL1];
		if (character->_castingCount >= SKILLMANAGER->FindSkill(skillName)->getCastCountMax()) {
			character->_castingCount = 0;
			character->_state = CHAR_STATE::SKILL1;
			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL1)];
			character->_isStateChanged = true;
		}
		break;
	case ORDER_KINDS::SKILL2:
		skillName = character->_skillName[(int)SKILL_NUM::SKILL2];
		if (character->_castingCount >= SKILLMANAGER->FindSkill(skillName)->getCastCountMax()) {
			character->_castingCount = 0;
			character->_state = CHAR_STATE::SKILL2;
			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL2)];
			character->_isStateChanged = true;
		}

		break;
	case ORDER_KINDS::SKILL3:
		skillName = character->_skillName[(int)SKILL_NUM::SKILL3];
		if (character->_castingCount >= SKILLMANAGER->FindSkill(skillName)->getCastCountMax()) {
			character->_castingCount = 0;
			character->_state = CHAR_STATE::SKILL3;
			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL3)];
			character->_isStateChanged = true;
		}

		break;
	case ORDER_KINDS::SKILL4:
		skillName = character->_skillName[(int)SKILL_NUM::SKILL4];
		if (character->_castingCount >= SKILLMANAGER->FindSkill(skillName)->getCastCountMax()) {
		//if (character->_castingCount >= character->CAST4COUNT_MAX) {
			character->_castingCount = 0;
			character->_state = CHAR_STATE::SKILL4;
			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL4)];
			character->_isStateChanged = true;
		}
		break;


	default:
		character->_castingCount = 0;
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
		break;
	}


	
}
