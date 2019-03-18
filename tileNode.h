#pragma once
#include "gameNode.h"
#include "objects.h"

const int TILESIZE_WID = 128;
const int TILESIZE_HEI = 64;



//타일 속성
enum T_ATTRIBUTE
{
	T_ATTR_NONE = 0x00000000UL,
	T_ATTR_UNMOVE = 0x00000001UL,
	T_ATTR_UNITON = 0x00000002UL,
};

//지형 이미지 키값 배열 번호
typedef enum TERRAIN_ARRAY_NUM
{
	TERNUM_NONE = -1,
	TER_BASIC,

	TERNUM_END,



}TERNUM;

typedef enum OBJECT_ARRAY_NUM
{
	OBJNUM_NONE = -1,
	OBJ_BASIC,
	OBJ_HOUSE,
	OBJ_COMB,
	OBJ_CRYSTAL,

	
	OBJNUM_END,
}OBJNUM;
//지형 이미지 키값
static string _terrainImageKey[10] = { "tile1","","","","","","","","","" };
static string _objectImageKey[10] = { "objSample1","objSample2","objSample3","objSample4","","","","","","" };


struct tagTileInfo {

	image* img;
	TERRAIN_ARRAY_NUM terImgNum;
	int frameX;
	int frameY;
	POINT pickIdx;

	T_ATTRIBUTE terAttr;
	RECT rc;

	int zlvl;
	
	void setTileInfo(TERRAIN_ARRAY_NUM terImgNum,
		int frameX, int frameY, POINT pickIdx,
		T_ATTRIBUTE terAttr, RECT rc, int zlvl) {
		
		this->terImgNum = terImgNum;
		this->frameX = frameX;
		this->frameY = frameY;
		this->pickIdx = pickIdx;

		this->terAttr = terAttr;
		
		this->rc = rc;
		this->zlvl = zlvl;


		if (terImgNum != TERNUM::TERNUM_NONE) {
			switch (terImgNum)
			{
			case TERNUM_NONE:
				break;
			case TER_BASIC:
				img = IMAGEMANAGER->findImage(_terrainImageKey[TER_BASIC].c_str());
				break;
			case TERNUM_END:
				break;
			default:
				break;
			}
		}

	}

	void BrushTileInfo(TERRAIN_ARRAY_NUM terImgNum,
		int frameX, int frameY) {

		this->terImgNum = terImgNum;
		this->frameX = frameX;
		this->frameY = frameY;
		
		if (terImgNum != TERNUM::TERNUM_NONE) {
			switch (terImgNum)
			{
			case TERNUM_NONE:
				break;
			case TER_BASIC:
				img = IMAGEMANAGER->findImage(_terrainImageKey[TER_BASIC].c_str());
				break;
			case TERNUM_END:
				break;
			default:
				break;
			}
		}

	}

	tagTileInfo getTileInfo() {
		tagTileInfo tileInfo;
		tileInfo.img = this->img;
		tileInfo.terImgNum = this->terImgNum;
		tileInfo.frameX = this->frameX;
		tileInfo.frameY = this->frameY;
		tileInfo.pickIdx = this->pickIdx;
		tileInfo.terAttr = this->terAttr;
		tileInfo.rc = this->rc;
		tileInfo.zlvl = this->zlvl;
		

		return tileInfo;
	}

	void init() {
		this->img = nullptr;
		this->terImgNum = TERNUM_NONE;
		this->frameX = NULL;
		this->frameY = NULL;
		this->pickIdx = { NULL,NULL };

		this->terAttr = T_ATTR_NONE;
		this->rc = { NULL,NULL,NULL,NULL };
		this->zlvl = NULL;
		
	}

};

struct tagObjInfo {

	image* img;
	OBJNUM objNum;
	RECT sampleRc;
	POINT mapIdx;

	POINTFLOAT pos;
	RECT rc;
	//int zLevel;

