#include "stdafx.h"
#include "eStatePattern.h"
#include "enemy.h"
#include "character.h"


eStatePattern::eStatePattern()
{
}


eStatePattern::~eStatePattern()
{
}

void eStatePattern::Idle(enemy * enemy)
{
	enemy->_tileForRender = enemy->_pCurTile;
	enemy->_isAtkFin = false;
	bool isNearChar = false;
	int targetCharIdx = -1;
	int targetCharDistance = 999999;
	int nearCharIdx = -1;
	
	//	isNoticeTrue,
	if (enemy->_isNotice) {

		//	자기 주변에 캐릭터 있나 검색 (nearCharIdx 세팅)
		vChara* pvChara = enemy->_vChara;
		for (int i = 0; i < pvChara->size(); i++) {
			bool isAliveChar = (*pvChara)[i]->_state != CHAR_STATE::DEAD;
			//	살아있는 캐릭터에 대하여,
			if (isAliveChar) {
				int differIdxSize = abs(enemy->getChara(i)->mapIdx.x - enemy->_mapIdx.x) + abs(enemy->getChara(i)->mapIdx.y - enemy->_mapIdx.y);
				//	idx차이가 1,0 이라면, (한칸떨어졌거나, 겹쳐있든가)
				if (differIdxSize < 2) {
					targetCharIdx = i;
					isNearChar = true;
				}

				//	idx차이가 많이나면, 가장 가까운놈 저장
				else {
					if (differIdxSize < targetCharDistance) {
						targetCharDistance = differIdxSize;
						nearCharIdx = i;
					}
					

				}
			}
			
		}
		//	MOB_SKELL의 공격, 이동 소스
		if (enemy->_name == ENEMY_NAME::MOB_SKEL) {
			//	근처 캐릭터 있으면 공격
			if (isNearChar) {
				enemy->_atkCount++;
				if (enemy->_atkCount > enemy->ATKCOUNT_MAX) {
					enemy->_atkCount = 0;
					enemy->_targetCharIdx = targetCharIdx;
					enemy->_state = E_STATE::E_ATK1;
					enemy->_isStateChanged = true;
				}

			}

			//	캐릭터 없으면 이동
			else {
				//	그나마 가장 가까운 캐릭터가 검색되었다면,
				if (nearCharIdx != -1) {
					enemy->_targetCharIdx = nearCharIdx;
					enemy->_state = E_STATE::E_MOVE;
					enemy->_isStateChanged = true;
					ASTARFUNC->PathFind(enemy->_mapIdx, enemy->getChara(nearCharIdx)->mapIdx, enemy->_mapIdx, enemy->_lWayIdxList);
					//	검색이 됐고, -1,-,1 이 아니라면 -> 마지막좌표(플레이어)는 뺴라.
					if (enemy->_lWayIdxList.size() != 0 && enemy->_lWayIdxList.begin()->x != -1) {
						enemy->_lWayIdxList.pop_back();
					}
				}
			}
		}
		//	MOB_SKELL의 공격, 이동 소스 끗


		//	카이저의 행동에 대한 소스
		else if (enemy->_name == ENEMY_NAME::MOB_KAISER) {


			if (enemy->_bossAction == BOSS_ACTION::BOSS_ACTION_NONE) {
				ChooseSkill(enemy);
				TargetSelectFunc(enemy);
			}

			vChara* pvChara = enemy->_vChara;
			POINT targetIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;
			int distance = abs(targetIdx.x - enemy->_mapIdx.x) + abs(targetIdx.y - enemy->_mapIdx.y);
			int skillRange;
			
			
			
			BOSS_ACTION actionKinds = enemy->_bossAction;
			switch (actionKinds)
			{
			case BOSS_ACTION_NONE:
				break;
			case BOSS_SNATCH:
				enemy->_curSkillName = "snatch";
				skillRange = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getRange();
				//	스킬범위 내 라면,
				if (skillRange >= distance) {

					//	스킬범위표시기능 + 방향설정기능 추가 =================

					//	에너미 Dir설정(남은거리에따라)
					SetDirBeforeSkillCast(enemy, targetIdx);


					//	스킬범위표시기능, vector추가부분 =====================

					// 스킬방향 설정 (= 에너미 방향)
					SKILL_DIR skillDir;
					SetSkillDir(enemy, &skillDir);
					int AugIdxSize = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdxSize(skillDir);
					enemy->_targetMapIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;

					for (int i = 0; i < AugIdxSize; i++) {
						POINT augTileIdx = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdx(skillDir, i);
						POINT targetTileIdx = { targetIdx.x + augTileIdx.x, targetIdx.y + augTileIdx.y };
						enemy->_skillMaskTile.addTargetTile(enemy->_maskImgNum, targetTileIdx, enemy->_maskImgNum);
					}
					
					//	스킬범위표시기능, vector추가부분 끗 =====================


					



					enemy->_state = E_STATE::E_SKILL1_CAST;
					enemy->_isStateChanged = true;
					
				}
				//	스킬범위밖이므로, 이동계산
				else {
					ASTARFUNC->PathFind(enemy->_mapIdx, targetIdx, enemy->_mapIdx, enemy->_lWayIdxList);
					//	스킬범위만큼 리스트에서 뺴줌. 최대사정거리 유지
					for (int i = 0; i < skillRange; i++) {
						if (enemy->_lWayIdxList.size() == 0)	break;
						enemy->_lWayIdxList.pop_back();
					}
					enemy->_state = E_STATE::E_MOVE;
					enemy->_isStateChanged = true;

				}
				


				break;
			case BOSS_ATK1:
				enemy->_curSkillName = "bossAtk1";

				//	스킬범위 내
				skillRange = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getRange();
				if (skillRange >= distance) {

					//	스킬범위표시기능 + 방향설정기능 추가 =================

					//	에너미 Dir설정(남은거리에따라)
					SetDirBeforeSkillCast(enemy, targetIdx);


					//	스킬범위표시기능, vector추가부분 =====================

					// 스킬방향 설정 (= 에너미 방향)
					SKILL_DIR skillDir;
					SetSkillDir(enemy, &skillDir);
					int AugIdxSize = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdxSize(skillDir);
					enemy->_targetMapIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;

					for (int i = 0; i < AugIdxSize; i++) {
						POINT augTileIdx = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdx(skillDir, i);
						POINT targetTileIdx = { targetIdx.x + augTileIdx.x, targetIdx.y + augTileIdx.y };
						enemy->_skillMaskTile.addTargetTile(enemy->_maskImgNum, targetTileIdx, enemy->_maskImgNum);
					}

					//	스킬범위표시기능, vector추가부분 끗 =====================

					enemy->_state = E_STATE::E_SKILL1_CAST;
					enemy->_isStateChanged = true;
					
				}
				//	스킬범위밖이므로, 이동계산
				else {
					ASTARFUNC->PathFind(enemy->_mapIdx, targetIdx, enemy->_mapIdx, enemy->_lWayIdxList);
					//	스킬범위만큼 리스트에서 뺴줌. 최대사정거리 유지
					for (int i = 0; i < skillRange; i++) {
						if (enemy->_lWayIdxList.size() == 0)	break;
						enemy->_lWayIdxList.pop_back();
					}
					enemy->_state = E_STATE::E_MOVE;
					enemy->_isStateChanged = true;

				}
				break;
			case BOSS_ATK2:
				enemy->_curSkillName = "bossAtk2";

				//	스킬범위 내
				skillRange = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getRange();
				if (skillRange >= distance) {

					//	스킬범위표시기능 + 방향설정기능 추가 =================

				//	에너미 Dir설정(남은거리에따라)
					SetDirBeforeSkillCast(enemy, targetIdx);


					//	스킬범위표시기능, vector추가부분 =====================

					// 스킬방향 설정 (= 에너미 방향)
					SKILL_DIR skillDir;
					SetSkillDir(enemy, &skillDir);
					int AugIdxSize = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdxSize(skillDir);
					enemy->_targetMapIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;

					for (int i = 0; i < AugIdxSize; i++) {
						POINT augTileIdx = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdx(skillDir, i);
						POINT targetTileIdx = { targetIdx.x + augTileIdx.x, targetIdx.y + augTileIdx.y };
						enemy->_skillMaskTile.addTargetTile(enemy->_maskImgNum, targetTileIdx, enemy->_maskImgNum);
					}

					//	스킬범위표시기능, vector추가부분 끗 =====================

					enemy->_state = E_STATE::E_SKILL1_CAST;
					enemy->_isStateChanged = true;
					//enemy->_targetMapIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;
				}
				//	스킬범위밖이므로, 이동계산
				else {
					ASTARFUNC->PathFind(enemy->_mapIdx, targetIdx, enemy->_mapIdx, enemy->_lWayIdxList);
					//	스킬범위만큼 리스트에서 뺴줌. 최대사정거리 유지
					for (int i = 0; i < skillRange; i++) {
						if (enemy->_lWayIdxList.size() == 0)	break;
						enemy->_lWayIdxList.pop_back();
					}
					enemy->_state = E_STATE::E_MOVE;
					enemy->_isStateChanged = true;

				}
				break;
			case BOSS_BUFF:
				enemy->_curSkillName = "bossBuff";


				//	스킬범위 내
				skillRange = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getRange();
				if (skillRange >= distance) {

					//	스킬범위표시기능 + 방향설정기능 추가 =================

				//	에너미 Dir설정(남은거리에따라)
					SetDirBeforeSkillCast(enemy, targetIdx);


					//	스킬범위표시기능, vector추가부분 =====================

					// 스킬방향 설정 (= 에너미 방향)
					SKILL_DIR skillDir;
					SetSkillDir(enemy, &skillDir);
					int AugIdxSize = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdxSize(skillDir);
					enemy->_targetMapIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;

					for (int i = 0; i < AugIdxSize; i++) {
						POINT augTileIdx = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getAugIdx(skillDir, i);
						POINT targetTileIdx = { targetIdx.x + augTileIdx.x, targetIdx.y + augTileIdx.y };
						enemy->_skillMaskTile.addTargetTile(enemy->_maskImgNum, targetTileIdx, enemy->_maskImgNum);
					}

					//	스킬범위표시기능, vector추가부분 끗 =====================

					enemy->_state = E_STATE::E_SKILL1_CAST;
					enemy->_isStateChanged = true;
					//enemy->_targetMapIdx = (*pvChara)[enemy->_targetCharIdx]->mapIdx;
				}
				//	스킬범위밖이므로, 이동계산
				else {
					ASTARFUNC->PathFind(enemy->_mapIdx, targetIdx, enemy->_mapIdx, enemy->_lWayIdxList);
					//	스킬범위만큼 리스트에서 뺴줌. 최대사정거리 유지
					for (int i = 0; i < skillRange; i++) {
						if (enemy->_lWayIdxList.size() == 0)	break;
						enemy->_lWayIdxList.pop_back();
					}
					enemy->_state = E_STATE::E_MOVE;
					enemy->_isStateChanged = true;

				}
				break;
			case BOSS_HOLD:
				enemy->_state = E_STATE::E_BLOCK;
				enemy->_isStateChanged = true;

				enemy->_targetMapIdx = enemy->_mapIdx;
				break;
			case BOSS_ACTION_END:
				break;
			default:
				break;
			}

			
		}
		
	}
		


}

