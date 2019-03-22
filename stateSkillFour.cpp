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
		skillNode* curSkill = SKILLMANAGER->FindSkill(character->_skillName[(int)SKILL_NUM::SKILL4]);
		curSkill->StartSkillEffect(
			character->_lOrderList.begin()->targetMapIdx, 
			(int)character->_dir);
		character->_coolDownTimer[0][ORDER_KINDS::SKILL4] = 0;
		character->setCurMpAug(-curSkill->getManaCost());
		
		
		SKILL_KINDS skillKinds = curSkill->getSkillKinds();

		//	공격시 사용되는 스킬의 특수능력
		SKILL_ATTR skillAttr = curSkill->getAttr();
		//	특수능력 적용확률
		float attrAdjustRatio = curSkill->getAttrAdjustRatio();
		vEnemy* _vEnemy = character->_vEnemy;
		SKILL_DIR skillDir = ConvertCharDirToSkillDir(character);
		POINT curIdx = character->_lOrderList.begin()->targetMapIdx;
		POINT tileIdxOnSkill;		//	스킬이 적용될 타일인덱스
		vChara* pvChara = character->_pvChara;
		int vCharaSize = character->_pvChara->size();

		switch (skillKinds)
		{
		case SKILL_KINDS_NONE:
			break;
		case SKILL_KINDS_ATK:
		{
			//	적에게 맞았는가 판단하고 데미지 적용
		//	스킬이 적용될 타일인덱스와
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	몹전체를 검색해서 몹의 인덱스와
				for (int j = 0; j < _vEnemy->size(); j++) {
					//	인덱스가 같으면 -> 데미지 적용!
					if ((*_vEnemy)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*_vEnemy)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	데미지 적용식
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

						//	속성적용
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
		}
			break;
		case SKILL_KINDS_HEAL:
		{
			//	아군에게 맞았는가 판단하고 데미지 적용
			//	스킬이 적용될 타일인덱스와
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	아군캐릭전체를 검색해서 캐릭터의 인덱스와
				for (int j = 0; j < vCharaSize; j++) {
					//	인덱스가 같으면 -> 데미지 적용!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	힐 적용식
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
			//	아군에게 맞았는가 판단하고 버프 적용
			//	스킬이 적용될 타일인덱스와
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	아군캐릭전체를 검색해서 캐릭터의 인덱스와
				for (int j = 0; j < vCharaSize; j++) {
					//	인덱스가 같으면 -> 버프 적용!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	버프 적용식
						(*pvChara)[j]->addBuff(curSkill->getSkillName(),
							IMAGEMANAGER->findImage(curSkill->getSkillName().c_str()),
							KEYANIMANAGER->findAnimation("buff", curSkill->getSkillName()),
							0, curSkill->getDuration());
					}
				}
			}
			break;
		case SKILL_KINDS_RESUR:
			//	아군에게 맞았는가 판단하고 부활 적용
			//	스킬이 적용될 타일인덱스와
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	아군캐릭전체를 검색해서 캐릭터의 인덱스와
				for (int j = 0; j < vCharaSize; j++) {
					//	인덱스가 같으면 -> 부활 적용!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	부활 적용식
						(*pvChara)[j]->ResurrectChar();
					}
				}
			}
			break;
		default:
			break;
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
