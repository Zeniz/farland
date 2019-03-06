#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "enemy.h"
#include "skeleton.h"
#include "objects.h"
#include <algorithm>

class mapEditor : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;

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

	
	vvMap _vvTerSamples[TERNUM_END];
	vector<POINT> _vMagicSelectList;


	POINT _tileNum;
	vvMap _vvMap;
	vObj _vObj;						//	info�� �����ϵ��� ���ľ���. ���߿� �ε��Ҷ� ��¥ ����->zorder������ �����...
	vEnemy _vEnemy;

	vector<tagObjSpriteInfo*> _vObjInfo;		//	�Ⱦ� �Ф� zorder������...
	vector<tagEnemySpriteInfoForMapEditor*> _vEnemyInfo;		//	�Ⱦ� �Ф� zorder������...
	vector<objects> _vZOrder;
	
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
	

	bool _isChoosingSample;
	int _curTerSampleIdx;		//	���� �����̹��� ��ȣ		   -> ���� ������ 1���� �ǹ̾���
	int _curObjSampleIdx;		//	���� ������ �����̹��� �ε���
	int _curUnitSampleIdx;		//	���� ���� �����̹��� �ε���  -> ���� ������1���� �ǹ̾���
	TILE* _cursorTile;			//	Ŀ���� ���� ������Ʈ
	tagObjSpriteInfo _cursorObjInfo;
	tagEnemySpriteInfoForMapEditor _cursorUnitInfo;
	

	POINTF _ptMousePrePos;	//	�ڵ�����

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
	void AdjustHillToObj(int idxX, int idxY, int augHeiLvl);	//����� �����, rc�� �����ϰų�, ������ ������ٰų�...-> �ϴ� rc�����̴°ɷ�
	void AdjustHillToEnemy(int idxX, int idxY, int augHeiLvl);	//����� �����, rc�� �����ϰų�, ������ ������ٰų�...-> �ϴ� rc�����̴°ɷ�

	//	=== MenusFunc ===
	void SaveMapFunc();
	void LoadMapFunc();
	void TileSampleFunc();
	void ObjSampleFunc();
	void UnitSampleFunc();


	//	===	utils ===
	POINT CursorPtToSampleIdx();
	void TransTileValue(TILE* sour, TILE* dest);
	bool IsSameTile(TILE* sour, TILE* dest);
	void MakeObjOnMap(tagObjSpriteInfo obj, int idxX, int idxY);
	void MakeUnitOnMap(tagEnemySpriteInfoForMapEditor unit, int idxX, int idxY);
	

	//	===	render ===
	void CursorSampleRender();	//	Ŀ���� ���� ���� Ÿ�� �������� ����
	void PreviewRender();
	void MagicSelectRender();
	
	void PickIdxTileRender(int idxX, int idxY);
	void SampleRender();

	void TileRender(int idxX, int idxY);
	void ObjRender();		//	z-order�� �ٲ����
	void UnitRender();		//	z-order�� �ٲ����
	void SortedRender(int idxX, int idxY);
	void ObjRender(int idxX, int idxY);		//	sort �Ǿ�����! render�� ����
	void UnitRender(int idxX, int idxY);

};

