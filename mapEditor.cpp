#include "stdafx.h"
#include "mapEditor.h"
#pragma warning(disable: 4996)

mapEditor::mapEditor()
{
	IMAGEMANAGER->addImage("frame", L"images/mapEditor/frame.png", 1600, 900);
	IMAGEMANAGER->addFrameImage("buttons", L"images/mapEditor/buttons.png", 320, 256, 2, 8);
	IMAGEMANAGER->addFrameImage("toolIcons", L"images/mapEditor/toolIcons.png", 128, 512, 2, 8);


	IMAGEMANAGER->addFrameImage("tile1", L"images/map/tileSample1.png", 896, 384, 7, 6);
	IMAGEMANAGER->addImage("objSample1", L"images/map/objSample1.png", 512, 544);
	IMAGEMANAGER->addImage("objSample2", L"images/map/objSample2.png", 1152, 544);
	IMAGEMANAGER->addImage("objSample3", L"images/map/objSample3.png", 512, 512);
	IMAGEMANAGER->addImage("objSample4", L"images/map/objSample4.png", 1024, 544);

	IMAGEMANAGER->addFrameImage("mobSprite", L"images/mapEditor/mobSprite.png", 144, 144, 1, 1);
	 

	InitTileSamples();
	InitObjSamples();
	InitMobSamples();

	//	카메라 설정
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);



	//_vSampleTerImg.clear();
	//_vSampleTerImg.push_back(IMAGEMANAGER->findImage("tile1"));		//	tileNode의 이넘순서에 맞게 pushBack

	_vMagicSelectList.clear();

	_tileNum.x = 20;
	_tileNum.y = 20;

	
	_vvMap.clear();
	_vObj.clear();
	_vObjInfo.clear();
	_vEnemy.clear();
	_vEnemyInfo.clear();

	for (int i = 0; i < _tileNum.y; i++) {
		vLine _vLine;
		_vLine.clear();
		_vLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->init();
			tmpTile->_pos = ConvertIdxToPosFloat(j, i, TILESIZE_WID, TILESIZE_HEI);
			tmpTile->_idx.x = j;
			tmpTile->_idx.y = i;
			tmpTile->_pickIdx = tmpTile->_idx;

			//tmpTile->_pos.x = WINSIZEX / 2 + ((j - i)*(TILESIZE_WID / 2));			//tmpPt.x = WINSIZEX / 2 - (i*(TILESIZE_WID / 2)) + (j*(TILESIZE_WID / 2));
			//tmpTile->_pos.y = TILESIZE_HEI / 2 + ((i + j) * (TILESIZE_HEI / 2));	//TILESIZE_HEI / 2 + (i * (TILESIZE_HEI / 2)) + (j * (TILESIZE_HEI/2));

			_vLine.push_back(tmpTile);
		}
		_vvMap.push_back(_vLine);
	}

	_frameImg = IMAGEMANAGER->findImage("frame");

	//	메뉴버튼
	for (int i = MENU_MAPIDX; i < MENU_END; i++) {
		//	버튼들
		_buttons[i].img = IMAGEMANAGER->findImage("buttons");
		_buttons[i].isOn = false;
		if (i < 6) {
			_buttons[i].rc = RectMake(i*_buttons[i].img->GetFrameWidth(), 0, _buttons[i].img->GetFrameWidth(), _buttons[i].img->GetFrameHeight());
		}
		else {
			_buttons[i].rc = RectMake(1072 + (i-6)*_buttons[i].img->GetFrameWidth(), 0, _buttons[i].img->GetFrameWidth(), _buttons[i].img->GetFrameHeight());
		}
		
		
		
	}
	//	툴
	for (int i = TOOL_CURSOR; i < TOOL_END; i++) {
		//	툴들
		_toolIcons[i].img = IMAGEMANAGER->findImage("toolIcons");
		_toolIcons[i].isOn = false;
		_toolIcons[i].rc = RectMake(0, 32 + i * _toolIcons[i].img->GetFrameHeight(), _toolIcons[i].img->GetFrameWidth(), _toolIcons[i].img->GetFrameHeight());
	}

	_mapIdx = 0;
	_areaIdx = 0;

	_selectedTool = E_TOOLS::TOOL_NONE;
	_selectedMenu = E_MENU::MENU_NONE;

	_cursorSelectIdx[0] = { -1,-1 };
	_cursorSelectIdx[1] = { -1,-1 };
	_cursorSelectIdxSorted[0] = { -1,-1 };
	_cursorSelectIdxSorted[1] = { -1,-1 };
	//_isLButtonDown = false;
	
	_mapTileRc = { 64,32,1408,900 };

	_isChoosingSample = false;
	_curTerSampleIdx = TERNUM_BASIC;
	_curObjSampleIdx = OBJNUM_BASIC;
	_curUnitSampleIdx = MOB_SKEL;
	_cursorTile = nullptr;
	_cursorObjInfo.init();
	_cursorUnitInfo.init();

	_ptMousePrePos = { -1,-1 };

	_resizeMapCounter = 0;
	_mapIdxAdjustCounter = 0;
	
	SetClipRangeFunc();

}


mapEditor::~mapEditor()
{
}

HRESULT mapEditor::init()
{
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);

	_vMagicSelectList.clear();

	_tileNum.x = 20;
	_tileNum.y = 20;

	_vvMap.clear();
	_vObj.clear();
	_vEnemy.clear();
	//_vObjInfo.clear();
	//_vEnemyInfo.clear();

	for (int i = 0; i < _tileNum.y; i++) {
		vLine _vLine;
		_vLine.clear();
		_vLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->init();
			tmpTile->_pos = ConvertIdxToPosFloat(j, i, TILESIZE_WID, TILESIZE_HEI);
			tmpTile->_idx.x = j;
			tmpTile->_idx.y = i;
			tmpTile->_pickIdx = tmpTile->_idx;

			//tmpTile->_pos.x = WINSIZEX / 2 + ((j - i)*(TILESIZE_WID / 2));	//tmpPt.x = WINSIZEX / 2 - (i*(TILESIZE_WID / 2)) + (j*(TILESIZE_WID / 2));
			//tmpTile->_pos.y = TILESIZE_HEI / 2 + ((i + j) * (TILESIZE_HEI / 2));	//TILESIZE_HEI / 2 + (i * (TILESIZE_HEI / 2)) + (j * (TILESIZE_HEI/2));


			_vLine.push_back(tmpTile);

		}
		_vvMap.push_back(_vLine);
	}

	_mapIdx = 0;
	_areaIdx = 0;
	_selectedTool = E_TOOLS::TOOL_NONE;
	_selectedMenu = E_MENU::MENU_NONE;

	_cursorSelectIdx[0] = { -1,-1 };
	_cursorSelectIdx[1] = { -1,-1 };
	_cursorSelectIdxSorted[0] = { -1,-1 };
	_cursorSelectIdxSorted[1] = { -1,-1 };
	//_isLButtonDown = false;
	
	_isChoosingSample = false;
	_curTerSampleIdx = TERNUM_BASIC;
	_curObjSampleIdx = OBJNUM_BASIC;
	_curUnitSampleIdx = MOB_SKEL;

	_cursorTile = nullptr;
	_cursorObjInfo.init();
	_cursorUnitInfo.init();

	_ptMousePrePos = { -1,-1 };

	_resizeMapCounter = 0;
	_mapIdxAdjustCounter = 0;

	SetClipRangeFunc();

	return S_OK;
}

HRESULT mapEditor::init(int tileNumX, int tileNumY)
{
	POINT tmpCamStartPos = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpCamStartPos, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);

	_vMagicSelectList.clear();

	_tileNum.x = tileNumX;
	_tileNum.y = tileNumY;

	_vvMap.clear();
	_vObj.clear();
	_vEnemy.clear();
	//_vObjInfo.clear();
	//_vEnemyInfo.clear();

	for (int i = 0; i < _tileNum.y; i++) {
		vLine _vLine;
		_vLine.clear();
		_vLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->init();
			tmpTile->_pos = ConvertIdxToPosFloat(j, i, TILESIZE_WID, TILESIZE_HEI);
			tmpTile->_idx.x = j;
			tmpTile->_idx.y = i;
			tmpTile->_pickIdx = tmpTile->_idx;
			
			_vLine.push_back(tmpTile);
		}
		_vvMap.push_back(_vLine);
	}

	_mapIdx = 0;
	_areaIdx = 0;
	_selectedTool = E_TOOLS::TOOL_NONE;
	_selectedMenu = E_MENU::MENU_NONE;

	_cursorSelectIdx[0] = { -1,-1 };
	_cursorSelectIdx[1] = { -1,-1 };
	_cursorSelectIdxSorted[0] = { -1,-1 };
	_cursorSelectIdxSorted[1] = { -1,-1 };
	//_isLButtonDown = false;

	_isChoosingSample = false;
	_curTerSampleIdx = TERNUM_BASIC;
	_curObjSampleIdx = OBJNUM_BASIC;
	_curUnitSampleIdx = MOB_SKEL;

	_cursorTile = nullptr;
	_cursorObjInfo.init();
	_cursorUnitInfo.init();

	_ptMousePrePos = { -1,-1 };

	_resizeMapCounter = 0;
	_mapIdxAdjustCounter = 0;

	SetClipRangeFunc();

	return S_OK;
}

void mapEditor::release()
{
}

void mapEditor::update()
{
	CAMERA2D->update();
	SetClipRangeFunc();

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		ClearInfoInCursor();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) {
		MakeHillFunc(+1);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2)) {
		MakeHillFunc(-1);
	}
	

	AdjustMapIdxFunc();
	ResizeMapFunc();

	SelectToolFunc();
	SelectMenuFunc();
	
	SwitchToolsFunc();
	SwitchMenusFunc();


}

void mapEditor::render()
{
	int objRenderCount = 0;
	int unitRenderCount = 0;
	//	통합 렌더

	//	클리핑
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;

			SortedRender(j, i, objRenderCount, unitRenderCount);
			//윤곽선그리기
			D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);

		}
	}

	//	non-클리핑
	//for (int i = 0; i < _tileNum.y; i++) {
	//	for (int j = 0; j < _tileNum.x; j++) {
	//		SortedRender(j,i, objRenderCount, unitRenderCount);
	//		//윤곽선그리기
	//		D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);
	//	}
	//}



	//	맵타일 
	//for (int i = 0; i < _tileNum.y; i++) {
	//	for (int j = 0; j < _tileNum.x; j++) {
	//		//윤곽선그리기
	//		D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);
	//		//	타일그림
	//		TileRender(j, i);
	//	}
	//}

	//	선택된 맵타일 윤곽선
	if (_cursorSelectIdxSorted[0].x != -1 && _cursorSelectIdxSorted[0].y != -1 &&
		_cursorSelectIdxSorted[1].x != -1 && _cursorSelectIdxSorted[1].y != -1) {
		for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
			for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
				D2DMANAGER->drawDiamondLine(0xFF0000, _vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 2);
				//	픽인덱스타일에 파랑테두리그리기
				PickIdxTileRender(j, i);
			}
		}
	}
	
	//	매직선택 윤곽선
	MagicSelectRender();

	////	오브젝트 렌더
	//ObjRender();
	//
	////	유닛 렌더
	//UnitRender();

	//	커서 미리보기 렌더
	PreviewRender();


	//	샘플 렌더
	if (_isChoosingSample) {
		SampleRender();
		
	}
	



	//	프레임 -> 마지막에 출력
	_frameImg->renderABS();
	for (int i = 0; i < MENU_END; i++) {
		_buttons[i].img->frameRenderABS(_buttons[i].rc.left, _buttons[i].rc.top, _buttons[i].isOn, i, 1.0f);
		
	}
	for (int i = 0; i < TOOL_END; i++) {
		_toolIcons[i].img->frameRenderABS(_toolIcons[i].rc.left, _toolIcons[i].rc.top, _toolIcons[i].isOn, i, 1.0f);
	}

	//	맵 인덱스
	WCHAR str[64];
	swprintf_s(str, L"%d", _mapIdx);
	D2DMANAGER->drawText(str, CAMERA2D->getCamPosX()+125, CAMERA2D->getCamPosY() ,30);


	//	커서가 잡고있는 타일
	CursorSampleRender();


	/*
	POINT idx;
	idx = ConvertPosToIdx(_ptMouse.x, _ptMouse.y,
		TILESIZE_WID, TILESIZE_HEI);
	wstring str = L"Idx : ";
	str += to_wstring(idx.x);
	str += L" ";
	str += to_wstring(idx.y);
	D2DMANAGER->drawText(str.c_str(), CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 100);

	wstring str2 = L"vvmap[0][0].pos";
	str2 += to_wstring(_vvMap[0][0]->_pos.x);
	str2 += L" ";
	str2 += to_wstring(_vvMap[0][0]->_pos.y);
	D2DMANAGER->drawText(str2.c_str(), CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY() + 200);
	*/

	

}

