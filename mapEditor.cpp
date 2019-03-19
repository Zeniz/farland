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



	_vMagicSelectList.clear();

	//	vvMap 생성!
	{
		_tileNum.x = 20;
		_tileNum.y = 20;

		_vvMap.clear();


		for (int i = 0; i < _tileNum.y; i++) {
			vLine _vLine;
			_vLine.clear();
			_vLine.reserve(_tileNum.x);
			for (int j = 0; j < _tileNum.x; j++) {
				TILE* tmpTile = new TILE;
				tmpTile->init();
				tmpTile->setObjectiveVal(j, i);
				tmpTile->_tileInfo.pickIdx = tmpTile->_mapIdx;
				_vLine.push_back(tmpTile);
			}
			_vvMap.push_back(_vLine);
		}
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
	_curTerSampleIdx = TER_BASIC;
	_curObjSampleIdx = OBJ_BASIC;
	_curUnitSampleIdx = MOB_SKEL;
	_cursorTile = nullptr;

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

	for (int i = 0; i < _tileNum.y; i++) {
		vLine _vLine;
		_vLine.clear();
		_vLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->init();
			tmpTile->setObjectiveVal(j, i);
			tmpTile->_tileInfo.pickIdx = tmpTile->_mapIdx;

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
	
	
	_isChoosingSample = false;
	_curTerSampleIdx = TER_BASIC;
	_curObjSampleIdx = OBJ_BASIC;
	_curUnitSampleIdx = MOB_SKEL;

	_cursorTile = nullptr;

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
	

	for (int i = 0; i < _tileNum.y; i++) {
		vLine _vLine;
		_vLine.clear();
		_vLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->init();
			tmpTile->setObjectiveVal(j, i);
			tmpTile->_tileInfo.pickIdx = tmpTile->_mapIdx;
			
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
	_curTerSampleIdx = TER_BASIC;
	_curObjSampleIdx = OBJ_BASIC;
	_curUnitSampleIdx = MOB_SKEL;

	_cursorTile = nullptr;

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

	bool isFoundObjStart = false;
	bool isFoundEnemyStart = false;


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
	
	//	갈수있는길 표시
	if (KEYMANAGER->isToggleKey(VK_HOME)) {
		MoveableTileRender();
	} 
	if (KEYMANAGER->isToggleKey(VK_END)) {
		MapIdxRender();
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

			tagTileInfo tileInfo;
			tileInfo.setTileInfo(TERNUM::TER_BASIC, j, i, { NULL,NULL }, T_ATTRIBUTE::T_ATTR_NONE, rc, 0);
			tmpTile->setTileInfo(tileInfo);
			tmpTile->_pos = pos;
			
			


			vLine.push_back(tmpTile);
		}
		_vvTerSamples[TER_BASIC].push_back(vLine);
	}



	return S_OK;
}

HRESULT mapEditor::InitObjSamples()
{
	//	초기화
	
	for (int i = OBJNUM_NONE + 1; i < OBJNUM_END; i++) {
		for (int j = 0; j < 20; j++) {
			_objSamples[i][j].init();
		}
	}

	//	1페이지
	{
		for (int i = 0; i < 4; i++) {
			_objSamples[OBJNUM::OBJ_BASIC][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_BASIC].c_str());
			_objSamples[OBJNUM::OBJ_BASIC][i].objNum = OBJ_BASIC;
			
			
			_objSamples[OBJNUM::OBJ_BASIC][i].centerPosInImg.x = 66 + (i * 128);
			_objSamples[OBJNUM::OBJ_BASIC][i].centerPosInImg.y = 246;
			_objSamples[OBJNUM::OBJ_BASIC][i].sampleRc = RectMake(i * 128, 0, 128, 272);
			_objSamples[OBJNUM::OBJ_BASIC][i].objTileSize = { 1,1 };

			_objSamples[OBJNUM::OBJ_BASIC][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
			
		}
		for (int i = 4; i < 8; i++) {
			_objSamples[OBJNUM::OBJ_BASIC][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_BASIC].c_str());
			_objSamples[OBJNUM::OBJ_BASIC][i].objNum = OBJ_BASIC;

			_objSamples[OBJNUM::OBJ_BASIC][i].centerPosInImg.x = 50 + (i - 4) * 128;
			_objSamples[OBJNUM::OBJ_BASIC][i].centerPosInImg.y = 400;
			_objSamples[OBJNUM::OBJ_BASIC][i].sampleRc = RectMake((i - 4) * 128, 273, 128, 142);
			_objSamples[OBJNUM::OBJ_BASIC][i].objTileSize = { 1,1 };

			_objSamples[OBJNUM::OBJ_BASIC][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
			
			
		}
		for (int i = 8; i < 12; i++) {
			_objSamples[OBJNUM::OBJ_BASIC][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_BASIC].c_str());
			_objSamples[OBJNUM::OBJ_BASIC][i].objNum = OBJ_BASIC;


			_objSamples[OBJNUM::OBJ_BASIC][i].centerPosInImg.x = 64 + (i - 8) * 128;
			_objSamples[OBJNUM::OBJ_BASIC][i].centerPosInImg.y = 512;

			_objSamples[OBJNUM::OBJ_BASIC][i].sampleRc = RectMake((i - 8) * 128, 416, 128, 128);
			_objSamples[OBJNUM::OBJ_BASIC][i].objTileSize = { 1,1 };
			
			_objSamples[OBJNUM::OBJ_BASIC][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
		}
	}
	//	2페이지
	{
		_objSamples[OBJNUM::OBJ_HOUSE][0].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_HOUSE].c_str());
		_objSamples[OBJNUM::OBJ_HOUSE][0].objNum = OBJ_HOUSE;

		_objSamples[OBJNUM::OBJ_HOUSE][0].centerPosInImg.x = 256;
		_objSamples[OBJNUM::OBJ_HOUSE][0].centerPosInImg.y = 544 - TILESIZE_HEI / 2;
		_objSamples[OBJNUM::OBJ_HOUSE][0].sampleRc = RectMake(0, 0, 576, 544);
		_objSamples[OBJNUM::OBJ_HOUSE][0].objTileSize = { 4,5 };

		_objSamples[OBJNUM::OBJ_HOUSE][0].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
		

		_objSamples[OBJNUM::OBJ_HOUSE][1].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_HOUSE].c_str());
		_objSamples[OBJNUM::OBJ_HOUSE][1].objNum = OBJ_HOUSE;

		_objSamples[OBJNUM::OBJ_HOUSE][1].centerPosInImg.x = 896;
		_objSamples[OBJNUM::OBJ_HOUSE][1].centerPosInImg.y = 544 - TILESIZE_HEI / 2;
		_objSamples[OBJNUM::OBJ_HOUSE][1].sampleRc = RectMake(576, 0, 576, 544);
		_objSamples[OBJNUM::OBJ_HOUSE][1].objTileSize = { 5,4 };
		
		_objSamples[OBJNUM::OBJ_HOUSE][1].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
	}
	
	//	3페이지
	{
		for (int i = 0; i < 4; i++) {
			_objSamples[OBJNUM::OBJ_COMB][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_COMB].c_str());
			_objSamples[OBJNUM::OBJ_COMB][i].objNum = OBJ_COMB;

			_objSamples[OBJNUM::OBJ_COMB][i].centerPosInImg.x = 64 + (i * 128);
			_objSamples[OBJNUM::OBJ_COMB][i].centerPosInImg.y = 160;
			_objSamples[OBJNUM::OBJ_COMB][i].sampleRc = RectMake(0 + (i * 128), 0, 128, 192);
			_objSamples[OBJNUM::OBJ_COMB][i].objTileSize = { 1,1 };

			_objSamples[OBJNUM::OBJ_COMB][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
			
		}
		for (int i = 4; i < 6; i++) {
			_objSamples[OBJNUM::OBJ_COMB][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_COMB].c_str());
			_objSamples[OBJNUM::OBJ_COMB][i].objNum = OBJ_COMB;

			_objSamples[OBJNUM::OBJ_COMB][i].centerPosInImg.x = 64 + ((i-4) * 128);
			_objSamples[OBJNUM::OBJ_COMB][i].centerPosInImg.y = 352;
			_objSamples[OBJNUM::OBJ_COMB][i].sampleRc = RectMake(0 + (i - 4) * 128, 192, 128, 192);
			_objSamples[OBJNUM::OBJ_COMB][i].objTileSize = { 1,1 };

			_objSamples[OBJNUM::OBJ_COMB][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
			
		} 
		//	풀떼기
		for (int i = 6; i < 10; i++) {
			_objSamples[OBJNUM::OBJ_COMB][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_COMB].c_str());
			_objSamples[OBJNUM::OBJ_COMB][i].objNum = OBJ_COMB;

			_objSamples[OBJNUM::OBJ_COMB][i].centerPosInImg.x = 64 + (i - 6) * 128;
			_objSamples[OBJNUM::OBJ_COMB][i].centerPosInImg.y = 480;
			_objSamples[OBJNUM::OBJ_COMB][i].sampleRc = RectMake(0 + (i - 6) * 128, 384, 128, 128);
			_objSamples[OBJNUM::OBJ_COMB][i].objTileSize = { 1,1 };

			_objSamples[OBJNUM::OBJ_COMB][i].terAttr = T_ATTRIBUTE::T_ATTR_NONE;
			
		}
	}
	//	4페이지 - 크리스탈
	{
		for (int i = 0; i < 4; i++) {
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_CRYSTAL].c_str());
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].objNum = OBJ_CRYSTAL;
			
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].centerPosInImg.x = 128 + (i * 256);
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].centerPosInImg.y = 304;
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].sampleRc = RectMake(0 + (i * 256), 0, 256, 336);
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].objTileSize = { 2,2 };

			_objSamples[OBJNUM::OBJ_CRYSTAL][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
			
			
		}
		for (int i = 4; i < 9; i++) {
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_CRYSTAL].c_str());
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].objNum = OBJ_CRYSTAL;

			_objSamples[OBJNUM::OBJ_CRYSTAL][i].centerPosInImg.x = 64 + (i - 4) * 128;
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].centerPosInImg.y = 512;
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].sampleRc = RectMake(0 + (i - 4) * 128, 337, 128, 208);
			_objSamples[OBJNUM::OBJ_CRYSTAL][i].objTileSize = { 1,1 };

			_objSamples[OBJNUM::OBJ_CRYSTAL][i].terAttr = T_ATTRIBUTE::T_ATTR_UNMOVE;
			
		}
		
	}

	return S_OK;

}

