#include "stdafx.h"
#include "charLeon.h"


charLeon::charLeon()
{
	IMAGEMANAGER->addFrameImage("charLeon", L"images/characters/leonSprite.png", 2048, 4096, 8, 16);
	KEYANIMANAGER->addAnimationType("leon");

	int leonIdleFrontAry[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "idleFront", "charLeon", 
		leonIdleFrontAry, 4, 5, true);

	int leonIdleBackAry[] = { 8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "idleBack", "charLeon",
		leonIdleBackAry, 4, 5, true);

	int leonMoveFrontAry[] = { 16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "moveFront", "charLeon",
		leonMoveFrontAry, 4, 5, true);

	int leonMoveBackAry[] = { 24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "moveBack", "charLeon",
		leonMoveBackAry, 4, 5, true);

	int leonCastFrontAry[] = { 32,33,34 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "castFront", "charLeon",
		leonCastFrontAry, 3, 5, true);

	int leonCastBackAry[] = { 40,41,42 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "castBack", "charLeon",
		leonCastBackAry, 3, 5, true);

	int leonAtk1FrontAry [] = { 48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk1Front", "charLeon",
		leonAtk1FrontAry, 4, 5, false);

	int leonAtk1BackAry[] = { 56,57,58,59 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk1Back", "charLeon",
		leonAtk1BackAry, 4, 5, false);

	int leonAtk2FrontAry[] = { 64,65,66,67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk2Front", "charLeon",
		leonAtk2FrontAry, 6, 5, false);

	int leonAtk2BackAry[] = { 72,73,74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk2Back", "charLeon",
		leonAtk2BackAry, 6, 5, false);

	int leonAtk3FrontAry[] = { 80,81,82,83,84 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk3Front", "charLeon",
		leonAtk3FrontAry, 5, 5, false);
	int leonAtk3BackAry[] = { 88,89,90,91,92 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk3Back", "charLeon",
		leonAtk3BackAry, 5, 5, false);

	int leonAtk4FrontAry[] = { 96,97,98,99,100,101,102 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk4Front", "charLeon",
		leonAtk4FrontAry, 7, 5, false);

	int leonAtk4BackAry[] = { 104,105,106,107,108,109,110 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "atk4Back", "charLeon",
		leonAtk4BackAry, 7, 5, false);

	int stateIdleFront[] = { 112 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateIdleFront", "charLeon",
		stateIdleFront, 1, 5, false);

	int stateDeadFront[] = { 113 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateDeadFront", "charLeon",
		stateDeadFront, 1, 5, true);

	int stateGethitFront[] = { 114 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateGetHitFront", "charLeon",
		stateGethitFront, 1, 2, false);

	int stateStoneFront[] = { 115 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateStoneFront", "charLeon",
		stateStoneFront, 1, 5, true);

	int stateFrozenFront[] = { 116 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateFrozenFront", "charLeon",
		stateFrozenFront, 1, 5, true);

	int stateGetHit2Front[] = { 117 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateGetHit2Front", "charLeon",
		stateGetHit2Front, 1, 5, false);

	int stateExhaustedFront[] = { 118 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateExhaustedFront", "charLeon",
		stateExhaustedFront, 1, 5, true);

	int stateBlockFront[] = { 119 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateBlockFront", "charLeon",
		stateBlockFront, 1, 5, true);


	int stateIdleBack[] = { 120 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateIdleBack", "charLeon",
		stateIdleBack, 1, 5, false);

	int stateDeadBack[] = { 121 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateDeadBack", "charLeon",
		stateDeadBack, 1, 5, true);

	int stateGethitBack[] = { 122 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateGetHitBack", "charLeon",
		stateGethitBack, 1, 2, false);

	int stateStoneBack[] = { 123 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateStoneBack", "charLeon",
		stateStoneBack, 1, 5, true);

	int stateFrozenBack[] = { 124 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateFrozenBack", "charLeon",
		stateFrozenBack, 1, 5, true);

	int stateGetHit2Back[] = { 125 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateGetHit2Back", "charLeon",
		stateGetHit2Back, 1, 5, false);

	int stateExhaustedBack[] = { 126 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateExhaustedBack", "charLeon",
		stateExhaustedBack, 1, 5, true);

	int stateBlockBack[] = { 127 };
	KEYANIMANAGER->addArrayFrameAnimation("leon", "stateBlockBack", "charLeon",
		stateBlockBack, 1, 5, true);


}


