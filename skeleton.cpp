#include "stdafx.h"
#include "skeleton.h"


skeleton::skeleton()
{
	IMAGEMANAGER->addFrameImage("mobSkel", L"images/mob/mob_Skel.png", 2048, 1536, 8, 8);
	KEYANIMANAGER->addAnimationType("skel");

	int idleFront[] = { 0,1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "idleFront", "mobSkel",
		idleFront, 3, 4, true);
	int idleBack[] = { 8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "idleBack", "mobSkel",
		idleBack, 3, 4, true);

	int moveFront[] = { 16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "moveFront", "mobSkel",
		moveFront, 4, 4, true);
	int moveBack[] = { 24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "moveBack", "mobSkel",
		moveBack, 4, 4, true);

	int atkFront[] = { 32,33,34 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "atkFront", "mobSkel",
		atkFront, 3, 4, false);
	int atkBack[] = { 40,41,42 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "atkBack", "mobSkel",
		atkBack, 3, 4, false);

	// =======================



	int stateIdleFront[] = { 48 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateIdleFront", "mobSkel",
		stateIdleFront, 1, 5, false);

	int stateDeadFront[] = { 49 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateDeadFront", "mobSkel",
		stateDeadFront, 1, 1, true);

	int stateGethitFront[] = { 50 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateGetHitFront", "mobSkel",
		stateGethitFront, 1, 2, false);

	int stateStoneFront[] = { 51 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateStoneFront", "mobSkel",
		stateStoneFront, 1, 5, true);

	int stateFrozenFront[] = { 52 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateFrozenFront", "mobSkel",
		stateFrozenFront, 1, 5, true);

	int stateGetHit2Front[] = { 53 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateGetHit2Front", "mobSkel",
		stateGetHit2Front, 1, 60, false);

	int stateExhaustedFront[] = { 54 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateExhaustedFront", "mobSkel",
		stateExhaustedFront, 1, 5, true);

	int stateBlockFront[] = { 55 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateBlockFront", "mobSkel",
		stateBlockFront, 1, 1, true);


	int stateIdleBack[] = { 56 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateIdleBack", "mobSkel",
		stateIdleBack, 1, 5, false);

	int stateDeadBack[] = { 57 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateDeadBack", "mobSkel",
		stateDeadBack, 1, 5, true);

	int stateGetHitBack[] = { 58 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateGetHitBack", "mobSkel",
		stateGetHitBack, 1, 2, false);

	int stateStoneBack[] = { 59 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateStoneBack", "mobSkel",
		stateStoneBack, 1, 5, true);

	int stateFrozenBack[] = { 60 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateFrozenBack", "mobSkel",
		stateFrozenBack, 1, 5, true);

	int stateGetHit2Back[] = { 61 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateGetHit2Back", "mobSkel",
		stateGetHit2Back, 1, 60, false);

	int stateExhaustedBack[] = { 62 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateExhaustedBack", "mobSkel",
		stateExhaustedFront, 1, 5, true);

	int stateBlockBack[] = { 63 };
	KEYANIMANAGER->addArrayFrameAnimation("skel", "stateBlockBack", "mobSkel",
		stateBlockFront, 1, 1, true);



}


skeleton::~skeleton()
{
}

HRESULT skeleton::init()
{
	_img = IMAGEMANAGER->findImage("mobSkel");
	_ani = KEYANIMANAGER->findAnimation("skel", "idleFront");
	_imgNum = E_IMGNUM::MOB_SKEL;

	_mapIdx = { NULL,NULL };
	_pCurTile = nullptr;
	for (int i = 0; i < E_ATTR::ATTR_END; i++) {
		_attrValue[i] = 0;
	}

	

	return S_OK;
}

void skeleton::InitObjectiveValDefault(POINT mapIdx)
{
	_img = IMAGEMANAGER->findImage("mobSkel");
	_frameX = _frameY = NULL;

	_pos = ConvertIdxToPosFloat(mapIdx.x, mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	_rc = RectMake(_pos.x - 128, _pos.y - 156,
		_img->GetFrameWidth(), _img->GetFrameHeight());
	_targetedRc = RectMake(_pos.x - WID_FROM_CENTERPOS, _pos.y - LEN_TO_TOP_FROM_CENTERPOS,
		WID_FROM_CENTERPOS * 2, LEN_TO_TOP_FROM_CENTERPOS + LEN_TO_BOTTOM_FROM_CENTERPOS);
	_zLevel = 0;

	_ani = KEYANIMANAGER->findAnimation("skel", "idleFront");
	_pCurTile = (*_vvMap)[mapIdx.y][mapIdx.x];

	_mapIdx = mapIdx;

}

void skeleton::InitCharacteristicValDefault()
{
	_statValue[E_STATS::E_CURHP] = this->BASIC_MAX_HP;
	_statValue[E_STATS::E_MAXHP] = this->BASIC_MAX_HP;
	_statValue[E_STATS::E_CURMP] = this->BASIC_MAX_MP;
	_statValue[E_STATS::E_MAXMP] = this->BASIC_MAX_MP;

	_statValue[E_STATS::E_MOVESPD] = this->BASIC_MOVESPD;
	_statValue[E_STATS::E_CASTSPD] = this->BASIC_CASTSPD;

	_statValue[E_STATS::E_ATK] = this->BASIC_ATK;
	_statValue[E_STATS::E_DEF] = this->BASIC_DEF;
	_statValue[E_STATS::E_MATK] = this->BASIC_MATK;
	_statValue[E_STATS::E_MDEF] = this->BASIC_MDEF;
	
	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };

	_imgNum = E_IMGNUM::MOB_SKEL;
	_dir = E_DIR::DIR_LB;
	_state = E_STATE::E_IDLE;


}