void eStatePattern::Dead(enemy * enemy)
{
	enemy->_deleteDelayCount++;
}

void eStatePattern::GetDmg(enemy * enemy)
{
	if (!enemy->_ani->isPlay()) {
		enemy->_state = enemy->_preState;
		enemy->_isStateChanged = true;
	}
}

void eStatePattern::Stoned(enemy * enemy)
{
}

void eStatePattern::Frozen(enemy * enemy)
{
}

void eStatePattern::GetCriDmg(enemy * enemy)
{
}

void eStatePattern::Stunned(enemy * enemy)
{
	enemy->_abnormalConditionCount++;
	if (enemy->_abnormalConditionCount > enemy->STUNNED_COUNTMAX) {
		enemy->_abnormalConditionCount = 0;
		enemy->_state = enemy->_preState;
		enemy->_isStateChanged = true;
	}
}

void eStatePattern::Deffence(enemy * enemy)
{
	//	아직작성안함 -> idle로 일단 보내겠음
	enemy->_state = E_STATE::E_IDLE;
	enemy->_bossAction = BOSS_ACTION::BOSS_ACTION_NONE;
	enemy->_isStateChanged = true;


}

void eStatePattern::Move(enemy * enemy)
{
	CalTileForRender(enemy);
	if (enemy->_lWayIdxList.size() != 0) {
		POINT targetIdx = { enemy->_lWayIdxList.begin()->x, enemy->_lWayIdxList.begin()->y };
		//	못가는 곳 판정이 났으면, 아이들로 바꾸고 지워라
		if (targetIdx.x == -1 && targetIdx.y == -1) {
			enemy->_state = E_STATE::E_IDLE;
			//enemy->_curState = character->_arrStatePattern[static_cast<const int>(E_STATE::IDLE)];
			enemy->_isStateChanged = true;
			//if ((enemy->_lOrderList.begin()->kinds) == E_STATE::E_MOVE)
			//	enemy->_lOrderList.pop_front();

		}
		//	벡터 계산
		//	targetIdx와 나의 차이는, x쪽에서 1나거나, y쪽에서 1난다.
		//	x쪽에서 +1이면, vecX 증가, vecY 증가,
		//	y쪽에서 +1이면, vecX 감소, vecY 증가,
		enemy->_moveVec.x = (targetIdx.x - enemy->_mapIdx.x) * TILESIZE_WID / enemy->_statValue[E_STATS::E_MOVESPD]
			+ (-1)*(targetIdx.y - enemy->_mapIdx.y) * TILESIZE_WID / enemy->_statValue[E_STATS::E_MOVESPD];
		enemy->_moveVec.y = (targetIdx.x - enemy->_mapIdx.x) * TILESIZE_HEI / enemy->_statValue[E_STATS::E_MOVESPD]
			+ (targetIdx.y - enemy->_mapIdx.y) * TILESIZE_HEI / enemy->_statValue[E_STATS::E_MOVESPD];

		CalDirFunc(enemy);

		vvMap* pvvMap = enemy->_vvMap;

		//	오차허용계산
		if (abs((*pvvMap)[targetIdx.y][targetIdx.x]->_pos.x - enemy->_pos.x) < enemy->FLOAT_ERROR) {
			enemy->_moveVec.x = 0;
			enemy->_pos.x = (*pvvMap)[targetIdx.y][targetIdx.x]->_pos.x;
		}
		if (abs((*pvvMap)[targetIdx.y][targetIdx.x]->_pos.y - enemy->_pos.y) < enemy->FLOAT_ERROR) {
			enemy->_moveVec.y = 0;
			enemy->_pos.y = (*pvvMap)[targetIdx.y][targetIdx.x]->_pos.y;
		}
		//	다음타일에 도착했다면,
		if (enemy->_moveVec.x == 0 && enemy->_moveVec.y == 0) {
			enemy->_mapIdx.x = enemy->_lWayIdxList.begin()->x;
			enemy->_mapIdx.y = enemy->_lWayIdxList.begin()->y;
			enemy->_pCurTile = (*pvvMap)[enemy->_mapIdx.y][enemy->_mapIdx.x];
			enemy->_lWayIdxList.pop_front();

			//	MAXCOUNT만큼 타일이동했으면, idle로 변환.
			enemy->_moveTileCount++;
			if (enemy->_moveTileCount > enemy->MOVETILECOUNT_MAX) {
				enemy->_moveTileCount = 0;
				enemy->_state = E_STATE::E_IDLE;
				enemy->_lWayIdxList.clear();
				enemy->_isStateChanged = true;
				return;

			}
		}

		//	이동적용
		enemy->_pos.x += enemy->_moveVec.x;
		enemy->_pos.y += enemy->_moveVec.y;
		//enemy->_rc = RectMake(enemy->_pos.x - 128, enemy->_pos.y - 160,
		//	enemy->_img->GetFrameWidth(), enemy->_img->GetFrameHeight());
		enemy->_rc = RectMake(enemy->_pos.x - 128,
			enemy->_pos.y - 156,
			enemy->_img->GetFrameWidth(),
			enemy->_img->GetFrameHeight());
		
		enemy->_targetedRc = RectMake(enemy->_pos.x - enemy->WID_FROM_CENTERPOS,
			enemy->_pos.y - enemy->LEN_TO_TOP_FROM_CENTERPOS,
			enemy->WID_FROM_CENTERPOS * 2, 
			enemy->LEN_TO_TOP_FROM_CENTERPOS + enemy->LEN_TO_BOTTOM_FROM_CENTERPOS);
		
	
	}
	//	목적지 도착
	else {
		enemy->_state = E_STATE::E_IDLE;
		//enemy->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		enemy->_isStateChanged = true;
		//if ((enemy->_lOrderList.begin()->kinds) == E_STATE::E_MOVE)
		//	enemy->_lOrderList.pop_front();
	}

}

