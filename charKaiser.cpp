#include "stdafx.h"
#include "charKaiser.h"


charKaiser::charKaiser()
{
	IMAGEMANAGER->addFrameImage("charKaiser", L"images/characters/kaiserSprite.png", 2560, 2560, 10, 10);
	KEYANIMANAGER->addAnimationType("kaiser");

	int idleFront[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "idleFront", "charKaiser",
		idleFront, 4, 5, true);

	int idleBack[] = { 10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "idleBack", "charKaiser",
		idleBack, 4, 5, true);

	int moveFront[] = { 20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "moveFront", "charKaiser",
		moveFront, 4, 5, true);

	int moveBack[] = { 30,31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "moveBack", "charKaiser",
		moveBack, 4, 5, true);

	int castStartFront[] = { 60,};
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "castStartFront", "charKaiser",
		castStartFront, 1, 5, false);

	int castFront[] = { 60,61,62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "castFront", "charKaiser",
		castFront, 4, 5, true);

	int castEndFront[] = { 64,65 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "castEndFront", "charKaiser",
		castEndFront, 2, 2, false);


	int castStartBack[] = { 70 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "castStartBack", "charKaiser",
		castStartBack, 1, 5, false);

	int castBack[] = { 70,71,72,73 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "castBack", "charKaiser",
		castBack, 4, 5, true);

	int castEndBack[] = { 74,75 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "castEndBack", "charKaiser",
		castEndBack, 2, 5, false);


	int stateIdleFront[] = { 80 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateIdleFront", "charKaiser",
		stateIdleFront, 1, 5, false);

	int stateDeadFront[] = { 81 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateDeadFront", "charKaiser",
		stateDeadFront, 1, 5, true);

	int stateGethitFront[] = { 82 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateGetHitFront", "charKaiser",
		stateGethitFront, 1, 5, false);

	int stateStoneFront[] = { 83 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateStoneFront", "charKaiser",
		stateStoneFront, 1, 5, true);

	int stateFrozenFront[] = { 84 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateFrozenFront", "charKaiser",
		stateFrozenFront, 1, 5, true);

	int stateGetHit2Front[] = { 85 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateGetHit2Front", "charKaiser",
		stateGetHit2Front, 1, 5, false);

	int stateExhaustedFront[] = { 86 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateExhaustedFront", "charKaiser",
		stateExhaustedFront, 1, 5, true);

	int stateBlockFront[] = { 87 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateBlockFront", "charKaiser",
		stateBlockFront, 1, 5, true);


	int stateIdleBack[] = { 90 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateIdleBack", "charKaiser",
		stateIdleBack, 1, 5, false);

	int stateDeadBack[] = { 91 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateDeadBack", "charKaiser",
		stateDeadBack, 1, 5, true);

	int stateGethitBack[] = { 92 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateGetHitBack", "charKaiser",
		stateGethitBack, 1, 2, false);

	int stateStoneBack[] = { 93 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateStoneBack", "charKaiser",
		stateStoneBack, 1, 5, true);

	int stateFrozenBack[] = { 94 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateFrozenBack", "charKaiser",
		stateFrozenBack, 1, 5, true);

	int stateGetHit2Back[] = { 95 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateGetHit2Back", "charKaiser",
		stateGetHit2Back, 1, 5, false);

	int stateExhaustedBack[] = { 96 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateExhaustedBack", "charKaiser",
		stateExhaustedBack, 1, 5, true);

	int stateBlockBack[] = { 97 };
	KEYANIMANAGER->addArrayFrameAnimation("kaiser", "stateBlockBack", "charKaiser",
		stateBlockBack, 1, 5, true);
}


charKaiser::~charKaiser()
{
}

HRESULT charKaiser::init()
{
	_img = IMAGEMANAGER->findImage("charKaiser");

	_name = ENEMY_NAME::MOB_KAISER;
	

	_isNotice = false;
	_targetCharIdx = -1;
	_bossAction = BOSS_ACTION::BOSS_ACTION_NONE;
	_maskImgNum = 3;
	_skillMaskTile.init();

	return S_OK;
}

