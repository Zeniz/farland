#include "stdafx.h"
#include "CharInfoUI.h"


CharInfoUI::CharInfoUI()
{
	IMAGEMANAGER->addImage("CharUIBack", L"images/UI/charInfoUI/charInfoUIBackImg.png", 954, 176);
	IMAGEMANAGER->addFrameImage("Portraits", L"images/UI/charInfoUI/portraits.png", 2400, 528, 10, 3);
	IMAGEMANAGER->addFrameImage("CharUIBar", L"images/UI/charInfoUI/CharUIBarImg.png", 160, 51, 1, 3);
	IMAGEMANAGER->addFrameImage("SkillMask", L"images/UI/charInfoUI/skillMask.png", 192, 20, 1, 1);
	IMAGEMANAGER->addFrameImage("OrderListMask", L"images/UI/charInfoUI/orderListMask.png", 219, 28, 1, 1);
	

	_backImg = IMAGEMANAGER->findImage("CharUIBack");
	_portrait = IMAGEMANAGER->findImage("Portraits");
	_barsImg = IMAGEMANAGER->findImage("CharUIBar");
	_skillMask = IMAGEMANAGER->findImage("SkillMask");
	_orderListMask = IMAGEMANAGER->findImage("OrderListMask");
	

	
	_portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
	_name = CHAR_NAME::NONE;
	_state = nullptr;
	_lOrderList = nullptr;
	
	
	//for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
	//	for (int j = 0; j < CHAR_VALUE_KINDS::KINDS_END; j++) {
	//		(*_charValue)[i][j] = NULL;
	//	}
	//}
	for (int i = 0; i < RATIOS::RATIOS_END; i++) {
		_ratios[i] = NULL;
	}

	_maxHp = NULL;
	_maxMp = NULL;
	_maxSp = NULL;
	_curHp = NULL;
	_curMp = NULL;
	_curSp = NULL;


}


CharInfoUI::~CharInfoUI()
{
}

HRESULT CharInfoUI::setValue(CHAR_NAME name, CHAR_STATE* stateAddr, list<ORDER_KINDS>* lOrderList, float* charValue0, float* charValue1)
{
	_portraitKinds = CHAR_PORTRAIT_KINDS::BASIC;
	_name = name;
	switch (name)
	{
	case CHAR_NAME::NONE:
		break;
	case CHAR_NAME::LEON:
		swprintf_s(_nameStr, L"레온");
		//_nameStr = L"레온";
		break;
	case CHAR_NAME::CAREN:
		swprintf_s(_nameStr, L"카렌");
		//_nameStr = L"카렌";
		break;
	default:
		break;
	}

	_state = stateAddr;
	_lOrderList = lOrderList;
	
	for (int i = 0; i < CHAR_VALUE_KINDS::KINDS_END; i++) {
		_charValue[CUR][i] = &charValue0[i];
		_charValue[AUG][i] = &charValue1[i];
	}
	
	
	
	CalRatios();
	


	return S_OK;
}

void CharInfoUI::release()
{
}

void CharInfoUI::update()
{
	CalRatios();
}

void CharInfoUI::render()
{
	WCHAR str[128];
	//	검은종이 깔고~
	_backImg->renderABS(BACKIMG_START.x, BACKIMG_START.y, 1.0f);
	//	초상화 뽑고
	_portrait->frameRenderABS(BACKIMG_START.x, BACKIMG_START.y, (int)_portraitKinds, (int)_name, 1.0f);
	//	이름 써주고,
	D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFFFFFF, 1.0f), L"consolas", 25, _nameStr,
		NAME_START.x + CAMERA2D->getCamPosX(), NAME_START.y + CAMERA2D->getCamPosY(), 
		NAME_START.x + CAMERA2D->getCamPosX()+150, NAME_START.y + CAMERA2D->getCamPosY()+50);
	
	//	바 + 바 숫자
	for (int i = 0; i < 3; i++) {
		// 이미지깔고
		_barsImg->frameRenderABS(BAR_START.x, BAR_START.y + i * BAR_YGAP, 0, 0,
			_barsImg->GetFrameWidth()*_ratios[i], _barsImg->GetFrameHeight(),
			0, i, 1.0f);
		//	숫자넣고
		
		if (i == 0) {
			swprintf_s(str, L"%.f\t/    %.f", _curHp, _maxHp);
		}
		else if (i == 1) {
			swprintf_s(str, L"%.f\t/    %.f", _curMp, _maxMp);
		}
		else if (i == 2) {
			swprintf_s(str, L"%.f\t/    %.f", _curSp, _maxSp);
		}
		D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0xFFFFFF, 2.0f), L"consolas", 15, str, 
			BAR_INFO_START.x + CAMERA2D->getCamPosX()- 10,
			BAR_INFO_START.y + (i*BAR_YGAP) + CAMERA2D->getCamPosY() - 5,
			BAR_START.x + _barsImg->GetFrameWidth(), (BAR_START.y + i * BAR_YGAP) + _barsImg->GetFrameHeight());

	}
	


	
}

void CharInfoUI::CalRatios()
{
	
	_maxHp = (*_charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::MAX_HP]) + (*_charValue[CHAR_VALUE_CURAUG::AUG][CHAR_VALUE_KINDS::MAX_HP]);
	_maxMp = (*_charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::MAX_MP]) + (*_charValue[CHAR_VALUE_CURAUG::AUG][CHAR_VALUE_KINDS::MAX_MP]);
	_maxSp = (*_charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::MAX_SP]) + (*_charValue[CHAR_VALUE_CURAUG::AUG][CHAR_VALUE_KINDS::MAX_SP]);
	_curHp = (*_charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::CUR_HP]);
	_curMp = (*_charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::CUR_MP]);
	_curSp = (*_charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::CUR_SP]);
	if (_maxHp != 0) {
		_ratios[HP_RATIO] = _curHp / _maxHp;
	}
	else {
		_ratios[HP_RATIO] = 0;
	}
	if (_maxMp != 0) {
		_ratios[MP_RATIO] = _curMp / _maxMp;
	}
	else {
		_ratios[MP_RATIO] = 0;
	}
	if (_maxSp != 0) {
		_ratios[SP_RATIO] = _curSp / _maxSp;
	}
	else {
		_ratios[SP_RATIO] = 0;
	}
}
