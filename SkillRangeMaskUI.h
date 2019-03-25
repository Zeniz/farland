#pragma once
#include "gameNode.h"

struct tagMaskInfo {
	int imgNum;
	POINT mapIdx;
	int skillNum;
};


//	_lorderlist.begin이 skill or move 일 때, order.mapidx에 마스크 오버랩할것.
//	렌더순서는, 타일 깔고 그위에 해야함. ui들처럼 마지막에 해버리면 안됨. -> render따로 만들어서 따로할것.
class SkillRangeMaskUI : public gameNode
{
private:
	image* _maskImg;
	vector<tagMaskInfo> _vMaskInfo;
	
public:
	SkillRangeMaskUI();
	~SkillRangeMaskUI();

	HRESULT init();
	void release();
	void render();

	void addTargetTile(int imgNum, POINT mapIdx, int skillNum);
	int getSkillNum(int idx) { return _vMaskInfo[idx].imgNum; }
	int getVMaskInfoSize() { return _vMaskInfo.size(); }
	void ClearVMaskInfo();
};