HRESULT mapEditor::InitTileSamples()
{
	//	terrain

	//	tile11
	for (int i = 0; i < IMAGEMANAGER->findImage("tile1")->GetMaxFrameY() + 1; i++) {
		vLine vLine;
		vLine.clear();
		for (int j = 0; j < IMAGEMANAGER->findImage("tile1")->GetMaxFrameX() + 1; j++) {
			TILE* tmpTile = new TILE;
			POINTFLOAT pos;
			RECT rc;

			pos = { (float)(SAMPLE_PALLET_START_X + TILESIZE_WID / 2 + j * TILESIZE_WID),
					(float)(SAMPLE_PALLET_START_Y + TILESIZE_HEI / 2 + i * TILESIZE_HEI) };
			rc = RectMakeCenter(pos.x, pos.y, TILESIZE_WID, TILESIZE_HEI);

			tmpTile->init(IMAGEMANAGER->findImage("tile1"), TERRAIN_ARRAY_NUM::TERNUM_BASIC,
				j, i, { NULL,NULL }, { NULL,NULL }, T_ATTRIBUTE::T_ATTR_NONE, pos, rc, 0);

			vLine.push_back(tmpTile);
		}
		_vvTerSamples[TERNUM_BASIC].push_back(vLine);
	}



	return S_OK;
}

HRESULT mapEditor::InitObjSamples()
{
	//	초기화
	for (int i = OBJNUM_BASIC; i < OBJNUM_END; i++) {
		for (int j = 0; j < 12; j++) {
			_objImgInfo[i][j].centerPosInImg.x = NULL;
			_objImgInfo[i][j].centerPosInImg.y = NULL;
			_objImgInfo[i][j].sampleRc = { NULL,NULL,NULL,NULL };
			_objImgInfo[i][j].objTileSize = { NULL,NULL };
			_objImgInfo[i][j].imgNum = OBJNUM_NONE;
			_objImgInfo[i][j].img = nullptr;
			_objImgInfo[i][j].zLvl = NULL;
			_objImgInfo[i][j].attr = O_ATTR_NONE;
		}
		
	}

	//	1페이지
	{
		for (int i = 0; i < 4; i++) {
			_objImgInfo[OBJNUM_BASIC][i].centerPosInImg.x = 66 + (i * 128);
			_objImgInfo[OBJNUM_BASIC][i].centerPosInImg.y = 246;
			_objImgInfo[OBJNUM_BASIC][i].sampleRc = RectMake(i * 128, 0, 128, 272);
			_objImgInfo[OBJNUM_BASIC][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_BASIC][i].imgNum = OBJNUM_BASIC;
			_objImgInfo[OBJNUM_BASIC][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_BASIC].c_str());
			_objImgInfo[OBJNUM_BASIC][i].zLvl = 2;
			_objImgInfo[OBJNUM_BASIC][i].attr = O_ATTR_UNMOVE;

		}
		for (int i = 4; i < 9; i++) {
			_objImgInfo[OBJNUM_BASIC][i].centerPosInImg.x = 50 + (i - 4) * 96;
			_objImgInfo[OBJNUM_BASIC][i].centerPosInImg.y = 400;
			_objImgInfo[OBJNUM_BASIC][i].sampleRc = RectMake((i - 4) * 96, 273, 96, 144);
			_objImgInfo[OBJNUM_BASIC][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_BASIC][i].imgNum = OBJNUM_BASIC;
			_objImgInfo[OBJNUM_BASIC][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_BASIC].c_str());
			_objImgInfo[OBJNUM_BASIC][i].zLvl = 2;
			_objImgInfo[OBJNUM_BASIC][i].attr = O_ATTR_UNMOVE;
		}
		for (int i = 9; i < 12; i++) {
			_objImgInfo[OBJNUM_BASIC][i].centerPosInImg.x = 64 + (i - 9) * 128;
			_objImgInfo[OBJNUM_BASIC][i].centerPosInImg.y = 512;
			_objImgInfo[OBJNUM_BASIC][i].sampleRc = RectMake((i - 9) * 128, 416, 128, 128);
			_objImgInfo[OBJNUM_BASIC][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_BASIC][i].imgNum = OBJNUM_BASIC;
			_objImgInfo[OBJNUM_BASIC][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_BASIC].c_str());
			_objImgInfo[OBJNUM_BASIC][i].zLvl = 2;
			_objImgInfo[OBJNUM_BASIC][i].attr = O_ATTR_UNMOVE;
		}
	}
	//	2페이지
	{
		_objImgInfo[OBJNUM_HOUSE][0].centerPosInImg.x = 256;
		_objImgInfo[OBJNUM_HOUSE][0].centerPosInImg.y = 544 - TILESIZE_HEI / 2;
		_objImgInfo[OBJNUM_HOUSE][0].sampleRc = RectMake(0, 0, 576, 544);
		_objImgInfo[OBJNUM_HOUSE][0].objTileSize = { 4,5 };
		_objImgInfo[OBJNUM_HOUSE][0].imgNum = OBJNUM_HOUSE;
		_objImgInfo[OBJNUM_HOUSE][0].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_HOUSE].c_str());
		_objImgInfo[OBJNUM_HOUSE][0].zLvl = 1;
		_objImgInfo[OBJNUM_HOUSE][0].attr = O_ATTR_UNMOVE;

		_objImgInfo[OBJNUM_HOUSE][1].centerPosInImg.x = 896;
		_objImgInfo[OBJNUM_HOUSE][1].centerPosInImg.y = 544 - TILESIZE_HEI / 2;
		_objImgInfo[OBJNUM_HOUSE][1].sampleRc = RectMake(576, 0, 576, 544);
		_objImgInfo[OBJNUM_HOUSE][1].objTileSize = { 5,4 };
		_objImgInfo[OBJNUM_HOUSE][1].imgNum = OBJNUM_HOUSE;
		_objImgInfo[OBJNUM_HOUSE][1].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_HOUSE].c_str());
		_objImgInfo[OBJNUM_HOUSE][1].zLvl = 1;
		_objImgInfo[OBJNUM_HOUSE][1].attr = O_ATTR_UNMOVE;
	}
	
	//	3페이지
	{
		for (int i = 0; i < 4; i++) {
			_objImgInfo[OBJNUM_COMB][i].centerPosInImg.x = 64 + (i * 128);
			_objImgInfo[OBJNUM_COMB][i].centerPosInImg.y = 160;
			_objImgInfo[OBJNUM_COMB][i].sampleRc = RectMake(0 + (i * 128), 0, 128, 192);
			_objImgInfo[OBJNUM_COMB][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_COMB][i].imgNum = OBJNUM_COMB;
			_objImgInfo[OBJNUM_COMB][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_COMB].c_str());
			_objImgInfo[OBJNUM_COMB][i].zLvl = 2;
			_objImgInfo[OBJNUM_COMB][i].attr = O_ATTR_UNMOVE;
		}
		for (int i = 4; i < 6; i++) {
			_objImgInfo[OBJNUM_COMB][i].centerPosInImg.x = 64 + ((i-4) * 128);
			_objImgInfo[OBJNUM_COMB][i].centerPosInImg.y = 352;
			_objImgInfo[OBJNUM_COMB][i].sampleRc = RectMake(0 + (i - 4) * 128, 192, 128, 192);
			_objImgInfo[OBJNUM_COMB][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_COMB][i].imgNum = OBJNUM_COMB;
			_objImgInfo[OBJNUM_COMB][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_COMB].c_str());
			_objImgInfo[OBJNUM_COMB][i].zLvl = 2;
			_objImgInfo[OBJNUM_COMB][i].attr = O_ATTR_UNMOVE; 
		} 
		//	풀떼기
		for (int i = 6; i < 10; i++) {
			_objImgInfo[OBJNUM_COMB][i].centerPosInImg.x = 64 + (i - 6) * 128;
			_objImgInfo[OBJNUM_COMB][i].centerPosInImg.y = 480;
			_objImgInfo[OBJNUM_COMB][i].sampleRc = RectMake(0 + (i - 6) * 128, 384, 128, 128);
			_objImgInfo[OBJNUM_COMB][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_COMB][i].imgNum = OBJNUM_COMB;
			_objImgInfo[OBJNUM_COMB][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_COMB].c_str());
			_objImgInfo[OBJNUM_COMB][i].zLvl = 2;
			_objImgInfo[OBJNUM_COMB][i].attr = O_ATTR_NONE;
		}
	}
	//	4페이지 - 크리스탈
	{
		for (int i = 0; i < 4; i++) {
			_objImgInfo[OBJNUM_CRYSTAL][i].centerPosInImg.x = 128 + (i * 256);
			_objImgInfo[OBJNUM_CRYSTAL][i].centerPosInImg.y = 304;
			_objImgInfo[OBJNUM_CRYSTAL][i].sampleRc = RectMake(0 + (i * 256), 0, 256, 336);
			_objImgInfo[OBJNUM_CRYSTAL][i].objTileSize = { 2,2 };
			_objImgInfo[OBJNUM_CRYSTAL][i].imgNum = OBJNUM_CRYSTAL;
			_objImgInfo[OBJNUM_CRYSTAL][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_CRYSTAL].c_str());
			_objImgInfo[OBJNUM_CRYSTAL][i].zLvl = 2;
			_objImgInfo[OBJNUM_CRYSTAL][i].attr = O_ATTR_UNMOVE;
		}
		for (int i = 4; i < 9; i++) {
			_objImgInfo[OBJNUM_CRYSTAL][i].centerPosInImg.x = 64 + (i - 4) * 128;
			_objImgInfo[OBJNUM_CRYSTAL][i].centerPosInImg.y = 512;
			_objImgInfo[OBJNUM_CRYSTAL][i].sampleRc = RectMake(0 + (i - 4) * 128, 337, 128, 208);
			_objImgInfo[OBJNUM_CRYSTAL][i].objTileSize = { 1,1 };
			_objImgInfo[OBJNUM_CRYSTAL][i].imgNum = OBJNUM_CRYSTAL;
			_objImgInfo[OBJNUM_CRYSTAL][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJNUM_CRYSTAL].c_str());
			_objImgInfo[OBJNUM_CRYSTAL][i].zLvl = 2;
			_objImgInfo[OBJNUM_CRYSTAL][i].attr = O_ATTR_UNMOVE;
		}
		
	}

	return S_OK;

}