void eStatePattern::Atk1(enemy * enemy)
{
	//if (!enemy->_isAtkFin) {
	//	enemy->_dir = CalDirToPlayer(enemy);
	//}


	if (!enemy->_isAtkFin && enemy->_ani->isLastFrame()) {
	//if (enemy->_ani->isLastFrame()) {
		enemy->_isAtkFin = true;
		enemy->_ani->stop();
		//	타겟캐릭터의 hp를 에너미의 value중, atk만큼 깎는다. 
		//	스킬배수 추가예정
		enemy->getChara(enemy->_targetCharIdx)->setCurHpAug(-enemy->_statValue[E_STATS::E_ATK]);
	}
}

void eStatePattern::Atk2(enemy * enemy)
{
}

void eStatePattern::Atk3(enemy * enemy)
{
}

void eStatePattern::Skill1Cast(enemy * enemy)
{
	enemy->_castingCount += enemy->_statValue[E_STATS::E_CASTSPD];
	int castCountMax = SKILLMANAGER->FindSkill(enemy->_curSkillName)->getCastCountMax();

	if (enemy->_castingCount > castCountMax) {
		enemy->_skillMaskTile.ClearVMaskInfo();		//	마스크 리스트 클리어

		enemy->_castingCount = 0;
		enemy->_state = E_STATE::E_SKILL1_SHOT;
		enemy->_isStateChanged = true;
	}

}

