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
	//	�������� ������, ��������!
	if (character->_ani->isLastFrame()) {
		skillNode* curSkill = SKILLMANAGER->FindSkill(character->_skillName[(int)SKILL_NUM::SKILL4]);
		curSkill->StartSkillEffect(
			character->_lOrderList.begin()->targetMapIdx, 
			(int)character->_dir);
		character->_coolDownTimer[0][ORDER_KINDS::SKILL4] = 0;
		character->setCurMpAug(-curSkill->getManaCost());
		
		
		SKILL_KINDS skillKinds = curSkill->getSkillKinds();

		//	���ݽ� ���Ǵ� ��ų�� Ư���ɷ�
		SKILL_ATTR skillAttr = curSkill->getAttr();
		//	Ư���ɷ� ����Ȯ��
		float attrAdjustRatio = curSkill->getAttrAdjustRatio();
		vEnemy* _vEnemy = character->_vEnemy;
		SKILL_DIR skillDir = ConvertCharDirToSkillDir(character);
		POINT curIdx = character->_lOrderList.begin()->targetMapIdx;
		POINT tileIdxOnSkill;		//	��ų�� ����� Ÿ���ε���
		vChara* pvChara = character->_pvChara;
		int vCharaSize = character->_pvChara->size();

		switch (skillKinds)
		{
		case SKILL_KINDS_NONE:
			break;
		case SKILL_KINDS_ATK:
		{
			//	������ �¾Ҵ°� �Ǵ��ϰ� ������ ����
		//	��ų�� ����� Ÿ���ε�����
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	����ü�� �˻��ؼ� ���� �ε�����
				for (int j = 0; j < _vEnemy->size(); j++) {
					//	�ε����� ������ -> ������ ����!
					if ((*_vEnemy)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*_vEnemy)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	������ �����
						(*_vEnemy)[j]->setCurHpAug(
							-(	character->_charValue[0][CHAR_VALUE_KINDS::ATK] *
								curSkill->getMultiNumPhysic()
								+
								character->_charValue[1][CHAR_VALUE_KINDS::ATK] *
								curSkill->getMultiNumPhysic()
								+
								character->_charValue[0][CHAR_VALUE_KINDS::M_ATK] *
								curSkill->getMultiNumMagic()
								+
								character->_charValue[1][CHAR_VALUE_KINDS::M_ATK] *
								curSkill->getMultiNumMagic()
								));

						//	�Ӽ�����
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
		}
			break;
		case SKILL_KINDS_HEAL:
		{
			//	�Ʊ����� �¾Ҵ°� �Ǵ��ϰ� ������ ����
			//	��ų�� ����� Ÿ���ε�����
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	�Ʊ�ĳ����ü�� �˻��ؼ� ĳ������ �ε�����
				for (int j = 0; j < vCharaSize; j++) {
					//	�ε����� ������ -> ������ ����!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	�� �����
						(*pvChara)[j]->healCurHpAug(
							+(character->_charValue[0][CHAR_VALUE_KINDS::ATK] *
								curSkill->getMultiNumPhysic()
								+
								character->_charValue[1][CHAR_VALUE_KINDS::ATK] *
								curSkill->getMultiNumPhysic()
								+
								character->_charValue[0][CHAR_VALUE_KINDS::M_ATK] *
								curSkill->getMultiNumMagic()
								+
								character->_charValue[1][CHAR_VALUE_KINDS::M_ATK] *
								curSkill->getMultiNumMagic()
								));
					}
				}
			}
		}
			break;
		case SKILL_KINDS_BUFF:
			//	�Ʊ����� �¾Ҵ°� �Ǵ��ϰ� ���� ����
			//	��ų�� ����� Ÿ���ε�����
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	�Ʊ�ĳ����ü�� �˻��ؼ� ĳ������ �ε�����
				for (int j = 0; j < vCharaSize; j++) {
					//	�ε����� ������ -> ���� ����!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	���� �����
						(*pvChara)[j]->addBuff(curSkill->getSkillName(),
							IMAGEMANAGER->findImage(curSkill->getSkillName().c_str()),
							KEYANIMANAGER->findAnimation("buff", curSkill->getSkillName()),
							0, curSkill->getDuration());
					}
				}
			}
			break;
		case SKILL_KINDS_RESUR:
			//	�Ʊ����� �¾Ҵ°� �Ǵ��ϰ� ��Ȱ ����
			//	��ų�� ����� Ÿ���ε�����
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	�Ʊ�ĳ����ü�� �˻��ؼ� ĳ������ �ε�����
				for (int j = 0; j < vCharaSize; j++) {
					//	�ε����� ������ -> ��Ȱ ����!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	��Ȱ �����
						(*pvChara)[j]->ResurrectChar();
					}
				}
			}
			break;
		default:
			break;
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
