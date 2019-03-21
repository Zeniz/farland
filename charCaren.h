#pragma once
#include "character.h"
class charCaren : public Character
{
private:



	const float BASIC_MAXHP = 80;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 200;
	const float BASIC_REGENMP = 5;

	const float BASIC_MOVESPD = 34.0f;			//	������ ����. �������� ������ (35�ȵ� -> moveVec = 0 ������ �׷����� ��, �ʹ� �߰��ɰ���...)
	const float BASIC_CASTSPD = 5.0f;

	const float BASIC_ATK = 5;
	const float BASIC_DEF = 5;
	const float BASIC_MATK = 20;
	const float BASIC_MDEF = 20;


public:
	charCaren();
	~charCaren();

	HRESULT init();		//	ĳ���� ��, ��������Ʈ�� �̸��� �̴�

	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void InitCharacteristicAugValDefault()				override;

	void release();
	void update() override;

	void setAni();
};