HRESULT mapEditor::InitMobSamples()
{
	_enemySamples[MOB_SKEL].centerPosInImg.x = 64;
	_enemySamples[MOB_SKEL].centerPosInImg.y = 128;
	_enemySamples[MOB_SKEL].name = MOB_SKEL;
	_enemySamples[MOB_SKEL].spriteImg = IMAGEMANAGER->findImage("mobSprite");
	_enemySamples[MOB_SKEL].sampleRc = RectMake(0, 0,
		_enemySamples[MOB_SKEL].spriteImg->GetFrameWidth(), _enemySamples[MOB_SKEL].spriteImg->GetFrameHeight());

	
	_enemySamples[MOB_SKEL].mobTileSize = { 1,1 };

	_enemySamples[MOB_SKEL].mapIdx = { NULL,NULL };	//	직접 찍을때 값 따로 넣어줌
	

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
		tmpTile->_mapIdx.x = _tileNum.x - 1;
		tmpTile->_mapIdx.y = i;
		tmpTile->_tileInfo.pickIdx = tmpTile->_mapIdx;
		tmpTile->_pos = ConvertIdxToPosFloat(tmpTile->_mapIdx.x, tmpTile->_mapIdx.y, TILESIZE_WID, TILESIZE_HEI);

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
		tmpTile->_mapIdx.x = i;
		tmpTile->_mapIdx.y = _tileNum.y - 1;
		tmpTile->_tileInfo.pickIdx = tmpTile->_mapIdx;
		tmpTile->_pos = ConvertIdxToPosFloat(tmpTile->_mapIdx.x, tmpTile->_mapIdx.y, TILESIZE_WID, TILESIZE_HEI);

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
	
	//	클리핑
	for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
		for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
			if (i < 0)				continue;
			if (i > _tileNum.y - 1)	continue;
			if (j < 0)				continue;
			if (j > _tileNum.x - 1)	continue;
			if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {

					//타일이 선택되어있다면 -> 타일 칠함
					if (_cursorTile != nullptr) {
						if (_cursorTile->_tileInfo.img != nullptr) {
							//TransTileValue(_cursorTile, _vvMap[i][j]);
							MakeTileOnMap(_cursorTile, j, i);
							return;
						}
					}
					else if (_cursorObj.img != nullptr) {
						MakeObjOnMap(_cursorObj, j, i);
						return;
					}
					else if (_cursorEnemy.spriteImg != nullptr) {
						MakeUnitOnMap(_cursorEnemy, j, i);
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
					if (_vvMap[i][j]->_tileInfo.terImgNum != TERNUM_NONE) {
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

								//	오브제 삭제
								TransObjValue(&nullTile, _vvMap[ii][jj]);
								//	몹 삭제
								DeleteUnit(jj, ii);
								
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
						//	오브제 삭제
						TransObjValue(&nullTile, _vvMap[id.y][id.x]);
						//	몹 삭제
						DeleteUnit((int)id.x, (int)id.y);
					}
					return;
				}
			}
		}
	}

	//	범위가 없을 때.
	else {


		//	클리핑
		for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
			for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
				if (i < 0)				continue;
				if (i > _tileNum.y - 1)	continue;
				if (j < 0)				continue;
				if (j > _tileNum.x - 1)	continue;

				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {

						TransObjValue(&nullTile, _vvMap[i][j]);
						DeleteUnit(j,i);

						return;
					}
				}
			}
		}
	}


}

