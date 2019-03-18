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

	//	ĳ���� ��ü�� ũ�� = 100,150 (�߽������κ��� ������30, ���� 120)
	
	const float BASIC_MAX_HP = 100;
	const float BASIC_MAX_MP = 50;
	const float BASIC_MOVESPD = 100;
	const float BASIC_CASTSPD = 1.0f;

	const float BASIC_ATK = 5;
	const float BASIC_DEF = 1;
	const float BASIC_MATK = 3;
	const float BASIC_MDEF = 5;

	


public:
	skeleton();
	~skeleton();


	HRESULT init() override;
	void InitObjectiveValDefault(POINT mapIdx)	override;
	void InitCharacteristicValDefault()			override;
	void release() override;
	void update() override;
	void render() override;

	void setAni();

	//	ani2���迭�� attrValue�迭�� 0,0 ������.
	//void setNewSkel(E_IMGNUM imgNum, animation* ani, POINTFLOAT pos, RECT rc, int zLvl,
	//	float curHp, float maxHp, float curMp, float maxMp, POINT mapIdx, float attrValue);

	//void setNewSkel()
	void setNewSkelforMapEditor(ENEMY_NAME mobName, POINT mapIdx);


};

