#include "stdafx.h"
#include "character.h"

#include "charStatePattern.h"
#include "stateIdle.h"
#include "stateMove.h"
#include "stateCast.h"
#include "stateDead.h"
#include "stateGetHit.h"
#include "stateStone.h"
#include "stateFrozen.h"
#include "stateGetHit2.h"
#include "stateBlock.h"

#include "stateBasicAtk.h"
#include "stateSkillOne.h"
#include "stateSkillTwo.h"
#include "stateSkillThree.h"
#include "stateSkillFour.h"


Character::Character()
{
	//	<objects> : public
	_img = nullptr;
	_frameX = NULL;
	_frameY = NULL;
	
	_pos = { NULL,NULL };
	_rc = { NULL,NULL,NULL,NULL };
	_zLevel = NULL;	
	_objKinds = OBJ_KINDS::OBJKIND_CHAR;

	_ani = nullptr;
	_isStateChanged = true;
	_frontTile = nullptr;
	_curTile = nullptr;
	_targetTile = nullptr;

	for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
		for (int j = 0; j < CHAR_VALUE_KINDS::CHAR_VALUE_NONE; j++) {
			_charValue[i][j] = NULL;
		}
	}
	
	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };
	

	_name = CHAR_NAME::NONE;
	_dir = CHAR_DIR::NONE;
	_state = CHAR_STATE::NONE;
	//_statePattern = nullptr;
	for (int i = 0; i < static_cast<const int>(CHAR_STATE::CHAR_STATE_END); i++)
		_arrStatePattern[i] = nullptr;

	_portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
	_portraitFrameIdx = { NULL,NULL };
	_curSkill = SKILL_NUM::NONE;
	_lOrderList.clear();
	_lWayIdxList.clear();


	_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)] = new stateIdle();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)] = new stateMove();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::CASTING)] = new stateCast();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::DEAD)] = new stateDead();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::GETHIT)] = new stateGetHit();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::STONE)] = new stateStone();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::FROZEN)] = new stateFrozen();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::GETHIT2)] = new stateGetHit2();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::BLOCK)] = new stateBlock();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::BASIC_ATK)] = new stateBasicAtk();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL1)] = new stateSkillOne();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL2)] = new stateSkillTwo();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL3)] = new stateSkillThree();
	_arrStatePattern[static_cast<const int>(CHAR_STATE::SKILL4)] = new stateSkillFour();


	screenRc = RectMake(0, 0, UI_START_X, UI_START_Y);
	
	_mode = ORDER_KINDS::NONE;
	_isOrderFin = true;
	_isSelectedChar = false;
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < ORDER_KINDS::ORDER_END; j++) {
			_coolDownTimer[i][j] = 0;
		}
	}
	_coolDownTimer[1][ORDER_KINDS::MOVE] = 50;
	_coolDownTimer[1][ORDER_KINDS::HOLD] = 50;
	_coolDownTimer[1][ORDER_KINDS::ATTACK] = 100;
	_coolDownTimer[1][ORDER_KINDS::SKILL1] = 200;
	_coolDownTimer[1][ORDER_KINDS::SKILL2] = 250;
	_coolDownTimer[1][ORDER_KINDS::SKILL3] = 300;
	_coolDownTimer[1][ORDER_KINDS::SKILL4] = 350;
	
	_skillTileMask.init();
	_holdCounter = 0;
	_holdCounterMax = 60;
	_targetEnemyIdx = -1;
	_aStarCount = 0;
	_basicAtkCount = 0;
	

	
	_isOnAtking = false;
	_isCastBegin = false;

	_vBuff.clear();
	
	
	EFFECTMANAGER->addEffect("atkMode", "images/skillEffect/atkModeEffect.png", 4401, 178, 163, 178, 5, 0.167f, 5);
	EFFECTMANAGER->addEffect("defMode", "images/skillEffect/defModeEffect.png", 4401, 178, 163, 178, 5, 0.167f, 5);
	EFFECTMANAGER->addEffect("meteor", "images/skillEffect/meteor.png", 8338, 490, 758, 490, 5, 0.167f, 5);
	
}


