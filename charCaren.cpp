#include "stdafx.h"
#include "charCaren.h"


charCaren::charCaren()
{
	IMAGEMANAGER->addFrameImage("charCaren", L"images/characters/carenSprite.png", 3584, 2560, 14, 10);
	KEYANIMANAGER->addAnimationType("caren");

	int idleFront[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "idleFront", "charCaren",
		idleFront, 4, 5, true);

	int idleBack[] = { 14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "idleBack", "charCaren",
		idleBack, 4, 5, true);

	int moveFront[] = { 28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "moveFront", "charCaren",
		moveFront, 4, 5, true);

	int moveBack[] = { 42,43,44,45 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "moveBack", "charCaren",
		moveBack, 4, 5, true);

	int castStartFront[] = { 56,57,58,59,60 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "castStartFront", "charCaren",
		castStartFront, 5, 5, false);

	int castFront[] = { 61,62,63,64,63,62,61 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "castFront", "charCaren",
		castFront, 7, 5, true);

	int castEndFront[] = { 65,66,67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "castEndFront", "charCaren",
		castEndFront, 5, 5, false);

	int atkFront[] = { 65,66,67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "atk1Front", "charCaren",
		atkFront, 5, 5, false);


	int castStartBack[] = { 70,71,72,73,74 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "castStartBack", "charCaren",
		castStartBack, 5, 5, false);

	int castBack[] = { 75,76,77,78,77,76,75 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "castBack", "charCaren",
		castBack, 7, 5, true);
	
	int castEndBack[] = { 79,80,81,82,83 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "castEndBack", "charCaren",
		castEndBack, 5, 5, false);

	int atkBack[] = { 79,80,81,82,83 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "atk1Back", "charCaren",
		atkBack, 5, 5, false);

	int stateIdleFront[] = { 84 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateIdleFront", "charCaren",
		stateIdleFront, 1, 5, false);

	int stateDeadFront[] = { 85 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateDeadFront", "charCaren",
		stateDeadFront, 1, 5, true);

	int stateGethitFront[] = { 86 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateGetHitFront", "charCaren",
		stateGethitFront, 1, 5, false);

	int stateStoneFront[] = { 87 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateStoneFront", "charCaren",
		stateStoneFront, 1, 5, true);

	int stateFrozenFront[] = { 88 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateFrozenFront", "charCaren",
		stateFrozenFront, 1, 5, true);

	int stateGetHit2Front[] = { 89 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateGetHit2Front", "charCaren",
		stateGetHit2Front, 1, 5, false);

	int stateExhaustedFront[] = { 90 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateExhaustedFront", "charCaren",
		stateExhaustedFront, 1, 5, true);

	int stateBlockFront[] = { 91 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateBlockFront", "charCaren",
		stateBlockFront, 1, 5, true);


	int stateIdleBack[] = { 98 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateIdleBack", "charCaren",
		stateIdleBack, 1, 5, false);

	int stateDeadBack[] = { 99 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateDeadBack", "charCaren",
		stateDeadBack, 1, 5, true);

	int stateGethitBack[] = { 100 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateGetHitBack", "charCaren",
		stateGethitBack, 1, 2, false);

	int stateStoneBack[] = { 101 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateStoneBack", "charCaren",
		stateStoneBack, 1, 5, true);

	int stateFrozenBack[] = { 102 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateFrozenBack", "charCaren",
		stateFrozenBack, 1, 5, true);

	int stateGetHit2Back[] = { 103 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateGetHit2Back", "charCaren",
		stateGetHit2Back, 1, 5, false);

	int stateExhaustedBack[] = { 104 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateExhaustedBack", "charCaren",
		stateExhaustedBack, 1, 5, true);

	int stateBlockBack[] = { 105 };
	KEYANIMANAGER->addArrayFrameAnimation("caren", "stateBlockBack", "charCaren",
		stateBlockBack, 1, 5, true);

}


charCaren::~charCaren()
{
}

HRESULT charCaren::init()
{
	_img = IMAGEMANAGER->findImage("charCaren");
	_maskImgNum = 1;
	//_frameX = NULL;
	//_frameY = NULL;
	//
	//_pos = { NULL,NULL };
	//_rc = { NULL,NULL,NULL,NULL };
	//_zLevel = NULL;
	//_objKinds = OBJ_KINDS::OBJKIND_CHAR;
	//
	//_ani = nullptr;
	//_frontTile = nullptr;
	//_curTile = nullptr;
	//_targetTile = nullptr;
	//
	//
	//for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
	//	for (int j = 0; j < CHAR_VALUE_KINDS::CHAR_VALUE_NONE; j++) {
	//		_charValue[i][j] = NULL;
	//	}
	//}
	//
	//_moveVec = { NULL,NULL };
	//_probePos = { NULL,NULL };

	_name = CHAR_NAME::CAREN;
	//_dir = CHAR_DIR::NONE;
	//_state = CHAR_STATE::NONE;
	//_statePattern = nullptr;
	//for (int i = 0; i < static_cast<const int>(CHAR_STATE::CHAR_STATE_END); i++)
	//	_arrStatePattern[i] = nullptr;

	//_portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
	//_portraitFrameIdx = { NULL,NULL };
	//_curSkill = CUR_SKILL::NONE;
	//_lOrderList.clear();
	//_lWayIdxList.clear();


	return S_OK;
}

