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
		skillNode* curSkill = SKILLMANAGER->FindSkill(character->_skillName[(int)SKILL_NUM::SKILL1]);
		curSkill->StartSkillEffect(
			character->mapIdx, (int)character->_dir);
		character->_coolDownTimer[0][ORDER_KINDS::SKILL1] = 0;


		//	적에게 맞았는가 판단하고 데미지 적용

		vEnemy* _vEnemy = character->_vEnemy;
		SKILL_DIR skillDir = ConvertCharDirToSkillDir(character);
		POINT curIdx = character->mapIdx;
		//	스킬이 적용될 타일인덱스와
		for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
			POINT tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
			//	몹전체를 검색해서 몹의 인덱스와
			for (int j = 0; j < _vEnemy->size(); j++) {
				//	인덱스가 같으면 -> 데미지 적용!
				if ((*_vEnemy)[j]->_mapIdx.x == tileIdxOnSkill.x &&
					(*_vEnemy)[j]->_mapIdx.y == tileIdxOnSkill.y) {
					//	데미지 적용식
					(*_vEnemy)[j]->setCurHpAug(
						-(character->_charValue[0][CHAR_VALUE_KINDS::ATK] *
							curSkill->getMultiNum() *
							character->SKILL1_MULTI +
							character->_charValue[1][CHAR_VALUE_KINDS::ATK] *
							curSkill->getMultiNum() *
							character->SKILL1_MULTI));
				}
			}
			

		}

		//	데미지 적용식
		//(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
		//	-(character->_charValue[0][CHAR_VALUE_KINDS::ATK]* 
		//		curSkill->getMultiNum() *
		//		character->SKILL1_MULTI +
		//	character->_charValue[1][CHAR_VALUE_KINDS::ATK]*
		//		curSkill->getMultiNum() *
		//		character->SKILL1_MULTI));


		//	공격적용 후, 오더 삭제후 idle로 돌아감
		if (character->_lOrderList.size() != 0) {
			character->_lOrderList.pop_front();
		}
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}
	
}