charLeon::~charLeon()
{
}

HRESULT charLeon::init()
{
	_img = IMAGEMANAGER->findImage("charLeon");
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

	_name = CHAR_NAME::LEON;
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


void charLeon::InitObjectiveValDefault(POINT mapIdx)
{
	_img = IMAGEMANAGER->findImage("charLeon");
	_frameX = 0;
	_frameY = 0;

	_pos = ConvertIdxToPosFloat(mapIdx.x, mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());
	_zLevel = 0;

	_ani = KEYANIMANAGER->findAnimation("leon", "idleFront");
	_curTile = (*_vvMap)[mapIdx.y][mapIdx.x];
	_frontTile = nullptr;
	_targetTile = nullptr;
}

void charLeon::InitCharacteristicValDefault()
{
	_charValue[CUR][MAX_HP]		= this->BASIC_MAXHP;
	_charValue[CUR][CUR_HP]		= this->BASIC_MAXHP;
	_charValue[CUR][REGEN_HP]	= this->BASIC_REGENHP;
	_charValue[CUR][MAX_MP]		= this->BASIC_MAXMP;
	_charValue[CUR][CUR_MP]		= this->BASIC_MAXMP;
	_charValue[CUR][REGEN_MP]	= this->BASIC_REGENMP;
	_charValue[CUR][MOVE_SPD]	= this->BASIC_MOVESPD;
	_charValue[CUR][CASTING_SPD] = this->BASIC_CASTSPD;
	_charValue[CUR][ATK]		= this->BASIC_ATK;
	_charValue[CUR][DEF]		= this->BASIC_DEF;
	_charValue[CUR][M_ATK]		= this->BASIC_MATK;
	_charValue[CUR][M_DEF]		= this->BASIC_MDEF;


	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };	//	업뎃필요,

	_name = CHAR_NAME::LEON;
	_dir = CHAR_DIR::RB;
	_state = CHAR_STATE::IDLE;
	_curState = _arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
}

void charLeon::InitCharacteristicAugValDefault()
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


void charLeon::release()
{
}


