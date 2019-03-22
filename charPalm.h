#pragma once
#include "character.h"
class charPalm : public Character
{
private:

	const float BASIC_MAXHP = 100;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 150;
	const float BASIC_REGENMP = 5;

	const float BASIC_MOVESPD = 30.0f;			//	나누는 숫자. 낮을수록 빨라짐 (35안됨 -> moveVec = 0 떄무네 그런가봄 ㅠ, 너무 잘게쪼개져...)
	const float BASIC_CASTSPD = 2.5f;

	const float BASIC_ATK = 8;
	const float BASIC_DEF = 5;
	const float BASIC_MATK = 15;
	const float BASIC_MDEF = 10;




public:
	charPalm();
	~charPalm();

	HRESULT init();		//	캐릭터 중, 스프라이트와 이름만 이닛

	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void InitCharacteristicAugValDefault()				override;

	void release();
	void update() override;

	void setAni();

};

