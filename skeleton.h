#pragma once
#include "enemy.h"
class skeleton : public enemy
{
private:
	//	 : public <objects>
	//image* _img;	//int _frameX;	//int _frameY;	//POINTFLOAT _pos;	//RECT _rc;	//int _zLevel;

	//	: protected <enemy>
	//float _curHp;	//float _maxHp;	//float _curMp;	//float _maxMp;	//POINT _mapIdx;	//animation _ani[E_DIR::DIR_END][E_STATUS::STATUS_END];
	//float _attrValue[E_ATTR::ATTR_END] //E_IMGNUM _imgNum;

public:
	skeleton();
	~skeleton();


	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	//	ani2차배열과 attrValue배열은 0,0 넣을것.
	void setNewSkel(E_IMGNUM imgNum, animation* ani, POINTFLOAT pos, RECT rc, int zLvl,
		float curHp, float maxHp, float curMp, float maxMp, POINT mapIdx, float attrValue);
	void setNewSkelforMapEditor(E_IMGNUM imgNum, POINT mapIdx);
};

