#include "stdafx.h"
#include "CharInfoUI.h"


CharInfoUI::CharInfoUI()
{
	IMAGEMANAGER->addImage("CharUIBack", L"images/UI/charInfoUI/charInfoUIBackImg.png", 954, 176);
	IMAGEMANAGER->addFrameImage("Portraits", L"images/UI/charInfoUI/portraits.png", 2400, 528, 10, 3);
	IMAGEMANAGER->addFrameImage("CharUIBar", L"images/UI/charInfoUI/CharUIBarImg.png", 160, 51, 1, 3);
	IMAGEMANAGER->addFrameImage("SkillMask", L"images/UI/charInfoUI/skillMask.png", 192, 20, 1, 1);
	IMAGEMANAGER->addFrameImage("SkillMaskSelect", L"images/UI/charInfoUI/skillMaskSelect.png", 192, 20, 1, 1);
	IMAGEMANAGER->addFrameImage("OrderListMask", L"images/UI/charInfoUI/orderListMask.png", 155, 28, 1, 1);
	

	_backImg = IMAGEMANAGER->findImage("CharUIBack");
	_portrait = IMAGEMANAGER->findImage("Portraits");
	_barsImg = IMAGEMANAGER->findImage("CharUIBar");
	_skillMask = IMAGEMANAGER->findImage("SkillMask");
	_skillMaskSelect = IMAGEMANAGER->findImage("SkillMaskSelect");
	_orderListMask = IMAGEMANAGER->findImage("OrderListMask");
	
	_brush = D2DMANAGER->createBrush(0xFFFFFF, 1.0f);

	_curSelectChar = -1;

	
	
	//for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
	//	for (int j = 0; j < CHAR_VALUE_KINDS::KINDS_END; j++) {
	//		(*_charValue)[i][j] = NULL;
	//	}
	//}
	


}


CharInfoUI::~CharInfoUI()
{
}



HRESULT CharInfoUI::init()
{

	_backImg = IMAGEMANAGER->findImage("CharUIBack");
	_portrait = IMAGEMANAGER->findImage("Portraits");
	_barsImg = IMAGEMANAGER->findImage("CharUIBar");
	_skillMask = IMAGEMANAGER->findImage("SkillMask");
	_skillMaskSelect = IMAGEMANAGER->findImage("SkillMaskSelect");
	_orderListMask = IMAGEMANAGER->findImage("OrderListMask");

	_curSelectChar = -1;

	_vCharInfo.clear();


	return S_OK;
}

void CharInfoUI::release()
{
}

void CharInfoUI::update()
{
	SelectCharFunc();
	
	//ĳ���� ���õǾ��ٸ�,
	if(-1 < _curSelectChar && _curSelectChar < _vCharInfo.size()){
		CalRatios(&_vCharInfo[_curSelectChar]);
		SelectPortrait(&_vCharInfo[_curSelectChar]);
		_mode = _charMgr->getCharMode(_curSelectChar);
	}


	if (_mode != ORDER_KINDS::NONE) {
		//�ۼ��ؾߵ�
	}
	
}

