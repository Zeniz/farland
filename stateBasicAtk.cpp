#include "stdafx.h"
#include "stateBasicAtk.h"


stateBasicAtk::stateBasicAtk()
{
}


stateBasicAtk::~stateBasicAtk()
{
}

void stateBasicAtk::onIdle(Character * character)
{
}

void stateBasicAtk::onMove(Character * character)
{
}

void stateBasicAtk::onCast(Character * character)
{
}

void stateBasicAtk::onDead(Character * character)
{
}

void stateBasicAtk::onGetHit(Character * character)
{
}

void stateBasicAtk::onStone(Character * character)
{
}

void stateBasicAtk::onFrozen(Character * character)
{
}

void stateBasicAtk::onGetHit2(Character * character)
{
}

void stateBasicAtk::onBlock(Character * character)
{
}

void stateBasicAtk::onBasicAtk(Character * character)
{
}

void stateBasicAtk::onSkillOne(Character * character)
{
}

void stateBasicAtk::onSkillTwo(Character * character)
{
}

void stateBasicAtk::onSkillThree(Character * character)
{
}

void stateBasicAtk::onSkillFour(Character * character)
{
}

void stateBasicAtk::update(Character * character)
{
	character->_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;
	
	//	상하좌우에 적이 있나? -> idle에서 공속과 근처몹 검사해서 해당하면 이쪽으로 넘어올거임.
	//ChkNearbyEnemy(character, &isNearEnemy);

	//	프레임이 끝나면, 공격적용!
	if (character->_ani->isLastFrame()) {
		vEnemy* _vEnemy = character->_vEnemy;

		(*_vEnemy)[character->_targetEnemyIdx]->setCurHpAug(
			-(character->_charValue[0][CHAR_VALUE_KINDS::ATK] +
			character->_charValue[1][CHAR_VALUE_KINDS::ATK]));






		//	공격적용 후, 다시 move로 가서 반복
		character->_state = CHAR_STATE::MOVE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
		character->_isStateChanged = true;
	}
		





		


	
	


	/*
	else {
	
		
		//	길을 찾앗으면, -> move와 같음
		if (character->_lWayIdxList.size() != 0 && character->_lWayIdxList.begin()->x != -1) {
			//	move!
			CalTileForRender(character);

			if (character->_lWayIdxList.size() != 0) {
				POINT targetIdx = { character->_lWayIdxList.begin()->x, character->_lWayIdxList.begin()->y };
				//	못가는 곳 판정이 났으면, 아이들로 바꾸고 지워라
				if (targetIdx.x == -1 && targetIdx.y == -1) {
					character->_state = CHAR_STATE::IDLE;
					character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
					character->_isStateChanged = true;
					if ((character->_lOrderList.begin()->kinds) == ORDER_KINDS::ATTACK)
						character->_lOrderList.pop_front();

				}
				//	벡터 계산
				//	targetIdx와 나의 차이는, x쪽에서 1나거나, y쪽에서 1난다.
				//	x쪽에서 +1이면, vecX 증가, vecY 증가,
				//	y쪽에서 +1이면, vecX 감소, vecY 증가,
				character->_moveVec.x = (targetIdx.x - character->mapIdx.x) * TILESIZE_WID / character->_charValue[CUR][MOVE_SPD]
					+ (-1)*(targetIdx.y - character->mapIdx.y) * TILESIZE_WID / character->_charValue[CUR][MOVE_SPD];
				character->_moveVec.y = (targetIdx.x - character->mapIdx.x) * TILESIZE_HEI / character->_charValue[CUR][MOVE_SPD]
					+ (targetIdx.y - character->mapIdx.y) * TILESIZE_HEI / character->_charValue[CUR][MOVE_SPD];

				CalDirFunc(character);

				vvMap* pvvMap = character->_vvMap;

				//	오차허용계산
				if (abs((*pvvMap)[targetIdx.y][targetIdx.x]->_pos.x - character->_pos.x) < character->FLOAT_ERROR) {
					character->_moveVec.x = 0;
					character->_pos.x = (*pvvMap)[targetIdx.y][targetIdx.x]->_pos.x;
				}
				if (abs((*pvvMap)[targetIdx.y][targetIdx.x]->_pos.y - character->_pos.y) < character->FLOAT_ERROR) {
					character->_moveVec.y = 0;
					character->_pos.y = (*pvvMap)[targetIdx.y][targetIdx.x]->_pos.y;
				}
				//	다음타일에 도착했다면,
				if (character->_moveVec.x == 0 && character->_moveVec.y == 0) {
					character->mapIdx.x = character->_lWayIdxList.begin()->x;
					character->mapIdx.y = character->_lWayIdxList.begin()->y;
					character->_curTile = (*pvvMap)[character->mapIdx.y][character->mapIdx.x];
					character->_lWayIdxList.pop_front();
				}

				//	이동적용
				character->_pos.x += character->_moveVec.x;
				character->_pos.y += character->_moveVec.y;
				character->_rc = RectMake(character->_pos.x - 128, character->_pos.y - 160,
					character->_img->GetFrameWidth(), character->_img->GetFrameHeight());

			}
			//			MOVE와 달리 목적지 도착시 공격해야됨.
			////	목적지 도착
			//else {
			//	character->_state = CHAR_STATE::IDLE;
			//	character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
			//	character->_isStateChanged = true;
			//	if ((character->_lOrderList.begin()->kinds) == ORDER_KINDS::MOVE)
			//		character->_lOrderList.pop_front();
			//}
		}

	}
	*/
	

}

