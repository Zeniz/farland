#pragma once
#include "UIObjects.h"
#include "CharMgr.h"
#include "character.h"


//	_lorderlist.begin�� skill or move �� ��, order.mapidx�� ����ũ �������Ұ�.
//	����������, Ÿ�� ��� ������ �ؾ���. ui��ó�� �������� �ع����� �ȵ�. -> render���� ���� �����Ұ�.
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

