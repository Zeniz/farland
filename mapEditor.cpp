#include "stdafx.h"
#include "mapEditor.h"


mapEditor::mapEditor()
{
	IMAGEMANAGER->addImage("frame", L"images/mapEditor/frame.png", 1600, 900);
	IMAGEMANAGER->addFrameImage("buttons", L"images/mapEditor/buttons.png", 320, 256, 2, 8);
	IMAGEMANAGER->addFrameImage("toolIcons", L"images/mapEditor/toolIcons.png", 128, 448, 2, 7);


	IMAGEMANAGER->addFrameImage("sample1", L"images/map/map1.png", 768, 256, 6, 4);


	//	카메라 설정
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);



	_vSampleImg.clear();
	_vSampleImg.push_back(make_pair("sample1", IMAGEMANAGER->findImage("sample1")));


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

			tmpTile->_pos = ConvertIdxToPos(j, i, TILESIZE_WID, TILESIZE_HEI);

			//tmpTile->_pos.x = WINSIZEX / 2 + ((j - i)*(TILESIZE_WID / 2));			//tmpPt.x = WINSIZEX / 2 - (i*(TILESIZE_WID / 2)) + (j*(TILESIZE_WID / 2));
			//tmpTile->_pos.y = TILESIZE_HEI / 2 + ((i + j) * (TILESIZE_HEI / 2));	//TILESIZE_HEI / 2 + (i * (TILESIZE_HEI / 2)) + (j * (TILESIZE_HEI/2));

			_vLine.push_back(tmpTile);
		}
		_vvMap.push_back(_vLine);
	}

	_frameImg = IMAGEMANAGER->findImage("frame");

	for (int i = 0; i < 8; i++) {
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
	for (int i = 0; i < 7; i++) {
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
	_isLButtonDown = false;
	
	_mapTileRc = { 64,32,1408,900 };
}


mapEditor::~mapEditor()
{
}

HRESULT mapEditor::init()
{
	POINT tmpPt = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpPt, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);

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
			tmpTile->_pos = ConvertIdxToPos(j, i, TILESIZE_WID, TILESIZE_HEI);

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
	_isLButtonDown = false;
	

	return S_OK;
}

HRESULT mapEditor::init(int tileNumX, int tileNumY)
{
	POINT tmpCamStartPos = { -WINSIZEX / 2,0 };
	CAMERA2D->setFocusOn(tmpCamStartPos, cameraState::EVENT_CAMERA);
	CAMERA2D->setState(cameraState::EVENT_CAMERA);

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
			tmpTile->_pos = ConvertIdxToPos(j, i, TILESIZE_WID, TILESIZE_HEI);
			
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
	_isLButtonDown = false;

	return S_OK;
}

void mapEditor::release()
{
}

void mapEditor::update()
{
	CAMERA2D->update();
	if (!PtInRect(&_mapTileRc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
		SelectToolFunc();
		SelectMenuFunc();
	}
	else {
		SelectMapTile();
	}
	
	


}

void mapEditor::render()
{
	//	맵타일 윤곽선그리기
	for (int i = 0; i < _tileNum.y; i++) {
		for (int j = 0; j < _tileNum.x; j++) {
			D2DMANAGER->drawDiamondLine(_vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI);
		}
	}

	//	선택된 맵타일 윤곽선
	if (_cursorSelectIdx[0].x != -1 && _cursorSelectIdx[0].y != -1) {
		for (int i = _cursorSelectIdx[0].y; i <= _cursorSelectIdx[1].y; i++) {
			for (int j = _cursorSelectIdx[0].x; j <= _cursorSelectIdx[1].x; j++) {
				D2DMANAGER->drawDiamondLine(0xFF0000, _vvMap[i][j]->_pos.x, _vvMap[i][j]->_pos.y, TILESIZE_WID, TILESIZE_HEI,2);
			}
		}
	}
	
	
	//	프레임 -> 마지막에 출력
	_frameImg->renderABS();
	for (int i = 0; i < 8; i++) {
		_buttons[i].img->frameRenderABS(_buttons[i].rc.left, _buttons[i].rc.top, _buttons[i].isOn, i, 1.0f);
		
	}
	for (int i = 0; i < 7; i++) {
		_toolIcons[i].img->frameRenderABS(_toolIcons[i].rc.left, _toolIcons[i].rc.top, _toolIcons[i].isOn, i, 1.0f);
	}


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
}

void mapEditor::SelectMenuFunc()
{
	for (int i = E_MENU::MENU_SAVE; i < E_MENU::MENU_END; i++) {
		if (i == MENU_MAPIDX || i == MENU_AREAIDX)	continue;
		if (PtInRect(&_buttons[i].rc, PointMake(_ptMouseAbs.x, _ptMouseAbs.y))) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				if (_selectedMenu != -1) 
					_buttons[_selectedMenu].isOn = false;
				_selectedMenu = i;
				_buttons[i].isOn = true;
			}
		}
	}
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
					_isLButtonDown = true;
					_cursorSelectIdx[0] = { j,i };
					_cursorSelectIdx[1] = { j,i };
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
					_isLButtonDown = false;
					_cursorSelectIdx[1] = { j,i };
				}
			}
		}
	}
}
