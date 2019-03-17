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

void enemy::setHpBar(POINT augPos)
{
	_hpBar = new enemyHpBar;
	_hpBar->init(&_statValue[E_STATS::E_CURHP], &_statValue[E_STATS::E_MAXHP], &_pos, augPos);
}


