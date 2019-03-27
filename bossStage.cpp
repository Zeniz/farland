#include "stdafx.h"
#include "bossStage.h"




bossStage::bossStage()
{
}


bossStage::~bossStage()
{
}

HRESULT bossStage::init()
{
	_bgImg = IMAGEMANAGER->addImage("bossStageBG", L"images/map/bossStageBG.png", 1600, 900);
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::PLAYER_CAMERA);
	CAMERA2D->setState(cameraState::PLAYER_CAMERA);
	SOUNDMANAGER->addSound("bossStageBGM", "sounds/bossStageBGM.mid", true, true);

	_mapLoader = new mapLoader;
	_mapLoader->LoadMap(20, &_vvMap, &_tileNum, &_vEnemy);

	_charMgr = new CharMgr;
	_charMgr->init();
	_charMgr->LinkToVvMap(&_vvMap);

	_enemyMgr = new enemyMgr;
	_enemyMgr->init();
	_enemyMgr->LinkToMap(&_vvMap);

	_charMgr->LinkToVEnemy(_enemyMgr->getVEnemy());
	_enemyMgr->LinkToVChara(_charMgr->getVChara());


	_UIMgr = new UIMgr;
	_UIMgr->init();
	_UIMgr->LinkToMap(&_vvMap);
	_UIMgr->LinkToCharMgr(_charMgr);
	_UIMgr->LinkToVEnemy(_enemyMgr->getVEnemy());

	_selectedUI = UI_KINDS::UI_KINDS_NONE;
	_selectedUI |= UI_KINDS::MASK_TILE;
	_selectedUI |= UI_KINDS::CHARINFO;
	_selectedUI |= UI_KINDS::TIMEDELAY;		//	타임딜레이 셋팅needed
	_selectedUI |= UI_KINDS::STAGECLEAR;



	_UIMgr->setSelectUI(_selectedUI);
	_UIMgr->_timeDelayUI->setIsMobSlowMode(true);
	_UIMgr->_timeDelayUI->setIsCharSlowMode(true);
	_UIMgr->CalNextStage("bossStage");

	//	============캐릭터 추가=======

	//	===	Leon ===
	Character* tmpChar;
	tmpChar = _charMgr->MakeNewChara(CHAR_NAME::LEON);		//	뉴떄려줌, 링크걸고 리턴

	tmpChar->InitObjectiveValDefault({ 0,9 });
	tmpChar->InitCharacteristicValDefault();
	tmpChar->InitCharacteristicAugValDefault();
	tmpChar->AddSkill(SKILL_NUM::SKILL1, "slashOne");
	tmpChar->AddSkill(SKILL_NUM::SKILL2, "doubleSlash");
	tmpChar->AddSkill(SKILL_NUM::SKILL3, "roundSlash");
	tmpChar->AddSkill(SKILL_NUM::SKILL4, "slashUlti");

	//tmpChar->AddSkill(SKILL_NUM::SKILL1, "bossAtk1");
	//tmpChar->AddSkill(SKILL_NUM::SKILL2, "bossAtk2");
	//tmpChar->AddSkill(SKILL_NUM::SKILL3, "snatch");
	//tmpChar->AddSkill(SKILL_NUM::SKILL4, "bossBuff");

	_charMgr->AddCharacter(tmpChar);
	_UIMgr->AddChar(tmpChar);

	//	===	Caren ===
	Character* tmpChar2;
	tmpChar2 = _charMgr->MakeNewChara(CHAR_NAME::CAREN);

	tmpChar2->InitObjectiveValDefault({ 0,10 });
	tmpChar2->InitCharacteristicValDefault();
	tmpChar2->InitCharacteristicAugValDefault();
	tmpChar2->AddSkill(SKILL_NUM::SKILL1, "thunder");
	tmpChar2->AddSkill(SKILL_NUM::SKILL2, "flameBurst");
	tmpChar2->AddSkill(SKILL_NUM::SKILL3, "flameNova");
	tmpChar2->AddSkill(SKILL_NUM::SKILL4, "meteor");

	_charMgr->AddCharacter(tmpChar2);
	_UIMgr->AddChar(tmpChar2);

	//	=== Palm ===
	Character* tmpChar3;
	tmpChar3 = _charMgr->MakeNewChara(CHAR_NAME::PALM);

	tmpChar3->InitObjectiveValDefault({ 0,8 });
	tmpChar3->InitCharacteristicValDefault();
	tmpChar3->InitCharacteristicAugValDefault();
	tmpChar3->AddSkill(SKILL_NUM::SKILL1, "heal1");
	tmpChar3->AddSkill(SKILL_NUM::SKILL2, "heal2");
	tmpChar3->AddSkill(SKILL_NUM::SKILL3, "buff1");
	tmpChar3->AddSkill(SKILL_NUM::SKILL4, "resurrection");

	_charMgr->AddCharacter(tmpChar3);
	_UIMgr->AddChar(tmpChar3);


	//	=== 아군캐릭터들에게 주소보내줌 ===
	for (int i = 0; i < _charMgr->getVChara()->size(); i++) {
		_charMgr->TransAddrVCharaToChara(_charMgr->getVChara(), i);
	}


	//	=============적 추가 ===========
	/*
	enemy* tmpEnemy;
	tmpEnemy = _enemyMgr->MakeNewEnemy(ENEMY_NAME::MOB_SKEL);		//	뉴 떄리고, 링크걸고 리턴

	tmpEnemy->InitObjectiveValDefault({ 10,10 });
	tmpEnemy->InitCharacteristicValDefault();
	tmpEnemy->setHpBar(PointMake(0,-130));

	_enemyMgr->AddEnemy(tmpEnemy);
	*/


	//	===	Kaiser AI ====

	
	enemy* tmpKaiser;
	tmpKaiser = _enemyMgr->MakeNewEnemy(ENEMY_NAME::MOB_KAISER);

	tmpKaiser->InitObjectiveValDefault({ 24,10 });
	tmpKaiser->InitCharacteristicValDefault();
	tmpKaiser->setHpBar(PointMake(0, -130));
	tmpKaiser->setDir(E_DIR::DIR_LT);

	_enemyMgr->AddEnemy(tmpKaiser);
	



	SAFE_DELETE(_mapLoader);

	return S_OK;
}