void eStatePattern::Skill1Shot(enemy * enemy)
{
	//	프레임이 끝나면, 공격적용!
	if (enemy->_ani->isLastFrame()) {

		enemy->_state = E_STATE::E_IDLE;
		enemy->_bossAction = BOSS_ACTION::BOSS_ACTION_NONE;
		vvMap* pvvMap = enemy->_vvMap;		//	vvMap에서 Zlvl 받아서, startSkillEffect에 추가해서 계산해야함
		//	이펙트 적용
		skillNode* curSkill = SKILLMANAGER->FindSkill(enemy->_curSkillName);
		POINT targetMapIdx = enemy->_targetMapIdx;
		curSkill->StartSkillEffect(
			enemy->_targetMapIdx,
			(int)enemy->_dir,
			(*pvvMap)[targetMapIdx.y][targetMapIdx.x]->_zLevel);

		//	판정적용
		SKILL_KINDS skillKinds = curSkill->getSkillKinds();

		//	공격시 사용되는 스킬의 특수능력
		SKILL_ATTR skillAttr = curSkill->getAttr();
		//	특수능력 적용확률
		float attrAdjustRatio = curSkill->getAttrAdjustRatio();
		POINT tileIdxOnSkill;		//	스킬이 적용될 타일인덱스
		SKILL_DIR skillDir = ConvertCharDirToSkillDir(enemy);
		POINT curIdx = enemy->_targetMapIdx;
		vChara* pvChara = enemy->_vChara;

		
		switch (skillKinds)
		{
		case SKILL_KINDS_NONE:
			break;
		case SKILL_KINDS_ATK:
		{
			// 캐릭에게 맞았는가 판단하고 데미지 적용
			// 스킬이 적용될 타일인덱스
			for (int i = 0; i < curSkill->getAugIdxSize(skillDir); i++) {
				tileIdxOnSkill = { curIdx.x + curSkill->getAugIdx(skillDir, i).x, curIdx.y + curSkill->getAugIdx(skillDir, i).y };
				//	캐릭터전체를 검색해서 캐릭터의 인덱스와
				for (int j = 0; j < pvChara->size(); j++) {
					//	인덱스가 같으면 -> 데미지 적용!
					if ((*pvChara)[j]->_mapIdx.x == tileIdxOnSkill.x &&
						(*pvChara)[j]->_mapIdx.y == tileIdxOnSkill.y) {
						//	데미지 적용식
						(*pvChara)[j]->setCurHpAug(
							-(enemy->_statValue[E_STATS::E_ATK] *
								curSkill->getMultiNumPhysic()
								+
								enemy->_statValue[E_STATS::E_MATK] *
								curSkill->getMultiNumMagic()
								));
					}
				}
			}
		}
			
			break;
		case SKILL_KINDS_HEAL:
			break;
		case SKILL_KINDS_BUFF:
			//enemy->addBuff(curSkill->getSkillName(), 
			//	IMAGEMANAGER->findImage(curSkill->getSkillName().c_str()),
			//	KEYANIMANAGER->findAnimation(curSkill->getSkillName(), curSkill->getSkillName()),
			//	0, curSkill->getDuration());
				

			break;
		case SKILL_KINDS_RESUR:
			break;
		default:
			break;
		}



	}


}