Character::~Character()
{
}

HRESULT Character::init()
{
	_img = NULL;
	_frameX = NULL;
	_frameY = NULL;

	_pos = { NULL,NULL };
	_rc = { NULL,NULL,NULL,NULL };
	_zLevel = NULL;
	_objKinds = OBJ_KINDS::OBJKIND_CHAR;

	_ani = nullptr;
	_frontTile = nullptr;
	_curTile = nullptr;
	_targetTile = nullptr;


	for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
		for (int j = 0; j < CHAR_VALUE_KINDS::CHAR_VALUE_NONE; j++) {
			_charValue[i][j] = NULL;
		}
	}

	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };

	_name = CHAR_NAME::NONE;
	_dir = CHAR_DIR::NONE;
	_state = CHAR_STATE::NONE;
	//_statePattern = nullptr;
	for (int i = 0; i < static_cast<const int>(CHAR_STATE::CHAR_STATE_END); i++)
		_arrStatePattern[i] = nullptr;

	_portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
	_portraitFrameIdx = { NULL,NULL };
	_curSkill = SKILL_NUM::NONE;
	_lOrderList.clear();
	_lWayIdxList.clear();

	_holdCounter = 0;
	_holdCounterMax = 60;
	
	

	return S_OK;
}

void Character::aniRender()
{
	_skillTileMask.render();



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
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFF1111, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 20, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));

	swprintf_s(str, L"mapIdx : [%d,%d]", _curTile->_mapIdx.x, _curTile->_mapIdx.y);
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xF00000, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 40, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));

	swprintf_s(str, L"_vvMap->zlevel : [%d]", (*_vvMap)[_curTile->_mapIdx.y][_curTile->_mapIdx.x]->_zLevel);
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xF00000, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 60, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));
}

void Character::BuffRender()
{
	for (int i = 0; i < _vBuff.size(); i++) {
		_vBuff[i].img->aniRender(
			_pos.x -_vBuff[i].img->GetFrameWidth()/2,
			_pos.y - _vBuff[i].img->GetFrameHeight()/2 - TILESIZE_HEI,
			_vBuff[i].ani);
	}
}



void Character::InitObjectiveVal(image* img, POINTFLOAT pos, int zlvl, animation * ani, TILE * curTile)
{
	_img = img;
	_frameX = 0;
	_frameY = 0;

	_pos = pos;
	_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());
	_zLevel = zlvl;

	_ani = ani;
	_curTile = curTile;
	_tileForRender = _curTile;
	_frontTile = nullptr;
	_targetTile = nullptr;

}

void Character::InitCharacteristicVal(float maxHp, float curHp, float regenHp,
	float maxMp, float curMp, float regenMp,
	float moveSpd, float castSpd, float atk, float def,
	float mAtk, float mDef,
	CHAR_NAME charName, CHAR_DIR charDir, CHAR_STATE charState)
{
	_charValue[CUR][MAX_HP] = maxHp;
	_charValue[CUR][CUR_HP] = curHp;
	_charValue[CUR][REGEN_HP] = regenHp;
	_charValue[CUR][MAX_MP] = maxMp;
	_charValue[CUR][CUR_MP] = curMp;
	_charValue[CUR][REGEN_MP] = regenMp;
	_charValue[CUR][MOVE_SPD] = moveSpd;
	_charValue[CUR][CASTING_SPD] = castSpd;
	_charValue[CUR][ATK] = atk;
	_charValue[CUR][DEF] = def;
	_charValue[CUR][M_ATK] = mAtk;
	_charValue[CUR][M_DEF] = mDef;


	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };	//	업뎃필요,

	_name = charName;
	_dir = charDir;
	_state = charState;
	


}

