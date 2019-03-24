#pragma once
#include "character.h"
#include "enemy.h"



class charKaiser : public enemy
{
private:


	const float BASIC_MAXHP = 1000;
	const float BASIC_REGENHP = 1;
	const float BASIC_MAXMP = 999999;
	const float BASIC_REGENMP = 5;

	const float BASIC_MOVESPD = 30.0f;			//	³ª´©´Â ¼ýÀÚ. ³·À»¼ö·Ï »¡¶óÁü (35¾ÈµÊ -> moveVec = 0 ‹š¹«³× ±×·±°¡º½ ¤Ð, ³Ê¹« Àß°ÔÂÉ°³Á®...)
	const float BASIC_CASTSPD = 2.0f;

	const float BASIC_ATK = 5;
	const float BASIC_DEF = 2;
	const float BASIC_MATK = 20;
	const float BASIC_MDEF = 20;

	const int NOTICE_RANGE = 10;
	


	
	BOSS_ACTION _curKaiserSkill;
	


public:
	charKaiser();
	~charKaiser();

	HRESULT init() override;		

	void InitObjectiveValDefault(POINT mapIdx)			override;
	void InitCharacteristicValDefault()					override;
	void release() override;
	void update() override;

	void setAni();


	

};

