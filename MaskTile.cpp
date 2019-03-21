#include "stdafx.h"
#include "MaskTile.h"


MaskTile::MaskTile()
{
	
}


MaskTile::~MaskTile()
{
}

HRESULT MaskTile::init()
{
	IMAGEMANAGER->addImage("maskTile", L"images/UI/maskTile/maskTile.png", 128, 64);
	_maskImg = IMAGEMANAGER->findImage("maskTile");
	_mapIdx = { NULL, NULL };
	_pos = { NULL, NULL };
	_rc = { NULL,NULL, NULL, NULL };
	_alpha = 0.f;
	_isAlphaRise = true;


	return S_OK;
}

HRESULT MaskTile::init(vvMap* vvMapAddr)
{
	IMAGEMANAGER->addImage("maskTile", L"images/UI/maskTile/maskTile.png", 128, 64);
	_maskImg = IMAGEMANAGER->findImage("maskTile");
	_mapIdx = { NULL, NULL };
	_pos = { NULL, NULL };
	_rc = { NULL,NULL, NULL, NULL };
	_alpha = 0.f;
	_isAlphaRise = true;

	_vvMap = vvMapAddr;


	return S_OK;
}

void MaskTile::release()
{
}

void MaskTile::update()
{
	_mapIdx = ConvertPosToIdx(_ptMouse.x, _ptMouse.y, TILESIZE_WID, TILESIZE_HEI);
	_pos = ConvertIdxToPos(_mapIdx.x, _mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
	_rc = RectMakeCenter(_pos.x, _pos.y, TILESIZE_WID, TILESIZE_HEI);

	if (_isAlphaRise) {
		_alpha += ALPHA_AUG_SPD;
		if (_alpha >= 1.0f) {
			_alpha = 1.0f;
			_isAlphaRise = false;
		}
	}
	else {
		_alpha -= ALPHA_AUG_SPD;
		if (_alpha <= 0.f) {
			_alpha = 0.f;
			_isAlphaRise = true;
		}
	}


}

void MaskTile::render()
{
	if (0 > _mapIdx.x || _mapIdx.x >= (*_vvMap)[0].size())	return;
	if (0 > _mapIdx.y || _mapIdx.y >= (*_vvMap).size())		return;
	_maskImg->render(_rc.left, _rc.top - (*_vvMap)[_mapIdx.y][_mapIdx.x]->_zLevel * (TILESIZE_HEI/2), _alpha);
}