void Character::InitCharacteristicAugVal(float augMaxHp, float augCurHp, float augRegenHp, float augMaxMp, float augCurMp, float augRegenMp, float augMoveSpd, float augCastSpd, float augAtk, float augDef, float augMAtk, float augMDef)
{
	_charValue[AUG][MAX_HP] = augMaxHp;
	_charValue[AUG][CUR_HP] = augCurHp;
	_charValue[AUG][REGEN_HP] = augRegenHp;
	_charValue[AUG][MAX_MP] = augMaxMp;
	_charValue[AUG][CUR_MP] = augCurMp;
	_charValue[AUG][REGEN_MP] = augRegenMp;
	_charValue[AUG][MOVE_SPD] = augMoveSpd;
	_charValue[AUG][CASTING_SPD] = augCastSpd;
	_charValue[AUG][ATK] = augAtk;
	_charValue[AUG][DEF] = augDef;
	_charValue[AUG][M_ATK] = augMAtk;
	_charValue[AUG][M_DEF] = augMDef;
}



void Character::InitCharacteristicAugVal()
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

void Character::MoveFunc()
{
	if (_lWayIdxList.size() != 0) {



		POINT targetIdx = { _lWayIdxList.begin()->x, _lWayIdxList.begin()->y };
		//	벡터 계산
		_moveVec.x = (targetIdx.x - mapIdx.x) * TILESIZE_WID / _charValue[CUR][MOVE_SPD];
		_moveVec.y = (targetIdx.y - mapIdx.y) * TILESIZE_HEI / _charValue[CUR][MOVE_SPD];

		//	오차허용계산
		if (abs((*_vvMap)[targetIdx.y][targetIdx.x]->_pos.x - _pos.x) < FLOAT_ERROR) {
			_moveVec.x = 0;
			_pos.x = (*_vvMap)[targetIdx.y][targetIdx.x]->_pos.x;
		}
		if (abs((*_vvMap)[targetIdx.y][targetIdx.x]->_pos.y - _pos.y) < FLOAT_ERROR) {
			_moveVec.y = 0;
			_pos.y = (*_vvMap)[targetIdx.y][targetIdx.x]->_pos.y;
		}
		//	도착했다면,
		if (_moveVec.x == 0 && _moveVec.y == 0) {
			_lWayIdxList.pop_front();
		}

		//	이동적용
		_pos.x += _moveVec.x;
		_pos.y += _moveVec.y;
		_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());

	}
}

void Character::MakeIdleByEndAni()
{
	if (!_ani->isPlay()) {
		this->setStatePattern(CHAR_STATE::IDLE);
		//_isStateChanged = true;
		//_state = CHAR_STATE::IDLE;
		
	}
}

void Character::CoolDownFunc()
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

void Character::SetModeFunc()
{
	if (KEYMANAGER->isOnceKeyDown('M')) {
		if (_mode == ORDER_KINDS::MOVE) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::MOVE;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('H')) {
		if (_mode == ORDER_KINDS::HOLD) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::HOLD;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('A')) {
		if (_mode == ORDER_KINDS::ATTACK) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::ATTACK;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('Q')) {
		if (_mode == ORDER_KINDS::SKILL1) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::SKILL1;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('W')) {
		if (_mode == ORDER_KINDS::SKILL2) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::SKILL2;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('E')) {
		if (_mode == ORDER_KINDS::SKILL3) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::SKILL3;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('R')) {
		if (_mode == ORDER_KINDS::SKILL4) {
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_mode = ORDER_KINDS::SKILL4;
		}
	}
}