void CharInfoUI::render()
{
	//if (_curSelectChar != -1) {
	if(-1 < _curSelectChar && _curSelectChar < _vCharInfo.size()){
		WCHAR str[128];
		//	�������� ���~
		_backImg->renderABS(BACKIMG_START.x, BACKIMG_START.y, 1.0f);
		//	�ʻ�ȭ �̰�
		_portrait->frameRenderABS(BACKIMG_START.x, BACKIMG_START.y, (int)_vCharInfo[_curSelectChar].portraitKinds, (int)_vCharInfo[_curSelectChar].name, 1.0f);
		
		//	�̸� ���ְ�,
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 25, _vCharInfo[_curSelectChar].nameStr,
			NAME_START.x + CAMERA2D->getCamPosX(), NAME_START.y + CAMERA2D->getCamPosY(),
			NAME_START.x + CAMERA2D->getCamPosX() + 150, NAME_START.y + CAMERA2D->getCamPosY() + 50);

		//	�� + �� ����
		for (int i = 0; i < 3; i++) {
			// �̹������
			_barsImg->frameRenderABS(BAR_START.x, BAR_START.y + i * BAR_YGAP, 0, 0,
				_barsImg->GetFrameWidth()*_vCharInfo[_curSelectChar].ratios[i], _barsImg->GetFrameHeight(),
				0, i, 1.0f);
			//	���ڳְ�

			if (i == 0) {
				swprintf_s(str, L"%.f\t/    %.f", _vCharInfo[_curSelectChar].curHp, _vCharInfo[_curSelectChar].maxHp);
			}
			else if (i == 1) {
				swprintf_s(str, L"%.f\t/    %.f", _vCharInfo[_curSelectChar].curMp, _vCharInfo[_curSelectChar].maxMp);
			}
			else if (i == 2) {
				swprintf_s(str, L"%.f\t/    %.f", _vCharInfo[_curSelectChar].curSp, _vCharInfo[_curSelectChar].maxSp);
			}
			D2DMANAGER->drawTextD2D(_brush, L"consolas", 15, str,
				BAR_INFO_START.x + CAMERA2D->getCamPosX() - 10,
				BAR_INFO_START.y + (i*BAR_YGAP) + CAMERA2D->getCamPosY() - 5,
				BAR_START.x + _barsImg->GetFrameWidth(), (BAR_START.y + i * BAR_YGAP) + _barsImg->GetFrameHeight());
		}
		
		//	�������ͽ� �̸��� (atk,def, m.atk, m.def, movespd, castspd,)
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, L"ATK",
			CAMERA2D->getCamPosX() + INFO_START.x, CAMERA2D->getCamPosY() + INFO_START.y, 
			CAMERA2D->getCamPosX() + INFO_START.x + 50, CAMERA2D->getCamPosY() + INFO_START.y + 50);
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, L"DEF",
			CAMERA2D->getCamPosX() + INFO_START.x, CAMERA2D->getCamPosY() + INFO_START.y + 25,
			CAMERA2D->getCamPosX() + INFO_START.x + 50, CAMERA2D->getCamPosY() + INFO_START.y + 50 + 25);
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, L"M.ATK",
			CAMERA2D->getCamPosX() + INFO_START.x, CAMERA2D->getCamPosY() + INFO_START.y + 50,
			CAMERA2D->getCamPosX() + INFO_START.x + 50, CAMERA2D->getCamPosY() + INFO_START.y + 50 + 50);
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, L"M.DEF",
			CAMERA2D->getCamPosX() + INFO_START.x, CAMERA2D->getCamPosY() + INFO_START.y + 75,
			CAMERA2D->getCamPosX() + INFO_START.x + 50, CAMERA2D->getCamPosY() + INFO_START.y + 50 + 75);
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, L"MOVE_SPD",
			CAMERA2D->getCamPosX() + INFO_START.x, CAMERA2D->getCamPosY() + INFO_START.y + 100,
			CAMERA2D->getCamPosX() + INFO_START.x + 100, CAMERA2D->getCamPosY() + INFO_START.y + 50 + 100);
		D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, L"CAST_SPD",
			CAMERA2D->getCamPosX() + INFO_START.x, CAMERA2D->getCamPosY() + INFO_START.y + 125,
			CAMERA2D->getCamPosX() + INFO_START.x + 100, CAMERA2D->getCamPosY() + INFO_START.y + 50 + 125);

		//	�������ͽ� ������ ���
		for (int i = 11; i < 15; i++) {
			WCHAR str[128];
			swprintf_s(str, L"%.f + %.f", *_vCharInfo[_curSelectChar].charValue[CUR][i], *_vCharInfo[_curSelectChar].charValue[AUG][i]);
			D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, str,
				CAMERA2D->getCamPosX() + INFO_DATA_START.x,			CAMERA2D->getCamPosY() + INFO_DATA_START.y + (i - 11)* INFO_YGAP,
				CAMERA2D->getCamPosX() + INFO_DATA_START.x + 100,	CAMERA2D->getCamPosY() + INFO_DATA_START.y + (i - 11)* INFO_YGAP + 50);
		}
		for (int i = 9; i < 11; i++) {
			WCHAR str[128];
			swprintf_s(str, L"%.f + %.f", *_vCharInfo[_curSelectChar].charValue[CUR][i], *_vCharInfo[_curSelectChar].charValue[AUG][i]);
			D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, str,
				CAMERA2D->getCamPosX() + INFO_DATA_START.x, CAMERA2D->getCamPosY() + INFO_DATA_START.y + (i - 5)* INFO_YGAP,
				CAMERA2D->getCamPosX() + INFO_DATA_START.x + 100, CAMERA2D->getCamPosY() + INFO_DATA_START.y + (i - 5)* INFO_YGAP + 50);
		}


		//	��ų����ũ  + ��ų��(�ؾߵ�)
		for (int i = 0; i < 7; i++) {
			
			ORDER_KINDS curMode = (*_charMgr->getVChara())[_curSelectChar]->_mode;	//	���� ĳ������ ���
			float ratio = (*_charMgr->getVChara())[_curSelectChar]->_coolDownTimer[0][i] / (*_charMgr->getVChara())[_curSelectChar]->_coolDownTimer[1][i];

			//	���� ���õ� ��尡, ����� ��ų�� ���ٸ�,
			if (_mode == i) {
			//if (_mode == ORDER_KINDS::MOVE && i == 0) {
				_skillMaskSelect->renderABS(SKILL_START.x, SKILL_START.y + i * SKILL_YGAP, _skillMask->GetWidth() * ratio, _skillMask->GetHeight(), 0.8f);
			}
			
			else {
				//													���� �ʺ� ratio�����ؾ���	
				_skillMask->renderABS(SKILL_START.x, SKILL_START.y + i * SKILL_YGAP, _skillMask->GetWidth() * ratio, _skillMask->GetHeight(), 0.8f);
			}
			

			WCHAR str[128];
			//	i�� ���� ��Ʈ�� ����
			switch (i)
			{
			case 0:
				swprintf_s(str, L"[M] Move");
				break;
			case 1:
				swprintf_s(str, L"[H] Hold");
				break;
			case 2:
				swprintf_s(str, L"[A] Attack");
				break;
			case 3:
				swprintf_s(str, L"[Q] SKILL1");		//	��ų�� �޾ƿ;���
				break;
			case 4:
				swprintf_s(str, L"[W] SKILL2");
				break;
			case 5:
				swprintf_s(str, L"[E] SKILL3");
				break;
			case 6:
				swprintf_s(str, L"[R] SKILL4");
				break;
			default:
				break;
			}
			D2DMANAGER->drawTextD2D(_brush, L"consolas", 18, str,
				CAMERA2D->getCamPosX() + SKILL_START.x, CAMERA2D->getCamPosY() + SKILL_START.y + i* SKILL_YGAP,
				CAMERA2D->getCamPosX() + SKILL_START.x + 100, CAMERA2D->getCamPosY() + SKILL_START.y + i* SKILL_YGAP + 50);
		}

		//	��������Ʈ
		{
			//	��������Ʈ txt
			WCHAR str[128];
			swprintf_s(str, L"Order List");
			D2DMANAGER->drawTextD2D(_brush, L"consolas", 20, str,
				CAMERA2D->getCamPosX() + ORDERLIST_START.x + 15, CAMERA2D->getCamPosY() + ORDERLIST_START.y - 25,
				CAMERA2D->getCamPosX() + ORDERLIST_START.x + 200, CAMERA2D->getCamPosY() + ORDERLIST_START.y);

			list<tagOrderInfo>::iterator iter = _vCharInfo[_curSelectChar].lOrderList->begin();
			int count = 0;
			POINT mapIdx;
			
			for (iter; iter != _vCharInfo[_curSelectChar].lOrderList->end(); iter++) {
				if (count == 5)	break;
				//	���� ������ ����, str����
				switch (iter->kinds)
				{
				case ORDER_KINDS::ATTACK:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"ATK [%d,%d]", mapIdx.x, mapIdx.y);
					break;
				case ORDER_KINDS::HOLD:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"HOLD [%d,%d]", mapIdx.x, mapIdx.y);
					break;
				case ORDER_KINDS::MOVE:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"MOVE [%d,%d]", mapIdx.x, mapIdx.y);
					break;
				case ORDER_KINDS::SKILL1:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"SKILL1 [%d,%d]", mapIdx.x, mapIdx.y);
					break;
				case ORDER_KINDS::SKILL2:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"SKILL2 [%d,%d]", mapIdx.x, mapIdx.y);
					break;
				case ORDER_KINDS::SKILL3:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"SKILL3 [%d,%d]", mapIdx.x, mapIdx.y);
					break;
				case ORDER_KINDS::SKILL4:
					mapIdx = iter->targetMapIdx;
					swprintf_s(str, L"SKILL4 [%d,%d]", mapIdx.x, mapIdx.y);
					break;


				default:
					break;
				}
				//	��������Ʈ ����ũ
				_orderListMask->renderABS(ORDERLIST_START.x, ORDERLIST_START.y + count * ORDER_YGAP);
				//	���� txt
				D2DMANAGER->drawTextD2D(_brush, L"consolas", 20, str,
					CAMERA2D->getCamPosX() + ORDERLIST_START.x + 10, CAMERA2D->getCamPosY() + ORDERLIST_START.y + count * ORDER_YGAP);
				count++;
			}
			
			

		}
		
		
	}
	
	


	
}