HRESULT mapEditor::InitMobSamples()
{
	_enemyInfo[MOB_SKEL].tileCenterPosAtSprite.x = 64;
	_enemyInfo[MOB_SKEL].tileCenterPosAtSprite.y = 128;
	_enemyInfo[MOB_SKEL].imgNum = MOB_SKEL;
	_enemyInfo[MOB_SKEL].sampleImg = IMAGEMANAGER->findImage("mobSprite");
	_enemyInfo[MOB_SKEL].sampleRc = RectMake(0, 0,
		_enemyInfo[MOB_SKEL].sampleImg->GetFrameWidth(), _enemyInfo[MOB_SKEL].sampleImg->GetFrameHeight());

	_enemyInfo[MOB_SKEL].rc = RectMake(0, 0, 0, 0);	//	직접 찍을때 값 따로 넣어줌
	_enemyInfo[MOB_SKEL].mobTileSize = { 1,1 };

	_enemyInfo[MOB_SKEL].zLvl = 0;
	_enemyInfo[MOB_SKEL].mapIdx = { NULL,NULL };	//	직접 찍을때 값 따로 넣어줌
	

	return S_OK;
}

void mapEditor::SelectToolFunc()
{
	for (int i = E_TOOLS::TOOL_CURSOR; i < E_TOOLS::TOOL_END; i++) {

		if (PtInRect(&_toolIcons[i].rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				if(_selectedTool != -1)
					_toolIcons[_selectedTool].isOn = false;
				_selectedTool = i;
				_toolIcons[i].isOn = true;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('V')) {
		if(_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_CURSOR;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('B')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_BRUSH;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('W')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_MAGICBONG;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('I')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_SPOID;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('E')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_TILE_ERASER;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('R')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_OBJ_ERASER;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('G')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_PAINT;
		_toolIcons[_selectedTool].isOn = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('H')) {
		if (_selectedTool != -1)
			_toolIcons[_selectedTool].isOn = false;
		_selectedTool = TOOL_HAND;
		_toolIcons[_selectedTool].isOn = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) {
		_selectedTool = TOOL_HAND;
		_toolIcons[_selectedTool].isOn = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE)) {
		_toolIcons[TOOL_HAND].isOn = false;
		for (int i = 0; i < TOOL_END; i++) {
			if (_toolIcons[i].isOn) {
				_selectedTool = i;
				break;
			}
		}

	}

}

void mapEditor::SelectMenuFunc()
{
	for (int i = E_MENU::MENU_SAVE; i < E_MENU::MENU_END; i++) {
		if (i == MENU_MAPIDX || i == MENU_AREAIDX)	continue;
		if (PtInRect(&_buttons[i].rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//	전에 눌렸던 것은 일단 끄고,
				if (_selectedMenu != -1)
					_buttons[_selectedMenu].isOn = false;

				//	이전과 선택한 것이 같다면 -> 꺼버려라
				if (_selectedMenu == i) {
					if (_selectedMenu == MENU_TILE ||
						_selectedMenu == MENU_OBJ ||
						_selectedMenu == MENU_UNIT) {
						_isChoosingSample = false;
					}
					_selectedMenu = -1;
					_buttons[i].isOn = false;


				}
				//	이전과 다른것을 선택한 것이라면 -> 켜라
				else {
					_selectedMenu = i;
					_buttons[i].isOn = true;
					if (_selectedMenu == MENU_TILE ||
						_selectedMenu == MENU_OBJ ||
						_selectedMenu == MENU_UNIT) {
						_isChoosingSample = true;
					}
				}
			}
				
		}
	}
	if (KEYMANAGER->isOnceKeyDown('T')) {
		if (_selectedMenu != -1)
			_buttons[_selectedMenu].isOn = false;
		//	이전 것이 같은거였으면,
		if (_selectedMenu == MENU_TILE) {
			_selectedMenu = -1;
			//	위에서 이미 isOn = false
			_isChoosingSample = false;
			
		}
		//	이전 것이 다른거였으면,
		else {
			_selectedMenu = MENU_TILE;
			_buttons[_selectedMenu].isOn = true;
			_isChoosingSample = true;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('O')) {
		if (_selectedMenu != -1)
			_buttons[_selectedMenu].isOn = false;
		//	이전 것이 같은거였으면,
		if (_selectedMenu == MENU_OBJ) {
			_selectedMenu = -1;
			//	위에서 이미 isOn = false
			_isChoosingSample = false;

		}
		//	이전 것이 다른거였으면,
		else {
			_selectedMenu = MENU_OBJ;
			_buttons[_selectedMenu].isOn = true;
			_isChoosingSample = true;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('U')) {
		if (_selectedMenu != -1)
			_buttons[_selectedMenu].isOn = false;
		//	이전 것이 같은거였으면,
		if (_selectedMenu == MENU_UNIT) {
			_selectedMenu = -1;
			//	위에서 이미 isOn = false
			_isChoosingSample = false;

		}
		//	이전 것이 다른거였으면,
		else {
			_selectedMenu = MENU_UNIT;
			_buttons[_selectedMenu].isOn = true;
			_isChoosingSample = true;
		}
	}

}



void mapEditor::SwitchToolsFunc()
{
	if (!_isChoosingSample) {
		if (PtInRect(&_mapTileRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {

			switch (_selectedTool) {

			case TOOL_CURSOR:
				SelectMapTile();
				break;

			case TOOL_BRUSH:
				BrushTile();
				break;

			case TOOL_MAGICBONG:
				MagicSelect();
				break;

			case TOOL_SPOID:
				SpoidFunc();
				break;

			case TOOL_TILE_ERASER:
				EraseTile();
				break;
			case TOOL_OBJ_ERASER:
				EraseObj();
				break;
			case TOOL_PAINT:
				PaintFunc();
				break;

			case TOOL_HAND:
				HandFunc();
				break;


			}
		}
	}
	
}

void mapEditor::SwitchMenusFunc()
{
	switch (_selectedMenu) {
	
	case MENU_SAVE:
		SaveMapFunc();
		_selectedMenu = -1;
		_buttons[MENU_SAVE].isOn = false;

		break;
	case MENU_LOAD:
		LoadMapFunc();
		_selectedMenu = -1;
		_buttons[MENU_LOAD].isOn = false;

		break;
	case MENU_TILE:
		if (_isChoosingSample) {			//	필요없긴 함...
			TileSampleFunc();
		}
		

		break;
	case MENU_OBJ:
		if (_isChoosingSample) {			//	필요없긴 함..
			ObjSampleFunc();
		}

		break;
	case MENU_UNIT:
		UnitSampleFunc();

		break;
	case MENU_AREAMODE:


		break;

	}


}


void mapEditor::AdjustMapIdxFunc()
{
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6)) {
		_mapIdxAdjustCounter++;
		if (_mapIdxAdjustCounter > MAPIDX_COUNT_MAX) {
			_mapIdxAdjustCounter = 0;
			_mapIdx++;
		}
		
	}
	else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4)) {
		_mapIdxAdjustCounter++;
		if (_mapIdxAdjustCounter > MAPIDX_COUNT_MAX) {
			_mapIdxAdjustCounter = 0;
			if (_mapIdx > 0) {
				_mapIdx--;
			}
			
		}
	}
	
}

void mapEditor::ResizeMapFunc()
{
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD3)) {
		_resizeMapCounter++;
		if (_resizeMapCounter > RESIZE_MAP_COUNT_MAX) {
			_resizeMapCounter = 0;
			
			AddMapX();
			
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1)) {
		_resizeMapCounter++;
		if (_resizeMapCounter > RESIZE_MAP_COUNT_MAX) {
			_resizeMapCounter = 0;
			
			AddMapY();
			
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD7)) {
		_resizeMapCounter++;
		if (_resizeMapCounter > RESIZE_MAP_COUNT_MAX) {
			_resizeMapCounter = 0;
			if (_tileNum.x > 1) {
				
				EraseMapX();
				
			}
			
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_NUMPAD9)) {
		_resizeMapCounter++;
		if (_resizeMapCounter > RESIZE_MAP_COUNT_MAX) {
			_resizeMapCounter = 0;
			if (_tileNum.y > 1) {
				
				EraseMapY();
				
			}
			
		}
	}
}



void mapEditor::AddMapX()
{
	_tileNum.x++;
	for (int i = 0; i < _tileNum.y; i++) {
		TILE* tmpTile = new TILE;
		tmpTile->init();
		tmpTile->_idx.x = _tileNum.x - 1;
		tmpTile->_idx.y = i;
		tmpTile->_pickIdx = tmpTile->_idx;
		tmpTile->_pos = ConvertIdxToPosFloat(tmpTile->_idx.x, tmpTile->_idx.y, TILESIZE_WID, TILESIZE_HEI);

		_vvMap[i].push_back(tmpTile);
	}
}

void mapEditor::AddMapY()
{
	_tileNum.y++;

	vLine tmpLine;
	tmpLine.clear();

	for (int i = 0; i < _tileNum.x; i++) {
		TILE* tmpTile = new TILE;
		tmpTile->init();
		tmpTile->_idx.x = i;
		tmpTile->_idx.y = _tileNum.y - 1;
		tmpTile->_pickIdx = tmpTile->_idx;
		tmpTile->_pos = ConvertIdxToPosFloat(tmpTile->_idx.x, tmpTile->_idx.y, TILESIZE_WID, TILESIZE_HEI);

		tmpLine.push_back(tmpTile);
	}
	_vvMap.push_back(tmpLine);
}

void mapEditor::EraseMapX()
{
	_tileNum.x--;
	for (int i = 0; i < _tileNum.y; i++) {
		SAFE_DELETE(_vvMap[i][_tileNum.x]);
		_vvMap[i].pop_back();
	}
	
}

void mapEditor::EraseMapY()
{
	_tileNum.y--;
	for (int i = 0; i < _tileNum.x; i++) {
		SAFE_DELETE(_vvMap[_tileNum.y][i]);
	}
	_vvMap.pop_back();
}

void mapEditor::ClearInfoInCursor()
{
	_cursorTile = nullptr;
	_cursorSelectIdx[0].x = -1;
	_cursorSelectIdx[0].y = -1;
	_cursorSelectIdx[1].x = -1;
	_cursorSelectIdx[1].y = -1;
	_vMagicSelectList.clear();
	_cursorObjInfo.init();
	_cursorUnitInfo.init();
}

void mapEditor::SetClipRangeFunc()
{
	_clipMapIdx[0] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[1] = ConvertPosToIdx(CAMERA2D->getCamPosX() + WINSIZEX / 2, CAMERA2D->getCamPosY() + WINSIZEY / 2, TILESIZE_WID, TILESIZE_HEI);
	_clipMapIdx[0].x -= CLIP_TILENUM_WID / 2;
	_clipMapIdx[0].y -= CLIP_TILENUM_HEI / 2;
	_clipMapIdx[1].x += CLIP_TILENUM_WID / 2;
	_clipMapIdx[1].y += CLIP_TILENUM_HEI / 2;
}



void mapEditor::SelectMapTile()
{
	//for (int i = 0; i < _tileNum.y; i++) {
	//	for (int j = 0; j < _tileNum.x; j++) {
	//	클리핑
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;


			POINTF pt;
			pt.x = _ptMouseAbs.x - CAMERA2D->getCamPosX();
			pt.y = _ptMouseAbs.y - CAMERA2D->getCamPosY();
			if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_vMagicSelectList.clear();
					_cursorSelectIdx[0] = { j,i };
					_cursorSelectIdx[1] = { j,i };
				}
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					_cursorSelectIdx[1] = { j,i };
				}


				if (_cursorSelectIdx[0].x > _cursorSelectIdx[1].x) {
					_cursorSelectIdxSorted[0].x = _cursorSelectIdx[1].x;
					_cursorSelectIdxSorted[1].x = _cursorSelectIdx[0].x;
				}
				else {
					_cursorSelectIdxSorted[0].x = _cursorSelectIdx[0].x;
					_cursorSelectIdxSorted[1].x = _cursorSelectIdx[1].x;
				}
				if (_cursorSelectIdx[0].y > _cursorSelectIdx[1].y) {
					_cursorSelectIdxSorted[0].y = _cursorSelectIdx[1].y;
					_cursorSelectIdxSorted[1].y = _cursorSelectIdx[0].y;
				}
				else {
					_cursorSelectIdxSorted[0].y = _cursorSelectIdx[0].y;
					_cursorSelectIdxSorted[1].y = _cursorSelectIdx[1].y;
				}

			}
		}
	}
}