void eStatePattern::Skill2Cast(enemy * enemy)
{
}

void eStatePattern::Skill2Shot(enemy * enemy)
{
}

void eStatePattern::Skill3Cast(enemy * enemy)
{
}

void eStatePattern::Skill3Shot(enemy * enemy)
{
}

void eStatePattern::Skill4Cast(enemy * enemy)
{
}

void eStatePattern::Skill4Shot(enemy * enemy)
{
}

void eStatePattern::CalDirFunc(enemy * enemy)
{
	POINTFLOAT moveVec = enemy->_moveVec;
	if (moveVec.x > 0 && moveVec.y > 0) {
		if (enemy->_dir != E_DIR::DIR_RB) {
			enemy->_dir = E_DIR::DIR_RB;
			enemy->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::RB;
	}
	else if (moveVec.x > 0 && moveVec.y < 0) {
		if (enemy->_dir != E_DIR::DIR_RT) {
			enemy->_dir = E_DIR::DIR_RT;
			enemy->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::RB;
	}
	else if (moveVec.x < 0 && moveVec.y > 0) {
		if (enemy->_dir != E_DIR::DIR_LB) {
			enemy->_dir = E_DIR::DIR_LB;
			enemy->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::LB;
	}
	else if (moveVec.x < 0 && moveVec.y < 0) {
		if (enemy->_dir != E_DIR::DIR_LT) {
			enemy->_dir = E_DIR::DIR_LT;
			enemy->_isStateChanged = true;
		}

		//character->_dir = CHAR_DIR::LT;
	}
}

void eStatePattern::CalTileForRender(enemy * enemy)
{
	POINT tileIdx;
	vvMap* vvMap = enemy->_vvMap;
	E_DIR dir = enemy->_dir;

	switch (dir)
	{
	case DIR_NONE:
		break;
	case DIR_LT:
		enemy->_probePos.x = enemy->_pos.x - TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y - TILESIZE_HEI / 4;
		break;
	case DIR_RT:
		enemy->_probePos.x = enemy->_pos.x + TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y - TILESIZE_HEI / 4;
		break;
	case DIR_LB:
		enemy->_probePos.x = enemy->_pos.x - TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y + TILESIZE_HEI / 4;
		break;
	case DIR_RB:
		enemy->_probePos.x = enemy->_pos.x + TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y + TILESIZE_HEI / 4;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
	tileIdx = ConvertPosToIdx(enemy->_probePos.x, enemy->_probePos.y,
		TILESIZE_WID, TILESIZE_HEI);
	if (0 <= tileIdx.x && tileIdx.x < (*vvMap)[0].size() &&
		0 <= tileIdx.y && tileIdx.y < (*vvMap).size()) {
		enemy->_tileForRender = (*vvMap)[tileIdx.y][tileIdx.x];
	}
	else {
		enemy->_tileForRender = enemy->_pCurTile;
	}
	

}


void eStatePattern::CalDirToPlayer(enemy * enemy)
{
	//E_DIR dir = E_DIR::DIR_LB;
	vChara* _vChara = (enemy->_vChara);
	POINT playerMapIdx = (*_vChara)[enemy->_targetCharIdx]->mapIdx;

	if (enemy->_mapIdx.x - 1 == playerMapIdx.x &&
		enemy->_mapIdx.y == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_LT;
		//*dir = E_DIR::DIR_LT;
	}
	else if(enemy->_mapIdx.x + 1 == playerMapIdx.x &&
		enemy->_mapIdx.y == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_RB;
		//*dir = E_DIR::DIR_RB;
	}
	else if (enemy->_mapIdx.x == playerMapIdx.x &&
		enemy->_mapIdx.y - 1 == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_RT;
		//*dir = E_DIR::DIR_RT;
	}
	else if (enemy->_mapIdx.x + 1 == playerMapIdx.x &&
		enemy->_mapIdx.y + 1 == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_LB;
		//*dir = E_DIR::DIR_LB;
	}
	

	//return dir;
}

void eStatePattern::ChooseSkill(enemy * enemy)
{
	int randNum;
	BOSS_ACTION bossAction = BOSS_ACTION_NONE;
	randNum = RND->getFromIntTo(0, enemy->BOSS_ACTIONNUM);
	switch (randNum)
	{
	case BOSS_SNATCH:
		enemy->_bossAction = BOSS_SNATCH;
		
		break;
	case BOSS_ATK1:
		enemy->_bossAction = BOSS_ATK1;
		break;
	case BOSS_ATK2:
		enemy->_bossAction = BOSS_ATK2;
		break;
	case BOSS_BUFF:
		enemy->_bossAction = BOSS_SNATCH;
		break;
	case BOSS_HOLD:
		enemy->_bossAction = BOSS_HOLD;
		break;

	default:
		break;
	}
	
}

SKILL_DIR eStatePattern::ConvertCharDirToSkillDir(enemy * enemy)
{
	SKILL_DIR skillDir = SKILL_DIR::SKILL_DIR_NONE;
	E_DIR dir = enemy->_dir;
	if (dir == E_DIR::DIR_LT) {
		skillDir = SKILL_DIR::SKILL_DIR_LT;
	}
	else if (dir == E_DIR::DIR_LB) {
		skillDir = SKILL_DIR::SKILL_DIR_LB;
	}
	else if (dir == E_DIR::DIR_RT) {
		skillDir = SKILL_DIR::SKILL_DIR_RT;
	}
	else if (dir == E_DIR::DIR_RB) {
		skillDir = SKILL_DIR::SKILL_DIR_RB;
	}
	return skillDir;
}

void eStatePattern::TargetSelectFunc(enemy * enemy)
{
	int curMinDistance = 9999999;
	vChara* pvChara = enemy->_vChara;

	for (int i = 0; i < pvChara->size(); i++) {
		
		
		if ((*pvChara)[i]->getCharValueCur()[CHAR_VALUE_KINDS::CUR_HP] <= 0)
			continue;
		//if((*pvChara)[i]->_state == CHAR_STATE::DEAD) continue;

		POINT targetIdx = (*pvChara)[i]->mapIdx;
		int distance;
		distance = abs(targetIdx.x - enemy->_mapIdx.x) + abs(targetIdx.y - enemy->_mapIdx.y);
		if (curMinDistance > distance) {
			curMinDistance = distance;
			enemy->_targetCharIdx = i;
		}
	}
	
}

void eStatePattern::SetDirBeforeSkillCast(enemy * enemy, POINT targetIdx)
{
	int differX = targetIdx.x - enemy->_mapIdx.x;
	int differY = targetIdx.y - enemy->_mapIdx.y;

	if (abs(differX) > abs(differY)) {
		if (differX < 0) {
			enemy->_dir = E_DIR::DIR_LT;
		}
		else {
			enemy->_dir = E_DIR::DIR_RB;
		}
	}
	else {
		if (differY < 0) {
			enemy->_dir = E_DIR::DIR_RT;
		}
		else {
			enemy->_dir = E_DIR::DIR_LB;
		}
	}
}

void eStatePattern::SetSkillDir(enemy * enemy, SKILL_DIR * skillDir)
{
	switch (enemy->_dir)
	{
	case E_DIR::DIR_LT:
		*skillDir = SKILL_DIR::SKILL_DIR_LT;
		break;
	case E_DIR::DIR_LB:
		*skillDir = SKILL_DIR::SKILL_DIR_LB;
		break;
	case E_DIR::DIR_RT:
		*skillDir = SKILL_DIR::SKILL_DIR_RT;
		break;
	case E_DIR::DIR_RB:
		*skillDir = SKILL_DIR::SKILL_DIR_RB;
		break;
	default:
		break;
	}
}
