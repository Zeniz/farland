#include "stdafx.h"
#include "mapEditor.h"
#pragma warning(disable: 4996)

mapEditor::mapEditor()
{
	IMAGEMANAGER->addImage("frame", L"images/mapEditor/frame.png", 1600, 900);
	IMAGEMANAGER->addFrameImage("buttons", L"images/mapEditor/buttons.png", 320, 256, 2, 8);
	IMAGEMANAGER->addFrameImage("toolIcons", L"images/mapEditor/toolIcons.png", 128, 512, 2, 8);


	IMAGEMANAGER->addFrameImage("tile1", L"images/map/tileSample1.png", 640, 384, 5, 6);
	

	initSamples();

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
	_cursorTile = nullptr;

	_ptMousePrePos = { -1,-1 };

	_resizeMapCounter = 0;
	_mapIdxAdjustCounter = 0;
	
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

	_ptMousePrePos = { -1,-1 };

	_resizeMapCounter = 0;
	_mapIdxAdjustCounter = 0;

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

	_ptMousePrePos = { -1,-1 };

	_resizeMapCounter = 0;
	_mapIdxAdjustCounter = 0;

	return S_OK;
}

void mapEditor::release()
{
}

void mapEditor::update()
{
	CAMERA2D->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		_cursorTile = nullptr;
		_cursorSelectIdx[0].x = -1;
		_cursorSelectIdx[0].y = -1;
		_cursorSelectIdx[1].x = -1;
		_cursorSelectIdx[1].y = -1;
		_vMagicSelectList.clear();
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
	//	맵타일 
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			//윤곽선그리기
			D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);
			//	타일그림
			TileRender(j, i);
		}
	}

	//	선택된 맵타일 윤곽선
	if (_cursorSelectIdxSorted[0].x != -1 && _cursorSelectIdxSorted[0].y != -1) {
		for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
			for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
				D2DMANAGER->drawDiamondLine(0xFF0000, _vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 2);
			}
		}
	}
	
	//	매직선택 윤곽선
	MagicSelectRender();

	//	커서 미리보기 렌더
	PreviewRender();



	if (_isChoosingSample) {
		//	테스트용 샘플출력
		for (int i = 0; i < _vvTerSamples[_curTerSampleIdx].size(); i++) {
			for (int j = 0; j < _vvTerSamples[_curTerSampleIdx][0].size(); j++) {
				_vvTerSamples[_curTerSampleIdx][i][j]->_img->frameRenderABS(
					_vvTerSamples[_curTerSampleIdx][i][j]->_rc.left,
					_vvTerSamples[_curTerSampleIdx][i][j]->_rc.top,
					_vvTerSamples[_curTerSampleIdx][i][j]->_frameX,
					_vvTerSamples[_curTerSampleIdx][i][j]->_frameY,
					1.0f);
				D2DMANAGER->drawRectangle(0xFF0000,
					_vvTerSamples[_curTerSampleIdx][i][j]->_rc.left + CAMERA2D->getCamPosX()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_rc.top + CAMERA2D->getCamPosY()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_rc.right + CAMERA2D->getCamPosX()
					, _vvTerSamples[_curTerSampleIdx][i][j]->_rc.bottom + CAMERA2D->getCamPosY());
			}
		}
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

HRESULT mapEditor::initSamples()
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
				j, i, { NULL,NULL }, T_ATTRIBUTE::T_ATTR_NONE, pos, rc, 0);

			vLine.push_back(tmpTile);
		}
		_vvTerSamples[TERNUM_BASIC].push_back(vLine);
	}



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
		TileSampleFunc();

		break;
	case MENU_OBJ:


		break;
	case MENU_UNIT:


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

void mapEditor::SelectMapTile()
{
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
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

		for (int i = 0; i < _tileNum.y; i++) {
			for (int j = 0; j < _tileNum.x; j++) {
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

}

void mapEditor::MagicSelect()
{

	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
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
				}
			}
		}
	}
}

void mapEditor::SpoidFunc()
{
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					if (_vvMap[i][j]->_terImgNum != TERNUM_NONE) {
						TransTileValue(_vvMap[i][j], _cursorTile);
					}
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
		for (int i = 0; i < _tileNum.y; i++) {
			for (int j = 0; j < _tileNum.x; j++) {
				if (PtInDiamond(_vvMap[i][j]->_pos, _ptMouse)) {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {

						TransTileValue(&nullTile, _vvMap[i][j]);
					}
				}
			}
		}
	}
	

}