void charLeon::update()
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
/*
void charLeon::aniRender()
{
	if (_dir == CHAR_DIR::LT || _dir == CHAR_DIR::RB) {
		_img->aniRenderReverseX(_rc.left, _rc.top - _curTile->_zLevel*(TILESIZE_HEI / 2), this->_ani);
	}
	else {
		_img->aniRender(_rc.left, _rc.top - _curTile->_zLevel*(TILESIZE_HEI / 2), this->_ani);
	}
	
	WCHAR str[128];
	switch (_state)
	{
	case CHAR_STATE::NONE:
		swprintf_s(str, L"state : NONE");
		break;
	case CHAR_STATE::IDLE:
		swprintf_s(str, L"state : IDLE");
		break;
	case CHAR_STATE::MOVE:
		swprintf_s(str, L"state : MOVE");
		break;
	case CHAR_STATE::CASTING:
		swprintf_s(str, L"state : CASTING");
		break;
	case CHAR_STATE::DEAD:
		swprintf_s(str, L"state : DEAD");
		break;
	case CHAR_STATE::GETHIT:
		swprintf_s(str, L"state : GETHIT");
		break;
	case CHAR_STATE::STONE:
		swprintf_s(str, L"state : STONE");
		break;
	case CHAR_STATE::FROZEN:
		swprintf_s(str, L"state : FROZEN");
		break;
	case CHAR_STATE::GETHIT2:
		swprintf_s(str, L"state : GETHIT2");
		break;
	case CHAR_STATE::BLOCK:
		swprintf_s(str, L"state : BLOCK");
		break;
	case CHAR_STATE::BASIC_ATK:
		swprintf_s(str, L"state : BASIC_ATK");
		break;
	case CHAR_STATE::SKILL1:
		swprintf_s(str, L"state : SKILL1");
		break;
	case CHAR_STATE::SKILL2:
		swprintf_s(str, L"state : SKILL2");
		break;
	case CHAR_STATE::SKILL3:
		swprintf_s(str, L"state : SKILL3");
		break;
	case CHAR_STATE::SKILL4:
		swprintf_s(str, L"state : SKILL4");
		break;
	case CHAR_STATE::CHAR_STATE_END:
		swprintf_s(str, L"state : CHAR_STATE_END");
		break;
	default:
		break;
	}

	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xF00000, 1.0f), L"consolas", 20, str, _rc.left, _rc.top, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));
	//D2DMANAGER->drawText(str, _rc.left, _rc.top - 20);

	switch (_dir)
	{
	case CHAR_DIR::NONE:
		swprintf_s(str, L"dir : NONE");
		break;
	case CHAR_DIR::LT:
		swprintf_s(str, L"dir : LT");
		break;
	case CHAR_DIR::RT:
		swprintf_s(str, L"dir : RT");
		break;
	case CHAR_DIR::LB:
		swprintf_s(str, L"dir : LB");
		break;
	case CHAR_DIR::RB:
		swprintf_s(str, L"dir : RB");
		break;
	case CHAR_DIR::CHAR_DIR_END:
		break;
	default:
		break;
	}
	//D2DMANAGER->drawText(str, _rc.left, _rc.top - 40);
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFF1111, 1.0f), L"consolas", 20, str, _rc.left, _rc.top-20, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));
	
	swprintf_s(str, L"mapIdx : [%d,%d]",_curTile->_mapIdx.x, _curTile->_mapIdx.y);
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xF00000, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 40, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));

	swprintf_s(str, L"isOnAtk : [%d]", _isOnAtking);
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xF00000, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 60, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));
	
	swprintf_s(str, L"waylistSize : [%d]", _lWayIdxList.size());
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xF00000, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 80, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));
	
	
}
*/


/*
void charLeon::KnowingTileFunc()
{
	//mapIdx = ConvertPosToIdx(_pos.x, _pos.y, TILESIZE_WID, TILESIZE_HEI);
	//_curTile = (*_vvMap)[mapIdx.y][mapIdx.x];

	switch (_dir)
	{
	case CHAR_DIR::LT:
		_frontTile = (*_vvMap)[mapIdx.y][mapIdx.x - 1];
		break;
	case CHAR_DIR::RT:
		_frontTile = (*_vvMap)[mapIdx.y - 1][mapIdx.x];
		break;
	case CHAR_DIR::LB:
		_frontTile = (*_vvMap)[mapIdx.y + 1][mapIdx.x];
		break;
	case CHAR_DIR::RB:
		_frontTile = (*_vvMap)[mapIdx.y][mapIdx.x + 1];
		break;
	default:
		break;
	}

}

void charLeon::CalTileforRenderFunc()
{
	POINTFLOAT probe;
	POINT tileIdx;
	switch (_dir)
	{
	case CHAR_DIR::NONE:
		break;
	case CHAR_DIR::LT:
		probe.x = _pos.x - TILESIZE_WID / 4;
		probe.y = _pos.y - TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::RT:
		probe.x = _pos.x + TILESIZE_WID / 4;
		probe.y = _pos.y - TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::LB:
		probe.x = _pos.x - TILESIZE_WID / 4;
		probe.y = _pos.y + TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::RB:
		probe.x = _pos.x + TILESIZE_WID / 4;
		probe.y = _pos.y + TILESIZE_HEI / 4;
		break;
	case CHAR_DIR::CHAR_DIR_END:
		break;
	default:
		break;
	}

	tileIdx = ConvertPosToIdx(probe.x, probe.y, TILESIZE_WID, TILESIZE_HEI);
	if (0 < tileIdx.x && (*_vvMap)[0].size() &&
		0 < tileIdx.y && (*_vvMap).size()) {
		_tileForRender = (*_vvMap)[tileIdx.y][tileIdx.x];
	}
	else {
		_tileForRender = _curTile;
	}
}
*/
void charLeon::setAni()
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
				_ani = KEYANIMANAGER->findAnimation("leon", "idleFront");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("leon", "moveFront");				
				break;
			case CHAR_STATE::CASTING:
				_ani = KEYANIMANAGER->findAnimation("leon", "castFront");				
				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateDeadFront");			
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateGetHitFront");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateStoneFront");				
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateFrozenFront");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateGetHit2Front");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateBlockFront");
				break;
			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk1Front");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk2Front");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk3Front");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk4Front");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk4Front");	//	임시 -> 해당스킬 이름으로 바꿔야함
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
				_ani = KEYANIMANAGER->findAnimation("leon", "idleBack");
				break;
			case CHAR_STATE::MOVE:
				_ani = KEYANIMANAGER->findAnimation("leon", "moveBack");
				break;
			case CHAR_STATE::CASTING:
				_ani = KEYANIMANAGER->findAnimation("leon", "castBack");
				break;
			case CHAR_STATE::DEAD:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateDeadBack");
				break;
			case CHAR_STATE::GETHIT:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateGetHitBack");
				break;
			case CHAR_STATE::STONE:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateStoneBack");
				break;
			case CHAR_STATE::FROZEN:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateFrozenBack");
				break;
			case CHAR_STATE::GETHIT2:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateGetHit2Back");
				break;
			case CHAR_STATE::BLOCK:
				_ani = KEYANIMANAGER->findAnimation("leon", "stateBlockBack");
				break;

			case CHAR_STATE::BASIC_ATK:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk1Back");
				break;
			case CHAR_STATE::SKILL1:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk2Back");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL2:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk3Back");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL3:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk4Back");	//	임시 -> 해당스킬 이름으로 바꿔야함
				break;
			case CHAR_STATE::SKILL4:
				_ani = KEYANIMANAGER->findAnimation("leon", "atk4Back");	//	임시 -> 해당스킬 이름으로 바꿔야함
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

