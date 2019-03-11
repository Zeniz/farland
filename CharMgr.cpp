#include "stdafx.h"
#include "CharMgr.h"



CharMgr::CharMgr()
{
}


CharMgr::~CharMgr()
{
}

HRESULT CharMgr::init()
{
	InitArrStatePattern();

	_vChara.clear();

	_charInfoUI = new CharInfoUI;
	_charInfoUI->init();

	return S_OK;
}

void CharMgr::release()
{
}

void CharMgr::update()
{
	for (int i = 0; i < _vChara.size(); i++) {
		_vChara[i]->update();
		//	ĳ���� �������ΰŸ�, ����!
		if (_vChara[i]->_isSelectedChar) {
			_charInfoUI->update();
		}
	}
	//	ĳ������ ���.
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		for (int i = 0; i < _vChara.size(); i++) {
			_vChara[i]->setIsSelectedChar(false);
		}
	}
	//	ù��°ĳ������
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		for (int i = 0; i < _vChara.size(); i++) {
			_vChara[i]->setIsSelectedChar(false);
			
		}
		_vChara[0]->setIsSelectedChar(true);

		
		

		_charInfoUI->setValue(_vChara[0]->_name, &(_vChara[0]->_state), &(_vChara[0]->_lOrderList), (_vChara[0]->_charValue[0]), (_vChara[0]->_charValue[1]));
	}
	//	2��°ĳ������
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		for (int i = 0; i < _vChara.size(); i++) {
			_vChara[i]->setIsSelectedChar(false);
		}
		if (_vChara.size() >= 2) {
			_vChara[1]->setIsSelectedChar(true);
			_charInfoUI->setValue(_vChara[1]->_name, &(_vChara[1]->_state), &(_vChara[1]->_lOrderList), (_vChara[1]->_charValue[0]), (_vChara[1]->_charValue[1]));
		}
			
	}
	//	3��°ĳ������
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
		for (int i = 0; i < _vChara.size(); i++) {
			_vChara[i]->setIsSelectedChar(false);
		}
		if (_vChara.size() >= 3) {
			_vChara[2]->setIsSelectedChar(true);
			_charInfoUI->setValue(_vChara[2]->_name, &(_vChara[2]->_state), &(_vChara[2]->_lOrderList), (_vChara[2]->_charValue[0]), (_vChara[2]->_charValue[1]));
		}
	}
}

void CharMgr::render(int idxX, int idxY)
{
	for (int i = 0; i < _vChara.size(); i++) {
		if (_vChara[i]->getTileforRender()->_idx.x == idxX && _vChara[i]->getTileforRender()->_idx.y == idxY) {
			_vChara[i]->aniRender();
		}

	}
}

void CharMgr::RenderCharInfo()
{
	for (int i = 0; i < _vChara.size(); i++) {
		if (_vChara[i]->_isSelectedChar) {
			_charInfoUI->render();
			return;
		}
	}
}



void CharMgr::InitArrStatePattern()
{
	_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)] = new stateIdle;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)] = new stateMove;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::CASTING)] = new stateCast;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::DEAD)] = new stateDead;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::GETHIT)] = new stateGetHit;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::STONE)] = new stateStone;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::FROZEN)] = new stateFrozen;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::GETHIT2)] = new stateGetHit2;
	_arrStatePattern[static_cast<const int>(CHAR_STATE::BLOCK)] = new stateBlock;


}


Character * CharMgr::MakeNewChara(CHAR_NAME charName)
{
	Character* _charaAddr = nullptr;
	switch (charName) {
	case CHAR_NAME::LEON:
		_charaAddr = new charLeon;
		_charaAddr->init();
		

		break;


	}

	_charaAddr->LinkToArrStatePattern(*_arrStatePattern);
	_charaAddr->LinkToVvMap(_vvMap);
	_charaAddr->LinkToVEnemy(_vEnemy);


	return _charaAddr;
}

//void CharMgr::InitObjectiveVal(Character * chara, image * img, POINTFLOAT pos, int zlvl, animation * ani, TILE * curTile)
//{
//	chara->InitObjectiveVal(img, pos, zlvl, ani, curTile);
//}
//
//void CharMgr::InitCharacteristicVal(Character * chara, float maxHp, float curHp, float regenHp, float maxMp, float curMp, float regenMp, float moveSpd, float castSpd, float atk, float def, float mAtk, float mDef, CHAR_NAME charName, CHAR_DIR charDir, CHAR_STATE charState)
//{
//	chara->InitCharacteristicVal(maxHp, curHp, regenHp, maxMp, curMp, regenMp, moveSpd, castSpd, atk, def, mAtk, mDef, charName, charDir, charState);
//}
//
//void CharMgr::InitCharacteristicAugVal(Character * chara, float augMaxHp, float augCurHp, float augRegenHp, float augMaxMp, float augCurMp, float augRegenMp, float augMoveSpd, float augCastSpd, float augAtk, float augDef, float augMAtk, float augMDef)
//{
//}
//
//void CharMgr::InitCharacteristicAugVal(Character * chara)
//{
//}


void CharMgr::AddCharacter(Character* chara)
{
	_vChara.push_back(chara);
}