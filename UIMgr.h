#pragma once
#include "gameNode.h"
#include "MaskTile.h"
#include "CharInfoUI.h"
#include "timeDelayUI.h"

enum UI_KINDS {
	UI_KINDS_NONE = 0x00000000UL,
	MASK_TILE = 0x00000001UL,
	CHARINFO = 0x00000002UL,
	TIMEDELAY = 0x00000004UL,



	UI_KINDS_END,
};


class UIMgr : public gameNode
{
public:
	unsigned char	_selectUI;

	MaskTile*	_maskTile;
	CharInfoUI* _charInfoUI;
	timeDelayUI* _timeDelayUI;

	


	vvMap* _vvMap;
	CharMgr* _charMgr;

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

};

