#include "stdafx.h"
#include "stateIdle.h"


stateIdle::stateIdle()
{
}


stateIdle::~stateIdle()
{
}

void stateIdle::onIdle(Character* character)
{
}

void stateIdle::onMove(Character* character)
{
}

void stateIdle::onCast(Character* character)
{
}

void stateIdle::onDead(Character* character)
{
}

void stateIdle::onGetHit(Character* character)
{
}

void stateIdle::onStone(Character* character)
{
}

void stateIdle::onFrozen(Character* character)
{
}

void stateIdle::onGetHit2(Character* character)
{
}

void stateIdle::onBlock(Character* character)
{
}

void stateIdle::onBasicAtk(Character * character)
{
}

void stateIdle::onSkillOne(Character * character)
{
}

void stateIdle::onSkillTwo(Character * character)
{
}

void stateIdle::onSkillThree(Character * character)
{
}

void stateIdle::onSkillFour(Character * character)
{
}

void stateIdle::update(Character* character)
{
	character->_portraitKinds = CHAR_PORTRAIT_KINDS::BASIC;
	character->_tileForRender = character->_curTile;

	//	공격오더중, 재이동을 위해 명령재실행(move로 시작하는)을 판단하는 변수.
	bool isNeedMoveAgain = true;

	//	ATK으로 가는 코드
	//	공격준비중이라면, ATK
	//if (character->_lOrderList.size() != 0 && character->_lOrderList.begin()->kinds == ORDER_KINDS::ATTACK) {
	//	//	이동을 다 했고, 쿨타임 준비가됐다면,
	//	if (character->_lWayIdxList.size() == 0) {
	//		if (character->_coolDownTimer[0][ORDER_KINDS::ATTACK] >= character->_coolDownTimer[1][ORDER_KINDS::ATTACK]) {
	//			bool isNearEnemy = false;
	//			//	상하좌우에 적이 있나?
	//			ChkNearbyEnemy(character, &isNearEnemy);
	//			if (isNearEnemy) {
	//				//	character->_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;
	//
	//				character->_state = CHAR_STATE::BASIC_ATK;
	//				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::BASIC_ATK)];
	//				character->_isStateChanged = true;
	//				return;
	//			}
	//			else { return; }
	//
	//
	//		}
	//		else {
	//			return;
	//		}
	//	}
	//}
	
	//	ATK/SKILL1234 로 가는 통합 함수
	if (character->_lOrderList.size() != 0) {
		if (character->_lOrderList.begin()->kinds == ORDER_KINDS::ATTACK) {
			CalForJumptoAtkState(character, ORDER_KINDS::ATTACK, &isNeedMoveAgain);
		}
		else if (character->_lOrderList.begin()->kinds == ORDER_KINDS::SKILL1) {
			CalForJumptoAtkState(character, ORDER_KINDS::SKILL1, &isNeedMoveAgain);
		}
		else if (character->_lOrderList.begin()->kinds == ORDER_KINDS::SKILL2) {
			CalForJumptoAtkState(character, ORDER_KINDS::SKILL2, &isNeedMoveAgain);
		}
		else if (character->_lOrderList.begin()->kinds == ORDER_KINDS::SKILL3) {
			CalForJumptoAtkState(character, ORDER_KINDS::SKILL3, &isNeedMoveAgain);
		}
		else if (character->_lOrderList.begin()->kinds == ORDER_KINDS::SKILL4) {
			CalForJumptoAtkState(character, ORDER_KINDS::SKILL4, &isNeedMoveAgain);
		}
	}

	if (isNeedMoveAgain) {
		//	오더리스트가 있다면, -> 오더 실행하라(state에 따라 패턴넣어줌)
		if (character->_lOrderList.size() != 0) {
			ORDER_KINDS order = (character->_lOrderList.begin()->kinds);
			switch (order)
			{
			case ORDER_KINDS::NONE:
				break;
			case ORDER_KINDS::HOLD:
				character->_coolDownTimer[0][ORDER_KINDS::HOLD] = 0;
				character->_state = CHAR_STATE::BLOCK;
				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::BLOCK)];
				character->_isStateChanged = true;
				character->_isOnAtking = false;
				EFFECTMANAGER->play("defMode", character->_pos.x, character->_rc.top);
				
				break;
			case ORDER_KINDS::MOVE:
				character->_coolDownTimer[0][ORDER_KINDS::MOVE] = 0;
				character->_state = CHAR_STATE::MOVE;
				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
				character->_isStateChanged = true;
				character->_isOnAtking = false;
				break;
			case ORDER_KINDS::ATTACK:
				//_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;	//	-> move부터 시작되므로, Attk패턴 중에 계속 0 으로 만들자.
				character->_state = CHAR_STATE::MOVE;
				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
				character->_isStateChanged = true;
				character->_isOnAtking = true;
				EFFECTMANAGER->play("atkMode", character->_pos.x, character->_rc.top);
				break;
			case ORDER_KINDS::SKILL1: case ORDER_KINDS::SKILL2:
			case ORDER_KINDS::SKILL3: case ORDER_KINDS::SKILL4:
				character->_state = CHAR_STATE::MOVE;
				character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
				character->_isStateChanged = true;
				character->_isOnAtking = true;

				break;
			default:
				break;
			}

		}
	}

	
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
	//	vvMap* pvvMap = character->_vvMap;
	//	POINT ClickedIdx;
	//	ClickedIdx = ConvertPosToIdx(_ptMouse.x, _ptMouse.y, TILESIZE_WID, TILESIZE_HEI);
	//
	//	if (0 <= ClickedIdx.x && ClickedIdx.x < (*pvvMap)[0].size() &&
	//		0 <= ClickedIdx.y && ClickedIdx.y < (*pvvMap).size()) {
	//		if ((*pvvMap)[ClickedIdx.y][ClickedIdx.x]->_terAttr == T_ATTRIBUTE::T_ATTR_NONE) {
	//			character->_targetTile = ((*pvvMap)[ClickedIdx.y][ClickedIdx.x]);
	//			ASTARFUNC->PathFind(character->mapIdx, PointMake(ClickedIdx.x, ClickedIdx.y), character->mapIdx, character->_lWayIdxList);
	//			character->_state = CHAR_STATE::MOVE;
	//			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
	//			character->_isStateChanged = true;
	//
	//		}
	//	}
	//	
	//}
}

