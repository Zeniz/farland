#include "stdafx.h"
#include "skeleton.h"


skeleton::skeleton()
{
}


skeleton::~skeleton()
{
}

HRESULT skeleton::init()
{
	return E_NOTIMPL;
}

void skeleton::release()
{
}

void skeleton::update()
{
}

void skeleton::render()
{
}

void skeleton::setNewSkel(E_IMGNUM imgNum, animation * ani, POINTFLOAT pos, RECT rc, int zLvl, float curHp, float maxHp, float curMp, float maxMp, POINT mapIdx, float attrValue)
{
	_imgNum = imgNum;
	_img = IMAGEMANAGER->findImage(_enemyImgKey[imgNum].c_str());
	
	_ani[0][0] = ani;
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

void skeleton::setNewSkelforMapEditor(E_IMGNUM imgNum, POINT mapIdx)
{
	_imgNum = imgNum;
	_img = IMAGEMANAGER->findImage(_enemyImgKey[imgNum].c_str());
	_mapIdx = mapIdx;
	_pos = ConvertIdxToPosFloat(_mapIdx.x, _mapIdx.y, TILESIZE_WID, TILESIZE_HEI);		
	_rc = RectMake(_pos.x - TILESIZE_WID / 2, _pos.y + TILESIZE_HEI / 2 - _img->GetFrameHeight(),
		_img->GetFrameWidth(), _img->GetFrameHeight());

	_ani[0][0] = nullptr;
	_zLevel = NULL;
	_curHp = NULL;
	_maxHp = NULL;
	_curMp = NULL;
	_maxMp = NULL;
	_attrValue[0] = NULL;

	_frameX = 0;
	_frameY = 0;
}