void mapEditor::BrushTile()
{
	if (_cursorTile != nullptr) {

		//for (int i = 0; i < _tileNum.y; i++) {
		//	for (int j = 0; j < _tileNum.x; j++) {

		//	클리핑
		for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
			for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
				if (i < 0)				continue;
				if (i > _tileNum.y - 1)	continue;
				if (j < 0)				continue;
				if (j > _tileNum.x - 1)	continue;

				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						//_vvMap[i][j] = _cursorTile;
						TransTileValue(_cursorTile, _vvMap[i][j]);

						return;
					}
				}
			}
		}
	}
	else if (_cursorObjInfo.img != nullptr) {
		for (int i = 0; i < _tileNum.y; i++) {
			for (int j = 0; j < _tileNum.x; j++) {
				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						//_vvMap[i][j] = _cursorTile;
						MakeObjOnMap(_cursorObjInfo, j, i);

						return;
					}
				}
			}
		}
	}
	else if (_cursorUnitInfo.sampleImg != nullptr) {
		for (int i = 0; i < _tileNum.y; i++) {
			for (int j = 0; j < _tileNum.x; j++) {
				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						//_vvMap[i][j] = _cursorTile;
						MakeUnitOnMap(_cursorUnitInfo, j, i);

						return;
					}
				}
			}
		}
	}

}

void mapEditor::MagicSelect()
{

	//for (int i = 0; i < _tileNum.y; i++) {
	//	for (int j = 0; j < _tileNum.x; j++) {
	//	클리핑
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;

			if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_vMagicSelectList.clear();
					_cursorSelectIdx[0] = { -1,-1 };
					_cursorSelectIdx[1] = { -1,-1 };
					_cursorSelectIdxSorted[0] = { -1,-1 };
					_cursorSelectIdxSorted[0] = { -1,-1 };
					TILE* stdTile = _vvMap[i][j];
					for (int ii = 0; ii < _tileNum.y; ii++) {
						for (int jj = 0; jj < _tileNum.x; jj++) {
							if (IsSameTile(stdTile, _vvMap[ii][jj])) {
								_vMagicSelectList.push_back(PointMake(jj, ii));
							}
						}
					}
					return;
				}
			}
		}
	}
}

void mapEditor::SpoidFunc()
{
	//for (int i = 0; i < _tileNum.y; i++) {
	//	for (int j = 0; j < _tileNum.x; j++) {

	//	클리핑
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;

			if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					if (_vvMap[i][j]->_terImgNum != TERNUM_NONE) {
						TransTileValue(_vvMap[i][j], _cursorTile);
					}
					return;
				}
			}
		}
	}
}

void mapEditor::EraseTile()
{
	TILE nullTile;
	nullTile.init();
	
	//	커서로 구역 잡았을때,
	if (_cursorSelectIdx[0].x != -1) {
		for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
			for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						for (int ii = _cursorSelectIdxSorted[0].y; ii <= _cursorSelectIdxSorted[1].y; ii++) {
							for (int jj = _cursorSelectIdxSorted[0].x; jj <= _cursorSelectIdxSorted[1].x; jj++) {

								TransTileValue(&nullTile, _vvMap[ii][jj]);

							}
						}
						return;
					}
				}
			}
		}
	}
	//	마술봉으로 잡았을 때
	else if (_vMagicSelectList.size() != 0) {
		for (int i = 0; i < _vMagicSelectList.size(); i++) {
			POINT idx = _vMagicSelectList[i];
			if (PtInDiamond(_vvMap[idx.y][idx.x]->_pos, _ptMouse)) {
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					for (int j = 0; j < _vMagicSelectList.size(); j++) {
						POINT id = _vMagicSelectList[j];
						TransTileValue(&nullTile, _vvMap[id.y][id.x]);
					}
					return;
				}
			}
		}
	}
	
	//	범위가 없을 때.
	else {

		//for (int i = 0; i < _tileNum.y; i++) {
		//	for (int j = 0; j < _tileNum.x; j++) {

		//	클리핑
		for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
			for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
				if (i < 0)				continue;
				if (i > _tileNum.y - 1)	continue;
				if (j < 0)				continue;
				if (j > _tileNum.x - 1)	continue;

				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {

						TransTileValue(&nullTile, _vvMap[i][j]);
						return;
					}
				}
			}
		}
	}
	

}

void mapEditor::EraseObj()
{

	//	커서로 구역 잡았을때,
	if (_cursorSelectIdx[0].x != -1) {
		for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
			for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						for (int ii = _cursorSelectIdxSorted[0].y; ii <= _cursorSelectIdxSorted[1].y; ii++) {
							for (int jj = _cursorSelectIdxSorted[0].x; jj <= _cursorSelectIdxSorted[1].x; jj++) {

								//	오브젝트 삭제
								for (int k = 0; k < _vObj.size(); ) {
									if (_vObj[k]->_mapIdx.x == jj && _vObj[k]->_mapIdx.y == ii) {
										SAFE_DELETE(_vObj[k]);
										_vObj.erase(_vObj.begin() + k);
										_vvMap[ii][jj]->_terAttr = T_ATTR_NONE;
									}
									else {
										k++;
									}
								}
								//	몹 삭제
								for (int k = 0; k < _vEnemy.size(); ) {
									if (_vEnemy[k]->_mapIdx.x == jj && _vEnemy[k]->_mapIdx.y == ii) {
										SAFE_DELETE(_vEnemy[k]);
										_vEnemy.erase(_vEnemy.begin() + k);
										//_vvMap[ii][jj]->_terAttr = T_ATTR_NONE;
									}
									else {
										k++;
									}
								}


								//for (int k = 0; k < _vObjInfo.size(); ) {
								//	if (_vObjInfo[k]->mapIdx.x == jj && _vObjInfo[k]->mapIdx.y == ii) {
								//		SAFE_DELETE(_vObjInfo[k]);
								//		_vObjInfo.erase(_vObjInfo.begin() + k);
								//		_vvMap[ii][jj]->_terAttr = T_ATTR_NONE;
								//	}
								//	else {
								//		k++;
								//	}
								//}

							}
						}
						return;
					}
				}
			}
		}
	}
	//	마술봉으로 잡았을 때
	else if (_vMagicSelectList.size() != 0) {
		for (int i = 0; i < _vMagicSelectList.size(); i++) {
			POINT idx = _vMagicSelectList[i];
			if (PtInDiamond(_vvMap[idx.y][idx.x]->_pos, _ptMouse)) {
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					for (int j = 0; j < _vMagicSelectList.size(); j++) {
						POINT id = _vMagicSelectList[j];

						//	오브젝 삭제
						for (int k = 0; k < _vObj.size(); k++) {
							if (_vObj[k]->_mapIdx.x == id.x && _vObj[k]->_mapIdx.y == id.y) {
								SAFE_DELETE(_vObj[k]);
								_vObj.erase(_vObj.begin() + k);
								_vvMap[id.y][id.x]->_terAttr = T_ATTR_NONE;
							}
							else {
								k++;
							}
						}


						//	몹 삭제
						for (int k = 0; k < _vObj.size(); k++) {
							if (_vEnemy[k]->_mapIdx.x == id.x && _vEnemy[k]->_mapIdx.y == id.y) {
								SAFE_DELETE(_vEnemy[k]);
								_vEnemy.erase(_vEnemy.begin() + k);
								//_vvMap[id.y][id.x]->_terAttr = T_ATTR_NONE;
							}
							else {
								k++;
							}
						}

						//for (int k = 0; k < _vObjInfo.size(); k++) {
						//	if (_vObjInfo[k]->mapIdx.x == id.x && _vObjInfo[k]->mapIdx.y == id.y) {
						//		SAFE_DELETE(_vObjInfo[k]);
						//		_vObjInfo.erase(_vObjInfo.begin() + k);
						//		_vvMap[id.y][id.x]->_terAttr = T_ATTR_NONE;
						//	}
						//	else {
						//		k++;
						//	}
						//}


					}
					return;
				}
			}
		}
	}

	//	범위가 없을 때.
	else {
		//for (int i = 0; i < _tileNum.y; i++) {
		//	for (int j = 0; j < _tileNum.x; j++) {
		
		//	클리핑
		for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
			for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
				if (i < 0)				continue;
				if (i > _tileNum.y - 1)	continue;
				if (j < 0)				continue;
				if (j > _tileNum.x - 1)	continue;

				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {

						//	obj 삭제
						for (int k = 0; k < _vObj.size(); k++) {
							if (_vObj[k]->_mapIdx.x == j && _vObj[k]->_mapIdx.y == i) {
								SAFE_DELETE(_vObj[k]);
								_vObj.erase(_vObj.begin() + k);
								_vvMap[i][j]->_terAttr = T_ATTR_NONE;
								return;		//	1개만 지울거니까, 지우고 리턴해도됨
							}
							else {
								k++;
							}
						}

						//	몹 삭제
						for (int k = 0; k < _vEnemy.size(); k++) {
							if (_vEnemy[k]->_mapIdx.x == j && _vEnemy[k]->_mapIdx.y == i) {
								SAFE_DELETE(_vEnemy[k]);
								_vEnemy.erase(_vEnemy.begin() + k);
								//_vvMap[i][j]->_terAttr = T_ATTR_NONE;
								return;		//	위에서 오브젝 삭제하고 리턴함 ㅠㅠ 유닛 이레이저를 만들던가..범위잡아서 지우든가 ㅇㅇ..
							}
							else {
								k++;
							}
						}

						//for (int k = 0; k < _vObjInfo.size(); k++) {
						//	if (_vObjInfo[k]->mapIdx.x == j && _vObjInfo[k]->mapIdx.y == i) {
						//		SAFE_DELETE(_vObjInfo[k]);
						//		_vObjInfo.erase(_vObjInfo.begin() + k);
						//		_vvMap[i][j]->_terAttr = T_ATTR_NONE;
						//		return;		//	1개만 지울거니까, 지우고 리턴해도됨
						//	}
						//	else {
						//		k++;
						//	}
						//}


					}
				}
			}
		}
	}


}

void mapEditor::PaintFunc()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		//	타일일떄,
		if (_cursorTile != nullptr) {
			if (_cursorSelectIdxSorted[0].x != -1) {
				for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
					for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
						TransTileValue(_cursorTile, _vvMap[i][j]);
					}
				}
				return;
			}
			else if (_vMagicSelectList.size() != 0) {
				for (int i = 0; i < _vMagicSelectList.size(); i++) {
					POINT idx = _vMagicSelectList[i];
					TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
				}
				return;
			}
		}
		//	오브젝일떄,
		else if (_cursorObjInfo.img != nullptr) {
			if (_cursorSelectIdxSorted[0].x != -1) {
				for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
					for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
						//TransTileValue(_cursorTile, _vvMap[i][j]);
						MakeObjOnMap(_cursorObjInfo, j, i);
					}
				}
				return;
			}
			else if (_vMagicSelectList.size() != 0) {
				for (int i = 0; i < _vMagicSelectList.size(); i++) {
					POINT idx = _vMagicSelectList[i];
					//TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
					MakeObjOnMap(_cursorObjInfo, idx.x, idx.y);

				}
				return;
			}
		}
		else if (_cursorUnitInfo.sampleImg != nullptr) {
			if (_cursorSelectIdxSorted[0].x != -1) {
				for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
					for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
						//TransTileValue(_cursorTile, _vvMap[i][j]);
						MakeUnitOnMap(_cursorUnitInfo, j, i);
					}
				}
				return;
			}
			else if (_vMagicSelectList.size() != 0) {
				for (int i = 0; i < _vMagicSelectList.size(); i++) {
					POINT idx = _vMagicSelectList[i];
					//TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
					MakeUnitOnMap(_cursorUnitInfo, idx.x, idx.y);

				}
				return;
			}
		}
		
	}
	
}

