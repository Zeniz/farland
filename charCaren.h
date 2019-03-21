#pragma once
#include "character.h"
class charCaren : public Character
{
private:



	const float BASIC_MAXHP = 80;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 200;
	const float BASIC_REGENMP = 5;

	const float BASIC_MOVESPD = 34.0f;			//	나누는 숫자. 낮을수록 빨라짐 (35안됨 -> moveVec = 0 떄무네 그런가봄 ㅠ, 너무 잘게쪼개져...)
	const float BASIC_CASTSPD = 5.0f;

	const float BASIC_ATK = 5;
	const float BASIC_DEF = 5;
	const float BASIC_MATK = 20;
	const float BASIC_MDEF = 20;


public:
	charCaren();
	~charCaren();

	HRESULT init();		//	캐릭터 중, 스프라이트와 이름만 이닛

	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void InitCharacteristicAugValDefault()				override;

	void release();
	void update() override;

	void setAni();
};