void stateBasicAtk::ChkNearbyEnemy(Character * chara, bool * isNearEnemy)
{
	POINT curMapIdx = chara->mapIdx;
	vEnemy* _vEnemy = chara->_vEnemy;

	if (curMapIdx.x - 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		return;
	}
	if (curMapIdx.x + 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		return;
	}
	if (curMapIdx.x == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y - 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		return;
	}
	if (curMapIdx.x == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y + 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		return;
	}

	*isNearEnemy = false;
	return;
}

void stateBasicAtk::CalDirFunc(Character * character)
{
	POINTFLOAT moveVec = character->_moveVec;
	if (moveVec.x > 0 && moveVec.y > 0) {
		if (character->_dir != CHAR_DIR::RB) {
			character->_dir = CHAR_DIR::RB;
			character->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::RB;
	}
	else if (moveVec.x > 0 && moveVec.y < 0) {
		if (character->_dir != CHAR_DIR::RT) {
			character->_dir = CHAR_DIR::RT;
			character->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::RB;
	}
	else if (moveVec.x < 0 && moveVec.y > 0) {
		if (character->_dir != CHAR_DIR::LB) {
			character->_dir = CHAR_DIR::LB;
			character->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::LB;
	}
	else if (moveVec.x < 0 && moveVec.y < 0) {
		if (character->_dir != CHAR_DIR::LT) {
			character->_dir = CHAR_DIR::LT;
			character->_isStateChanged = true;
		}

		//character->_dir = CHAR_DIR::LT;
	}
}

void stateBasicAtk::CalTileForRender(Character * character)
{
	POINTFLOAT probe;
	POINT tileIdx;
	vvMap* pvvMap = character->_vvMap;
	switch (character->_dir)
	{
	case CHAR_DIR::NONE:
		break;
	case CHAR_DIR::LT:
		probe.x = character->_pos.x - TILESIZE_WID / 4;
		probe.y = character->_pos.y - TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::RT:
		probe.x = character->_pos.x + TILESIZE_WID / 4;
		probe.y = character->_pos.y - TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::LB:
		probe.x = character->_pos.x - TILESIZE_WID / 4;
		probe.y = character->_pos.y + TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::RB:
		probe.x = character->_pos.x + TILESIZE_WID / 4;
		probe.y = character->_pos.y + TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::CHAR_DIR_END:
		break;
	default:
		break;
	}

	tileIdx = ConvertPosToIdx(probe.x, probe.y, TILESIZE_WID, TILESIZE_HEI);
	if (0 <= tileIdx.x && tileIdx.x < (*pvvMap)[0].size() &&
		0 <= tileIdx.y && tileIdx.y < (*pvvMap).size()) {
		character->_tileForRender = (*pvvMap)[tileIdx.y][tileIdx.x];
	}
	else {
		character->_tileForRender = character->_curTile;
	}
}