	//	맵에디터에서 쓰이는 용도
	POINT centerPosInImg;		// 선택시, 중심이 되는좌표 (마우스가 끌고다니는 좌표)
	POINT objTileSize;			//	중심좌표로부터, x,y방향으로 타일사이즈 크기



	void setObjInfo(OBJNUM objImgNum,
		RECT sampleRc, POINT idx,
		POINTFLOAT pos, RECT rc, int zlvl, 
		POINT centerPosInImg, POINT objTileSize) {

		this->objNum = objImgNum;
		this->sampleRc = sampleRc;
		this->mapIdx = idx;
		
		this->pos = pos;
		this->rc = rc;

		this->centerPosInImg = centerPosInImg;
		this->objTileSize = objTileSize;
		
		

		if (this->objNum != OBJNUM_NONE) {
			switch (this->objNum)
			{
				//	오브제 종류에 따라서, 이미지매니저한테서 img 넣어줌
			case OBJ_BASIC:
				this->img = IMAGEMANAGER->findImage(_objectImageKey[OBJ_BASIC].c_str());
				break;

			default:
				break;
			}
		}

	}

	tagObjInfo getObjInfo() {
		tagObjInfo objInfo;
		objInfo.img = this->img;
		objInfo.objNum = this->objNum;
		objInfo.sampleRc = this->sampleRc;
		objInfo.mapIdx = this->mapIdx;
		objInfo.pos = this->pos;
		objInfo.rc = this->rc;
		objInfo.centerPosInImg = this->centerPosInImg;
		objInfo.objTileSize = this->objTileSize;



		return objInfo;
	}


	void init() {
		this->img = nullptr;
		this->objNum = OBJNUM_NONE;
		this->sampleRc = { NULL,NULL,NULL,NULL };
		this->mapIdx = { NULL,NULL };
		

		this->pos = { NULL,NULL };
		this->rc = { NULL,NULL,NULL,NULL };
		
		this->centerPosInImg = { NULL,NULL };
		this->objTileSize = { NULL,NULL };
	}

	int getWid() {
		return this->sampleRc.right - this->sampleRc.left;
	}
	int getHei() {
		return this->sampleRc.bottom - this->sampleRc.top;
	}

	int getHeiPosToTop() {
		return this->centerPosInImg.y - this->sampleRc.top;
	}
	int getWidPosToLeft() {
		return this->centerPosInImg.x - this->sampleRc.left;
	}


};




typedef class tileNode : public objects
{
public:
	//	object로 받아옴
	//image* _img;
	//int _frameX;
	//int _frameY;
	//POINT _mapIdx;
	//POINTFLOAT _pos;
	//RECT _rc;
	//int _zLevel;
	//OBJ_KINDS _objKinds;
	
	//	=================

	tagTileInfo _tileInfo;
	tagObjInfo _objInfo;

public:
	//생성자
	tileNode()
	{
		_tileInfo.init();
		_objInfo.init();
	}
		
	~tileNode() {};

	//초기화
	HRESULT init()
	{
		_tileInfo.init();
		_objInfo.init();
		
		return S_OK;
	}
	


	void setObjectiveVal(int idxX, int idxY) {
		this->_pos = ConvertIdxToPosFloat(idxX, idxY, TILESIZE_WID, TILESIZE_HEI);
		this->_rc = RectMakeCenter(this->_pos.x, this->_pos.y, TILESIZE_WID, TILESIZE_HEI);
		this->_mapIdx = PointMake(idxX, idxY);
	}

	void setTileInfo(tagTileInfo tileInfo) {
		this->_tileInfo = tileInfo;
		this->_zLevel = tileInfo.zlvl;
		

	}
	void setObjInfo(tagObjInfo objInfo) {
		this->_objInfo = objInfo;
	}

	tagTileInfo getTileInfo() {
		return this->_tileInfo.getTileInfo();
	}
	tagObjInfo getObjInfo() {
		return this->_objInfo.getObjInfo();
	}


}TILE;

typedef vector<TILE*> vLine;
typedef vector<vLine> vvMap;