void CharInfoUI::addCharValue(CHAR_NAME name, CHAR_STATE* stateAddr, list<tagOrderInfo>* lOrderList, float* charValue0, float* charValue1)
{
	tagCharInfo charInfo;
	charInfo.name = name;
	switch (charInfo.name)
	{
	case CHAR_NAME::NONE:
		break;
	case CHAR_NAME::LEON:
		swprintf_s(charInfo.nameStr, L"����");
		break;
	case CHAR_NAME::CAREN:
		swprintf_s(charInfo.nameStr, L"ī��");
		break;
	default:
		break;
	}

	charInfo.portraitKinds = CHAR_PORTRAIT_KINDS::BASIC;
	charInfo.stateAddr = stateAddr;
	charInfo.lOrderList = lOrderList;
	for (int i = 0; i < CHAR_VALUE_KINDS::KINDS_END; i++) {
		charInfo.charValue[CUR][i] = &charValue0[i];
		charInfo.charValue[AUG][i] = &charValue1[i];
	}

	CalRatios(&charInfo);

	_vCharInfo.push_back(charInfo);

	
}

void CharInfoUI::addCharValue(Character * chara)
{
	tagCharInfo charInfo;
	charInfo.name = chara->_name;
	switch (charInfo.name)
	{
	case CHAR_NAME::NONE:
		break;
	case CHAR_NAME::LEON:
		swprintf_s(charInfo.nameStr, L"����");
		break;
	case CHAR_NAME::CAREN:
		swprintf_s(charInfo.nameStr, L"ī��");
		break;
	default:
		break;
	}

	charInfo.portraitKinds = CHAR_PORTRAIT_KINDS::BASIC;
	charInfo.stateAddr = &chara->_state;
	charInfo.lOrderList = &chara->_lOrderList;
	for (int i = 0; i < CHAR_VALUE_KINDS::KINDS_END; i++) {
		charInfo.charValue[CUR][i] = &chara->_charValue[CUR][i];
		charInfo.charValue[AUG][i] = &chara->_charValue[AUG][i];
	}

	CalRatios(&charInfo);

	_vCharInfo.push_back(charInfo);

}