void mapEditor::HandFunc()
{

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		

		POINT newFocus = PointMake(
			CAMERA2D->getCamPosX() - (int)(_ptMouseAbs.x - _ptMousePrePos.x),
			CAMERA2D->getCamPosY() - (int)(_ptMouseAbs.y - _ptMousePrePos.y));
		CAMERA2D->setFocusOn(newFocus, cameraState::EVENT_CAMERA);
		

	}
	_ptMousePrePos = _ptMouseAbs;
}

void mapEditor::MakeHillFunc(int augZlvl)
{
	//	커서로 구역설정시,
	if (_cursorSelectIdx[0].x != -1) {
		for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
			for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
				if (_vvMap[i][j]->_img == nullptr)	continue;
				if (_vvMap[i][j]->_zLevel + augZlvl >= 0) {
					_vvMap[i][j]->_zLevel += augZlvl;
					AdjustHillToObj(j, i, augZlvl);		//	오브젝트도 위치이동!(pos,rc)
					AdjustHillToEnemy(j, i, augZlvl);		//	Enemy도 위치이동!(pos,rc)

				}

				//	높아져서 덮어진부분 pickIdx로 픽 설정해준다.
				if (_vvMap[i][j]->_zLevel % 2 == 0) {						//	2lvl마다,
					for (int k = 0; k < _vvMap[i][j]->_zLevel / 2; k++) {
						if (i - (k + 1) < 0 || j - (k + 1) < 0)	continue;
						_vvMap[i - (k + 1)][j - (k + 1)]->_pickIdx = { j,i };
					}
				}
				//	낮아질때, pickIdx 초기화해준다.
				else if (_vvMap[i][j]->_zLevel % 2 == 1) {
					
					POINT overedTileIdx;		//	<- 덮여진 타일의 맨 위 인덱스
							//내리는타일인덱스 - zlvl/2 보다 한칸씩 위 <ex> z = 3 -> 위로 한칸하고 반 먹고있음, 즉 2칸위는 무효화해줘야함
					overedTileIdx.y = i - (int)(_vvMap[i][j]->_zLevel / 2);
					overedTileIdx.x = j - (int)(_vvMap[i][j]->_zLevel / 2);

					if (overedTileIdx.y - 1 >= 0 && overedTileIdx.x - 1 >= 0) {
						//	고유타일인덱스로 돌아가라.
						_vvMap[overedTileIdx.y - 1][overedTileIdx.x - 1]->_pickIdx = { overedTileIdx.x - 1, overedTileIdx.y - 1 };
					}

				}
				
			}
		}
	}
	//	마술봉으로 구역설정시,
	else if (_vMagicSelectList.size() != 0) {
		for (int i = 0; i < _vMagicSelectList.size(); i++) {
			POINT idx = _vMagicSelectList[i];
			if (_vvMap[idx.y][idx.x]->_img == nullptr)	 continue;
			if (_vvMap[idx.y][idx.x]->_zLevel + augZlvl > 0) {
				_vvMap[idx.y][idx.x]->_zLevel += augZlvl;
				AdjustHillToObj(idx.x, idx.y, augZlvl);
				AdjustHillToEnemy(idx.x, idx.y, augZlvl);		//	Enemy도 위치이동!(pos,rc)
			}
			//	높아져서 덮어진부분 pickIdx로 픽 설정해준다.
			if (_vvMap[idx.y][idx.x]->_zLevel % 2 == 0) {
				for (int k = 0; k < _vvMap[idx.y][idx.x]->_zLevel / 2; k++) {
					if (idx.y - (k + 1) < 0 || idx.x - (k + 1) < 0)	continue;
					_vvMap[idx.y - (k + 1)][idx.x - (k + 1)]->_pickIdx = { idx.x,idx.y };
				}
			}


		}
	}
}

void mapEditor::AdjustHillToObj(int idxX, int idxY, int augHeiLvl)
{
	for (int i = 0; i < _vObj.size(); i++) {
		if (_vObj[i]->_mapIdx.x == idxX &&
			_vObj[i]->_mapIdx.y == idxY) {

			_vObj[i]->_pos.y -= (TILESIZE_HEI / 2) * augHeiLvl;
			_vObj[i]->_rc.top -= (TILESIZE_HEI / 2) * augHeiLvl;
			_vObj[i]->_rc.bottom -= (TILESIZE_HEI / 2) * augHeiLvl;
		}
	}

	//for (int i = 0; i < _vObjInfo.size(); i++) {
	//	if (_vObjInfo[i]->mapIdx.x == idxX &&
	//		_vObjInfo[i]->mapIdx.y == idxY) {
	//
	//		//_vObjInfo[i]->zLvl += augHeiLvl;		//	계산안함. zlvl은 별도로 처리
	//
	//		_vObjInfo[i]->pos.y -= (TILESIZE_HEI / 2) * augHeiLvl;
	//		_vObjInfo[i]->rc.top -= (TILESIZE_HEI / 2) * augHeiLvl;
	//		_vObjInfo[i]->rc.bottom -= (TILESIZE_HEI / 2) * augHeiLvl;
	//	}
	//}

}

void mapEditor::AdjustHillToEnemy(int idxX, int idxY, int augHeiLvl)
{
	for (int i = 0; i < _vEnemy.size(); i++) {
		if (_vEnemy[i]->_mapIdx.x == idxX &&
			_vEnemy[i]->_mapIdx.y == idxY) {

			_vEnemy[i]->_pos.y -= (TILESIZE_HEI / 2) * augHeiLvl;
			_vEnemy[i]->_rc.top -= (TILESIZE_HEI / 2) * augHeiLvl;
			_vEnemy[i]->_rc.bottom -= (TILESIZE_HEI / 2) * augHeiLvl;
		}
	}

	//for (int i = 0; i < _vEnemyInfo.size(); i++) {
	//	if (_vEnemyInfo[i]->mapIdx.x == idxX &&
	//		_vEnemyInfo[i]->mapIdx.y == idxY) {
	//
	//		
	//
	//		_vEnemyInfo[i]->pos.y -= (TILESIZE_HEI / 2) * augHeiLvl;
	//		_vEnemyInfo[i]->rc.top -= (TILESIZE_HEI / 2) * augHeiLvl;
	//		_vEnemyInfo[i]->rc.bottom -= (TILESIZE_HEI / 2) * augHeiLvl;
	//	}
	//}

}


