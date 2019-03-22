#pragma once
#include "character.h"
class charPalm : public Character
{
private:

	const float BASIC_MAXHP = 100;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 150;
	const float BASIC_REGENMP = 5;

	const float BASIC_MOVESPD = 30.0f;			//	������ ����. �������� ������ (35�ȵ� -> moveVec = 0 ������ �׷����� ��, �ʹ� �߰��ɰ���...)
	const float BASIC_CASTSPD = 2.5f;

	const float BASIC_ATK = 8;
	const float BASIC_DEF = 5;
	const float BASIC_MATK = 15;
	const float BASIC_MDEF = 10;




public:
	charPalm();
	~charPalm();

	HRESULT init();		//	ĳ���� ��, ��������Ʈ�� �̸��� �̴�

	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void InitCharacteristicAugValDefault()				override;

	void release();
	void update() override;

	void setAni();

};