void skeleton::release()
{
}

void skeleton::update()
{
	//_mapIdx = ConvertPosToIdx(_pos.x, _pos.y, TILESIZE_WID, TILESIZE_HEI);
	_pCurTile = (*_vvMap)[_mapIdx.y][_mapIdx.x];

	setAni();
	MakeIdleByEndAni();
	patternUpdate();

	




}

void skeleton::render()
{
	//D2D_RECT_F playerRc = { _rc.left, _rc.top, _rc.right, _rc.bottom };
	//D2DMANAGER->fillRectangle(0xFFFFFF, playerRc);

	//	테스트용 출력 -- //뻑남 주의
	//WCHAR str[128];
	//TILE* nextTile = (*_vvMap)[_lWayIdxList.begin()->y][_lWayIdxList.begin()->x];
	//swprintf_s(str, L"nextTilePos[%.f/%.f]", nextTile->_pos.x, nextTile->_pos.y);
	//D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFF0000, 1.0f), L"consolas", 15,
	//	str, _rc.left, _rc.top - 20, true, D2DMANAGER->createBrush(0xFFFFFF,1.0f));
	//swprintf_s(str, L"_pos[%.f/%.f]", _pos.x, _pos.y);
	//D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFF0000, 1.0f), L"consolas", 15,
	//	str, _rc.left, _rc.top - 40, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));

	// =========================
	if (_dir == E_DIR::DIR_LT || _dir == E_DIR::DIR_RB) {
		_img->aniRenderReverseX(_rc.left, _rc.top - _pCurTile->_zLevel*(TILESIZE_HEI / 2), this->_ani);
	}
	else {
		_img->aniRender(_rc.left, _rc.top - _pCurTile->_zLevel*(TILESIZE_HEI / 2), this->_ani);
	}

	D2D_RECT_F rc = { _pos.x - 5, _pos.y - 5, _pos.x + 5, _pos.y + 5 };
	D2DMANAGER->fillRectangle(0xFFFFFF, rc);



}
void skeleton::setAni()
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
				_ani = KEYANIMANAGER->findAnimation("skel", "idleFront");
				break;
			case E_DEAD:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateDeadFront");
				break;
			case E_GETDMG:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateGetHitFront");
				break;
			case E_STONED:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateStoneFront");
				break;
			case E_FROZEN:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateFrozenFront");
				break;
			case E_GETCRIDMG:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateGetHit2Front");
				break;
			case E_STUNNED:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateExhaustedFront");
				break;
			case E_BLOCK:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateBlockFront");
				break;
			case E_MOVE:
				_ani = KEYANIMANAGER->findAnimation("skel", "moveFront");
				break;
			case E_ATK1:
				_ani = KEYANIMANAGER->findAnimation("skel", "atkFront");
				break;
			case E_ATK2:
				
				break;
			case E_ATK3:
				
				break;
			case E_SKILL1_CAST:
				
				break;
			case E_SKILL1_SHOT:
				
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
				_ani = KEYANIMANAGER->findAnimation("skel", "idleBack");
				break;
			case E_DEAD:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateDeadBack");
				break;
			case E_GETDMG:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateGetHitBack");
				break;
			case E_STONED:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateStoneBack");
				break;
			case E_FROZEN:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateFrozenBack");
				break;
			case E_GETCRIDMG:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateGetHit2Back");
				break;
			case E_STUNNED:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateExhaustedBack");
				break;
			case E_BLOCK:
				_ani = KEYANIMANAGER->findAnimation("skel", "stateBlockBack");
				break;
			case E_MOVE:
				_ani = KEYANIMANAGER->findAnimation("skel", "moveBack");
				break;
			case E_ATK1:
				_ani = KEYANIMANAGER->findAnimation("skel", "atkBack");
				break;
			case E_ATK2:

				break;
			case E_ATK3:

				break;
			case E_SKILL1_CAST:

				break;
			case E_SKILL1_SHOT:

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
void skeleton::setNewSkel(E_IMGNUM imgNum, animation * ani, POINTFLOAT pos, RECT rc, int zLvl, float curHp, float maxHp, float curMp, float maxMp, POINT mapIdx, float attrValue)
{
	_imgNum = imgNum;
	_img = IMAGEMANAGER->findImage(_enemyImgKey[imgNum].c_str());
	
	_ani = ani;
	_pos = pos;
	_rc = rc;
	_zLevel = zLvl;
	_curHp = curHp;
	_maxHp = maxHp;
	_curMp = curMp;
	_maxMp = maxMp;
	_mapIdx = mapIdx;
	_attrValue[0] = attrValue;

	_frameX = NULL;
	_frameY = NULL;
}
*/
void skeleton::setNewSkelforMapEditor(E_IMGNUM imgNum, POINT mapIdx)
{
	_imgNum = imgNum;
	_img = IMAGEMANAGER->findImage(_enemyImgKey[imgNum].c_str());
	_mapIdx = mapIdx;
	_pos = ConvertIdxToPosFloat(_mapIdx.x, _mapIdx.y, TILESIZE_WID, TILESIZE_HEI);		
	_rc = RectMake(_pos.x - TILESIZE_WID / 2, _pos.y + TILESIZE_HEI / 2 - _img->GetFrameHeight(),
		_img->GetFrameWidth(), _img->GetFrameHeight());

	_ani = nullptr;
	_zLevel = NULL;
	
	
	
	
	_attrValue[0] = NULL;

	_frameX = 0;
	_frameY = 0;
}