void mapEditor::SaveMapFunc()
{

	//HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData;
	//DWORD writeForMapSize, writeForMapData , writeForObjSize, writeForObjData;


	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForEnemy[20] = "enemyData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForObjSize[20] = "objSize";
	char fileNameForEnemySize[20] = "enemySize";
	

	char idxBuffer[5] = {};		//	맵 인덱스 저장소
	char mapSizeStr[20] = {};		//	맵 크기 str저장소
	char objSizeStr[20] = {};
	char enemySizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa임시 저장소
	char objNumBuffer[10] = {};		//	itoa임시 저장소
	char enemyNumBuffer[10] = {};		//	itoa임시 저장소

	//	파일이름 생성
	itoa(_mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");

	strcat_s(fileNameForObjSize, sizeof(fileNameForObjSize), idxBuffer);
	strcat_s(fileNameForObjSize, sizeof(fileNameForObjSize), ".map");
	strcat_s(fileNameForObj, sizeof(fileNameForObj), idxBuffer);
	strcat_s(fileNameForObj, sizeof(fileNameForObj), ".map");

	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), idxBuffer);
	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), ".map");
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), idxBuffer);
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), ".map");

	
	//	맵 크기 str 생성
	itoa(_tileNum.x, tileNumBuffer, 10);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), tileNumBuffer);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), ",");
	itoa(_tileNum.y, tileNumBuffer, 10);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), tileNumBuffer);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), ",");

	//	OBJ 크기 str 생성
	itoa(_vObj.size(), objNumBuffer, 10);
	//itoa(_vObjInfo.size(), objNumBuffer, 10);
	strcat_s(objSizeStr, sizeof(objSizeStr), objNumBuffer);
	strcat_s(objSizeStr, sizeof(objSizeStr), ",");

	//	Enemy 크기 str 생성
	itoa(_vEnemy.size(), enemyNumBuffer, 10);
	//itoa(_vEnemyInfo.size(), enemyNumBuffer, 10);
	strcat_s(enemySizeStr, sizeof(enemySizeStr), enemyNumBuffer);
	strcat_s(enemySizeStr, sizeof(enemySizeStr), ",");

	//	맵크기 저장한 파일 생성
	HANDLE fileForMapSize;
	DWORD writeForMapSize;

	fileForMapSize = CreateFile(fileNameForMapSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(fileForMapSize, mapSizeStr, sizeof(mapSizeStr), &writeForMapSize, NULL);
	CloseHandle(fileForMapSize);

	//	vObj크기 저장한 파일 생성
	HANDLE fileForObjSize;
	DWORD writeForObjSize;
	
	fileForObjSize = CreateFile(fileNameForObjSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(fileForObjSize, objSizeStr, sizeof(objSizeStr), &writeForObjSize, NULL);
	CloseHandle(fileForObjSize);

	//	vEnemy크기 저장한 파일 생성
	HANDLE fileForEnemySize;
	DWORD writeForEnemySize;
	
	fileForEnemySize = CreateFile(fileNameForEnemySize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(fileForEnemySize, enemySizeStr, sizeof(enemySizeStr), &writeForEnemySize, NULL);
	CloseHandle(fileForEnemySize);


	//==============================

	//	vv맵 데이터 1차배열로 복사중...
	tagTileInfo* saveTileAry = new tagTileInfo[_tileNum.x * _tileNum.y];
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			saveTileAry[i*_tileNum.x + j] = _vvMap[i][j]->getTileInfo();		//	포인터 주소 넘길게 아니라 값 넘겨라 임마
			//saveTileAry[i*_tileNum.x + j].setTileInfo(
			//	_vvMap[i][j]->getTileInfo().terImgNum,
			//	_vvMap[i][j]->getTileInfo().frameX,
			//	_vvMap[i][j]->getTileInfo().frameY,
			//	_vvMap[i][j]->getTileInfo().idx,
			//	_vvMap[i][j]->getTileInfo().pickIdx,
			//	_vvMap[i][j]->getTileInfo().terAttr,
			//	_vvMap[i][j]->getTileInfo().pos,
			//	_vvMap[i][j]->getTileInfo().rc,
			//	_vvMap[i][j]->getTileInfo().zLevel
			//);
		}
	}

	HANDLE fileForMapData;
	DWORD writeForMapData;

	fileForMapData = CreateFile(fileNameForMap, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	
	WriteFile(fileForMapData, saveTileAry, sizeof(tagTileInfo)*_tileNum.x * _tileNum.y, &writeForMapData, NULL);

	delete[] saveTileAry;

	CloseHandle(fileForMapData);
	
	

	//==============================

	//	v오브젝트 데이터 1차배열로 복사중...
	//tagObjInfo* saveObjAry = new tagObjInfo[_vObj.size()];
	//for (int i = 0; i < _vObj.size(); i++) {
	//	saveObjAry[i] = _vObj[i]->getObjInfo();
	//	
	//	//saveObjAry[i] = *_vObj[i];
	//
	//}

	//tagObjSpriteInfo* saveObjAry = new tagObjSpriteInfo[_vObjInfo.size()];
	//for (int i = 0; i < _vObjInfo.size(); i++) {
	//	saveObjAry[i] = *_vObjInfo[i];
	//
	//}

	tagObjSpriteInfo* saveObjAry = new tagObjSpriteInfo[_vObj.size()];
	for (int i = 0; i < _vObj.size(); i++) {
		saveObjAry[i] = _vObj[i]->getObjSpirteInfo();

	}

	HANDLE fileForObjData;
	DWORD writeForObjData;

	fileForObjData = CreateFile(fileNameForObj, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(fileForObjData, saveObjAry, sizeof(tagObjSpriteInfo)*_vObj.size(), &writeForObjData, NULL);
	//WriteFile(fileForObjData, saveObjAry, sizeof(tagObjSpriteInfo)*_vObjInfo.size(), &writeForObjData, NULL);
	
	delete[] saveObjAry;
	CloseHandle(fileForObjData);


	//==============================

	//	vEnemyInfo 데이터 1차배열로 복사중...
	tagEnemySpriteInfoForMapEditor* saveEnemyAry = new tagEnemySpriteInfoForMapEditor[_vEnemy.size()];
	for (int i = 0; i < _vEnemy.size(); i++) {
		saveEnemyAry[i] = _vEnemy[i]->getEnemyInfo();
	}

	////	vEnemyInfo 데이터 1차배열로 복사중...
	//tagEnemySpriteInfoForMapEditor* saveEnemyAry = new tagEnemySpriteInfoForMapEditor[_vEnemyInfo.size()];
	//for (int i = 0; i < _vEnemyInfo.size(); i++) {
	//	saveEnemyAry[i] = *_vEnemyInfo[i];
	//}

	HANDLE fileForEnemyData;
	DWORD writeForEnemyData;

	fileForEnemyData = CreateFile(fileNameForEnemy, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(fileForEnemyData, saveEnemyAry, sizeof(tagEnemySpriteInfoForMapEditor)*_vEnemy.size(), &writeForEnemyData, NULL);
	//WriteFile(fileForEnemyData, saveEnemyAry, sizeof(tagEnemySpriteInfoForMapEditor)*_vEnemyInfo.size(), &writeForEnemyData, NULL);

	delete[] saveEnemyAry;
	CloseHandle(fileForEnemyData);

}

void mapEditor::LoadMapFunc()
{
	//	벡터 초기화
	for (int i = _tileNum.y - 1; i >= 0; i--) {
		for (int j = _tileNum.x - 1; j >= 0; j--) {

			if (_vvMap[i][j]) {
				SAFE_DELETE(_vvMap[i][j]);
				_vvMap[i].pop_back();
			}
		}
		_vvMap.pop_back();
	}
	_vvMap.clear();

	
	for (int i = _vObj.size() - 1; i >= 0; i--) {
		if (_vObj[i]) {
			SAFE_DELETE(_vObj[i]);
			_vObj.pop_back();
		}
	}
	_vObj.clear();
	//for (int i = _vObjInfo.size() - 1; i >= 0; i--) {
	//	if (_vObjInfo[i]) {
	//		SAFE_DELETE(_vObjInfo[i]);
	//		_vObjInfo.pop_back();
	//	}
	//}
	//_vObjInfo.clear();

	for (int i = _vEnemy.size() - 1; i >= 0; i--) {
		if (_vEnemy[i]) {
			SAFE_DELETE(_vEnemy[i]);
			_vEnemy.pop_back();
		}
	}
	_vEnemy.clear();


	//for (int i = _vEnemyInfo.size() - 1; i >= 0; i--) {
	//	if (_vEnemyInfo[i]) {
	//		SAFE_DELETE(_vEnemyInfo[i]);
	//		_vEnemyInfo.pop_back();
	//	}
	//}
	//_vEnemyInfo.clear();

	


	HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData, fileForEnemySize, fileForEnemyData;
	DWORD readForMapSize, readForMapData, readForObjSize, readForObjData, readForEnemySize, readForEnemyData;

	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForEnemy[20] = "enemyData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForObjSize[20] = "objSize";
	char fileNameForEnemySize[20] = "enemySize";
	

	char idxBuffer[5] = {};		//	맵 인덱스 저장소
	char mapSizeStr[20] = {};		//	맵 크기 str저장소
	char objSizeStr[20] = {};
	char enemySizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa임시 저장소
	char objNumBuffer[10] = {};		//	itoa임시 저장소
	char enemyNumBuffer[10] = {};		//	itoa임시 저장소

	char* token;			
	char* context;		
	int tmpInt;
	int vObjSize;
	int vEnemySize;

	//	파일이름 생성
	itoa(_mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");

	strcat_s(fileNameForObjSize, sizeof(fileNameForObjSize), idxBuffer);
	strcat_s(fileNameForObjSize, sizeof(fileNameForObjSize), ".map");
	strcat_s(fileNameForObj, sizeof(fileNameForObj), idxBuffer);
	strcat_s(fileNameForObj, sizeof(fileNameForObj), ".map");

	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), idxBuffer);
	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), ".map");
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), idxBuffer);
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), ".map");


	//	맵크기 로드
	fileForMapSize = CreateFile(fileNameForMapSize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapSize, mapSizeStr, 20, &readForMapSize, NULL);
	CloseHandle(fileForMapSize);

	//	오브제 크기 로드
	fileForObjSize = CreateFile(fileNameForObjSize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjSize, objSizeStr, 20, &readForObjSize, NULL);
	CloseHandle(fileForObjSize);

	//	enemy 크기 로드
	fileForEnemySize = CreateFile(fileNameForEnemySize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemySize, enemySizeStr, 20, &readForEnemySize, NULL);
	CloseHandle(fileForEnemySize);


	//	맵 크기 넣어줌
	token = strtok_s(mapSizeStr, ",", &context);
	tmpInt = atoi(token);
	_tileNum.x = tmpInt;

	token = strtok_s(NULL, ",", &context);
	tmpInt = atoi(token);
	_tileNum.y = tmpInt;

	//	오브제 크기 넣어줌
	token = strtok_s(objSizeStr, ",", &context);
	tmpInt = atoi(token);
	vObjSize = tmpInt;

	//	enemy 크기 넣어줌
	token = strtok_s(enemySizeStr, ",", &context);
	tmpInt = atoi(token);
	vEnemySize = tmpInt;

	//	벡터 리사이즈
	//_vvMap.resize(_tileNum.y);
	//for (int i = 0; i < _tileNum.y; i++) {
	//	_vvMap[i].resize(_tileNum.x);
	//}
	//_vObj.resize(vObjSize);

	//	맵데이터 로드
	tagTileInfo* savedTileAry = new tagTileInfo[_tileNum.x * _tileNum.y];
	ZeroMemory(savedTileAry, sizeof(tagTileInfo) * (_tileNum.x * _tileNum.y));

	fileForMapData = CreateFile(fileNameForMap, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapData, savedTileAry, sizeof(tagTileInfo) * _tileNum.x * _tileNum.y, &readForMapData, NULL);
	CloseHandle(fileForMapData);

	//	vv맵에 데이터 적용
	for (int i = 0; i < _tileNum.y; i++) {
		vLine tmpVLine;
		tmpVLine.clear();
		tmpVLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->setTileInfo(savedTileAry[i*_tileNum.x + j]);
			tmpVLine.push_back(tmpTile);
		}
		_vvMap.push_back(tmpVLine);
	}
	//for (int i = 0; i < _tileNum.y; i++) {
	//	for (int j = 0; j < _tileNum.x; j++) {
	//		_vvMap[i][j]->setTileInfo(savedTileAry[i*_tileNum.x + j]);
	//	}
	//}


	/*
	//	obj데이터 로드
	tagObjInfo* savedObjAry = new tagObjInfo[vObjSize];
	ZeroMemory(savedObjAry, sizeof(tagObjInfo) * (vObjSize));

	fileForObjData = CreateFile(fileNameForObj, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjData, savedObjAry, sizeof(tagObjInfo) * vObjSize, &readForObjData, NULL);
	CloseHandle(fileForObjData);

	//	vObj에 데이터 적용
	for (int i = 0; i < vObjSize; i++) {
		OBJ* tmpObj = new OBJ;
		tmpObj->setObjInfo(savedObjAry[i]);
		_vObj.push_back(tmpObj);
	}
	*/

	//	obj데이터 로드
	tagObjSpriteInfo* savedObjAry = new tagObjSpriteInfo[vObjSize];
	ZeroMemory(savedObjAry, sizeof(tagObjSpriteInfo) * (vObjSize));

	fileForObjData = CreateFile(fileNameForObj, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjData, savedObjAry, sizeof(tagObjSpriteInfo) * vObjSize, &readForObjData, NULL);
	CloseHandle(fileForObjData);

	//	vObj에 데이터 적용
	for (int i = 0; i < vObjSize; i++) {
		OBJ* tmpObj = new OBJ;
		tmpObj->setObjFromSpriteInfo(savedObjAry[i]);
		_vObj.push_back(tmpObj);
	}
	
	////	vObj에 데이터 적용
	//for (int i = 0; i < vObjSize; i++) {
	//	tagObjSpriteInfo* tmpObj = new tagObjSpriteInfo;
	//	*tmpObj = savedObjAry[i];
	//	_vObjInfo.push_back(tmpObj);
	//}



	//	enemy데이터 로드
	tagEnemySpriteInfoForMapEditor* savedEnemyAry = new tagEnemySpriteInfoForMapEditor[vEnemySize];
	ZeroMemory(savedEnemyAry, sizeof(tagEnemySpriteInfoForMapEditor) * (vEnemySize));

	fileForEnemyData = CreateFile(fileNameForEnemy, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemyData, savedEnemyAry, sizeof(tagEnemySpriteInfoForMapEditor) * vEnemySize, &readForEnemyData, NULL);
	CloseHandle(fileForEnemyData);

	//	vEnemyInfo에 데이터 적용
	for (int i = 0; i < vEnemySize; i++) {
		tagEnemySpriteInfoForMapEditor loadEnemyInfo;
		loadEnemyInfo = savedEnemyAry[i];
		switch (loadEnemyInfo.imgNum) {
		case MOB_SKEL:
			enemy* tmpSkel = new skeleton;
			tmpSkel->setEnemyInfo(
				loadEnemyInfo.tileCenterPosAtSprite,
				loadEnemyInfo.sampleRc,
				loadEnemyInfo.pos,
				loadEnemyInfo.mobTileSize,
				loadEnemyInfo.imgNum,
				loadEnemyInfo.zLvl,
				loadEnemyInfo.mapIdx,
				loadEnemyInfo.rc
			);
			_vEnemy.push_back(tmpSkel);

			break;
			//	몹 추가될떄마다 여기서 뉴!!!
		}
		
	}

	////	vEnemyInfo에 데이터 적용
	//for (int i = 0; i < vEnemySize; i++) {
	//	tagEnemySpriteInfoForMapEditor* tmpEnemy = new tagEnemySpriteInfoForMapEditor;
	//	*tmpEnemy = savedEnemyAry[i];
	//	_vEnemyInfo.push_back(tmpEnemy);
	//}

}

void mapEditor::TileSampleFunc()
{
	for (int i = 0; i < _vvTerSamples[_curTerSampleIdx].size() - 2; i++) {
		for (int j = 0; j < _vvTerSamples[_curTerSampleIdx][0].size(); j++) {
			if (PtInRect(&_vvTerSamples[_curTerSampleIdx][i][j]->_rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_cursorObjInfo.init();
					_cursorUnitInfo.init();
					_cursorTile = _vvTerSamples[_curTerSampleIdx][i][j];
					
					//	선택시 자동으로 브러시로 전환
					//if (_selectedTool != -1)
					//	_toolIcons[_selectedTool].isOn = false;
					//_selectedTool = TOOL_BRUSH;
					//_toolIcons[_selectedTool].isOn = true;

					//	샘플 선택완료, 타일메뉴 끄기
					_isChoosingSample = false;
					_selectedMenu = -1;
					_buttons[MENU_TILE].isOn = false;

				}
			}
		}
	}
}

