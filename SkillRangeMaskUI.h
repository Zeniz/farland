#pragma once
#include "gameNode.h"

struct tagMaskInfo {
	int imgNum;
	POINT mapIdx;
	int skillNum;
};


//	_lorderlist.begin�� skill or move �� ��, order.mapidx�� ����ũ �������Ұ�.
//	����������, Ÿ�� ��� ������ �ؾ���. ui��ó�� �������� �ع����� �ȵ�. -> render���� ���� �����Ұ�.
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

