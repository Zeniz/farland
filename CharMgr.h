#pragma once
#include "gameNode.h"

#include "character.h"
#include "enemy.h"
#include "charLeon.h"


#include "charStatePattern.h"
#include "stateIdle.h"
#include "stateMove.h"
#include "stateCast.h"
#include "stateDead.h"
#include "stateGetHit.h"
#include "stateStone.h"
#include "stateFrozen.h"
#include "stateGetHit2.h"
#include "stateBlock.h"

class CharMgr : public gameNode
{
	typedef vector<enemy*> vEnemy;

	charStatePattern* _arrStatePattern[static_cast<const int>(CHAR_STATE::CHAR_STATE_END)];
	vector<Character*> _vChara;

	
	vvMap* _vvMap;
	vEnemy* _vEnemy;

public:
	CharMgr();
	~CharMgr();

	HRESULT init();
	void release();
	void update();
	void render(int idxX, int idxY);


	void InitArrStatePattern();		

	
	Character* MakeNewChara(CHAR_NAME charName);

	//void InitObjectiveVal(Character* chara, image* img, POINTFLOAT pos, int zlvl, animation* ani, TILE* curTile);
	//void InitCharacteristicVal(Character* chara, float maxHp, float curHp, float regenHp,
	//	float maxMp, float curMp, float regenMp,
	//	float moveSpd, float castSpd,
	//	float atk, float def, float mAtk, float mDef,
	//	CHAR_NAME charName, CHAR_DIR charDir, CHAR_STATE charState
	//);
	//void InitCharacteristicAugVal(Character* chara, float augMaxHp, float augCurHp, float augRegenHp,
	//	float augMaxMp, float augCurMp, float augRegenMp,
	//	float augMoveSpd, float augCastSpd,
	//	float augAtk, float augDef, float augMAtk, float augMDef
	//);
	//void InitCharacteristicAugVal(Character* chara);	//	증가치 null

 	void AddCharacter(Character* chara);


	void LinkToVvMap(vvMap* vvMapAddr) { _vvMap = vvMapAddr; }
	void LinkToVEnemy(vEnemy* vEnemyAddr) { _vEnemy = vEnemyAddr; }


	//	테스트용
	list<POINT>* getWayListAddr(int charIdx) { return _vChara[charIdx]->getWaylistAddr(); }


};