tagCharInfo CharInfoUI::findCharInfo(CHAR_NAME name)
{
	tagCharInfo charInfo;
	charInfo.init();
	for (int i = 0; i < _vCharInfo.size(); i++) {
		if (_vCharInfo[i].name == name) {
			charInfo = _vCharInfo[i];
			break;
		}
	}
	return charInfo;
}

int CharInfoUI::getIdxOfChar(CHAR_NAME name)
{
	for (int i = 0; i < _vCharInfo.size(); i++) {
		if (_vCharInfo[i].name == name) {
			return i;
		}
	}
}

void CharInfoUI::CalRatios(tagCharInfo * charInfo)
{
	charInfo->maxHp = (*charInfo->charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::MAX_HP]) + (*charInfo->charValue[CHAR_VALUE_CURAUG::AUG][CHAR_VALUE_KINDS::MAX_HP]);
	charInfo->maxMp = (*charInfo->charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::MAX_MP]) + (*charInfo->charValue[CHAR_VALUE_CURAUG::AUG][CHAR_VALUE_KINDS::MAX_MP]);
	charInfo->maxSp = (*charInfo->charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::MAX_SP]) + (*charInfo->charValue[CHAR_VALUE_CURAUG::AUG][CHAR_VALUE_KINDS::MAX_SP]);
	charInfo->curHp = (*charInfo->charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::CUR_HP]);
	charInfo->curMp = (*charInfo->charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::CUR_MP]);
	charInfo->curSp = (*charInfo->charValue[CHAR_VALUE_CURAUG::CUR][CHAR_VALUE_KINDS::CUR_SP]);
	if (charInfo->maxHp != 0) { charInfo->ratios[HP_RATIO] = charInfo->curHp / charInfo->maxHp; }
	else { charInfo->ratios[HP_RATIO] = 0; }
	if (charInfo->maxMp != 0) { charInfo->ratios[MP_RATIO] = charInfo->curMp / charInfo->maxMp; }
	else { charInfo->ratios[MP_RATIO] = 0; }
	if (charInfo->maxSp != 0) { charInfo->ratios[SP_RATIO] = charInfo->curSp / charInfo->maxSp; }
	else { charInfo->ratios[SP_RATIO] = 0; }
}