void charCaren::InitObjectiveValDefault(POINT mapIdx)
{
	_img = IMAGEMANAGER->findImage("charCaren");
	_frameX = 0;
	_frameY = 0;

	_pos = ConvertIdxToPosFloat(mapIdx.x, mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());
	_zLevel = 0;

	_ani = KEYANIMANAGER->findAnimation("caren", "idleFront");
	_curTile = (*_vvMap)[mapIdx.y][mapIdx.x];
	_frontTile = nullptr;
	_targetTile = nullptr;
}

void charCaren::InitCharacteristicValDefault()
{
	_charValue[CUR][MAX_HP] = this->BASIC_MAXHP;
	_charValue[CUR][CUR_HP] = this->BASIC_MAXHP;
	_charValue[CUR][REGEN_HP] = this->BASIC_REGENHP;
	_charValue[CUR][MAX_MP] = this->BASIC_MAXMP;
	_charValue[CUR][CUR_MP] = this->BASIC_MAXMP;
	_charValue[CUR][REGEN_MP] = this->BASIC_REGENMP;
	_charValue[CUR][MOVE_SPD] = this->BASIC_MOVESPD;
	_charValue[CUR][CASTING_SPD] = this->BASIC_CASTSPD;
	_charValue[CUR][ATK] = this->BASIC_ATK;
	_charValue[CUR][DEF] = this->BASIC_DEF;
	_charValue[CUR][M_ATK] = this->BASIC_MATK;
	_charValue[CUR][M_DEF] = this->BASIC_MDEF;


	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };	//	업뎃필요,

	_name = CHAR_NAME::CAREN;
	_dir = CHAR_DIR::RB;
	_state = CHAR_STATE::IDLE;
	_curState = _arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
}

void charCaren::InitCharacteristicAugValDefault()
{
	_charValue[AUG][MAX_HP] = NULL;
	_charValue[AUG][CUR_HP] = NULL;
	_charValue[AUG][REGEN_HP] = NULL;
	_charValue[AUG][MAX_MP] = NULL;
	_charValue[AUG][CUR_MP] = NULL;
	_charValue[AUG][REGEN_MP] = NULL;
	_charValue[AUG][MOVE_SPD] = NULL;
	_charValue[AUG][CASTING_SPD] = NULL;
	_charValue[AUG][ATK] = NULL;
	_charValue[AUG][DEF] = NULL;
	_charValue[AUG][M_ATK] = NULL;
	_charValue[AUG][M_DEF] = NULL;
}

void charCaren::release()
{
}

void charCaren::update()
{
	mapIdx = _curTile->_mapIdx;
	_mapIdx = _curTile->_mapIdx;
	//	애니메이션 세팅
	setAni();
	//makeIdleByEndAni();
	MakeIdleByEndAni();
	CoolDownFunc();

	//	timedelay중에도 얘들은 실시간으로 업뎃해야하니,
	//	따로 뺴서 따로 업뎃해야하나? (일단 따로 뺴둠)charmgr->orderUpdate();
	//if (_isSelectedChar) {
	//	SetModeFunc();
	//	MakeOrder();
	//}

	BuffFunc();
	_curState->update(this);
}

void charCaren::setAni()
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
				_ani = KEYANIMANAGER->findAnimation("caren", "idleFront");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("caren", "moveFront");
				break;
			case CHAR_STATE::CASTING:
				if (_isCastBegin) {
					_isCastBegin = false;
					_ani = KEYANIMANAGER->findAnimation("caren", "castStartFront");
				}
				else {
					_ani = KEYANIMANAGER->findAnimation("caren", "castFront");
				}
				
				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateDeadFront");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateGetHitFront");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateStoneFront");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateFrozenFront");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateGetHit2Front");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateBlockFront");
				break;
			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("caren", "atk1Front");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
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
				_ani = KEYANIMANAGER->findAnimation("caren", "idleBack");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("caren", "moveBack");
				break;
			case CHAR_STATE::CASTING:
				if (_isCastBegin) {
					_isCastBegin = false;
					_ani = KEYANIMANAGER->findAnimation("caren", "castStartBack");
				}
				else {
					_ani = KEYANIMANAGER->findAnimation("caren", "castBack");
				}
				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateDeadBack");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateGetHitBack");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateStoneBack");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateFrozenBack");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateGetHit2Back");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("caren", "stateBlockBack");
				break;

			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("caren", "atk1Back");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndBack");
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndBack");
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndBack");
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("caren", "castEndBack");
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
