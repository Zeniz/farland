#include "stdafx.h"
#include "UIMgr.h"


UIMgr::UIMgr()
{
}


UIMgr::~UIMgr()
{
}

HRESULT UIMgr::init()
{
	_selectUI = UI_KINDS::UI_KINDS_NONE;

	_maskTile = nullptr;
	_charInfoUI = nullptr;



	_vvMap = nullptr;


	return S_OK;
}

void UIMgr::release()
{
}

void UIMgr::update()
{
	if (_selectUI & MASK_TILE) {
		_maskTile->update();
	}
	if (_selectUI & CHARINFO) {
		_charInfoUI->update();
	}
}

void UIMgr::render()
{
	if (_selectUI & MASK_TILE) {
		_maskTile->render();
	}
	if (_selectUI & CHARINFO) {
		_charInfoUI->render();
	}
}

void UIMgr::setSelectUI(unsigned char selectUI)
{
	_selectUI = selectUI;
	if (_selectUI & MASK_TILE) {
		_maskTile = new MaskTile;
		_maskTile->init();
		_maskTile->LinkToMap(_vvMap);
	}
	if (_selectUI & CHARINFO) {
		_charInfoUI = new CharInfoUI;
		_charInfoUI->init();
		_charInfoUI->LinkToCharMgr(_charMgr);
	}
}

void UIMgr::AddChar(CHAR_NAME name, CHAR_STATE * stateAddr, list<tagOrderInfo>* lOrderList, float * charValue0, float * charValue1)
{
	_charInfoUI->addCharValue(name, stateAddr, lOrderList, charValue0, charValue1);
}

void UIMgr::AddChar(Character * chara)
{
	_charInfoUI->addCharValue(chara);
}