void Character::MakeOrder()
{
	tagOrderInfo order;

	switch (_mode)
	{
	case ORDER_KINDS::MOVE:
		if (this->_coolDownTimer[0][ORDER_KINDS::MOVE] >= this->_coolDownTimer[1][ORDER_KINDS::MOVE]) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_isOnAtking = false;
				POINT ClickedIdx;
				ClickedIdx = ConvertPosToIdx(_ptMouse.x, _ptMouse.y, TILESIZE_WID, TILESIZE_HEI);
				//	맵 인덱스 안쪽이라면,
				if (0 <= ClickedIdx.x && ClickedIdx.x < (*_vvMap)[0].size() &&
					0 <= ClickedIdx.y && ClickedIdx.y < (*_vvMap).size()) {
					//	찍은곳이 갈 수 있는 곳이라면,
					if ((*_vvMap)[ClickedIdx.y][ClickedIdx.x]->_tileInfo.terAttr == T_ATTRIBUTE::T_ATTR_NONE) {
						ASTARFUNC->PathFind(mapIdx, PointMake(ClickedIdx.x, ClickedIdx.y), mapIdx, _lWayIdxList);
						if (_lWayIdxList.size() != 0) {
							_targetTile = ((*_vvMap)[ClickedIdx.y][ClickedIdx.x]);

							order.kinds = ORDER_KINDS::MOVE;
							order.targetMapIdx = _targetTile->_tileInfo.pickIdx;		//	인덱스
							//	넣기전, 기존 move/hold삭제
							for (_liOrderList = _lOrderList.begin(); _liOrderList != _lOrderList.end();) {
								if (_liOrderList->kinds == ORDER_KINDS::MOVE ||
									_liOrderList->kinds == ORDER_KINDS::HOLD ||
									_liOrderList->kinds == ORDER_KINDS::ATTACK ||
									_liOrderList->kinds == ORDER_KINDS::SKILL1 || 
									_liOrderList->kinds == ORDER_KINDS::SKILL2 ||
									_liOrderList->kinds == ORDER_KINDS::SKILL3 ||
									_liOrderList->kinds == ORDER_KINDS::SKILL4) {
									_liOrderList = _lOrderList.erase(_liOrderList);
								}
								else {
									_liOrderList++;
								}
							}

							//	오더추가! + cooldown = 0
							_lOrderList.push_back(order);
							_coolDownTimer[0][ORDER_KINDS::MOVE] = 0;
							//	Move의 특별행동 방지
							_isOnAtking = false;
						}

					}
				}

			}
		}
		break;
		//	case::move end;
	case ORDER_KINDS::HOLD:
	{
		_isOnAtking = false;
		//	한번만 들어오게끔
		//		1.-> 현재 실행하고있는게 홀드면 실행 ㄴㄴ,
		if (this->_lOrderList.size() != 0) {
			if (this->_lOrderList.begin()->kinds == ORDER_KINDS::HOLD) {
				break;
			}
		}
		//		2.-> 이미 홀드가 있다면 실행 ㄴㄴ,
		for (this->_liOrderList = this->_lOrderList.begin();
			this->_liOrderList != this->_lOrderList.end();
			_liOrderList++) {
			if (_liOrderList->kinds == ORDER_KINDS::HOLD)
				break;
		}

		//	위 조건에서 break안되면, 오더추가!
		if (this->_coolDownTimer[0][ORDER_KINDS::HOLD] >= this->_coolDownTimer[1][ORDER_KINDS::HOLD]) {
			order.kinds = ORDER_KINDS::HOLD;
			order.targetMapIdx = _curTile->_mapIdx;
			//	넣기전, 기존 hold | atk 삭제 + 가장 마지막Move의 targetIdx찾음
			for (_liOrderList = _lOrderList.begin(); _liOrderList != _lOrderList.end();) {
				if (_liOrderList->kinds == ORDER_KINDS::HOLD) {
					_liOrderList = _lOrderList.erase(_liOrderList);
				}
				else if (_liOrderList->kinds == ORDER_KINDS::ATTACK) {
					_liOrderList = _lOrderList.erase(_liOrderList);
				}
				else if (_liOrderList->kinds == ORDER_KINDS::MOVE) {
					order.targetMapIdx = _liOrderList->targetMapIdx;
					_liOrderList++;
				}
				else {
					_liOrderList++;
				}
			}

			//	오더추가! + cooldown = 0 + _mode = none;
			_lOrderList.push_back(order);
			//	쿨 타이머는, 실행됐을때 돌리자.
			//_coolDownTimer[0][ORDER_KINDS::HOLD] = 0;
			//_mode = ORDER_KINDS::NONE;

		}
		break;
	}
	case ORDER_KINDS::ATTACK:
		if (this->_coolDownTimer[0][ORDER_KINDS::ATTACK] >= this->_coolDownTimer[1][ORDER_KINDS::ATTACK]) {
			order.kinds = ORDER_KINDS::ATTACK;
			bool isClickedEnemy = false;
			isClickedEnemy = MakeClickedEnemyIdx();
			//	클릭해서 적의 인덱스를 가져왔다면,
			if (isClickedEnemy) {
				
				_aStarCount = 0;
				ASTARFUNC->PathFind(mapIdx, (*_vEnemy)[_targetEnemyIdx]->_mapIdx, mapIdx, _lWayIdxList);

				//	길을 찾았다면,
				if (_lWayIdxList.size() != 0 && _lWayIdxList.begin()->x != -1) {
					//	적이 서있는 타일인덱스는 뺴버리고,
					_lWayIdxList.pop_back();
					
					//order.kinds = ORDER_KINDS::ATTACK;
					//order.targetMapIdx = _targetTile->_tileInfo.pickIdx;		//	인덱스

					//	넣기전, 기존 hold, move삭제
					for (_liOrderList = _lOrderList.begin(); _liOrderList != _lOrderList.end();) {
						if (_liOrderList->kinds == ORDER_KINDS::HOLD ||
							_liOrderList->kinds == ORDER_KINDS::MOVE) {
							_liOrderList = _lOrderList.erase(_liOrderList);
						}
						else {
							_liOrderList++;
						}
					}
					//	타겟팅된 적의 인덱스
					POINT targetMapIdx = (*_vEnemy)[_targetEnemyIdx]->_mapIdx;
					_targetTile = ((*_vvMap)[targetMapIdx.y][targetMapIdx.x]);


					if (_lWayIdxList.size() != 0) {
						//	Move오더 추가
						order.kinds = ORDER_KINDS::MOVE;
						order.targetMapIdx = _lWayIdxList.back();		//	인덱스
						_lOrderList.push_back(order);
						//	Move의 특별행동
						_isOnAtking = true;
					}
					

					//	ATK오더 추가
					order.kinds = ORDER_KINDS::ATTACK;
					order.targetMapIdx = targetMapIdx;		//	인덱스
					_lOrderList.push_back(order);

					//	Atk쿨다운 0
					_coolDownTimer[0][ORDER_KINDS::MOVE] = 0;

					//	현재 선택한 모드 꺼주고,
					_mode = ORDER_KINDS::NONE;

					//	쿨다운은 실행될떄!
					//_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;
				}
			}

		}
		break;
	case ORDER_KINDS::SKILL1:
		MakeOrderOfSkill(_mode);
		
		//	이건 옛날꺼...구려
		/*
		if (this->_coolDownTimer[0][ORDER_KINDS::SKILL1] >= this->_coolDownTimer[1][ORDER_KINDS::SKILL1]) {
			order.kinds = ORDER_KINDS::SKILL1;
			bool isClickedEnemy = false;
			isClickedEnemy = MakeClickedEnemyIdx();
			//	클릭해서 적의 인덱스를 가져왔다면,
			if (isClickedEnemy) {

				_aStarCount = 0;
				ASTARFUNC->PathFind(mapIdx, (*_vEnemy)[_targetEnemyIdx]->_mapIdx, mapIdx, _lWayIdxList);

				//	길을 찾았다면,
				if (_lWayIdxList.size() != 0 && _lWayIdxList.begin()->x != -1) {
					//	적이 서있는 타일인덱스는 뺴버리고,
					_lWayIdxList.pop_back();
					POINT targetMapIdx = (*_vEnemy)[_targetEnemyIdx]->_mapIdx;
					_targetTile = ((*_vvMap)[targetMapIdx.y][targetMapIdx.x]);
					order.kinds = ORDER_KINDS::SKILL1;
					order.targetMapIdx = _targetTile->_tileInfo.pickIdx;		//	인덱스

					//	넣기전, 기존 hold삭제
					for (_liOrderList = _lOrderList.begin(); _liOrderList != _lOrderList.end();) {
						if (_liOrderList->kinds == ORDER_KINDS::HOLD ||
							_liOrderList->kinds == ORDER_KINDS::ATTACK) {
							_liOrderList = _lOrderList.erase(_liOrderList);
						}
						else {
							_liOrderList++;
						}
					}

					//	오더추가! + cooldown = 0
					_lOrderList.push_back(order);
					//	현재 선택한 모드 꺼주고,
					_mode = ORDER_KINDS::NONE;

					//	쿨다운은 실행될떄!
					//_coolDownTimer[0][ORDER_KINDS::ATTACK] = 0;
				}
			}

		}
		*/
		break;
	case ORDER_KINDS::SKILL2:
		MakeOrderOfSkill(_mode);
		
		break;
	case ORDER_KINDS::SKILL3:
		MakeOrderOfSkill(_mode);
		
		break;
	case ORDER_KINDS::SKILL4:
		MakeOrderOfSkill(_mode);

		break;

	default:
		break;
	}
}

