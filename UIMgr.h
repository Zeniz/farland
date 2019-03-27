#pragma once
#include "gameNode.h"
#include "MaskTile.h"
#include "CharInfoUI.h"
#include "timeDelayUI.h"
#include "stageClearUI.h"

enum UI_KINDS {
	UI_KINDS_NONE = 0x00000000UL,
	MASK_TILE = 0x00000001UL,
	CHARINFO = 0x00000002UL,
	TIMEDELAY = 0x00000004UL,
	STAGECLEAR = 0x00000008UL,



	UI_KINDS_END,
};


class UIMgr : public gameNode
{
public:
	unsigned char	_selectUI;

	MaskTile*	_maskTile;
	CharInfoUI* _charInfoUI;
	timeDelayUI* _timeDelayUI;
	stageClearUI* _stageClearUI;

	


	vvMap* _vvMap;
	CharMgr* _charMgr;
	vEnemy* _vpEnemy;

public:
	UIMgr();
	~UIMgr();

	HRESULT init();
	void release();
	void update();
	void render();

	void setSelectUI(unsigned char selectUI);
	void AddChar(CHAR_NAME name, CHAR_STATE* stateAddr, list<tagOrderInfo>* lOrderList, float* charValue0, float* charValue1);
	void AddChar(Character* chara);

	void LinkToMap(vvMap* vvMapAddr) { _vvMap = vvMapAddr; }
	void LinkToCharMgr(CharMgr* charMgrAddr) { _charMgr = charMgrAddr; }
	void LinkToVEnemy(vEnemy* vEnemyAddr) { _vpEnemy = vEnemyAddr; }

	void setPauseToTimeDelay(bool value) { _timeDelayUI->setPause(value); }

	void setStageClear(bool value) { _stageClearUI->setIsClear(value); }
	void CalNextStage(string curStageName) { _stageClearUI->CalNextStage(curStageName.c_str()); }
};

