#pragma once
#include "UIObjects.h"
#include "character.h"
#include "CharMgr.h"



enum RATIOS {
	RATIO_START = -1,
	HP_RATIO,
	MP_RATIO,
	SP_RATIO,
	RATIOS_END,

};

struct tagCharInfo {

	CHAR_NAME name;
	WCHAR nameStr[128];

	CHAR_PORTRAIT_KINDS portraitKinds;
	CHAR_STATE* stateAddr;
	list<tagOrderInfo>* lOrderList;

	float* charValue[CHAR_VALUE_CURAUG::CURAUG_END][CHAR_VALUE_KINDS::KINDS_END];
	float ratios[RATIOS_END];

	float maxHp;
	float maxMp;
	float maxSp;
	float curHp;
	float curMp;
	float curSp;

	void init() {
		name = CHAR_NAME::NONE;
		swprintf_s(nameStr, L"NONE");
		portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
		stateAddr = nullptr;
		lOrderList = nullptr;
		for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
			for (int j = 0; j < CHAR_VALUE_KINDS::KINDS_END; j++) {
				charValue[i][j] = nullptr;
			}
		}
		for (int i = 0; i < RATIOS::RATIOS_END; i++) {
			ratios[i] = NULL;
		}
		maxHp = 0.f;
		maxMp = 0.f;
		maxSp = 0.f;
		curHp = 0.f;
		curMp = 0.f;
		curSp = 0.f;
	}

};

class CharInfoUI : public UIObjects
{
	image* _backImg;
	image* _portrait;
	image* _barsImg;
	image* _skillMask;
	image* _skillMaskSelect;
	image* _orderListMask;

	ID2D1SolidColorBrush* _brush;


	vector<tagCharInfo> _vCharInfo;

	int _curSelectChar;

	CharMgr* _charMgr;
	ORDER_KINDS _mode;


	const POINT BACKIMG_START = {321, 725};
	const POINT BAR_START = { 577,784 };
	const POINT BAR_INFO_START = { 608, 788 };
	const int BAR_YGAP = 32;
	
	
	const POINT NAME_START = { 577,737 };
	const POINT INFO_START = { 740,737 };
	const POINT INFO_DATA_START = { 832,737 };
	const int INFO_YGAP = 25;

	const POINT SKILL_START = { 928,736 };
	const int SKILL_YGAP = 23;

	const POINT ORDERLIST_START = { 1124,756 };	//	y:736ÀÌ¾úÀ½
	const int ORDER_YGAP = 30;





public:
	CharInfoUI();
	~CharInfoUI();

	
	HRESULT init()	override;
	void release()	override;
	void update()	override;
	void render()	override;

	void addCharValue(CHAR_NAME name, CHAR_STATE* stateAddr, list<tagOrderInfo>* lOrderList, float* charValue0, float* charValue1);
	void addCharValue(Character* chara);

	tagCharInfo findCharInfo(CHAR_NAME name);
	int	getIdxOfChar(CHAR_NAME name);

	void CalRatios(tagCharInfo* charInfo);
	void SelectCharFunc();



	void LinkToCharMgr(CharMgr* charMgrAddr) { _charMgr = charMgrAddr; }
};

