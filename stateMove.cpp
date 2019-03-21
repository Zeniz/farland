#include "stdafx.h"
#include "stateMove.h"


stateMove::stateMove()
{
}


stateMove::~stateMove()
{
}

void stateMove::onIdle(Character* character)
{
}

void stateMove::onMove(Character* character)
{
	
}

void stateMove::onCast(Character* character)
{
}

void stateMove::onDead(Character* character)
{
}

void stateMove::onGetHit(Character* character)
{
}

void stateMove::onStone(Character* character)
{
}

void stateMove::onFrozen(Character* character)
{
}

void stateMove::onGetHit2(Character* character)
{
}

void stateMove::onBlock(Character* character)
{
}

void stateMove::onBasicAtk(Character * character)
{
}

void stateMove::onSkillOne(Character * character)
{
}

void stateMove::onSkillTwo(Character * character)
{
}

void stateMove::onSkillThree(Character * character)
{
}

void stateMove::onSkillFour(Character * character)
{
}

void stateMove::update(Character* character)
{
	CalTileForRender(character);
	character->_portraitKinds = CHAR_PORTRAIT_KINDS::JOYFUL;

	//	공격하러 가는중이면,
	if (character->_isOnAtking) {
		//	일정시간마다 astar로 길 재갱신 -> 오더 재갱신 처리
		character->_aStarCount++;
		if (character->_aStarCount > character->ASTAR_COUNT_MAX) {
			character->_aStarCount = 0;

			vEnemy* _vEnemy = character->_vEnemy;
			ASTARFUNC->PathFind(character->mapIdx,
				(*_vEnemy)[character->_targetEnemyIdx]->_mapIdx,
				character->mapIdx, character->_lWayIdxList);
			
			//	길이 없으면, -> 앞에 move하고 attak 오더 날려라, 그리고 idle로 돌아가라
			if (character->_lWayIdxList.size() != 0 && character->_lWayIdxList.begin()->x == -1) {
				if (character->_lOrderList.front().kinds == ORDER_KINDS::MOVE) {
					character->_lOrderList.pop_front();
				}
				if (character->_lOrderList.front().kinds == ORDER_KINDS::ATTACK) {
					character->_lOrderList.pop_front();
				}
				character->_state = CHAR_STATE::IDLE;
				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
				character->_isStateChanged = true;
				return;
			}
			// 길이 존재하면, waylist에서 몹있는 곳 날려라
			else if (character->_lWayIdxList.size() != 0 && character->_lWayIdxList.begin()->x != -1) {
				character->_lWayIdxList.pop_back();
			}
			
			//	처리된 waylist를 보고, 몹이 바로 옆이면,
			//	몹이 바로 앞에 있다면(마지막을 뻇는데 사이즈가 0 이라는건, 몹이 앞에있다는거 || 겹쳐있거나)
			if (character->_lWayIdxList.size() == 0) {
				//현재 오더리스트의 move를 뺴버리고, idle가서 공격신호받자.
				if (character->_lOrderList.front().kinds == ORDER_KINDS::MOVE) {
					character->_lOrderList.pop_front();
				}
				character->_state = CHAR_STATE::IDLE;
				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
				character->_isStateChanged = true;
				return;

			}

			//	몹있는곳을 waylist에서 뺏는데 더 이동해야한다면, -> 새로운 move오더로 교체하고, 밑에서 이동한다.
			else if (character->_lWayIdxList.size() != 0 && character->_lWayIdxList.begin()->x != -1) {

				character->_liWayIdxList = character->_lWayIdxList.end();
				character->_liWayIdxList--;

				vvMap* _vvMap = character->_vvMap;
				character->_targetTile = (*_vvMap)[character->_liWayIdxList->y][character->_liWayIdxList->x];

				character->_lOrderList.pop_front();
				tagOrderInfo order;
				order.kinds = ORDER_KINDS::MOVE;
				order.targetMapIdx = character->_targetTile->_mapIdx;
				character->_lOrderList.push_front(order);
			}
		}

	}
	


	if (character->_lWayIdxList.size() != 0) {
		POINT targetIdx = { character->_lWayIdxList.begin()->x, character->_lWayIdxList.begin()->y };
		//	못가는 곳 판정이 났으면, 아이들로 바꾸고 지워라
		if (targetIdx.x == -1 && targetIdx.y == -1) {
			character->_state = CHAR_STATE::IDLE;
			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
			character->_isStateChanged = true;
			if ((character->_lOrderList.begin()->kinds) == ORDER_KINDS::MOVE)
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

	//	단순이동 & 목적지 도착
	if (character->_lWayIdxList.size() == 0 && !character->_isOnAtking) {
		//	목적지 도착
	//else {
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
		if ((character->_lOrderList.begin()->kinds) == ORDER_KINDS::MOVE)
			character->_lOrderList.pop_front();
	//}
	}

	//	공격이동 & 목적지 도착 -> (move오더 삭제하고)일단 아이들로 보냄 -> idle에서 공격카운트 되면, 최종 공격 할거임.
	else if (character->_lWayIdxList.size() == 0 && character->_isOnAtking) {
		character->_lOrderList.pop_front();
		character->_state = CHAR_STATE::IDLE;
		character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		character->_isStateChanged = true;
	}

	
	
}

void stateMove::CalDirFunc(Character* character)
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

void stateMove::CalTileForRender(Character * character)
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
