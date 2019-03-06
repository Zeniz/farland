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
	vObj _vObj;						//	info만 저장하도록 고쳐야함. 나중에 로드할때 진짜 세팅->zorder떄무네 써야함...
	vEnemy _vEnemy;

	vector<tagObjSpriteInfo*> _vObjInfo;		//	안씀 ㅠㅠ zorder때무네...
	vector<tagEnemySpriteInfoForMapEditor*> _vEnemyInfo;		//	안씀 ㅠㅠ zorder때무네...
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
	int _curTerSampleIdx;		//	현재 샘플이미지 번호		   -> 현재 페이지 1개라 의미없음
	int _curObjSampleIdx;		//	현재 오브젝 샘플이미지 인덱스
	int _curUnitSampleIdx;		//	현재 유닛 샘플이미지 인덱스  -> 현재 페이지1개라 의미없음
	TILE* _cursorTile;			//	커서에 뭍힌 오브젝트
	tagObjSpriteInfo _cursorObjInfo;
	tagEnemySpriteInfoForMapEditor _cursorUnitInfo;
	

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
	void SelectMapTile();	//	cursor로 타일들 선택하는 func
	void BrushTile();
	void MagicSelect();
	void SpoidFunc();
	void EraseTile();
	void EraseObj();
	void PaintFunc();
	void HandFunc();

	void MakeHillFunc(int augZlvl);
	void AdjustHillToObj(int idxX, int idxY, int augHeiLvl);	//언덕이 생기면, rc를 움직일거냐, 렌더를 계산해줄거냐...-> 일단 rc움직이는걸로
	void AdjustHillToEnemy(int idxX, int idxY, int augHeiLvl);	//언덕이 생기면, rc를 움직일거냐, 렌더를 계산해줄거냐...-> 일단 rc움직이는걸로

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
	void CursorSampleRender();	//	커서가 현재 잡은 타일 우측위에 렌더
	void PreviewRender();
	void MagicSelectRender();
	
	void PickIdxTileRender(int idxX, int idxY);
	void SampleRender();

	void TileRender(int idxX, int idxY);
	void ObjRender();		//	z-order로 바꿔야함
	void UnitRender();		//	z-order로 바꿔야함
	void SortedRender(int idxX, int idxY);
	void ObjRender(int idxX, int idxY);		//	sort 되어있음! render만 ㄱㄱ
	void UnitRender(int idxX, int idxY);

};

