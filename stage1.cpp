#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{
}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::PLAYER_CAMERA);
	CAMERA2D->setState(cameraState::PLAYER_CAMERA);

	_mapLoader = new mapLoader;
	_mapLoader->LoadMap(10, &_vvMap, &_tileNum, &_vEnemy);

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

	// ============ ����� UI ���� ===========

	_selectedUI = UI_KINDS::UI_KINDS_NONE;
	_selectedUI |= UI_KINDS::MASK_TILE;
	_selectedUI |= UI_KINDS::CHARINFO;

	_UIMgr->setSelectUI(_selectedUI);


	//	============ĳ���� �߰�=======

	Character* tmpChar;
	tmpChar = _charMgr->MakeNewChara(CHAR_NAME::LEON);		//	��������, ��ũ�ɰ� ����

	tmpChar->InitObjectiveValDefault({ 0,0 });
	tmpChar->InitCharacteristicValDefault();
	tmpChar->InitCharacteristicAugValDefault();

	_charMgr->AddCharacter(tmpChar);
	_UIMgr->AddChar(tmpChar);


	//	=============�� �߰� ===========

	enemy* tmpEnemy;
	tmpEnemy = _enemyMgr->MakeNewEnemy(ENEMY_NAME::MOB_SKEL);		//	�� ������, ��ũ�ɰ� ����

	tmpEnemy->InitObjectiveValDefault({ 10,10 });
	tmpEnemy->InitCharacteristicValDefault();
	tmpEnemy->setHpBar(PointMake(0, -130));

	_enemyMgr->AddEnemy(tmpEnemy);


	SAFE_DELETE(_mapLoader);

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
{
	CAMERA2D->update();
	KEYANIMANAGER->update("leon");
	KEYANIMANAGER->update("skel");
	SetClipRangeFunc();

	_charMgr->update();
	_enemyMgr->update();


	_UIMgr->update();
}

void stage1::render()
{
	FloorTileRender();

	//	���ʹ�, ĳ����, ����Ÿ��, obj �����
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;
			//D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);


			//	���� Ÿ��
			ZTileRender(j, i);

			//	enemy
			_enemyMgr->render(j, i);


			//	player
			_charMgr->render(j, i);




			//	obj
			ObjRender(j, i);


		}
	}


	//_maskTile->render();

	//	astar�׽�Ʈ�� ���
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
}

void stage1::SetClipRangeFunc()
{
	_clipMapIdx[0] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[1] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[0].x -= CLIP_TILENUM_WID / 2;
	_clipMapIdx[0].y -= CLIP_TILENUM_HEI / 2;
	_clipMapIdx[1].x += CLIP_TILENUM_WID / 2;
	_clipMapIdx[1].y += CLIP_TILENUM_HEI / 2;
}

void stage1::FloorTileRender()
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

void stage1::ZTileRender(int idxX, int idxY)
{
	if (_vvMap[idxY][idxX]->_zLevel == 0) {
		return;
	}

	for (int i = _vvMap[idxY][idxX]->_zLevel; i >= 0; i--) {
		
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

void stage1::PlayerRender(int idxX, int idxY)
{
	_charMgr->render(idxX, idxY);
}

void stage1::EnemyRender(int idxX, int idxY, int & enemyCount)
{
	_enemyMgr->render(idxX, idxY);
}

void stage1::ObjRender(int idxX, int idxY)
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