void mapEditor::ObjSampleFunc()
{	
	//오브젝 페이지 넘기기
	if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
		_curObjSampleIdx+= 1;
		if (_curObjSampleIdx == OBJNUM_END)
			_curObjSampleIdx = OBJNUM_BASIC;
	}
	//	오브젝트 선택
	for (int i = 0; i < 12; i++) {
		if (_objImgInfo[_curObjSampleIdx][i].imgNum == OBJNUM_NONE)
			continue;
			
		if (PtInRect(&_objImgInfo[_curObjSampleIdx][i].sampleRc, PointMake(_ptMouseAbs.x - SAMPLE_PALLET_START_X, _ptMouseAbs.y - SAMPLE_PALLET_START_Y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//if (_cursorTile != nullptr) {
					_cursorTile = nullptr;
				//}
				_cursorUnitInfo.init();
				
				_cursorObjInfo = _objImgInfo[_curObjSampleIdx][i];


				//	선택시 자동으로 브러시로 전환
				//if (_selectedTool != -1)
				//	_toolIcons[_selectedTool].isOn = false;
				//_selectedTool = TOOL_BRUSH;
				//_toolIcons[_selectedTool].isOn = true;

				//	샘플 선택완료, 타일메뉴 끄기
				_isChoosingSample = false;
				_selectedMenu = -1;
				_buttons[MENU_TILE].isOn = false;
				
			}
		}
	}
}

void mapEditor::UnitSampleFunc()
{
	//	오브젝트 선택
	for (int i = 0; i < E_IMG_END; i++) {
		
		if (PtInRect(&_enemyInfo[i].sampleRc, PointMake(_ptMouseAbs.x - SAMPLE_PALLET_START_X, _ptMouseAbs.y - SAMPLE_PALLET_START_Y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//if (_cursorTile != nullptr) {
					_cursorTile = nullptr;
				//}				
				_cursorObjInfo.init();
				
				_cursorUnitInfo = _enemyInfo[i];


				//	선택시 자동으로 브러시로 전환
				//if (_selectedTool != -1)
				//	_toolIcons[_selectedTool].isOn = false;
				//_selectedTool = TOOL_BRUSH;
				//_toolIcons[_selectedTool].isOn = true;

				//	샘플 선택완료, 타일메뉴 끄기
				_isChoosingSample = false;
				_selectedMenu = -1;
				_buttons[MENU_TILE].isOn = false;

			}
		}
	}
}

POINT mapEditor::CursorPtToSampleIdx()
{
	POINT frameIdx;
	frameIdx.x = (_ptMouseAbs.x - SAMPLE_PALLET_START_X) / TILESIZE_WID;
	frameIdx.y = (_ptMouseAbs.y - SAMPLE_PALLET_START_Y) / TILESIZE_HEI;

	return frameIdx;
}

void mapEditor::TransTileValue(TILE * sour, TILE * dest)
{
	dest->_img = sour->_img;
	dest->_terImgNum = sour->_terImgNum;
	dest->_frameX = sour->_frameX;
	dest->_frameY = sour->_frameY;
	dest->_terAttr = sour->_terAttr;
	//dest->_zLevel = sour->_zLevel;


}

bool mapEditor::IsSameTile(TILE * sour, TILE * dest)
{
	if (dest->_img == sour->_img &&
		dest->_terImgNum == sour->_terImgNum &&
		dest->_frameX == sour->_frameX &&
		dest->_frameY == sour->_frameY &&
		dest->_terAttr == sour->_terAttr &&
		dest->_zLevel == sour->_zLevel
		)
		return true;

	return false;
}

void mapEditor::MakeObjOnMap(tagObjSpriteInfo obj, int idxX, int idxY)
{
	for (int i = 0; i < obj.objTileSize.y; i++) {
		for (int j = 0; j < obj.objTileSize.x; j++) {

			OBJ* tmpObj = new OBJ;
			if (idxY - i < 0)			continue;
			if (idxY - i >= _tileNum.y) continue;
			if (idxX - j < 0)			continue;
			if (idxX - j >= _tileNum.x) continue;

			POINTFLOAT pos = _vvMap[idxY - i][idxX - j]->_pos;
			RECT rc = RectMake(pos.x - TILESIZE_WID/2,
				pos.y - obj.getPixPosToTop() + (i*(TILESIZE_HEI/2)) + (j*(TILESIZE_HEI / 2)),
				TILESIZE_WID,
				obj.getHei() - (i*(TILESIZE_HEI / 2)) - (j*(TILESIZE_HEI / 2)));

			//	스프라이트 가져올 시작 구간 재조정
			//	x쪽으로 올라갈때 ->  가로 변화x / 세로 -= hei/2
			//	y쪽으로 올라갈떄 ->	가로
			RECT adjSampleRc = obj.sampleRc;
			
			
			//	오브젝의 (0,0)부분 먼저 잡고시작함
			adjSampleRc.left += (obj.objTileSize.x - 1)*(TILESIZE_WID / 2);
			//	i증가(2시방향)할때마다 반타일씩, j증가(10시방향)할때마다 반타일씩
			adjSampleRc.left += (i * (TILESIZE_WID / 2)) - (j* (TILESIZE_WID / 2));
			//	right는 left에서 wid만큼.
			adjSampleRc.right = adjSampleRc.left + TILESIZE_WID;

			tmpObj->init(obj.imgNum, obj.attr, PointMake(idxX - j, idxY - i), pos, rc, adjSampleRc, obj.zLvl, obj.objTileSize);
			_vObj.push_back(tmpObj);

		}
	}


	//OBJ* tmpObj = new OBJ;
	//POINTFLOAT pos = _vvMap[idxY][idxX]->_pos;
	//RECT rc = RectMake(pos.x - obj.getPixPosToLeft(),
	//	pos.y - obj.getPixPosToTop(),
	//	obj.getWid(),
	//	obj.getHei());
	//
	////	오브젝 이닛하고 푸시백
	//tmpObj->init(obj.imgNum, obj.attr, PointMake(idxX, idxY), pos, rc, obj.sampleRc, obj.zLvl, obj.objTileSize);
	//_vObj.push_back(tmpObj);

	//	맵에 속성 부여
	if (obj.attr == O_ATTR_UNMOVE) {
		for (int i = 0; i < obj.objTileSize.y; i++) {
			for (int j = 0; j < obj.objTileSize.x; j++) {
				if (idxY - i < 0)			continue;
				if (idxY - i >= _tileNum.y) continue;
				if (idxX - j < 0)			continue;
				if (idxX - j >= _tileNum.x) continue;

				_vvMap[idxY - i][idxX - j]->_terAttr = T_ATTR_UNMOVE;
			}
		}
	}
	
	sort(_vObj.begin(), _vObj.end(), compareObj);

	/*
	tagObjSpriteInfo* tmpObj = new tagObjSpriteInfo;
	tmpObj->init();
	*tmpObj = obj;
	POINTFLOAT pos = _vvMap[idxY][idxX]->_pos;
	RECT rc = RectMake(pos.x - obj.getPixPosToLeft(),
		pos.y - obj.getPixPosToTop(),
		obj.getWid(),
		obj.getHei());

	tmpObj->pos = pos;
	tmpObj->rc = rc;
	tmpObj->mapIdx = { idxX, idxY };

	//	맵에 속성 부여
	if (tmpObj->attr == O_ATTR_UNMOVE) {
		for (int i = 0; i < tmpObj->objTileSize.y; i++) {
			for (int j = 0; j < tmpObj->objTileSize.x; j++) {
				_vvMap[idxY - i][idxX - j]->_terAttr = T_ATTR_UNMOVE;
			}
		}
	}

	_vObjInfo.push_back(tmpObj);
	*/


}

void mapEditor::MakeUnitOnMap(tagEnemySpriteInfoForMapEditor unit, int idxX, int idxY)
{
	enemy* newEnemy;

	POINTFLOAT pos = _vvMap[idxY][idxX]->_pos;
	RECT rc = RectMake(pos.x - unit.getPixPosToLeft(),
		pos.y - unit.getPixPosToTop(),
		unit.getWid(),
		unit.getHei());

	switch (unit.imgNum) {
	case MOB_SKEL:
		newEnemy = new skeleton;
		newEnemy->setEnemyInfo(unit.tileCenterPosAtSprite, unit.sampleRc, 
			{ NULL,NULL },	//	pos
			unit.mobTileSize, unit.imgNum, unit.zLvl,
			{ NULL,NULL },	//	mapIdx;
			{ NULL,NULL,NULL,NULL });	//	rc

		newEnemy->_rc = rc;
		newEnemy->_mapIdx = { idxX, idxY };
		_vEnemy.push_back(newEnemy);


		break;
	}



	sort(_vEnemy.begin(), _vEnemy.end(), compareEnemy);

	//tagEnemySpriteInfoForMapEditor* tmpEnemyInfo = new tagEnemySpriteInfoForMapEditor;
	//tmpEnemyInfo->init();
	//*tmpEnemyInfo = unit;
	//
	//POINTFLOAT pos = _vvMap[idxY][idxX]->_pos;
	//RECT rc = RectMake(pos.x - tmpEnemyInfo->getPixPosToLeft(),
	//	pos.y - tmpEnemyInfo->getPixPosToTop(),
	//	tmpEnemyInfo->getWid(),
	//	tmpEnemyInfo->getHei());
	//
	//
	//
	//tmpEnemyInfo->pos = pos;
	//tmpEnemyInfo->rc = rc;
	//tmpEnemyInfo->mapIdx = { idxX, idxY };
	//
	//
	//_vEnemyInfo.push_back(tmpEnemyInfo);
}


void mapEditor::CursorSampleRender()
{
	if (_cursorTile != nullptr) {
		if (_cursorTile->_img != nullptr) {
			_cursorTile->_img->frameRenderABS(1441, 33, _cursorTile->_frameX, _cursorTile->_frameY, 1.0f);
		}
		
	}

}

void mapEditor::PreviewRender()
{
	if (_selectedTool == TOOL_BRUSH ||
		_selectedTool == TOOL_PAINT) {

		if (_cursorTile != nullptr) {
			if (_cursorTile->_img != nullptr) {
				_cursorTile->_img->frameRenderABS(_ptMouseAbs.x - TILESIZE_WID / 2, _ptMouseAbs.y - TILESIZE_HEI / 2,
					_cursorTile->_frameX, _cursorTile->_frameY, 0.5f);
			}
		}



		//_cursorObjInfo.img!=nullptr
		//if (_cursorObjInfo.imgNum != OBJNUM_NONE) {
		else if (_cursorObjInfo.img != nullptr) {

			_cursorObjInfo.img->renderABS(
				_ptMouseAbs.x - _cursorObjInfo.getPixPosToLeft(),
				_ptMouseAbs.y - _cursorObjInfo.getPixPosToTop(),

				//_ptMouseAbs.x - (_cursorObjInfo.centerPosInImg.x - _cursorObjInfo.sampleRc.left),
				//_ptMouseAbs.y - (_cursorObjInfo.centerPosInImg.y - _cursorObjInfo.sampleRc.top),

				_cursorObjInfo.sampleRc.left,
				_cursorObjInfo.sampleRc.top,

				_cursorObjInfo.getWid(),
				_cursorObjInfo.getHei(),
				//_cursorObjInfo.sampleRc.right - _cursorObjInfo.sampleRc.left,
				//_cursorObjInfo.sampleRc.bottom - _cursorObjInfo.sampleRc.top,
				0.5f);
		}


		else if (_cursorUnitInfo.sampleImg != nullptr) {

			_cursorUnitInfo.sampleImg->renderABS(
				_ptMouseAbs.x - _cursorUnitInfo.getPixPosToLeft(),
				_ptMouseAbs.y - _cursorUnitInfo.getPixPosToTop(),

				_cursorUnitInfo.sampleRc.left,
				_cursorUnitInfo.sampleRc.top,

				_cursorUnitInfo.getWid(),
				_cursorUnitInfo.getHei(),
				0.5f);

		}
	}

}

void mapEditor::MagicSelectRender()
{
	for (int i = 0; i < _vMagicSelectList.size(); i++) {
		POINT idx = _vMagicSelectList[i];
		D2DMANAGER->drawDiamondLine(0xFF0000, _vvMap[idx.y][idx.x]->_pos.x, _vvMap[idx.y][idx.x]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 2);

		//	픽인덱스타일에 파랑테두리그리기
		PickIdxTileRender(idx.y, idx.x);

	}
}

void mapEditor::TileRender(int idxX, int idxY)
{
	//if (_vvMap[idxY][idxX]->_img != nullptr) {
	//	_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2,
	//		_vvMap[idxY][idxX]->_frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
	//}

	if (_vvMap[idxY][idxX]->_img != nullptr) {
		for (int i = _vvMap[idxY][idxX]->_zLevel; i >= 0; i--) {
			if (i == 0) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
			}
			else if (i == 1) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI/2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, 4, 1.0f);
			}
			else {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, 5, 1.0f);
			}


		}
	}

}