//	홀드 스테이트에서 쓰임
void Character::HoldRegenFunc()
{
	if (_charValue[0][CHAR_VALUE_KINDS::CUR_HP] + _charValue[0][CHAR_VALUE_KINDS::REGEN_HP] < _charValue[0][CHAR_VALUE_KINDS::MAX_HP] + _charValue[1][CHAR_VALUE_KINDS::MAX_HP]) {
		_charValue[0][CHAR_VALUE_KINDS::CUR_HP] += _charValue[0][CHAR_VALUE_KINDS::REGEN_HP];
	}
	if (_charValue[0][CHAR_VALUE_KINDS::CUR_MP] + _charValue[0][CHAR_VALUE_KINDS::REGEN_MP] < _charValue[0][CHAR_VALUE_KINDS::MAX_MP] + _charValue[1][CHAR_VALUE_KINDS::MAX_MP]) {
		_charValue[0][CHAR_VALUE_KINDS::CUR_MP] += _charValue[0][CHAR_VALUE_KINDS::REGEN_MP];
	}
	if (_charValue[0][CHAR_VALUE_KINDS::CUR_SP] + _charValue[0][CHAR_VALUE_KINDS::REGEN_SP] < _charValue[0][CHAR_VALUE_KINDS::MAX_SP] + _charValue[1][CHAR_VALUE_KINDS::MAX_SP]) {
		_charValue[0][CHAR_VALUE_KINDS::CUR_SP] += _charValue[0][CHAR_VALUE_KINDS::REGEN_SP];
	}
}

