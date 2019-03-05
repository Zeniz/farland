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
		TOOL_BRUSH,
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

	//vector<image*> _vSampleTerImg;
	vvMap _vvTerSamples[TERNUM_END];
	vector<POINT> _vMagicSelectList;


	POINT _tileNum;
	vvMap _vvMap;
	vObj _vObj;
	
	image* _frameImg;
	tagButtons _buttons[MENU_END];
	tagButtons _toolIcons[TOOL_END];

	int _mapIdx;
	int _areaIdx;

	int _selectedTool;
	int _selectedMenu;

	RECT _mapTileRc;
	POINT _cursorSelectIdx[2];
	POINT _cursorSelectIdxSorted[2];
	//bool _isLButtonDown;

	bool _isChoosingSample;
	int _curTerSampleIdx;		//	현재 샘플이미지 번호
	int _curObjSampleIdx;		//	현재 오브젝 샘플이미지 인덱스
	TILE* _cursorTile;			//	커서에 뭍힌 오브젝트
	tagObjSpriteInfo _cursorObjInfo;

	POINTF _ptMousePrePos;	//	핸드툴용

	int _resizeMapCounter;
	int _mapIdxAdjustCounter;
	
	const int MAPIDX_COUNT_MAX = 5;
	const int RESIZE_MAP_COUNT_MAX = 5;
	const int SAMPLE_PALLET_START_X = 65;
	const int SAMPLE_PALLET_START_Y = 33;
	

public:
	mapEditor();
	~mapEditor();

	HRESULT init();
	HRESULT init(int tileNumX, int tileNumY);
	void release();
	void update();
	void render();

	HRESULT initSamples();
	void InitObjInfo();

	void SelectToolFunc();
	void SelectMenuFunc();
	

	void SwitchToolsFunc();
	void SwitchMenusFunc();

	//	===	otherFunc ===
	void AdjustMapIdxFunc();
	void ResizeMapFunc();
	void AddMapX();
	void AddMapY();
	void EraseMapX();
	void EraseMapY();

	
	


	//	===	ToolsFunc ===
	void SelectMapTile();	//	cursor
	void BrushTile();
	void MagicSelect();
	void SpoidFunc();
	void EraseTile();
	void EraseObj();
	void PaintFunc();
	void HandFunc();

	void MakeHillFunc(int augZlvl);
	void AdjustHillToObj(int idxX, int idxY, int augHeiLvl);

	//	=== MenusFunc ===
	void SaveMapFunc();
	void LoadMapFunc();
	void TileSampleFunc();
	void ObjSampleFunc();


	//	===	utils ===
	POINT CursorPtToSampleIdx();
	void TransTileValue(TILE* sour, TILE* dest);
	bool IsSameTile(TILE* sour, TILE* dest);
	void MakeObjOnMap(tagObjSpriteInfo obj, int idxX, int idxY);
	

	//	===	render ===
	void CursorSampleRender();	//	커서가 현재 잡은 타일 우측위에 렌더
	void PreviewRender();
	void MagicSelectRender();
	void TileRender(int idxX, int idxY);
	void PickIdxTileRender(int idxX, int idxY);
	void SampleRender();
	void ObjRender();

};