void mapEditor::PaintFunc()
{
	if (_cursorTile != nullptr) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			//	타일일떄,
			if (_cursorTile->_tileInfo.img != nullptr) {
				if (_cursorSelectIdxSorted[0].x != -1) {
					for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
						for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
							//TransTileValue(_cursorTile, _vvMap[i][j]);
							MakeTileOnMap(_cursorTile, j, i);
						}
					}
					return;
				}
				else if (_vMagicSelectList.size() != 0) {
					for (int i = 0; i < _vMagicSelectList.size(); i++) {
						POINT idx = _vMagicSelectList[i];
						//TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
						MakeTileOnMap(_cursorTile, idx.x, idx.y);
					}
					return;
				}
			}
			//	오브젝일떄,
			else if (_cursorTile->_objInfo.img != nullptr) {
				if (_cursorSelectIdxSorted[0].x != -1) {
					for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
						for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
							//TransTileValue(_cursorTile, _vvMap[i][j]);
							MakeObjOnMap(_cursorObj, j, i);
						}
					}
					return;
				}
				else if (_vMagicSelectList.size() != 0) {
					for (int i = 0; i < _vMagicSelectList.size(); i++) {
						POINT idx = _vMagicSelectList[i];
						//TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
						MakeObjOnMap(_cursorObj, idx.x, idx.y);

					}
					return;
				}
			}
			else if (_cursorEnemy.spriteImg != nullptr) {
				if (_cursorSelectIdxSorted[0].x != -1) {
					for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
						for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
							//TransTileValue(_cursorTile, _vvMap[i][j]);
							MakeUnitOnMap(_cursorEnemy, j, i);
						}
					}
					return;
				}
				else if (_vMagicSelectList.size() != 0) {
					for (int i = 0; i < _vMagicSelectList.size(); i++) {
						POINT idx = _vMagicSelectList[i];
						//TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
						MakeUnitOnMap(_cursorEnemy, idx.x, idx.y);

					}
					return;
				}
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
				if (_vvMap[i][j]->_tileInfo.img == nullptr)	continue;
				if (_vvMap[i][j]->_zLevel + augZlvl >= 0) {
					_vvMap[i][j]->_zLevel += augZlvl;
					_vvMap[i][j]->_tileInfo.zlvl += augZlvl;
					
				}

				//	높아져서 덮어진부분 pickIdx로 픽 설정해준다.
				if (_vvMap[i][j]->_zLevel % 2 == 0) {						//	2lvl마다,
					for (int k = 0; k < _vvMap[i][j]->_zLevel / 2; k++) {
						if (i - (k + 1) < 0 || j - (k + 1) < 0)	continue;
						_vvMap[i - (k + 1)][j - (k + 1)]->_tileInfo.pickIdx = { j,i };
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
						_vvMap[overedTileIdx.y - 1][overedTileIdx.x - 1]->_tileInfo.pickIdx = { overedTileIdx.x - 1, overedTileIdx.y - 1 };
					}

				}
				
			}
		}
	}
	//	마술봉으로 구역설정시,
	else if (_vMagicSelectList.size() != 0) {
		for (int i = 0; i < _vMagicSelectList.size(); i++) {
			POINT idx = _vMagicSelectList[i];
			if (_vvMap[idx.y][idx.x]->_tileInfo.img == nullptr)	 continue;
			if (_vvMap[idx.y][idx.x]->_zLevel + augZlvl > 0) {
				_vvMap[idx.y][idx.x]->_zLevel += augZlvl;
				//AdjustHillToObj(idx.x, idx.y, augZlvl);
				//AdjustHillToEnemy(idx.x, idx.y, augZlvl);		//	Enemy도 위치이동!(pos,rc)
			}
			//	높아져서 덮어진부분 pickIdx로 픽 설정해준다.
			if (_vvMap[idx.y][idx.x]->_zLevel % 2 == 0) {
				for (int k = 0; k < _vvMap[idx.y][idx.x]->_zLevel / 2; k++) {
					if (idx.y - (k + 1) < 0 || idx.x - (k + 1) < 0)	continue;
					_vvMap[idx.y - (k + 1)][idx.x - (k + 1)]->_tileInfo.pickIdx = { idx.x,idx.y };
				}
			}


		}
	}
}