void bossStage::release()
{
}

void bossStage::update()
{
	OPTIONMANAGER->update();
	if (OPTIONMANAGER->getIsOptionMode()) {
		_UIMgr->setPauseToTimeDelay(true);
	}


	if (!SOUNDMANAGER->isPlaySound("bossStageBGM")) {
		SOUNDMANAGER->play("bossStageBGM", OPTIONMANAGER->getRatioValue(OPTION_KINDS::BGM_VOLUME));
	}


	CAMERA2D->update();
	KEYANIMANAGER->update("buff1");
	KEYANIMANAGER->update("bossBuff");
	KEYANIMANAGER->update("leon");
	KEYANIMANAGER->update("caren");
	KEYANIMANAGER->update("palm");
	KEYANIMANAGER->update("skel");
	KEYANIMANAGER->update("kaiser");
	EFFECTMANAGER->update();
	SetClipRangeFunc();


	//	타임딜레이가 작동중이면,
	if (_UIMgr->_timeDelayUI != nullptr) {

		if (!_UIMgr->_timeDelayUI->getIsCharStop()) {
			_charMgr->update();
		}
		if (!_UIMgr->_timeDelayUI->getIsMobStop()) {
			_enemyMgr->update();
		}

	}
	//	타임딜레이가 작동중이 아니라면, 걍 다 업뎃
	else {
		_charMgr->update();
		_enemyMgr->update();
	}

	_charMgr->OrderUpdate();

	_UIMgr->update();


}

void bossStage::render()
{
	_bgImg->renderABS(0, 0, 1.0f);
	/*
	//	obj, enemy의 첫 렌더 인덱스 찾기. (vObj, vEnemy가 맵인덱스로  sort되어있음)
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;
			if (!isFoundObjStart) {
				for (int k = 0; k < _vObj.size(); k++) {
					if (_vObj[k]->_mapIdx.x == j && _vObj[k]->_mapIdx.y == i) {
						isFoundObjStart = true;
						objRenderCount = k;
						break;
					}
				}
			}
			if (!isFoundEnemyStart) {
				for (int k = 0; j < _vEnemy.size(); k++) {
					if (_vEnemy[k]->_mapIdx.x == j && _vEnemy[k]->_mapIdx.y == i) {
						isFoundEnemyStart = true;
						enemyRenderCount = k;
						break;
					}
				}
			}

		}
	}
	*/
	//	바닥타일 깔고,
	FloorTileRender();

	//	에너미, 캐릭터, 높이타일, obj 깔아줌
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;
			//D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);


			//	높이 타일
			ZTileRender(j, i);

			//	enemy
			_enemyMgr->render(j, i);


			//	player
			_charMgr->render(j, i);


			//	obj
			ObjRender(j, i);


		}
	}
	EFFECTMANAGER->render();


	//	astar테스트용 출력
	list<POINT>* tmpWaylistAddr = _charMgr->getWayListAddr(0);
	list<POINT>::iterator lIter;
	if (tmpWaylistAddr->size() != 0) {
		for (lIter = tmpWaylistAddr->begin();
			lIter != tmpWaylistAddr->end();
			lIter++) {

			D2DMANAGER->drawDiamondLine(0xFFFFFF,
				(_vvMap)[lIter->y][lIter->x]->_pos.x,
				(_vvMap)[lIter->y][lIter->x]->_pos.y,
				TILESIZE_WID,
				TILESIZE_HEI,
				3.0f
			);

		}
	}

	_UIMgr->render();

	//	캐릭터 정보 UI
	//_charMgr->RenderCharInfo();

	OPTIONMANAGER->render();

}

