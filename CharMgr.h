#pragma once
#include "gameNode.h"

#include "character.h"
#include "enemy.h"
#include "charLeon.h"
#include "charCaren.h"
#include "charPalm.h"


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
	int _selectedChar;
	
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

	void setSelectChar(int idx, bool value);
	
	ORDER_KINDS getCharMode(int idx) { return _vChara[idx]->getModeKinds(); }
//	list<ORDER_KINDS>* getOrderList(int idx) {return _vChara[idx] }
	
	TILE* getCurTile(int idx) { return _vChara[idx]->getCurTile(); }
	TILE* getTargetTile(int idx) { return _vChara[idx]->getTartgetTile(); }

	POINT getMapIdxOfChar(int idx) { return _vChara[idx]->mapIdx; }
	POINTFLOAT getPosOfChar(int idx) { return _vChara[idx]->_pos; }
	string getSkillNameOfChar(int charIdx, int skillIdx) { return _vChara[charIdx]->_skillName[skillIdx]; }


	void setCurHpAug(int idx, int augVal) { _vChara[idx]->setCurHpAug(augVal); }
	void setCurMpAug(int idx, int augVal) { _vChara[idx]->setCurMpAug(augVal); }
	void setCurSpAug(int idx, int augVal) { _vChara[idx]->setCurSpAug(augVal); }


	vector<Character*>* getVChara() { return &_vChara; }


	void LinkToVvMap(vvMap* vvMapAddr) { _vvMap = vvMapAddr; }
	//void LinkToEnemyMgr(enemyMgr* enemyMgrAddr) { _enemyMgr = enemyMgrAddr; }
	void LinkToVEnemy(vEnemy* vEnemyAddr) { _vEnemy = vEnemyAddr; }
	void TransAddrVCharaToChara(vChara* vCharaAddr, int idx) { _vChara[idx]->LinkToVChara(vCharaAddr); }
	




	//	테스트용
	list<POINT>* getWayListAddr(int charIdx) { return _vChara[charIdx]->getWaylistAddr(); }


};