void mapEditor::SaveMapFunc()
{

	//HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData;
	//DWORD writeForMapSize, writeForMapData , writeForObjSize, writeForObjData;


	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForEnemy[20] = "enemyData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForEnemySize[20] = "enemySize";
	

	char idxBuffer[5] = {};		//	맵 인덱스 저장소
	char mapSizeStr[20] = {};		//	맵 크기 str저장소
	char enemySizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa임시 저장소
	char enemyNumBuffer[10] = {};		//	itoa임시 저장소

	//	파일이름 생성
	itoa(_mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");

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


	//	Enemy 크기 str 생성
	itoa(_vEnemyInfo.size(), enemyNumBuffer, 10);
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
	

	tagObjInfo* saveObjAry = new tagObjInfo[_tileNum.x * _tileNum.y];
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			saveObjAry[i*_tileNum.x + j] = _vvMap[i][j]->getObjInfo();		//	포인터 주소 넘길게 아니라 값 넘겨라 임마
		}
	}

	HANDLE fileForObjData;
	DWORD writeForObjData;

	fileForObjData = CreateFile(fileNameForObj, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(fileForObjData, saveObjAry, sizeof(tagObjInfo)*_tileNum.x * _tileNum.y, &writeForObjData, NULL);
	//WriteFile(fileForObjData, saveObjAry, sizeof(tagObjSpriteInfo)*_vObjInfo.size(), &writeForObjData, NULL);
	
	delete[] saveObjAry;
	CloseHandle(fileForObjData);


	//==============================

	//	vEnemyInfo 데이터 1차배열로 복사중...
	enemyForMapEditor* saveEnemyAry = new enemyForMapEditor[_vEnemyInfo.size()];
	for (int i = 0; i < _vEnemyInfo.size(); i++) {
		saveEnemyAry[i] = _vEnemyInfo[i].getEnemyInfo();
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

	WriteFile(fileForEnemyData, saveEnemyAry, sizeof(enemyForMapEditor)*_vEnemyInfo.size(), &writeForEnemyData, NULL);
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


	HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData, fileForEnemySize, fileForEnemyData;
	DWORD readForMapSize, readForMapData, readForObjSize, readForObjData, readForEnemySize, readForEnemyData;

	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForEnemy[20] = "enemyData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForEnemySize[20] = "enemySize";
	

	char idxBuffer[5] = {};		//	맵 인덱스 저장소
	char mapSizeStr[20] = {};		//	맵 크기 str저장소
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

	//	enemy 크기 넣어줌
	token = strtok_s(enemySizeStr, ",", &context);
	tmpInt = atoi(token);
	vEnemySize = tmpInt;


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
			tmpTile->_tileInfo.img = IMAGEMANAGER->findImage(_terrainImageKey[tmpTile->_tileInfo.terImgNum].c_str());		//	이미지 잡아넣어줘야함
			tmpTile->setObjectiveVal(j, i);
			tmpTile->_zLevel = tmpTile->_tileInfo.zlvl;
			tmpVLine.push_back(tmpTile);
		}
		_vvMap.push_back(tmpVLine);
	}


	//	obj데이터 로드
	tagObjInfo* savedObjAry = new tagObjInfo[_tileNum.x * _tileNum.y];
	ZeroMemory(savedObjAry, sizeof(tagObjInfo) * (_tileNum.x * _tileNum.y));

	fileForObjData = CreateFile(fileNameForObj, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjData, savedObjAry, sizeof(tagObjInfo) * (_tileNum.x * _tileNum.y), &readForObjData, NULL);
	CloseHandle(fileForObjData);

	//	vObj에 데이터 적용
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			_vvMap[i][j]->setObjInfo (savedObjAry[i*_tileNum.x + j]);
			_vvMap[i][j]->_objInfo.img = IMAGEMANAGER->findImage(_objectImageKey[_vvMap[i][j]->_objInfo.objNum].c_str());	//	이미지 잡아넣어줘야함
		}
	}
	


	//	enemy데이터 로드
	enemyForMapEditor* savedEnemyAry = new enemyForMapEditor[vEnemySize];
	ZeroMemory(savedEnemyAry, sizeof(enemyForMapEditor) * (vEnemySize));

	fileForEnemyData = CreateFile(fileNameForEnemy, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemyData, savedEnemyAry, sizeof(enemyForMapEditor) * vEnemySize, &readForEnemyData, NULL);
	CloseHandle(fileForEnemyData);

	//	vEnemyInfo에 데이터 적용
	for (int i = 0; i < vEnemySize; i++) {
		enemyForMapEditor loadEnemyInfo;
		loadEnemyInfo = savedEnemyAry[i];
		loadEnemyInfo.spriteImg = IMAGEMANAGER->findImage("mobSprite");
		switch (loadEnemyInfo.name) {
		case MOB_SKEL:
			_vEnemyInfo.push_back(loadEnemyInfo);

			break;
			//	몹 추가될떄마다 여기서 뉴!!!
		}
		
	}

}