/*
void charLeon::makeIdleByEndAni()
{
	if (!_ani->isPlay()) {
		_isStateChanged = true;
		_state = CHAR_STATE::IDLE;
	}
}

void charLeon::CoolDownFunc()
{
	for (int i = 0; i < 7; i++) {
		if (_coolDownTimer[0][i] < _coolDownTimer[1][i]) {
			_coolDownTimer[0][i]++;
		}
		
		else if (_coolDownTimer[0][i] >= _coolDownTimer[1][i]) {
			_coolDownTimer[0][i] = _coolDownTimer[1][i];
		}
	}
}
*/
/*
void charLeon::OrderPerform()
{
	if (_lOrderList.size() != 0) {
		tagOrderInfo order = *_lOrderList.begin();
		
		switch (order.kinds)
		{
		case ORDER_KINDS::NONE:
			break;
		case ORDER_KINDS::HOLD:
			break;
		case ORDER_KINDS::MOVE:
			this->MoveFunc();
			break;
		case ORDER_KINDS::ATK:
			break;
		case ORDER_KINDS::SKILL1:
			break;
		case ORDER_KINDS::SKILL2:
			break;
		case ORDER_KINDS::SKILL3:
			break;
		case ORDER_KINDS::SKILL4:
			break;
		default:
			break;
		}

	}
	
	
}
*/



void charLeon::stateAniTest()
{
	
	if (KEYMANAGER->isOnceKeyDown('Q')) {
		_state = CHAR_STATE::MOVE;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('W')) {
		_state = CHAR_STATE::CASTING;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('E')) {
		_state = CHAR_STATE::DEAD;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('R')) {
		_state = CHAR_STATE::GETHIT;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('A')) {
		_state = CHAR_STATE::STONE;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('S')) {
		_state = CHAR_STATE::FROZEN;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('D')) {
		_state = CHAR_STATE::GETHIT2;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('F')) {
		_state = CHAR_STATE::BLOCK;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('Z')) {
		_state = CHAR_STATE::BASIC_ATK;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('X')) {
		_state = CHAR_STATE::SKILL1;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('C')) {
		_state = CHAR_STATE::SKILL2;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('V')) {
		_state = CHAR_STATE::SKILL3;
		_isStateChanged = true;
	}
	if (KEYMANAGER->isOnceKeyDown('B')) {
		_state = CHAR_STATE::SKILL4;
		_isStateChanged = true;
	}
	
}