bool Character::MakeClickedEnemyIdx()
{
	
	for (int i = 0; i < _vEnemy->size(); i++) {
		if (PtInRect(&(*_vEnemy)[i]->_targetedRc, PointMake(_ptMouse.x, _ptMouse.y))) {
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_targetEnemyIdx = i;
					return true;
				}
			}
		}
	}
	return false;
	
}

void Character::MakeOrderOfSkill(ORDER_KINDS skillOrder)
{
	tagOrderInfo order;

	if (this->_coolDownTimer[0][skillOrder] >= this->_coolDownTimer[1][skillOrder]) {
		//	이하 Move와 동일 -> except 마지막타일은 waylist에서 제거. 마지막타일은 타겟타일
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			POINT ClickedIdx;
			ClickedIdx = ConvertPosToIdx(_ptMouse.x, _ptMouse.y, TILESIZE_WID, TILESIZE_HEI);
			//	맵 인덱스 안쪽이라면,
			if (0 <= ClickedIdx.x && ClickedIdx.x < (*_vvMap)[0].size() &&
				0 <= ClickedIdx.y && ClickedIdx.y < (*_vvMap).size()) {
				//	찍은곳이 갈 수 있는 곳이라면,
				if ((*_vvMap)[ClickedIdx.y][ClickedIdx.x]->_tileInfo.terAttr == T_ATTRIBUTE::T_ATTR_NONE) {
					ASTARFUNC->PathFind(mapIdx, PointMake(ClickedIdx.x, ClickedIdx.y), mapIdx, _lWayIdxList);
					if (_lWayIdxList.size() != 0) {
						_targetTile = ((*_vvMap)[ClickedIdx.y][ClickedIdx.x]);		//	타겟타일(쓰기 애매...오더에 목표지점 넣어줌)
						
						//	사거리만큼 목적지부터 빼기 (근접은 1)
						int skillRange = SKILLMANAGER->FindSkill(this->_skillName[skillOrder - 3])->getRange();
						for (int i = 0; i < skillRange; i++) {
							if (_lWayIdxList.size() == 0) { break; }
							_lWayIdxList.pop_back();
						}
						
						

						order.kinds = ORDER_KINDS::MOVE;
						if (_lWayIdxList.size() != 0) {
							order.targetMapIdx = _lWayIdxList.back();		//	인덱스
						}
						else {
							order.targetMapIdx = _curTile->_mapIdx;
						}

						//	넣기전, 기존 atk/hold삭제
						for (_liOrderList = _lOrderList.begin(); _liOrderList != _lOrderList.end();) {
							if (_liOrderList->kinds == ORDER_KINDS::HOLD ||
								_liOrderList->kinds == ORDER_KINDS::ATTACK) {
								_liOrderList = _lOrderList.erase(_liOrderList);
							}
							else {
								_liOrderList++;
							}
						}

						//	Move오더추가! + cooldown = 0
						_lOrderList.push_back(order);
						//_coolDownTimer[0][ORDER_KINDS::MOVE] = 0;

						//	skill오더 추가! + cooldown =0
						order.kinds = skillOrder;
						order.targetMapIdx = ClickedIdx;
						_lOrderList.push_back(order);
						_coolDownTimer[0][skillOrder] = 0;
					}

				}
			}
		}
	}
}

