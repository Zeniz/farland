#pragma once
#include "UIObjects.h"
#include "CharMgr.h"
#include "character.h"


//	_lorderlist.begin이 skill or move 일 때, order.mapidx에 마스크 오버랩할것.
//	렌더순서는, 타일 깔고 그위에 해야함. ui들처럼 마지막에 해버리면 안됨. -> render따로 만들어서 따로할것.
class SkillRangeMaskUI :public UIObjects
{
private:
	image* _maskImg;
	
	
public:
	SkillRangeMaskUI();
	~SkillRangeMaskUI();

	HRESULT init()	override;
	void release()	override;
	void update()	override;
	void render()	override;
};

