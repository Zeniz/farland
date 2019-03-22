#include "stdafx.h"
#include "charPalm.h"


charPalm::charPalm()
{
	IMAGEMANAGER->addFrameImage("charPalm", L"images/characters/palmSprite.png", 2560, 2560, 10, 10);
	KEYANIMANAGER->addAnimationType("palm");

	int idleFront[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "idleFront", "charPalm",
		idleFront, 4, 5, true);

	int idleBack[] = { 10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "idleBack", "charPalm",
		idleBack, 4, 5, true);

	int moveFront[] = { 20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "moveFront", "charPalm",
		moveFront, 4, 5, true);

	int moveBack[] = { 30,31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "moveBack", "charPalm",
		moveBack, 4, 5, true);


	int atkFront[] = { 40,41,42,43,44,45,46,47,48 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "atk1Front", "charPalm",
		atkFront, 9, 5, false);

	int atkBack[] = { 50,51,52,53,54,55,56,57,58 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "atk1Back", "charPalm",
		atkBack, 9, 5, false);


	int castStartFront[] = { 60,61,62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "castStartFront", "charPalm",
		castStartFront, 4, 5, false);

	int castFront[] = { 64,65,64 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "castFront", "charPalm",
		castFront, 3, 5, true);

	int castEndFront[] = { 66,67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "castEndFront", "charPalm",
		castEndFront, 4, 5, false);



	int castStartBack[] = { 70,71,72,73 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "castStartBack", "charPalm",
		castStartBack, 4, 5, false);

	int castBack[] = { 74,75,74 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "castBack", "charPalm",
		castBack, 3, 5, true);

	int castEndBack[] = { 76,77,78,79 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "castEndBack", "charPalm",
		castEndBack, 4, 5, false);

	

	int stateIdleFront[] = { 80 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateIdleFront", "charPalm",
		stateIdleFront, 1, 5, false);

	int stateDeadFront[] = { 81 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateDeadFront", "charPalm",
		stateDeadFront, 1, 5, true);

	int stateGethitFront[] = { 82 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateGetHitFront", "charPalm",
		stateGethitFront, 1, 5, false);

	int stateStoneFront[] = { 83 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateStoneFront", "charPalm",
		stateStoneFront, 1, 5, true);

	int stateFrozenFront[] = { 84 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateFrozenFront", "charPalm",
		stateFrozenFront, 1, 5, true);

	int stateGetHit2Front[] = { 85 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateGetHit2Front", "charPalm",
		stateGetHit2Front, 1, 5, false);

	int stateExhaustedFront[] = { 86 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateExhaustedFront", "charPalm",
		stateExhaustedFront, 1, 5, true);

	int stateBlockFront[] = { 87 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateBlockFront", "charPalm",
		stateBlockFront, 1, 5, true);


	int stateIdleBack[] = { 90 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateIdleBack", "charPalm",
		stateIdleBack, 1, 5, false);

	int stateDeadBack[] = { 91 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateDeadBack", "charPalm",
		stateDeadBack, 1, 5, true);

	int stateGethitBack[] = { 92 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateGetHitBack", "charPalm",
		stateGethitBack, 1, 2, false);

	int stateStoneBack[] = { 93 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateStoneBack", "charPalm",
		stateStoneBack, 1, 5, true);

	int stateFrozenBack[] = { 94 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateFrozenBack", "charPalm",
		stateFrozenBack, 1, 5, true);

	int stateGetHit2Back[] = { 95 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateGetHit2Back", "charPalm",
		stateGetHit2Back, 1, 5, false);

	int stateExhaustedBack[] = { 96 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateExhaustedBack", "charPalm",
		stateExhaustedBack, 1, 5, true);

	int stateBlockBack[] = { 97 };
	KEYANIMANAGER->addArrayFrameAnimation("palm", "stateBlockBack", "charPalm",
		stateBlockBack, 1, 5, true);
}


charPalm::~charPalm()
{
}

HRESULT charPalm::init()
{
	_img = IMAGEMANAGER->findImage("charPalm");
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

	_name = CHAR_NAME::PALM;
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

void charPalm::InitObjectiveValDefault(POINT mapIdx)
{
	_img = IMAGEMANAGER->findImage("charPalm");
	_frameX = 0;
	_frameY = 0;

	_pos = ConvertIdxToPosFloat(mapIdx.x, mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());
	_zLevel = 0;

	_ani = KEYANIMANAGER->findAnimation("palm", "idleFront");
	_curTile = (*_vvMap)[mapIdx.y][mapIdx.x];
	_frontTile = nullptr;
	_targetTile = nullptr;
}

void charPalm::InitCharacteristicValDefault()
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

	_name = CHAR_NAME::PALM;
	_dir = CHAR_DIR::RB;
	_state = CHAR_STATE::IDLE;
	_curState = _arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
}

void charPalm::InitCharacteristicAugValDefault()
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

void charPalm::release()
{
}

void charPalm::update()
{
	mapIdx = _curTile->_mapIdx;
	_mapIdx = _curTile->_mapIdx;
	//	애니메이션 세팅
	setAni();
	//makeIdleByEndAni();
	MakeIdleByEndAni();
	CoolDownFunc();

	if (_isSelectedChar) {
		SetModeFunc();
		MakeOrder();
	}
	BuffFunc();

	_curState->update(this);
}

void charPalm::setAni()
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
				_ani = KEYANIMANAGER->findAnimation("palm", "idleFront");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("palm", "moveFront");
				break;
			case CHAR_STATE::CASTING:
				if (_isCastBegin) {
					_isCastBegin = false;
					_ani = KEYANIMANAGER->findAnimation("palm", "castStartFront");
				}
				else {
					_ani = KEYANIMANAGER->findAnimation("palm", "castFront");
				}

				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateDeadFront");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateGetHitFront");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateStoneFront");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateFrozenFront");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateGetHit2Front");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateBlockFront");
				break;
			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("palm", "atk1Front");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndFront");	//	임시 -> 해당스킬 이름으로 바꿔야함
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
				_ani = KEYANIMANAGER->findAnimation("palm", "idleBack");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("palm", "moveBack");
				break;
			case CHAR_STATE::CASTING:
				if (_isCastBegin) {
					_isCastBegin = false;
					_ani = KEYANIMANAGER->findAnimation("palm", "castStartBack");
				}
				else {
					_ani = KEYANIMANAGER->findAnimation("palm", "castBack");
				}
				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateDeadBack");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateGetHitBack");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateStoneBack");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateFrozenBack");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateGetHit2Back");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("palm", "stateBlockBack");
				break;

			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("palm", "atk1Back");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndBack");
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndBack");
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndBack");
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("palm", "castEndBack");
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