void Character::BuffFunc()
{
	for (int i = 0; i < _vBuff.size();) {
		// 시간다됐으면 -> 지워라
		if (_vBuff[i].curCount >= _vBuff[i].maxCount) {
			_vBuff[i].ani->stop();

			if (_vBuff[i].name == "buff1") {
				_charValue[1][CHAR_VALUE_KINDS::ATK] = 0;
				_charValue[1][CHAR_VALUE_KINDS::M_ATK] = 0;
				_charValue[1][CHAR_VALUE_KINDS::DEF] = 0;
				_charValue[1][CHAR_VALUE_KINDS::M_DEF] = 0;
			}


			_vBuff.erase(_vBuff.begin() + i);
		}
		//	아니면 적용 및 갱신
		else {
			
			// 버프들어오고 여기 소스에 온게 처음이면,
			if (_vBuff[i].curCount == 0) {
				if (_vBuff[i].name == "buff1") {
					_charValue[1][CHAR_VALUE_KINDS::ATK] = _charValue[0][CHAR_VALUE_KINDS::ATK];
					_charValue[1][CHAR_VALUE_KINDS::M_ATK] = _charValue[0][CHAR_VALUE_KINDS::M_ATK];
					_charValue[1][CHAR_VALUE_KINDS::DEF] = _charValue[0][CHAR_VALUE_KINDS::DEF];
					_charValue[1][CHAR_VALUE_KINDS::M_DEF] = _charValue[0][CHAR_VALUE_KINDS::M_DEF];
				}
			}
			_vBuff[i].curCount++;
			i++;
			
		}



		
		
	}
	
}
