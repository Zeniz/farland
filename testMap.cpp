#include "stdafx.h"
#include "testMap.h"




testMap::testMap()
{
}


testMap::~testMap()
{
}

HRESULT testMap::init()
{
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::PLAYER_CAMERA);
	CAMERA2D->setState(cameraState::PLAYER_CAMERA);

	_mapLoader = new mapLoader;
	_mapLoader->LoadMap(10, &_vvMap, &_tileNum, &_vObj, &_vEnemy);

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

	_selectedUI = UI_KINDS::UI_KINDS_NONE;
	_selectedUI |= UI_KINDS::MASK_TILE;
	_selectedUI |= UI_KINDS::CHARINFO;

	_UIMgr->setSelectUI(_selectedUI);


	//	============캐릭터 추가=======

	Character* tmpChar;
	tmpChar = _charMgr->MakeNewChara(CHAR_NAME::LEON);		//	뉴떄려줌, 링크걸고 리턴

	tmpChar->InitObjectiveValDefault({ 0,0 });
	tmpChar->InitCharacteristicValDefault();
	tmpChar->InitCharacteristicAugValDefault();
	
	_charMgr->AddCharacter(tmpChar);
	_UIMgr->AddChar(tmpChar);
	
	
	//	=============적 추가 ===========
	
	enemy* tmpEnemy;
	tmpEnemy = _enemyMgr->MakeNewEnemy(E_IMGNUM::MOB_SKEL);		//	뉴 떄리고, 링크걸고 리턴
	
	tmpEnemy->InitObjectiveValDefault({ 10,10 });
	tmpEnemy->InitCharacteristicValDefault();

	_enemyMgr->AddEnemy(tmpEnemy);
	

	SAFE_DELETE(_mapLoader);

	return S_OK;
}

void testMap::release()
{
}

void testMap::update()
{
	CAMERA2D->update();
	KEYANIMANAGER->update("leon");
	KEYANIMANAGER->update("skel");
	SetClipRangeFunc();

	_charMgr->update();
	_enemyMgr->update();


	_UIMgr->update();

	//_maskTile->update();
}

void testMap::render()
{
	int objRenderCount = 0;
	int enemyRenderCount = 0;
	bool isFoundObjStart = false;
	bool isFoundEnemyStart = false;

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
			
			EnemyRender(j, i, enemyRenderCount);
			
			//	player
			_charMgr->render(j, i);
			

			

			//	obj
			ObjRender(j, i, objRenderCount);


		}
	}

	
	//_maskTile->render();

	//	astar테스트용 출력
	list<POINT>* tmpWaylistAddr = _charMgr->getWayListAddr(0);
	list<POINT>::iterator lIter;
	if (tmpWaylistAddr->size() !=0) {
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


}

void testMap::SetClipRangeFunc()
{
	_clipMapIdx[0] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[1] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[0].x -= CLIP_TILENUM_WID / 2;
	_clipMapIdx[0].y -= CLIP_TILENUM_HEI / 2;
	_clipMapIdx[1].x += CLIP_TILENUM_WID / 2;
	_clipMapIdx[1].y += CLIP_TILENUM_HEI / 2;
}


void testMap::FloorTileRender()
{
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;
			D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);
			
			_vvMap[i][j]->_img->frameRender(_vvMap[i][j]->_pos.x - TILESIZE_WID / 2, _vvMap[i][j]->_pos.y - TILESIZE_HEI / 2,
				_vvMap[i][j]->_frameX, _vvMap[i][j]->_frameY, 1.0f);
			
		}
	}
			

}

void testMap::ZTileRender(int idxX, int idxY)
{
	if (_vvMap[idxY][idxX]->_img != nullptr) {
		//	추가됨
		if (_vvMap[idxY][idxX]->_zLevel == 0) {
			return;
		}

		for (int i = _vvMap[idxY][idxX]->_zLevel; i >= 0; i--) {
			//if (i == 0) {
			//	_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
			//		_vvMap[idxY][idxX]->_frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
			//}
			if (i == 0) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
			}

			else if(i == 1) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, 4, 1.0f);
			}
			else {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, 5, 1.0f);
			}


		}
	}
}

void testMap::PlayerRender(int idxX, int idxY)
{
	_charMgr->render(idxX, idxY);
}

void testMap::EnemyRender(int idxX, int idxY, int& enemyCount)
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

void testMap::ObjRender(int idxX, int idxY, int& objCount)
{
	if (objCount < _vObj.size()) {
		while (_vObj[objCount]->_mapIdx.x == idxX && _vObj[objCount]->_mapIdx.y == idxY) {
			_vObj[objCount]->_img->render(
				_vObj[objCount]->_rc.left,
				_vObj[objCount]->_rc.top,
				_vObj[objCount]->_sampleRc.left,
				_vObj[objCount]->_sampleRc.top,
				_vObj[objCount]->_sampleRc.right - _vObj[objCount]->_sampleRc.left,
				_vObj[objCount]->_sampleRc.bottom - _vObj[objCount]->_sampleRc.top,
				1.0f
			);

			objCount++;

			if (objCount >= _vObj.size())		break;
		}
	}


	
}