void stateIdle::ChkNearbyEnemy(Character * chara, bool * isNearEnemy)
{
	POINT curMapIdx = chara->mapIdx;
	vEnemy* _vEnemy = chara->_vEnemy;

	if (curMapIdx.x - 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		chara->_dir = CHAR_DIR::LT;
		return;
	}
	if (curMapIdx.x + 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		chara->_dir = CHAR_DIR::RB;
		return;
	}
	if (curMapIdx.x == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y - 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		chara->_dir = CHAR_DIR::RT;
		return;
	}
	if (curMapIdx.x == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y + 1 == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		chara->_dir = CHAR_DIR::LB;
		return;
	}
	//	나랑 겹쳐진곳 추가
	if (curMapIdx.x == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.x) &&
		curMapIdx.y == ((*_vEnemy)[chara->_targetEnemyIdx]->_mapIdx.y)) {
		*isNearEnemy = true;
		return;
	}


	*isNearEnemy = false;
	return;
}

void stateIdle::CalForJumptoAtkState(Character * character, ORDER_KINDS proceedOrder, bool* isNeedMoveAgain)
{
	*isNeedMoveAgain = true;
	if (character->_lOrderList.size() != 0 && character->_lOrderList.begin()->kinds == proceedOrder) {
		//	이동을 다 했고, 쿨타임 준비가됐다면,
		if (character->_lWayIdxList.size() == 0) {
			if (character->_coolDownTimer[0][proceedOrder] >= character->_coolDownTimer[1][proceedOrder]) {
				bool isNearEnemy = false;
				//	상하좌우에 적이 있나?
				ChkNearbyEnemy(character, &isNearEnemy);
				if (isNearEnemy) {
					//적이 근처에 있긴한데, 그놈이 이미 죽었다면 -> order삭제
					vEnemy* pvEnemy = character->_vEnemy;
					if ((*pvEnemy)[character->_targetEnemyIdx]->_state == E_STATE::E_DEAD) {
						character->_lOrderList.erase(character->_lOrderList.begin());
						return;
					}


					//	character->_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;
					CHAR_STATE destState;
					switch (proceedOrder)
					{
					case NONE:
						break;
					case MOVE:
						break;
					case HOLD:
						break;
					case ATTACK:
						destState = CHAR_STATE::BASIC_ATK;
						break;
					case SKILL1:
						destState = CHAR_STATE::CASTING;
						break;
					case SKILL2:
						destState = CHAR_STATE::CASTING;
						break;
					case SKILL3:
						destState = CHAR_STATE::CASTING;
						break;
					case SKILL4:
						destState = CHAR_STATE::CASTING;
						break;
					case ORDER_END:
						break;
					default:
						break;
					}

					character->_state = destState;
					character->_curState = character->_arrStatePattern[static_cast<const int>(destState)];
					character->_isStateChanged = true;
					*isNeedMoveAgain = false;
					return;
				}
				else {
					*isNeedMoveAgain = false;
					return;
				}


			}
			else {
				*isNeedMoveAgain = false;
				return;
			}
		}
	}
}

void stateIdle::CalForJumptoCastState(Character * character, ORDER_KINDS proceedOrder, bool * isNeedMoveAgain)
{
	*isNeedMoveAgain = true;
	if (character->_lOrderList.size() != 0 && character->_lOrderList.begin()->kinds == proceedOrder) {
		//	이동을 다 했고, 쿨타임 준비가됐다면,
		if (character->_lWayIdxList.size() == 0) {
			if (character->_coolDownTimer[0][proceedOrder] >= character->_coolDownTimer[1][proceedOrder]) {
				//	character->_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;
				CHAR_STATE destState;
				switch (proceedOrder)
				{
				case NONE:
					break;
				case MOVE:
					break;
				case HOLD:
					break;
				case ATTACK:
					destState = CHAR_STATE::BASIC_ATK;
					break;
				case SKILL1:
					destState = CHAR_STATE::CASTING;
					break;
				case SKILL2:
					destState = CHAR_STATE::CASTING;
					break;
				case SKILL3:
					destState = CHAR_STATE::CASTING;
					break;
				case SKILL4:
					destState = CHAR_STATE::CASTING;
					break;
				case ORDER_END:
					break;
				default:
					break;
				}

				character->_state = destState;
				character->_curState = character->_arrStatePattern[static_cast<const int>(destState)];
				character->_isStateChanged = true;
				*isNeedMoveAgain = false;
				return;
				


			}
			else {
				*isNeedMoveAgain = false;
				return;
			}
		}
	}
}