void mapEditor::EraseObj()
{
}

void mapEditor::PaintFunc()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (_vMagicSelectList.size() == 0) {
			for (int i = _cursorSelectIdxSorted[0].y; i <= _cursorSelectIdxSorted[1].y; i++) {
				for (int j = _cursorSelectIdxSorted[0].x; j <= _cursorSelectIdxSorted[1].x; j++) {
					TransTileValue(_cursorTile, _vvMap[i][j]);
				}
			}
		}
		else {
			for (int i = 0; i < _vMagicSelectList.size(); i++) {
				POINT idx = _vMagicSelectList[i];
				TransTileValue(_cursorTile, _vvMap[idx.y][idx.x]);
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
				if (_vvMap[i][j]->_zLevel + augZlvl > 0) {
					_vvMap[i][j]->_zLevel += augZlvl;
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
			}
		}
	}
}


void mapEditor::SaveMapFunc()
{

	HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData;
	DWORD writeForMapSize, writeForMapData , writeForObjSize, writeForObjData;


	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForObjSize[20] = "objSize";

	char idxBuffer[5] = {};		//	맵 인덱스 저장소
	char mapSizeStr[20] = {};		//	맵 크기 str저장소
	char objSizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa임시 저장소
	char objNumBuffer[10] = {};		//	itoa임시 저장소

	//	파일이름 생성
	itoa(_mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");

	strcat_s(fileNameForObjSize, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForObjSize, sizeof(fileNameForMap), ".map");
	strcat_s(fileNameForObj, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForObj, sizeof(fileNameForMap), ".map");

	
	//	맵 크기 str 생성
	itoa(_tileNum.x, tileNumBuffer, 10);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), tileNumBuffer);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), ",");
	itoa(_tileNum.y, tileNumBuffer, 10);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), tileNumBuffer);
	strcat_s(mapSizeStr, sizeof(mapSizeStr), ",");

	//	OBJ 크기 str 생성
	itoa(_vObj.size(), objNumBuffer, 10);
	strcat_s(objSizeStr, sizeof(objSizeStr), objNumBuffer);
	strcat_s(objSizeStr, sizeof(objSizeStr), ",");
	
	//	맵크기 저장한 파일 생성
	fileForMapSize = CreateFile(fileNameForMapSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(fileForMapSize, mapSizeStr, sizeof(mapSizeStr), &writeForMapSize, NULL);
	CloseHandle(fileForMapSize);

	//	vObj크기 저장한 파일 생성
	fileForObjSize = CreateFile(fileNameForObjSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(fileForObjSize, objSizeStr, sizeof(objSizeStr), &writeForObjSize, NULL);
	CloseHandle(fileForObjSize);

	//==============================

	//	vv맵 데이터 1차배열로 복사중...
	TILE* saveTileAry = new TILE[_tileNum.x * _tileNum.y];
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			saveTileAry[i*_tileNum.x + j] = *_vvMap[i][j];
		}
	}


	fileForMapData = CreateFile(fileNameForMap, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(fileForMapData, saveTileAry, sizeof(TILE)*_tileNum.x * _tileNum.y, &writeForMapData, NULL);
	CloseHandle(fileForMapSize);
	delete[] saveTileAry;

	//==============================

	//	v오브젝트 데이터 1차배열로 복사중...
	OBJ* saveObjAry = new OBJ[_vObj.size()];
	for (int i = 0; i < _vObj.size(); i++) {
		saveObjAry[i] = *_vObj[i];
	}

	fileForObjData = CreateFile(fileNameForObj, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(fileForObjData, saveObjAry, sizeof(OBJ)*_vObj.size(), &writeForObjData, NULL);
	CloseHandle(fileForObjData);
	delete[] saveObjAry;


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


	HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData;
	DWORD readForMapSize, readForMapData, readForObjSize, readForObjData;

	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForObjSize[20] = "objSize";

	char idxBuffer[5] = {};		//	맵 인덱스 저장소
	char mapSizeStr[20] = {};		//	맵 크기 str저장소
	char objSizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa임시 저장소
	char objNumBuffer[10] = {};		//	itoa임시 저장소

	char* token;			
	char* context;		
	int tmpInt;
	int vObjSize;

	//	파일이름 생성
	itoa(_mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");

	strcat_s(fileNameForObjSize, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForObjSize, sizeof(fileNameForMap), ".map");
	strcat_s(fileNameForObj, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForObj, sizeof(fileNameForMap), ".map");

	//	맵크기 로드
	fileForMapSize = CreateFile(fileNameForMapSize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapSize, mapSizeStr, 20, &readForMapSize, NULL);
	CloseHandle(fileForMapSize);

	//	오브제 크기 로드
	fileForObjSize = CreateFile(fileNameForObjSize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjSize, objSizeStr, 20, &readForObjSize, NULL);
	CloseHandle(fileForObjSize);

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

	//	벡터 리사이즈
	_vvMap.reserve(_tileNum.y);
	for (int i = 0; i < _tileNum.y; i++) {
		_vvMap[i].reserve(_tileNum.x);
	}

	_vObj.reserve(vObjSize);

	//	맵데이터 로드
	TILE* savedTileAry = new TILE[_tileNum.x * _tileNum.y];
	ZeroMemory(savedTileAry, sizeof(TILE) * (_tileNum.x * _tileNum.y));

	fileForMapData = CreateFile(fileNameForMap, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapData, savedTileAry, sizeof(TILE) * _tileNum.x * _tileNum.y, &readForMapData, NULL);
	CloseHandle(fileForMapData);

	//	vv맵에 데이터 적용
	for (int i = 0; i < _tileNum.y; i++) {
		vLine tmpVLine;
		tmpVLine.clear();
		tmpVLine.reserve(_tileNum.x);
		for (int j = 0; j < _tileNum.x; j++) {
			TILE* tmpTile = new TILE;
			*tmpTile = savedTileAry[i*_tileNum.x + j];
			tmpVLine.push_back(tmpTile);
		}
		_vvMap.push_back(tmpVLine);
	}

	//	obj데이터 로드
	OBJ* savedObjAry = new OBJ[vObjSize];
	ZeroMemory(savedObjAry, sizeof(OBJ) * (vObjSize));

	fileForObjData = CreateFile(fileNameForObj, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjData, savedObjAry, sizeof(OBJ) * vObjSize, &readForObjData, NULL);
	CloseHandle(fileForObjData);

	//	vObj에 데이터 적용
	for (int i = 0; i < vObjSize; i++) {
		OBJ* tmpObj = new OBJ;
		*tmpObj = savedObjAry[i];
		_vObj.push_back(tmpObj);
	}

}

void mapEditor::TileSampleFunc()
{
	for (int i = 0; i < _vvTerSamples[_curTerSampleIdx].size(); i++) {
		for (int j = 0; j < _vvTerSamples[_curTerSampleIdx][0].size(); j++) {
			if (PtInRect(&_vvTerSamples[_curTerSampleIdx][i][j]->_rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_cursorTile = _vvTerSamples[_curTerSampleIdx][i][j];
				}
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
	dest->_zLevel = sour->_zLevel;


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

void mapEditor::CursorSampleRender()
{
	if (_cursorTile != nullptr) {
		_cursorTile->_img->frameRenderABS(1441, 33, _cursorTile->_frameX, _cursorTile->_frameY, 1.0f);
	}

}

void mapEditor::PreviewRender()
{
	if (_cursorTile != nullptr) {
		if (_selectedTool == TOOL_BRUSH ||
			_selectedTool == TOOL_PAINT) {
			_cursorTile->_img->frameRenderABS(_ptMouseAbs.x - TILESIZE_WID / 2, _ptMouseAbs.y - TILESIZE_HEI / 2,
				_cursorTile->_frameX, _cursorTile->_frameY, 0.5f);
		}
	}
}

void mapEditor::MagicSelectRender()
{
	for (int i = 0; i < _vMagicSelectList.size(); i++) {
		POINT idx = _vMagicSelectList[i];
		D2DMANAGER->drawDiamondLine(0xFF0000, _vvMap[idx.y][idx.x]->_pos.x, _vvMap[idx.y][idx.x]->_pos.y, TILESIZE_WID, TILESIZE_HEI, 2);
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
