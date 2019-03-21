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
	//	�������� ������, ��������!
	if (character->_ani->isLastFrame()) {
		skillNode* curSkill = SKILLMANAGER->FindSkill(character->_skillName[(int)SKILL_NUM::SKILL3]);
		curSkill->StartSkillEffect(
			character->mapIdx, (int)character->_dir);
		character->_coolDownTimer[0][ORDER_KINDS::SKILL3] = 0;


		//	������ �¾Ҵ°� �Ǵ��ϰ� ������ ����

		vEnemy* _vEnemy = character->_vEnemy;
		SKILL_DIR skillDir = ConvertCharDirToSkillDir(character);
		POINT curIdx = character->mapIdx;
		//	��ų�� ����� Ÿ���ε�����
		for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
			POINT tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
			//	����ü�� �˻��ؼ� ���� �ε�����
			for (int j = 0; j < _vEnemy->size(); j++) {
				//	�ε����� ������ -> ������ ����!
				if ((*_vEnemy)[j]->_mapIdx.x == tileIdxOnSkill.x &&
					(*_vEnemy)[j]->_mapIdx.y == tileIdxOnSkill.y) {
					//	������ �����
					(*_vEnemy)[j]->setCurHpAug(
						-(character->_charValue[0][CHAR_VALUE_KINDS::ATK] *
							curSkill->getMultiNum() *
							character->SKILL1_MULTI +
							character->_charValue[1][CHAR_VALUE_KINDS::ATK] *
							curSkill->getMultiNum() *
							character->SKILL1_MULTI));

					//	�Ӽ�����
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
					//	�Ӽ����� ��-

				}
			}


		}

		//	������ �����
		//(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
		//	-(character->_charValue[0][CHAR_VALUE_KINDS::ATK]* 
		//		curSkill->getMultiNum() *
		//		character->SKILL1_MULTI +
		//	character->_charValue[1][CHAR_VALUE_KINDS::ATK]*
		//		curSkill->getMultiNum() *
		//		character->SKILL1_MULTI));


		//	�������� ��, ���� ������ idle�� ���ư�
		if (character->_lOrderList.size() != 0) {
			character->_lOrderList.pop_front();
		}
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}
}
