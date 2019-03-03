#pragma once
#include "gameNode.h"
#include "tileNode.h"
class mapEditor : public gameNode
{
private:
	struct tagButtons {
		image* img;
		RECT rc;
		bool isOn;
	};

	enum E_TOOLS {
		TOOL_NONE = -1,
		TOOL_CURSOR,
		TOOL_MAGICBONG,
		TOOL_SPOID,
		TOOL_TILE_ERASER,
		TOOL_OBJ_ERASER,
		TOOL_PAINT,
		TOOL_HAND,
		TOOL_END,
	};

	enum E_MENU {
		MENU_NONE = -1,
		MENU_MAPIDX,
		MENU_SAVE,
		MENU_LOAD,
		MENU_TILE,
		MENU_OBJ,
		MENU_UNIT,
		MENU_AREAMODE,
		MENU_AREAIDX,
		MENU_END,
	};

	vector<pair<string, image*>> _vSampleImg;
	POINT _tileNum;
	vvMap _vvMap;
	vObj _vObj;
	
	image* _frameImg;
	tagButtons _buttons[8];
	tagButtons _toolIcons[7];

	int _mapIdx;
	int _areaIdx;

	int _selectedTool;
	int _selectedMenu;

	RECT _mapTileRc;
	POINT _cursorSelectIdx[2];
	bool _isLButtonDown;
	


public:
	mapEditor();
	~mapEditor();

	HRESULT init();
	HRESULT init(int tileNumX, int tileNumY);
	void release();
	void update();
	void render();

	void SelectToolFunc();
	void SelectMenuFunc();
	void SelectMapTile();

};