void charKaiser::InitObjectiveValDefault(POINT mapIdx)
{
	_img = IMAGEMANAGER->findImage("charKaiser");
	_frameX = 0;
	_frameY = 0;

	_pos = ConvertIdxToPosFloat(mapIdx.x, mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());
	_zLevel = 0;

	_ani = KEYANIMANAGER->findAnimation("kaiser", "idleFront");
	_pCurTile = (*_vvMap)[mapIdx.y][mapIdx.x];
	_tileForRender = _pCurTile;
	
	_mapIdx = mapIdx;
}

void charKaiser::InitCharacteristicValDefault()
{
	_statValue[E_STATS::E_CURHP] = this->BASIC_MAXHP;
	_statValue[E_STATS::E_MAXHP] = this->BASIC_MAXHP;
	_statValue[E_STATS::E_CURMP] = this->BASIC_MAXMP;
	_statValue[E_STATS::E_MAXMP] = this->BASIC_MAXMP;

	_statValue[E_STATS::E_MOVESPD] = this->BASIC_MOVESPD;
	_statValue[E_STATS::E_CASTSPD] = this->BASIC_CASTSPD;

	_statValue[E_STATS::E_ATK] = this->BASIC_ATK;
	_statValue[E_STATS::E_DEF] = this->BASIC_DEF;
	_statValue[E_STATS::E_MATK] = this->BASIC_MATK;
	_statValue[E_STATS::E_MDEF] = this->BASIC_MDEF;

	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };

	_name = ENEMY_NAME::MOB_KAISER;
	_dir = E_DIR::DIR_LB;
	_state = E_STATE::E_IDLE;
}


void charKaiser::release()
{
}

void charKaiser::update()
{
	_pCurTile = (*_vvMap)[_mapIdx.y][_mapIdx.x];						//필수
	_zLevel = _pCurTile->_zLevel;										//필수


//	적 발견하는 조건
	if (!_isNotice) {
		NoticeFunc(this->NOTICE_RANGE);
	}

	setAni();
	MakeIdleByEndAni();
	patternUpdate();
	ChkDead();

	_hpBar->update();


}

void charKaiser::setAni()
{
	if (_isStateChanged) {
		_isStateChanged = false;
		_ani->stop();
		if (_dir == E_DIR::DIR_LB || _dir == E_DIR::DIR_RB) {
			switch (_state)
			{
			case E_STATUS_NONE:
				break;
			case E_IDLE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "idleFront");
				break;
			case E_DEAD:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateDeadFront");
				break;
			case E_GETDMG:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHitFront");
				break;
			case E_STONED:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateStoneFront");
				break;
			case E_FROZEN:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateFrozenFront");
				break;
			case E_GETCRIDMG:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHit2Front");
				break;
			case E_STUNNED:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateExhaustedFront");
				break;
			case E_BLOCK:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateBlockFront");
				break;
			case E_MOVE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "moveFront");
				break;
			case E_ATK1:
				
				break;
			case E_ATK2:

				break;
			case E_ATK3:

				break;
			case E_SKILL1_CAST:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castFront");
				break;
			case E_SKILL1_SHOT:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndFront");
				break;
			case E_SKILL2_CAST:

				break;
			case E_SKILL2_SHOT:

				break;
			case E_SKILL3_CAST:
				break;
			case E_SKILL3_SHOT:
				break;
			case E_SKILL4_CAST:
				break;
			case E_SKILL4_SHOT:
				break;
			case E_STATUS_END:
				break;
			default:
				break;
			}
		}

		else if (_dir == E_DIR::DIR_LT || _dir == E_DIR::DIR_RT) {
			switch (_state)
			{
			case E_STATUS_NONE:
				break;
			case E_IDLE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "idleBack");
				break;
			case E_DEAD:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateDeadBack");
				break;
			case E_GETDMG:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHitBack");
				break;
			case E_STONED:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateStoneBack");
				break;
			case E_FROZEN:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateFrozenBack");
				break;
			case E_GETCRIDMG:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHit2Back");
				break;
			case E_STUNNED:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateExhaustedBack");
				break;
			case E_BLOCK:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateBlockBack");
				break;
			case E_MOVE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "moveBack");
				break;
			case E_ATK1:
				
				break;
			case E_ATK2:

				break;
			case E_ATK3:

				break;
			case E_SKILL1_CAST:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castBack");

				break;
			case E_SKILL1_SHOT:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndBack");

				break;
			case E_SKILL2_CAST:

				break;
			case E_SKILL2_SHOT:

				break;
			case E_SKILL3_CAST:
				break;
			case E_SKILL3_SHOT:
				break;
			case E_SKILL4_CAST:
				break;
			case E_SKILL4_SHOT:
				break;
			case E_STATUS_END:
				break;
			default:
				break;
			}
		}
		_ani->start();


	}
}



