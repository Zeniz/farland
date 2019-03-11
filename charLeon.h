#pragma once
#include "character.h"
class charLeon : public Character
{
private:

	

	const float BASIC_MAXHP = 100;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 100;
	const float BASIC_REGENMP = 1;

	const float BASIC_MOVESPD = 20.0f;			//	������ ����. �������� ������
	const float BASIC_CASTSPD = 1.0f;

	const float BASIC_ATK = 10;
	const float BASIC_DEF = 5;
	const float BASIC_MATK = 10;
	const float BASIC_MDEF = 5;



public:
	charLeon();
	~charLeon();

	HRESULT init();		//	ĳ���� ��, ��������Ʈ�� �̸��� �̴�
	
	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void InitCharacteristicAugValDefault()				override;

	void release();
	void update() override;
	void aniRender() override;
	


	void KnowingTileFunc();
	void CalTileforRenderFunc();

	void setAni();
	void makeIdleByEndAni();

	void OrderPerform();
	void AddOrderMove();


	

	//	�׽�Ʈ��
	//	�ִϸ��̼� �׽�Ʈ
	void stateAniTest();
};

