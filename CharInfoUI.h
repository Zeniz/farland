#pragma once
#include "gameNode.h"
#include "character.h"


class CharInfoUI : public gameNode
{
	enum RATIOS {
		RATIO_START = -1,
		HP_RATIO,
		MP_RATIO,
		SP_RATIO,
		RATIOS_END,

	};
	image* _backImg;
	image* _portrait;
	image* _barsImg;
	image* _skillMask;
	image* _orderListMask;

	CHAR_PORTRAIT_KINDS _portraitKinds;
	CHAR_NAME _name;
	WCHAR _nameStr[128];
	CHAR_STATE* _state;
	list<ORDER_KINDS>* _lOrderList;


	float* _charValue[CHAR_VALUE_CURAUG::CURAUG_END][CHAR_VALUE_KINDS::KINDS_END];
	float _ratios[RATIOS_END];

	float _maxHp;
	float _maxMp;
	float _maxSp;
	float _curHp;
	float _curMp;
	float _curSp;

	const POINT BACKIMG_START = {321, 725};
	const POINT BAR_START = { 577,784 };
	const POINT BAR_INFO_START = { 608, 788 };
	const int BAR_YGAP = 32;
	
	
	const POINT NAME_START = { 577,737 };
	const POINT INFO_START = { 737,737 };
	const POINT ORDERLIST_START = { 1070,783 };





public:
	CharInfoUI();
	~CharInfoUI();

	HRESULT setValue(CHAR_NAME name, CHAR_STATE* stateAddr, list<ORDER_KINDS>* lOrderList, float* charValue0, float* charValue1);
	void release();
	void update();
	void render();




	void CalRatios();
};