void CharInfoUI::SelectCharFunc()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		if (_curSelectChar == 0) {
			_charMgr->setSelectChar(_curSelectChar, false);
			_curSelectChar = -1;
			_mode = ORDER_KINDS::NONE;
		}
		else {
			_charMgr->setSelectChar(_curSelectChar, false);
			_curSelectChar = 0;
			_charMgr->setSelectChar(_curSelectChar, true);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		if (_curSelectChar == 1) {
			_charMgr->setSelectChar(_curSelectChar, false);
			_curSelectChar = -1;
			_mode = ORDER_KINDS::NONE;
			
		}
		else {
			_charMgr->setSelectChar(_curSelectChar, false);
			_curSelectChar = 1;
			_charMgr->setSelectChar(_curSelectChar, true);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
		if (_curSelectChar == 2) {
			_charMgr->setSelectChar(_curSelectChar, false);
			_curSelectChar = -1;
			_mode = ORDER_KINDS::NONE;

		}
		else {
			_charMgr->setSelectChar(_curSelectChar, false);
			_curSelectChar = 2;
			_charMgr->setSelectChar(_curSelectChar, true);
		}
	}
}

void CharInfoUI::SelectPortrait(tagCharInfo * charInfo)
{
	CHAR_STATE charState = *(charInfo[_curSelectChar].stateAddr);
	switch (charState)
	{
	case CHAR_STATE::NONE:
		break;
	case CHAR_STATE::IDLE:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::BASIC;
		break;
	case CHAR_STATE::MOVE:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::JOYFUL;
		break;
	case CHAR_STATE::CASTING:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
		break;
	case CHAR_STATE::DEAD:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::DEAD;
		break;
	case CHAR_STATE::GETHIT:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::GETDMG;
		break;
	case CHAR_STATE::STONE:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::GETDMG;
		break;
	case CHAR_STATE::FROZEN:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::GETDMG;
		break;
	case CHAR_STATE::GETHIT2:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::GETDMG;
		break;
	case CHAR_STATE::BLOCK:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::SURPRISED;
		break;
	case CHAR_STATE::BASIC_ATK:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
		break;
	case CHAR_STATE::SKILL1:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
		break;
	case CHAR_STATE::SKILL2:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
		break;
	case CHAR_STATE::SKILL3:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
		break;
	case CHAR_STATE::SKILL4:
		_vCharInfo[_curSelectChar].portraitKinds = CHAR_PORTRAIT_KINDS::UPSET;
		break;
	case CHAR_STATE::CHAR_STATE_END:
		break;
	default:
		break;
	}
}