/*
void charKaiser::setAni()
{
	if (_isStateChanged) {
		_isStateChanged = false;
		_ani->stop();
		if (_dir == CHAR_DIR::LB || _dir == CHAR_DIR::RB) {
			switch (_state)
			{
			case CHAR_STATE::NONE:
				break;
			case CHAR_STATE::IDLE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "idleFront");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "moveFront");
				break;
			case CHAR_STATE::CASTING:
				if (_isCastBegin) {
					_isCastBegin = false;
					_ani = KEYANIMANAGER->findAnimation("kaiser", "castStartFront");
				}
				else {
					_ani = KEYANIMANAGER->findAnimation("kaiser", "castFront");
				}

				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateDeadFront");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHitFront");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateStoneFront");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateFrozenFront");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHit2Front");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateBlockFront");
				break;
			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "atk1Front");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::CHAR_STATE_END:
				break;
			default:
				break;
			}



		}
		else if (_dir == CHAR_DIR::LT || _dir == CHAR_DIR::RT) {
			switch (_state)
			{
			case CHAR_STATE::NONE:
				break;
			case CHAR_STATE::IDLE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "idleBack");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "moveBack");
				break;
			case CHAR_STATE::CASTING:
				if (_isCastBegin) {
					_isCastBegin = false;
					_ani = KEYANIMANAGER->findAnimation("kaiser", "castStartBack");
				}
				else {
					_ani = KEYANIMANAGER->findAnimation("kaiser", "castBack");
				}
				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateDeadBack");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHitBack");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateStoneBack");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateFrozenBack");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateGetHit2Back");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "stateBlockBack");
				break;

			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "atk1Back");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndBack");
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndBack");
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndBack");
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("kaiser", "castEndBack");
				break;

			case CHAR_STATE::CHAR_STATE_END:
				break;
			default:
				break;
			}
		}
		_ani->start();
	}
}


void charKaiser::AIForKaiser()
{
	if (_isNotice) {
		if (_state == E_STATE::E_IDLE) {
			
				ChooseSkill();
				TargetSelectFunc();

				//	길찾기
				ASTARFUNC->PathFind(mapIdx, (*_pvChara)[_targetCharIdx]->mapIdx, mapIdx, _lWayIdxList);
				//	길을 찾았으면,
				if (_lWayIdxList.size() != 0 && _lWayIdxList.begin()->x != -1) {
					_targetTile = ((*_vvMap)[(*_pvChara)[_targetCharIdx]->mapIdx.y][(*_pvChara)[_targetCharIdx]->mapIdx.x]);
					
					//	스킬 범위에 따라 lwaylist뺴줘야함
					int range = 0;
					switch (_curKaiserSkill)
					{
					case BOSS_SKILL_NONE:
						break;
					case BOSS_SNATCH:
						range = SKILLMANAGER->FindSkill("snatch")->getRange();
						break;
					case BOSS_ATK1:
						range = SKILLMANAGER->FindSkill("bossAtk1")->getRange();
						break;
					case BOSS_ATK2:
						range = SKILLMANAGER->FindSkill("bossAtk1")->getRange();
						break;
					case BOSS_BUFF:
						range = SKILLMANAGER->FindSkill("bossAtk1")->getRange();
						break;
					case BOSS_HOLD:
						range = 9999999;
						break;
					case KAISER_SKILL_END:
						break;
					default:
						break;
					}

					for (int i = 0; i < range; i++) {
						if (_lWayIdxList.size() == 0)	break;
						_lWayIdxList.pop_back();
					}
					//	스킬range만큼 뻇는데도 이동해야한다면, -> moveOrder먼저 삽입
					if (_lWayIdxList.size() != 0) {
						tagOrderInfo moveOrder;
						moveOrder.kinds = ORDER_KINDS::MOVE;
						moveOrder.targetMapIdx = _lWayIdxList.back();
						_lOrderList.push_back(moveOrder);
					}

					//	랜덤으로 결정된 스킬에 따라, 오더 설정
					tagOrderInfo skillOrder;
					switch (_curKaiserSkill)
					{
					case BOSS_SKILL_NONE:
						break;
					case BOSS_SNATCH:
						skillOrder.kinds = ORDER_KINDS::SKILL1;
						skillOrder.targetMapIdx = (*_pvChara)[_targetCharIdx]->mapIdx;
						break;
					case BOSS_ATK1:
						skillOrder.kinds = ORDER_KINDS::SKILL2;
						skillOrder.targetMapIdx = (*_pvChara)[_targetCharIdx]->mapIdx;
						break;
					case BOSS_ATK2:
						skillOrder.kinds = ORDER_KINDS::SKILL3;
						skillOrder.targetMapIdx = (*_pvChara)[_targetCharIdx]->mapIdx;
						break;
					case BOSS_BUFF:
						skillOrder.kinds = ORDER_KINDS::SKILL4;
						skillOrder.targetMapIdx = mapIdx;
						break;
					case BOSS_HOLD:
						skillOrder.kinds = ORDER_KINDS::HOLD;
						skillOrder.targetMapIdx = mapIdx;
						break;
					case KAISER_SKILL_END:
						break;
					default:
						break;
					}
					_lOrderList.push_back(skillOrder);


				}
				//	길을 못찾았으면,
				else {
					_curKaiserSkill = KAISER_SKILL::BOSS_HOLD;
					tagOrderInfo holdOrder;
					holdOrder.kinds = ORDER_KINDS::HOLD;
					holdOrder.targetMapIdx = mapIdx;
					_lOrderList.push_back(holdOrder);
				}

			}	//	오더리스트가 비어있다면 끗.
		}	//	Idle상태일떄 오더내리기 끗
	}
	else {
		NoticeFunc();
	}

	
}


void charKaiser::TargetSelectFunc()
{
	int curMinDistance = 9999999;
	for (int i = 0; i < _pvChara->size(); i++) {
		POINT targetIdx = (*_pvChara)[i]->mapIdx;
		int distance;
		distance = abs(targetIdx.x - mapIdx.x) + abs(targetIdx.y - mapIdx.y);
		if (curMinDistance > distance) {
			curMinDistance = distance;
			_targetCharIdx = i;
		}
	}
}

void charKaiser::ChooseSkill()
{
	int randNum;
	randNum = RND->getFromIntTo(0, KAISER_SKILL::KAISER_SKILL_END);
	switch (randNum)
	{
	case BOSS_SNATCH:
		_curKaiserSkill = BOSS_SNATCH;		
		break;
	case BOSS_ATK1:
		_curKaiserSkill = BOSS_ATK1;
		break;
	case BOSS_ATK2:
		_curKaiserSkill = BOSS_ATK2;
		break;
	case BOSS_BUFF:
		_curKaiserSkill = BOSS_BUFF;
		break;
	case BOSS_HOLD:
		_curKaiserSkill = BOSS_HOLD;
		break;
		
	default:
		break;
	}
}
*/