void mapEditor::TileSampleFunc()
{
	for (int i = 0; i < _vvTerSamples[_curTerSampleIdx].size() - 2; i++) {
		for (int j = 0; j < _vvTerSamples[_curTerSampleIdx][0].size(); j++) {
			if (PtInRect(&_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_cursorTile = _vvTerSamples[_curTerSampleIdx][i][j];
					_cursorObj.init();
					_cursorEnemy.init();

					
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
			_curObjSampleIdx = OBJ_BASIC;
	}
	//	오브젝트 선택
	for (int i = 0; i < 12; i++) {
		if (_objSamples[_curObjSampleIdx][i].objNum == OBJNUM_NONE)
			continue;
			
		if (PtInRect(&_objSamples[_curObjSampleIdx][i].sampleRc, PointMake(_ptMouseAbs.x - SAMPLE_PALLET_START_X, _ptMouseAbs.y - SAMPLE_PALLET_START_Y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//if (_cursorTile != nullptr) {
					_cursorTile = nullptr;
				//}
				_cursorEnemy.init();
				
				_cursorObj = _objSamples[_curObjSampleIdx][i];


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
	for (int i = 0; i < E_NAME_END; i++) {
		
		if (PtInRect(&_enemySamples[i].sampleRc, PointMake(_ptMouseAbs.x - SAMPLE_PALLET_START_X, _ptMouseAbs.y - SAMPLE_PALLET_START_Y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_cursorTile->init();
				_cursorObj.init();
				_cursorEnemy = _enemySamples[i];


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
	dest->_tileInfo = sour->_tileInfo;
	dest->_tileInfo.frameX = sour->_tileInfo.frameX;
	dest->_tileInfo.frameY = sour->_tileInfo.frameY;
	


}

void mapEditor::TransObjValue(TILE * sour, TILE * dest)
{
	//	지우기전에, 타일속성 NONE
	for (int i = 0; i < dest->_objInfo.objTileSize.y; i++) {
		for (int j = 0; j < dest->_objInfo.objTileSize.x; j++) {
			if (dest->_mapIdx.y - i < 0)			continue;
			if (dest->_mapIdx.y - i >= _tileNum.y) continue;
			if (dest->_mapIdx.x - j < 0)			continue;
			if (dest->_mapIdx.x - j >= _tileNum.x) continue;
			_vvMap[dest->_mapIdx.y - i][dest->_mapIdx.x - j]->_tileInfo.terAttr = T_ATTRIBUTE::T_ATTR_NONE;
		}
	}
	


	dest->_objInfo = sour->_objInfo;
	
}

void mapEditor::DeleteUnit(int idxX, int idxY)
{
	//	몹 삭제
	for (int k = 0; k < _vEnemyInfo.size(); ) {
		if (_vEnemyInfo[k].mapIdx.x == idxX && _vEnemyInfo[k].mapIdx.y == idxY) {
			_vEnemyInfo.erase(_vEnemyInfo.begin() + k);
		}
		else {
			k++;
		}
	}
}

bool mapEditor::IsSameTile(TILE * sour, TILE * dest)
{
	if (dest->_tileInfo.img == sour->_tileInfo.img &&
		dest->_tileInfo.frameX == sour->_tileInfo.frameX &&
		dest->_tileInfo.frameY == sour->_tileInfo.frameY && 
		dest->_zLevel == sour->_zLevel
		)
		return true;

	return false;
}

void mapEditor::MakeTileOnMap(TILE * sour, int idxX, int idxY)
{
	
	_vvMap[idxY][idxX]->_tileInfo.BrushTileInfo(sour->_tileInfo.terImgNum, sour->_tileInfo.frameX, sour->_tileInfo.frameY);
	_vvMap[idxY][idxX]->_tileInfo.zlvl = _vvMap[idxY][idxX]->_zLevel;
}

void mapEditor::MakeObjOnMap(tagObjInfo sour, int idxX, int idxY)
{
	_vvMap[idxY][idxX]->_objInfo = sour;
	_vvMap[idxY][idxX]->_objInfo.rc = RectMake(_vvMap[idxY][idxX]->_pos.x - sour.getWidPosToLeft(),
		_vvMap[idxY][idxX]->_pos.y - sour.getHeiPosToTop(),
		sour.getWid(),
		sour.getHei()
	);

	for (int i = 0; i < sour.objTileSize.y; i++) {
		for (int j = 0; j < sour.objTileSize.x; j++) {

			if (idxY - i < 0)			continue;
			if (idxY - i >= _tileNum.y) continue;
			if (idxX - j < 0)			continue;
			if (idxX - j >= _tileNum.x) continue;
			tagObjInfo splitedObj = sour;
			POINTFLOAT pos = _vvMap[idxY - i][idxX - j]->_pos;	//	계산위한 맵의 중심좌표
			//	그림 그릴 rc
			RECT rc = RectMake(
				pos.x - TILESIZE_WID / 2,
				pos.y - sour.getHeiPosToTop() + (i*(TILESIZE_HEI / 2)) + (j*(TILESIZE_HEI / 2)),
				TILESIZE_WID,
				sour.getHei() - (i*(TILESIZE_HEI / 2)) - (j*(TILESIZE_HEI / 2)));

			//	스프라이트 가져올 시작 구간 재조정
			//	x쪽으로 올라갈때 ->  가로 변화x / 세로 -= hei/2
			//	y쪽으로 올라갈떄 ->	가로
			RECT adjSampleRc = sour.sampleRc;


			//	오브젝의 (0,0)부분 먼저 잡고시작함
			adjSampleRc.left += (sour.objTileSize.x - 1)*(TILESIZE_WID / 2);
			//	i증가(2시방향)할때마다 반타일씩, j증가(10시방향)할때마다 반타일씩
			adjSampleRc.left += (i * (TILESIZE_WID / 2)) - (j* (TILESIZE_WID / 2));
			//	right는 left에서 wid만큼.
			adjSampleRc.right = adjSampleRc.left + TILESIZE_WID;

			//	쪼개진 obj 정보 적용
			splitedObj.rc = rc;		
			splitedObj.sampleRc = adjSampleRc;


			_vvMap[idxY - i][idxX - j]->_objInfo = splitedObj;
			
			
			_vvMap[idxY - i][idxX - j]->_tileInfo.terAttr = sour.terAttr;
			
			

		}
	}

}

void mapEditor::MakeUnitOnMap(enemyForMapEditor unit, int idxX, int idxY)
{
	POINTFLOAT pos = _vvMap[idxY][idxX]->_pos;
	RECT rc = RectMake(pos.x - unit.getWidPosToLeft(),
		pos.y - unit.getHeiPosToTop(),
		unit.getWid(),
		unit.getHei());

	enemyForMapEditor tmpEnemy;
	tmpEnemy = unit;
	tmpEnemy.rc = rc;
	

	_vEnemyInfo.push_back(tmpEnemy);

}


void mapEditor::CursorSampleRender()
{
	if (_cursorTile != nullptr) {
		if (_cursorTile->_img != nullptr) {
			_cursorTile->_img->frameRenderABS(1441, 33, _cursorTile->_tileInfo.frameX, _cursorTile->_tileInfo.frameY, 1.0f);
		}
		
	}

}

void mapEditor::PreviewRender()
{
	if (_selectedTool == TOOL_BRUSH ||
		_selectedTool == TOOL_PAINT) {

		if (_cursorTile != nullptr) {
			//	타일img가 비어있지않으면 -> 타일출력
			if (_cursorTile->_tileInfo.img != nullptr) {
				_cursorTile->_tileInfo.img->frameRenderABS(_ptMouseAbs.x - TILESIZE_WID / 2, _ptMouseAbs.y - TILESIZE_HEI / 2,
					_cursorTile->_tileInfo.frameX, _cursorTile->_tileInfo.frameY, 0.5f);
			}
		}
		//	Objimg가 비어있지않으면 -> 타일출력
		else if (_cursorObj.img != nullptr) {
			_cursorObj.img->renderABS(
				_ptMouseAbs.x -_cursorObj.getWidPosToLeft(),
				_ptMouseAbs.y -_cursorObj.getHeiPosToTop(),

				_cursorObj.sampleRc.left,
				_cursorObj.sampleRc.top,

				_cursorObj.getWid(),
				_cursorObj.getHei(),
				
				0.5f);
		}
		else if (_cursorEnemy.spriteImg != nullptr) {
			_cursorEnemy.spriteImg->renderABS(
				_ptMouseAbs.x - _cursorEnemy.getWidPosToLeft(),
				_ptMouseAbs.y - _cursorEnemy.getHeiPosToTop(),

				_cursorEnemy.sampleRc.left,
				_cursorEnemy.sampleRc.top,

				_cursorEnemy.getWid(),
				_cursorEnemy.getHei(),
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
					_vvMap[idxY][idxX]->_tileInfo.frameX, _vvMap[idxY][idxX]->_frameY, 1.0f);
			}
			else if (i == 1) {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI/2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_tileInfo.frameX, 4, 1.0f);
			}
			else {
				_vvMap[idxY][idxX]->_img->frameRender(_vvMap[idxY][idxX]->_pos.x - TILESIZE_WID / 2, _vvMap[idxY][idxX]->_pos.y - TILESIZE_HEI / 2 - (TILESIZE_HEI / 2) * (_vvMap[idxY][idxX]->_zLevel - i),
					_vvMap[idxY][idxX]->_tileInfo.frameX, 5, 1.0f);
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

	if (_vvMap[idxY][idxX]->_tileInfo.pickIdx.x != _vvMap[idxY][idxX]->_mapIdx.x ||
		_vvMap[idxY][idxX]->_tileInfo.pickIdx.y != _vvMap[idxY][idxX]->_mapIdx.y) {
		POINT pickIdx = _vvMap[idxY][idxX]->_tileInfo.pickIdx;
		
		D2DMANAGER->drawDiamondLine(0x4BA5FF, _vvMap[pickIdx.y][pickIdx.x]->_pos.x, _vvMap[pickIdx.y][pickIdx.x]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 2);
	}
}

void mapEditor::SampleRender()
{
	if (_selectedMenu == MENU_TILE) {
		for (int i = 0; i < _vvTerSamples[_curTerSampleIdx].size() - 2; i++) {		//	기둥 스프라이트 필요x 그래서 -2;
			for (int j = 0; j < _vvTerSamples[_curTerSampleIdx][0].size(); j++) {
				_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.img->frameRenderABS(
					_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc.left,
					_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc.top,
					_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.frameX,
					_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.frameY,
					1.0f);

				//	테두리
				D2DMANAGER->drawRectangle(0x8673CC,
					_vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc.left + CAMERA2D->getCamPosX()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc.top + CAMERA2D->getCamPosY()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc.right + CAMERA2D->getCamPosX()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_tileInfo.rc.bottom + CAMERA2D->getCamPosY());
			}
		}
	}
	else if (_selectedMenu == MENU_OBJ) {
		for (int i = 0; i < 12; i++) {
			if (_objSamples[_curObjSampleIdx][i].objNum == OBJNUM_NONE)	continue;
			_objSamples[_curObjSampleIdx][i].img->renderABS(
				_objSamples[_curObjSampleIdx][i].sampleRc.left + SAMPLE_PALLET_START_X,
				_objSamples[_curObjSampleIdx][i].sampleRc.top + SAMPLE_PALLET_START_Y,
				_objSamples[_curObjSampleIdx][i].sampleRc.left,
				_objSamples[_curObjSampleIdx][i].sampleRc.top,
				_objSamples[_curObjSampleIdx][i].getWid(),
				_objSamples[_curObjSampleIdx][i].getHei(),
				1.0f);

			D2DMANAGER->drawRectangle(0x8673CC,
				_objSamples[_curObjSampleIdx][i].sampleRc.left + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_objSamples[_curObjSampleIdx][i].sampleRc.top + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y,
				_objSamples[_curObjSampleIdx][i].sampleRc.right + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_objSamples[_curObjSampleIdx][i].sampleRc.bottom + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y);

			
			//	중점 확인용 ==========
			D2DMANAGER->drawRectangle(0x00FF4E,
				_objSamples[_curObjSampleIdx][i].centerPosInImg.x + CAMERA2D->getCamPosX() -5 + SAMPLE_PALLET_START_X,
				_objSamples[_curObjSampleIdx][i].centerPosInImg.y + CAMERA2D->getCamPosY() -5 + SAMPLE_PALLET_START_Y,
				_objSamples[_curObjSampleIdx][i].centerPosInImg.x + CAMERA2D->getCamPosX()+ 5 + SAMPLE_PALLET_START_X,
				_objSamples[_curObjSampleIdx][i].centerPosInImg.y + CAMERA2D->getCamPosY() + 5 + SAMPLE_PALLET_START_Y
			);
				


		}
	}
	else if (_selectedMenu == MENU_UNIT) {
		for (int i = 0; i < ENEMY_NAME::E_NAME_NONE; i++) {
			_vEnemyInfo[i].spriteImg->renderABS(
				_vEnemyInfo[i].sampleRc.left + SAMPLE_PALLET_START_X,
				_vEnemyInfo[i].sampleRc.top + SAMPLE_PALLET_START_Y,
				_vEnemyInfo[i].sampleRc.left,
				_vEnemyInfo[i].sampleRc.top,
				_vEnemyInfo[i].spriteImg->GetFrameWidth(),
				_vEnemyInfo[i].spriteImg->GetFrameWidth(),
				1.0f);

			//	테두리
			D2DMANAGER->drawRectangle(0x8673CC,
				_vEnemyInfo[i].sampleRc.left + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_vEnemyInfo[i].sampleRc.top + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y,
				_vEnemyInfo[i].sampleRc.right + CAMERA2D->getCamPosX() + SAMPLE_PALLET_START_X,
				_vEnemyInfo[i].sampleRc.bottom + CAMERA2D->getCamPosY() + SAMPLE_PALLET_START_Y);


			//	중점 확인용 ==========
			D2DMANAGER->drawRectangle(0x00FF4E,
				_vEnemyInfo[i].centerPosInImg.x + CAMERA2D->getCamPosX() - 5 + SAMPLE_PALLET_START_X,
				_vEnemyInfo[i].centerPosInImg.y + CAMERA2D->getCamPosY() - 5 + SAMPLE_PALLET_START_Y,
				_vEnemyInfo[i].centerPosInImg.x + CAMERA2D->getCamPosX() + 5 + SAMPLE_PALLET_START_X,
				_vEnemyInfo[i].centerPosInImg.y + CAMERA2D->getCamPosY() + 5 + SAMPLE_PALLET_START_Y
			);

		}



	}
	
}



void mapEditor::SortedRender(int idxX, int idxY, int& objCount, int& unitCount)
{
	//	타일렌더
	if (_vvMap[idxY][idxX]->_tileInfo.img != nullptr) {
		//	맵 높이만큼 그려줌
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

	//	유닛렌더
	for (int i = 0; i < _vEnemyInfo.size(); i++) {
		if (_vEnemyInfo[i].mapIdx.x == idxX && _vEnemyInfo[i].mapIdx.y == idxY) {

			_vEnemyInfo[i].spriteImg->render(
				_vEnemyInfo[i].rc.left,
				_vEnemyInfo[i].rc.top,
				_vEnemyInfo[i].sampleRc.left,
				_vEnemyInfo[i].sampleRc.top,
				_vEnemyInfo[i].sampleRc.right - _vEnemyInfo[i].sampleRc.left,
				_vEnemyInfo[i].sampleRc.bottom - _vEnemyInfo[i].sampleRc.top,
				1.0f);
		}
	}

	//	오브젝 렌더
	if (_vvMap[idxY][idxX]->_objInfo.img != nullptr) {
		_vvMap[idxY][idxX]->_objInfo.img->render(
			_vvMap[idxY][idxX]->_objInfo.rc.left,
			_vvMap[idxY][idxX]->_objInfo.rc.top,
			_vvMap[idxY][idxX]->_objInfo.sampleRc.left,
			_vvMap[idxY][idxX]->_objInfo.sampleRc.top,
			_vvMap[idxY][idxX]->_objInfo.sampleRc.right - _vvMap[idxY][idxX]->_objInfo.sampleRc.left,
			_vvMap[idxY][idxX]->_objInfo.sampleRc.bottom - _vvMap[idxY][idxX]->_objInfo.sampleRc.top,
			1.0f
		);
	
	
	}
	
}

void mapEditor::MoveableTileRender()
{
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			if (_vvMap[i][j]->_tileInfo.terAttr == T_ATTRIBUTE::T_ATTR_UNMOVE) {
				D2DMANAGER->drawDiamondLine(0xFF0000, _vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 5.0f);
			}
			else {
				D2DMANAGER->drawDiamondLine(0x00CC00, _vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 5.0f);
			}
			
		}
	}
}

void mapEditor::MapIdxRender()
{
	WCHAR wstr[128];

	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			swprintf_s(wstr, L"[%d/%d]", _vvMap[i][j]->_mapIdx.x, _vvMap[i][j]->_mapIdx.y);
			D2DMANAGER->drawTextD2D(D2DMANAGER->createBrush(0x000000, 1.0f), L"consolas", 15, wstr, _vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, true, D2DMANAGER->createBrush(0xFFFFFF, 1.0f));
		}
	}
}