void mapEditor::PickIdxTileRender(int idxX, int idxY)
{
	if (idxX < 0)			
		return;
	if (idxX > _tileNum.x - 1)
		return;
	if (idxY < 0)			
		return;
	if (idxY > _tileNum.y - 1)
		return;



	if (_vvMap[idxY][idxX]->_pickIdx.x != _vvMap[idxY][idxX]->_idx.x ||
		_vvMap[idxY][idxX]->_pickIdx.y != _vvMap[idxY][idxX]->_idx.y) {
		POINT pickIdx = _vvMap[idxY][idxX]->_pickIdx;
		
		D2DMANAGER->drawDiamondLine(0x4BA5FF, _vvMap[pickIdx.y][pickIdx.x]->_pos.x, _vvMap[pickIdx.y][pickIdx.x]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 2);
	}
}

void mapEditor::SampleRender()
{
	if (_selectedMenu == MENU_TILE) {
		for (int i = 0; i < _vvTerSamples[_curTerSampleIdx].size() - 2; i++) {		//	기둥 스프라이트 필요x 그래서 -2;
			for (int j = 0; j < _vvTerSamples[_curTerSampleIdx][0].size(); j++) {
				_vvTerSamples[_curTerSampleIdx][i][j]->_img->frameRenderABS(
					_vvTerSamples[_curTerSampleIdx][i][j]->_rc.left,
					_vvTerSamples[_curTerSampleIdx][i][j]->_rc.top,
					_vvTerSamples[_curTerSampleIdx][i][j]->_frameX,
					_vvTerSamples[_curTerSampleIdx][i][j]->_frameY,
					1.0f);

				//	테두리
				D2DMANAGER->drawRectangle(0x8673CC,
					_vvTerSamples[_curTerSampleIdx][i][j]->_rc.left + CAMERA2D->getCamPosX() 
					, _vvTerSamples[_curTerSampleIdx][i][j]->_rc.top + CAMERA2D->getCamPosY()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_rc.right + CAMERA2D->getCamPosX()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_rc.bottom + CAMERA2D->getCamPosY());
			}
		}
	}
	else if (_selectedMenu == MENU_OBJ) {
		for (int i = 0; i < 12; i++) {
			if (_objImgInfo[_curObjSampleIdx][i].imgNum == OBJNUM_NONE)	continue;
			_objImgInfo[_curObjSampleIdx][i].img->renderABS(
				_objImgInfo[_curObjSampleIdx][i].sampleRc.left + SAMPLE_PALLET_START_X,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.top + SAMPLE_PALLET_START_Y,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.left,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.top,
				_objImgInfo[_curObjSampleIdx][i].getWid(),
				_objImgInfo[_curObjSampleIdx][i].getHei(),
				1.0f);

			D2DMANAGER->drawRectangle(0x8673CC,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.left + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.top + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.right + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_objImgInfo[_curObjSampleIdx][i].sampleRc.bottom + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y);

			
			//	중점 확인용 ==========
			D2DMANAGER->drawRectangle(0x00FF4E,
				_objImgInfo[_curObjSampleIdx][i].centerPosInImg.x + CAMERA2D->getCamPosX() -5 + SAMPLE_PALLET_START_X,
				_objImgInfo[_curObjSampleIdx][i].centerPosInImg.y + CAMERA2D->getCamPosY() -5 + SAMPLE_PALLET_START_Y,
				_objImgInfo[_curObjSampleIdx][i].centerPosInImg.x + CAMERA2D->getCamPosX()+ 5 + SAMPLE_PALLET_START_X,
				_objImgInfo[_curObjSampleIdx][i].centerPosInImg.y + CAMERA2D->getCamPosY() + 5 + SAMPLE_PALLET_START_Y
			);
				


		}
	}
	else if (_selectedMenu == MENU_UNIT) {
		for (int i = 0; i < E_IMGNUM::E_IMG_END; i++) {
			_enemyInfo[i].sampleImg->renderABS(
				_enemyInfo[i].sampleRc.left + SAMPLE_PALLET_START_X,
				_enemyInfo[i].sampleRc.top + SAMPLE_PALLET_START_Y,
				_enemyInfo[i].sampleRc.left,
				_enemyInfo[i].sampleRc.top,
				_enemyInfo[i].sampleImg->GetFrameWidth(),
				_enemyInfo[i].sampleImg->GetFrameWidth(),
				1.0f);

			//	테두리
			D2DMANAGER->drawRectangle(0x8673CC,
				_enemyInfo[i].sampleRc.left + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_enemyInfo[i].sampleRc.top + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y,
				_enemyInfo[i].sampleRc.right + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_enemyInfo[i].sampleRc.bottom + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y);


			//	중점 확인용 ==========
			D2DMANAGER->drawRectangle(0x00FF4E,
				_enemyInfo[i].tileCenterPosAtSprite.x + CAMERA2D->getCamPosX() - 5 + SAMPLE_PALLET_START_X,
				_enemyInfo[i].tileCenterPosAtSprite.y + CAMERA2D->getCamPosY() - 5 + SAMPLE_PALLET_START_Y,
				_enemyInfo[i].tileCenterPosAtSprite.x + CAMERA2D->getCamPosX() + 5 + SAMPLE_PALLET_START_X,
				_enemyInfo[i].tileCenterPosAtSprite.y + CAMERA2D->getCamPosY() + 5 + SAMPLE_PALLET_START_Y
			);

		}



	}
	
}

void mapEditor::ObjRender()
{
	
	//	언덕값에따라 _rc, _pos처리해줄때의 렌더
	for (int i = 0; i < _vObj.size(); i++) {
		_vObj[i]->_img->render(
			_vObj[i]->_rc.left,
			_vObj[i]->_rc.top,
			_vObj[i]->_sampleRc.left,
			_vObj[i]->_sampleRc.top,
			_vObj[i]->_sampleRc.right - _vObj[i]->_sampleRc.left,
			_vObj[i]->_sampleRc.bottom - _vObj[i]->_sampleRc.top,
			1.0f
		);
	}
	

	/*
	//	언덕값에따라 _rc, _pos처리안하고, 자신의 맵타일의 높이로 렌더에서 계산처리
	for (int i = 0; i < _vObjInfo.size(); i++) {
		_vObjInfo[i]->img->render(
			_vObjInfo[i]->rc.left,
			_vObjInfo[i]->rc.top - _vvMap[_vObjInfo[i]->mapIdx.y][_vObjInfo[i]->mapIdx.x]->_zLevel * (TILESIZE_HEI/2),
			_vObjInfo[i]->sampleRc.left,
			_vObjInfo[i]->sampleRc.top,
			_vObjInfo[i]->sampleRc.right - _vObjInfo[i]->sampleRc.left,
			_vObjInfo[i]->sampleRc.bottom - _vObjInfo[i]->sampleRc.top,
			1.0f
		);
	}
	*/


}

void mapEditor::UnitRender()
{
	for (int i = 0; i < _vEnemy.size(); i++) {
		_vEnemy[i]->_sampleImg->render(
			_vEnemy[i]->_rc.left,
			_vEnemy[i]->_rc.top,
			_vEnemy[i]->_sampleRc.left,
			_vEnemy[i]->_sampleRc.top,
			_vEnemy[i]->getWid(),
			_vEnemy[i]->getHei(),
			1.0f
		);
	}


	//for (int i = 0; i < _vEnemyInfo.size(); i++) {
	//	_vEnemyInfo[i]->sampleImg->render(
	//		_vEnemyInfo[i]->rc.left,
	//		_vEnemyInfo[i]->rc.top,
	//		_vEnemyInfo[i]->sampleRc.left,
	//		_vEnemyInfo[i]->sampleRc.top,
	//		_vEnemyInfo[i]->getWid(),
	//		_vEnemyInfo[i]->getHei(),
	//		1.0f
	//	);
	//}

	/*
	for (int i = 0; i < _vEnemyInfo.size(); i++) {
		_vEnemyInfo[i]->sampleImg->render(
			_vEnemyInfo[i]->rc.left,
			_vEnemyInfo[i]->rc.top - _vvMap[_vEnemyInfo[i]->mapIdx.y][_vEnemyInfo[i]->mapIdx.x]->_zLevel * (TILESIZE_HEI / 2),
			_vEnemyInfo[i]->sampleRc.left,
			_vEnemyInfo[i]->sampleRc.top,
			_vEnemyInfo[i]->getWid(),
			_vEnemyInfo[i]->getHei(),
			1.0f
		);
	}
	*/
}

void mapEditor::SortedRender(int idxX, int idxY, int& objCount, int& unitCount)
{

	if (_vvMap[idxY][idxX]->_img != nullptr) {
		//	맵 높이만큼 그려줌
		for (int i = _vvMap[idxY][idxX]->_zLevel; i >= 0; i--) {
			if (i == 0) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
			}
			else if (i == 1) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, 4, 1.0f);
			}
			else {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_frameX, 5, 1.0f);
			}
		}
	}

	//	유닛렌더
	if (unitCount < _vEnemy.size()) {
		while (_vEnemy[unitCount]->_mapIdx.x == idxX && _vEnemy[unitCount]->_mapIdx.y == idxY) {
			UnitRender(unitCount);
			unitCount++;
			if (unitCount >= _vEnemy.size())		break;
		}
	}
		

	//	오브젝 렌더
	if (objCount < _vObj.size()) {
		while (_vObj[objCount]->_mapIdx.x == idxX && _vObj[objCount]->_mapIdx.y == idxY) {
			ObjRender(objCount);
			objCount++;

			if (objCount >= _vObj.size())		break;
		}
	}
	
}

void mapEditor::ObjRender(int idx)
{
	//	언덕값에따라 _rc, _pos처리해줄때의 렌더
	
	_vObj[idx]->_img->render(
		_vObj[idx]->_rc.left,
		_vObj[idx]->_rc.top,
		_vObj[idx]->_sampleRc.left,
		_vObj[idx]->_sampleRc.top,
		_vObj[idx]->_sampleRc.right - _vObj[idx]->_sampleRc.left,
		_vObj[idx]->_sampleRc.bottom - _vObj[idx]->_sampleRc.top,
		1.0f
	);
	
}

void mapEditor::UnitRender(int idx)
{
	_vEnemy[idx]->_sampleImg->render(
		_vEnemy[idx]->_rc.left,
		_vEnemy[idx]->_rc.top,
		_vEnemy[idx]->_sampleRc.left,
		_vEnemy[idx]->_sampleRc.top,
		_vEnemy[idx]->getWid(),
		_vEnemy[idx]->getHei(),
		1.0f
	);
	
}
