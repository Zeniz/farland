#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "enemyForMapEditor.h"



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

	
	vvMap _vvTerSamples[TERNUM_END];							//	�ٴ�Ÿ�� ���� �����
	tagObjInfo _objSamples[OBJNUM::OBJNUM_END][20];				//	obj	���� �����
	enemyForMapEditor _enemySamples[ENEMY_NAME::E_NAME_END];

	vector<enemyForMapEditor> _vEnemyInfo;

	vector<POINT> _vMagicSelectList;


	POINT _tileNum;
	vvMap _vvMap;
	
	
	image* _frameImg;					//���� �̹���
	tagButtons _buttons[MENU_END];
	tagButtons _toolIcons[TOOL_END];

	int _mapIdx;
	int _areaIdx;

	int _selectedTool;
	int _selectedMenu;

	RECT _mapTileRc;
	POINT _cursorSelectIdx[2];
	POINT _cursorSelectIdxSorted[2];
	

	bool _isChoosingSample;
	int _curTerSampleIdx;		//	���� �����̹��� ��ȣ		   -> ���� ������ 1���� �ǹ̾���
	int _curObjSampleIdx;		//	���� ������ �����̹��� �ε���
	int _curUnitSampleIdx;		//	���� ���� �����̹��� �ε���  -> ���� ������1���� �ǹ̾���
	TILE* _cursorTile;			//	Ŀ���� ���� Ÿ��
	tagObjInfo _cursorObj;
	enemyForMapEditor _cursorEnemy;	//	Ŀ���� ���� ��
	
	

	POINTF _ptMousePrePos;	//	�ڵ�����

	int _resizeMapCounter;
	int _mapIdxAdjustCounter;

	POINT _clipMapIdx[2];
	
	const int MAPIDX_COUNT_MAX = 5;
	const int RESIZE_MAP_COUNT_MAX = 5;
	const int SAMPLE_PALLET_START_X = 65;
	const int SAMPLE_PALLET_START_Y = 33;

	const int CLIP_TILENUM_WID = 35;
	const int CLIP_TILENUM_HEI = 35;
	

public:
	mapEditor();
	~mapEditor();

	HRESULT init();
	HRESULT init(int tileNumX, int tileNumY);
	void release();
	void update();
	void render();

	HRESULT InitTileSamples();
	HRESULT InitObjSamples();
	HRESULT InitMobSamples();

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
	
	void ClearInfoInCursor();

	void SetClipRangeFunc();


	//	===	ToolsFunc ===
	void SelectMapTile();	//	cursor�� Ÿ�ϵ� �����ϴ� func
	void BrushTile();
	void MagicSelect();
	void SpoidFunc();
	void EraseTile();
	void EraseObj();
	void PaintFunc();
	void HandFunc();

	void MakeHillFunc(int augZlvl);
	

	//	=== MenusFunc ===
	void SaveMapFunc();
	void LoadMapFunc();
	void TileSampleFunc();
	void ObjSampleFunc();
	void UnitSampleFunc();


	//	===	utils ===
	POINT CursorPtToSampleIdx();
	void TransTileValue(TILE* sour, TILE* dest);
	void TransObjValue(TILE* sour, TILE* dest);
	void DeleteUnit(int idxX, int idxY);
	bool IsSameTile(TILE* sour, TILE* dest);
	void MakeTileOnMap(TILE* sour, int idxX, int idxY);
	void MakeObjOnMap(tagObjInfo sour, int idxX, int idxY);
	void MakeUnitOnMap(enemyForMapEditor unit, int idxX, int idxY);
	

	//	===	render ===
	void CursorSampleRender();	//	Ŀ���� ���� ���� Ÿ�� �������� ����
	void PreviewRender();
	void MagicSelectRender();
	
	void PickIdxTileRender(int idxX, int idxY);
	void SampleRender();

	void TileRender(int idxX, int idxY);
	
	void SortedRender(int idxX, int idxY, int& objCount, int& unitCount);
	
	void MoveableTileRender();
	

};

//

/*

//	Ŭ����
for (int i = _clipMapIdx[0].y; i < _clipMapIdx[1].y; i++) {
	for (int j = _clipMapIdx[0].x; j < _clipMapIdx[1].x; j++) {
		if (i < 0)				continue;
		if (i > _tileNum.y - 1)	continue;
		if (j < 0)				continue;
		if (j > _tileNum.x - 1)	continue;

		*/