void bossStage::SetClipRangeFunc()
{
	_clipMapIdx[0] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[1] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[0].x -= CLIP_TILENUM_WID / 2;
	_clipMapIdx[0].y -= CLIP_TILENUM_HEI / 2;
	_clipMapIdx[1].x += CLIP_TILENUM_WID / 2;
	_clipMapIdx[1].y += CLIP_TILENUM_HEI / 2;
}


void bossStage::FloorTileRender()
{
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;
			D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);

			_vvMap[i][j]->_tileInfo.img->frameRender(_vvMap[i][j]->_pos.x - TILESIZE_WID / 2, _vvMap[i][j]->_pos.y - TILESIZE_HEI / 2,
				_vvMap[i][j]->_tileInfo.frameX, _vvMap[i][j]->_tileInfo.frameY, 1.0f);

		}
	}


}

void bossStage::ZTileRender(int idxX, int idxY)
{

	if (_vvMap[idxY][idxX]->_zLevel == 0) {
		return;
	}

	for (int i = _vvMap[idxY][idxX]->_zLevel; i >= 0; i--) {
		//if (i == 0) {
		//	_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
		//		_vvMap[idxY][idxX]->_frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
		//}
		if (i == 0) {
			_vvMap[idxY][idxX]->_tileInfo.img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
				_vvMap[idxY][idxX]->_tileInfo.frameX, _vvMap[idxY][idxX]->_tileInfo.frameY, 1.0f);
		}

		else if (i == 1) {
			_vvMap[idxY][idxX]->_tileInfo.img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
				_vvMap[idxY][idxX]->_tileInfo.frameX, 4, 1.0f);
		}
		else {
			_vvMap[idxY][idxX]->_tileInfo.img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
				_vvMap[idxY][idxX]->_tileInfo.frameX, 5, 1.0f);
		}


	}

}

void bossStage::PlayerRender(int idxX, int idxY)
{
	_charMgr->render(idxX, idxY);
}

void bossStage::EnemyRender(int idxX, int idxY, int& enemyCount)
{
	_enemyMgr->render(idxX, idxY);


	//	애니들어가야함
	//if (enemyCount < _vEnemy.size()) {
	//	while (_vEnemy[enemyCount]->_mapIdx.x == idxX && _vEnemy[enemyCount]->_mapIdx.y == idxY) {
	//		_vEnemy[enemyCount]->_sampleImg->render(
	//			_vEnemy[enemyCount]->_rc.left,
	//			_vEnemy[enemyCount]->_rc.top,
	//			_vEnemy[enemyCount]->_sampleRc.left,
	//			_vEnemy[enemyCount]->_sampleRc.top,
	//			_vEnemy[enemyCount]->getWid(),
	//			_vEnemy[enemyCount]->getHei(),
	//			1.0f
	//		);
	//
	//		enemyCount++;
	//		if (enemyCount >= _vEnemy.size())		break;
	//	}
	//}
}

void bossStage::ObjRender(int idxX, int idxY)
{
	if (_vvMap[idxY][idxX]->_objInfo.img != nullptr) {
		_vvMap[idxY][idxX]->_objInfo.img->render(
			_vvMap[idxY][idxX]->_objInfo.rc.left,
			_vvMap[idxY][idxX]->_objInfo.rc.top,
			_vvMap[idxY][idxX]->_objInfo.sampleRc.left,
			_vvMap[idxY][idxX]->_objInfo.sampleRc.top,
			_vvMap[idxY][idxX]->_objInfo.getWid(),
			_vvMap[idxY][idxX]->_objInfo.getHei(),
			1.0f);
	}



}


