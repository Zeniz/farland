#include "stdafx.h"
#include "enemy.h"
#include "character.h"

bool compareEnemy(enemy* e1, enemy* e2) {
	if (e1->_mapIdx.y != e2->_mapIdx.y) {
		return (e1->_mapIdx.y < e2->_mapIdx.y);
	}
	else {
		return (e1->_mapIdx.x < e2->_mapIdx.x);
	}

};

enemy::enemy()
{
	_moveTileCount = 0;
	_isStateChanged = true;
	_isAtkFin = false;
	_atkCount = 0;
	_deleteDelayCount = 0;
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	
}

void enemy::render()
{
	_skillMaskTile.render();

	if (_dir == E_DIR::DIR_LT || _dir == E_DIR::DIR_RB) {
		_img->aniRenderReverseX(_rc.left, _rc.top - _zLevel*(TILESIZE_HEI / 2), this->_ani);
	}
	else {
		_img->aniRender(_rc.left, _rc.top - _zLevel*(TILESIZE_HEI / 2), this->_ani);
	}

	_hpBar->render();

	D2D_RECT_F rc = { _pos.x - 5, _pos.y - 5, _pos.x + 5, _pos.y + 5 };
	D2DMANAGER->fillRectangle(0xFFFFFF, rc);


	WCHAR str[128];

	//swprintf_s(str, L"state : %d", (int)_state);

	
	switch (_state)
	{
	case E_STATUS_NONE:
		swprintf_s(str, L"state : NONE");
		break;
	case E_IDLE:
		swprintf_s(str, L"state : IDLE");
		break;
	case E_DEAD:
		swprintf_s(str, L"state : DEAD");
		break;
	case E_GETDMG:
		swprintf_s(str, L"state : GETDMG");
		break;
	case E_STONED:
		swprintf_s(str, L"state : STONED");
		break;
	case E_FROZEN:
		break;
	case E_GETCRIDMG:
		break;
	case E_STUNNED:
		break;
	case E_BLOCK:
		break;
	case E_MOVE:
		swprintf_s(str, L"state : MOVE");
		break;
	case E_ATK1:
		break;
	case E_ATK2:
		break;
	case E_ATK3:
		break;
	case E_SKILL1_CAST:
		swprintf_s(str, L"state : CAST");
		break;
	case E_SKILL1_SHOT:
		swprintf_s(str, L"state : SHOT");
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
		swprintf_s(str, L"state : ERROR");
		break;
	}
	
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFF1111, 1.0f), L"consolas", 20, str, _rc.left, _rc.top - 20, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));



	//	테스트 출력
	//WCHAR wstr[128];
	//swprintf_s(wstr, L"pTile->Zlvl : %d", _pCurTile->_zLevel);
	//D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFF0000, 1.0f), L"consolas", 15, wstr, _rc.left, _rc.top - 20, true, D2DMANAGER->createBrush(0x000000, 1.0f));
}


void enemy::patternUpdate()
{
	switch (_state)
	{
	case E_STATE::E_STATUS_NONE:
		break;
	case E_STATE::E_IDLE:
		_pattern.Idle(this);
		break;
	case E_STATE::E_DEAD:
		_pattern.Dead(this);
		break;
	case E_STATE::E_GETDMG:
		_pattern.GetDmg(this);
		break;
	case E_STATE::E_STONED:
		_pattern.Stoned(this);
		break;
	case E_STATE::E_FROZEN:
		_pattern.Frozen(this);
		break;
	case E_STATE::E_GETCRIDMG:
		_pattern.GetCriDmg(this);
		break;
	case E_STATE::E_STUNNED:
		_pattern.Stunned(this);
		break;
	case E_STATE::E_BLOCK:
		_pattern.Deffence(this);
		break;
	case E_STATE::E_MOVE:
		_pattern.Move(this);
		break;
	case E_STATE::E_ATK1:
		_pattern.Atk1(this);
		break;
	case E_STATE::E_ATK2:
		_pattern.Atk2(this);
		break;
	case E_STATE::E_ATK3:
		_pattern.Atk3(this);
		break;
	case E_STATE::E_SKILL1_CAST:
		_pattern.Skill1Cast(this);
		break;
	case E_STATE::E_SKILL1_SHOT:
		_pattern.Skill1Shot(this);
		break;
	case E_STATE::E_SKILL2_CAST:
		_pattern.Skill2Cast(this);
		break;
	case E_STATE::E_SKILL2_SHOT:
		_pattern.Skill2Shot(this);
		break;
	case E_STATE::E_SKILL3_CAST:
		_pattern.Skill3Cast(this);
		break;
	case E_STATE::E_SKILL3_SHOT:
		_pattern.Skill3Shot(this);
		break;
	case E_STATE::E_SKILL4_CAST:
		_pattern.Skill4Cast(this);
		break;
	case E_STATE::E_SKILL4_SHOT:
		_pattern.Skill4Shot(this);
		break;
	case E_STATE::E_STATUS_END:
		break;
	default:
		break;
	}
}

void enemy::MakeIdleByEndAni()
{
	if (!_ani->isPlay()) {
		_isStateChanged = true;
		_state = E_STATE::E_IDLE;
	}
}

void enemy::ChkDead()
{
	if (_statValue[E_STATS::E_CURHP] <= 0) {
		_state = E_STATE::E_DEAD;
	}
}

void enemy::NoticeFunc(int noticeRange)
{
	int minDifferIdxSize = 99999;
	for (int i = 0; i < _vChara->size(); i++) {
		int distance = abs((*_vChara)[i]->mapIdx.x - _mapIdx.x) + abs((*_vChara)[i]->mapIdx.y - _mapIdx.y);
		if (minDifferIdxSize > distance) {
			minDifferIdxSize = distance;
		}	
	}
	if (minDifferIdxSize <= noticeRange) {
		_isNotice = true;
	}
}

void enemy::setHpBar(POINT augPos)
{
	_hpBar = new enemyHpBar;
	_hpBar->init(&_statValue[E_STATS::E_CURHP], &_statValue[E_STATS::E_MAXHP], &_zLevel, &_pos, augPos);
}


