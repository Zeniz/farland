#include "stdafx.h"
#include "SkillRangeMaskUI.h"


SkillRangeMaskUI::SkillRangeMaskUI()
{
}


SkillRangeMaskUI::~SkillRangeMaskUI()
{
}

HRESULT SkillRangeMaskUI::init()
{
	IMAGEMANAGER->addFrameImage("onTileMask", L"images/UI/skillRangeMask/onSkillTileMask.png", 512, 64, 4, 1);
	_maskImg = IMAGEMANAGER->findImage("onTileMask");


	return S_OK;
}

void SkillRangeMaskUI::release()
{
}

void SkillRangeMaskUI::render()
{
	
	for (int i = 0; i < _vMaskInfo.size(); i++) {
		POINT pos = ConvertIdxToPos(_vMaskInfo[i].mapIdx.x, _vMaskInfo[i].mapIdx.y, TILESIZE_WID, TILESIZE_HEI);
		_maskImg->frameRender(
			pos.x - TILESIZE_WID/2,
			pos.y - TILESIZE_HEI/2,
			_vMaskInfo[i].imgNum,
			0,
			0.5f);
	}
}

void SkillRangeMaskUI::addTargetTile(int imgNum, POINT mapIdx, int skillNum)
{
	tagMaskInfo tmpMaskInfo;
	tmpMaskInfo.imgNum = imgNum;
	tmpMaskInfo.mapIdx = mapIdx;
	tmpMaskInfo.skillNum = skillNum;
	_vMaskInfo.push_back(tmpMaskInfo);
}

void SkillRangeMaskUI::ClearVMaskInfo()
{
	_vMaskInfo.clear();
}

