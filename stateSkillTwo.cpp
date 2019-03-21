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
	//	프레임이 끝나면, 공격적용!
	if (character->_ani->isLastFrame()) {
		skillNode* curSkill = SKILLMANAGER->FindSkill(character->_skillName[(int)SKILL_NUM::SKILL2]);
		curSkill->StartSkillEffect(
			character->mapIdx, (int)character->_dir);
		character->_coolDownTimer[0][ORDER_KINDS::SKILL2] = 0;


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

					//	속성적용
					SKILL_ATTR skillAttr = curSkill->getAttr();
					float attrAdjustRatio = curSkill->getAttrAdjustRatio();
					switch (skillAttr)
					{
					case SKILL_ATTR_NONE:
						break;
					case SKILL_ATTR_STUN:
						if (attrAdjustRatio * 100 > RND->getFromIntTo(1, 101)) {
							(*_vEnemy)[j]->setState(E_STATE::E_STUNNED);
						}
						break;
					case SKILL_ATTR_FROZEN:
						if (attrAdjustRatio * 100 > RND->getFromIntTo(1, 101)) {
							(*_vEnemy)[j]->setState(E_STATE::E_FROZEN);
						}
						break;
					case SKILL_ATTR_STONE:
						if (attrAdjustRatio * 100 > RND->getFromIntTo(1, 101)) {
							(*_vEnemy)[j]->setState(E_STATE::E_STONED);
						}
						break;
					default:
						break;
					}
					//	속성적용 끗-
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
