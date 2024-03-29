#pragma once
#include "character.h"
class charLeon : public Character
{
private:

	

	const float BASIC_MAXHP = 100;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 100;
	const float BASIC_REGENMP = 1;

	const float BASIC_MOVESPD = 20.0f;			//	나누는 숫자. 낮을수록 빨라짐
	const float BASIC_CASTSPD = 1.0f;

	const float BASIC_ATK = 10;
	const float BASIC_DEF = 8;
	const float BASIC_MATK = 10;
	const float BASIC_MDEF = 5;

	

public:
	charLeon();
	~charLeon();

	HRESULT init();		//	캐릭터 중, 스프라이트와 이름만 이닛
	
	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void InitCharacteristicAugValDefault()				override;

	void release();
	void update() override;
	
	void setAni();

	//void aniRender() override;


	//stateMove에있음
	//void KnowingTileFunc();
	//void CalTileforRenderFunc();		

	//void makeIdleByEndAni();
	//void CoolDownFunc();



	

	//	테스트용
	//	애니메이션 테스트
	void stateAniTest();
};

