#pragma once
#include "gameNode.h"
#include "objects.h"

const int TILESIZE_WID = 128;
const int TILESIZE_HEI = 64;



//타일 속성
enum T_ATTRIBUTE
{
	T_ATTR_NONE = 0x00000000UL,
	T_ATTR_UNMOVE = 0x00000001UL
};

enum O_ATTRIBUTE
{
	O_ATTR_NONE = 0x00000000UL,
	O_ATTR_UNMOVE = 0x00000001UL,
};

//지형 이미지 키값 배열 번호
typedef enum TERRAIN_ARRAY_NUM
{
	TERNUM_NONE = -1,
	TERNUM_BASIC,

	TERNUM_END,



}TERNUM;
//지형 이미지 키값
static string _terrainImageKey[10] = { "tile1","","","","","","","","","" };


//오브젝트 이미지 키값 배열 번호
typedef enum OBJECT_ARRAY_NUM
{
	OBJNUM_NONE = -1,
	OBJNUM_BASIC,
	OBJNUM_HOUSE,
	OBJNUM_COMB,
	OBJNUM_CRYSTAL,


	
	OBJNUM_END,


}OBJNUM;
//오브젝트 이미지 키값
static string _objectImageKey[10] = { "objSample1","objSample2","objSample3","objSample4","","","","","","" };

struct tagObjSpriteInfo {
	POINTFLOAT centerPosInImg;
	RECT sampleRc;
	POINT objTileSize;
	OBJECT_ARRAY_NUM imgNum;
	image* img;
	int zLvl;
	O_ATTRIBUTE attr;

	int getPixPosToTop() {
		return centerPosInImg.y - sampleRc.top;
	}
	int getPixPosToBot() {
		return sampleRc.bottom - centerPosInImg.y;
	}
	int getPixPosToLeft() {
		return centerPosInImg.x - sampleRc.left;
	}
	int getPixPosToRight() {
		return sampleRc.right - centerPosInImg.x;
	}
	int getWid() {
		return sampleRc.right - sampleRc.left;
	}
	int getHei() {
		return sampleRc.bottom - sampleRc.top;
	}
	void init() {
		this->sampleRc = { NULL,NULL,NULL,NULL };
		this->objTileSize = { NULL,NULL };
		this->centerPosInImg = { -1,-1 };		//	초기화 조건이 -1임.ObjSampleFunc()에서 쓰임
		this->attr = O_ATTR_NONE;
		this->imgNum = OBJNUM_NONE;
		this->img = nullptr;
		this->zLvl = NULL;
	}

};

static tagObjSpriteInfo _objImgInfo[OBJNUM_END][12];





struct tagTileInfo {
	TERRAIN_ARRAY_NUM terImgNum;
	int frameX;
	int frameY;
	POINT idx;
	POINT pickIdx;

	T_ATTRIBUTE terAttr;
	POINTFLOAT pos;
	RECT rc;
	int zLevel;
};

struct tagObjInfo {

	OBJNUM	objImgNum;
	int frameX;		//	필요없음
	int frameY;		//	필요없음
	POINTFLOAT pos;
	RECT rc;
	O_ATTRIBUTE	objAttr;

	POINT botTileIdx;
	POINT objTileSize;

	int zLevel;


};


typedef struct astarTile
{
public:
	enum ASTAR_NODE_TYPE
	{
		EMPTY = 0,
		BLOCK,
		START,
		DEST
	};

	POINT idx;
	POINT parentIndex = { -1,-1 };
	int zLevel = 0; 

	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;

	ASTAR_NODE_TYPE nodeType = EMPTY;

}ASTARTILE;

typedef class objNode : public objects
{
public:
	
	OBJNUM			_imgNum;
	O_ATTRIBUTE		_attr;
//	POINT _botTileIdx;
	POINT _objTileSize;
	POINT _mapIdx;

	RECT _sampleRc;
	POINTFLOAT _centerPosInImg;

public:
	objNode() :
		_imgNum(OBJNUM_NONE), _attr(O_ATTR_NONE) {};

	objNode(const objNode& obj) :
		_imgNum(obj._imgNum),	_attr(obj._attr) {};

	~objNode() {};

	HRESULT init() 
	{
		_img = nullptr;
		_imgNum = OBJNUM_NONE;
		_frameX = NULL;
		_frameY = NULL;
		_mapIdx = { NULL, NULL };

		_pos = { NULL, NULL };
		_rc = { NULL,NULL,NULL,NULL };
		_attr = O_ATTR_NONE;
		_zLevel = NULL;

		_sampleRc = { NULL, NULL, NULL, NULL };
		_centerPosInImg = { NULL, NULL };

		return S_OK;
	}

	HRESULT init(OBJNUM imgNum, O_ATTRIBUTE attr, POINT mapIdx, POINTFLOAT pos,
		RECT rc, RECT sampleRc, int zlvl, POINT objTileSize) {
		this->_imgNum = imgNum;
		this->_img = IMAGEMANAGER->findImage(_objectImageKey[imgNum].c_str());
		this->_attr = attr;
		this->_mapIdx = mapIdx;
		this->_pos = pos;
		this->_rc = rc;
		this->_sampleRc = sampleRc;
		this->_zLevel = zlvl;
		this->_objTileSize = objTileSize;


		this->_frameX = NULL;
		this->_frameY = NULL;
		this->_centerPosInImg = { NULL, NULL };
		
		return S_OK;

	}
		

	//objNode& operator = (const objNode& obj) 
	void operator = (const objNode& obj)
	{
		this->_img = obj._img;
		this->_imgNum = obj._imgNum;
		this->_frameX = obj._frameX;
		this->_frameY = obj._frameY;

		//this->_pos = obj._pos;
		//this->_rc = obj._rc;
		this->_attr = obj._attr;
		this->_zLevel = obj._zLevel;

	}

	bool operator == (const objNode& obj)
	{
		if (this->_img == obj._img						&&
			this->_imgNum == obj._imgNum				&&
			this->_frameX == obj._frameX				&&
			this->_frameY == obj._frameY				&&
			//this->_pos.x == obj._pos.x					&&
			//this->_pos.y == obj._pos.y					&&
			//this->_rc.left == obj._rc.left				&&
			//this->_rc.top == obj._rc.top				&&
			//this->_rc.right == obj._rc.right			&&
			//this->_rc.bottom == obj._rc.bottom			&&
			this->_attr == obj._attr					&&
			this->_zLevel == obj._zLevel
			)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator != (const objNode& obj)
	{
		if (this->_img == obj._img						&&
			this->_imgNum == obj._imgNum				&&
			this->_frameX == obj._frameX				&&
			this->_frameY == obj._frameY				&&
			//this->_pos.x == obj._pos.x					&&
			//this->_pos.y == obj._pos.y					&&
			//this->_rc.left == obj._rc.left				&&
			//this->_rc.top == obj._rc.top				&&
			//this->_rc.right == obj._rc.right			&&
			//this->_rc.bottom == obj._rc.bottom			&&
			this->_attr == obj._attr					&&
			this->_zLevel == obj._zLevel
			)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void setObjInfo(tagObjInfo objInfo) {
		this->_imgNum = objInfo.objImgNum;
		this->_frameX = objInfo.frameX;
		this->_frameY = objInfo.frameY;

		this->_pos = objInfo.pos;
		this->_rc = objInfo.rc;
		this->_attr = objInfo.objAttr;

		this->_zLevel = objInfo.zLevel;

		//this->_botTileIdx = objInfo.botTileIdx;
		this->_objTileSize = objInfo.objTileSize;
		


		this->_img = IMAGEMANAGER->findImage(_objectImageKey[_imgNum].c_str());
	}
	tagObjInfo getObjInfo() {
		tagObjInfo objInfo;
		
		objInfo.objImgNum = this->_imgNum;
		objInfo.frameX = this->_frameX;
		objInfo.frameY = this->_frameY;

		objInfo.pos = this->_pos;
		objInfo.rc = this->_rc;
		objInfo.objAttr = this->_attr;

		objInfo.zLevel = this->_zLevel;

		//objInfo.botTileIdx = this->_botTileIdx;
		objInfo.objTileSize = this->_objTileSize;

		return objInfo;
	}




}OBJ;

typedef class tileNode : public objects
{
public:
	//image* _terImg;
	TERNUM _terImgNum;
	//int _terFrameX;
	//int _terFrameY;
	POINT _idx;
	POINT _pickIdx;

	T_ATTRIBUTE _terAttr;
	//POINT _pos;
	//RECT _rc;
	
public:
	//생성자
	tileNode() :
		//_terImg(nullptr), _terImgNum(TERNUM_NONE), _terFrameX(NULL), _terFrameY(NULL), _idx({ NULL,NULL }),
		//_terAttr(T_ATTR_NONE), _pos({ NULL,NULL }), _rc({ NULL,NULL,NULL,NULL }) {};
		_terImgNum(TERNUM_NONE), _idx({ NULL,NULL }), _pickIdx({ NULL,NULL }), _terAttr(T_ATTR_NONE) {};
		
	tileNode(const tileNode& tile) :
		_terImgNum(tile._terImgNum), _idx(tile._idx),
		_terAttr(tile._terAttr) {};
	
	~tileNode() {};

	//초기화
	HRESULT init()
	{
		//_terImg = nullptr;
		//_terImgNum = TERNUM_NONE;
		//_terFrameX = NULL;
		//_terFrameY = NULL;
		//_idx = { NULL,NULL };
		//
		//_terAttr = T_ATTR_NONE;
		//_pos = { NULL,NULL };
		//_rc = { NULL,NULL,NULL,NULL };
		_img = nullptr;
		_terImgNum = TERNUM_NONE;
		_frameX = NULL;
		_frameY = NULL;
		_idx = { NULL, NULL };
		_pickIdx = { NULL, NULL };
		_terAttr = T_ATTR_NONE;
		_pos = { NULL,NULL };
		_rc = { NULL,NULL,NULL,NULL };
		_zLevel = NULL;


		return S_OK;
	}
	
	//HRESULT init(image* img, TERRAIN_ARRAY_NUM terImgNum, int frameX, int frameY, POINT idx, T_ATTRIBUTE T_attr, POINT pos, RECT rc) {
	//	_img = img;
	//	_terImgNum = terImgNum;
	//	_frameX = frameX;
	//	_frameY = frameY;
	//	_idx = idx;
	//
	//	_terAttr = T_attr;
	//	POINTFLOAT tmpPos;
	//	tmpPos.x = pos.x;
	//	tmpPos.y = pos.y;
	//	_pos = tmpPos;
	//	_rc = rc;
	//
	//	return S_OK;
	//}
	//HRESULT init(image* img, TERRAIN_ARRAY_NUM terImgNum, int frameX, int frameY, POINT idx, T_ATTRIBUTE T_attr, POINTFLOAT pos, RECT rc) {
	//	_img = img;
	//	_terImgNum = terImgNum;
	//	_frameX = frameX;
	//	_frameY = frameY;
	//	_idx = idx;
	//
	//	_terAttr = T_attr;
	//	_pos = pos;
	//	_rc = rc;
	//
	//	_zLevel = NULL;
	//	return S_OK;
	//}
	HRESULT init(image* img, TERRAIN_ARRAY_NUM terImgNum, int frameX, int frameY, POINT idx, POINT pickIdx,	T_ATTRIBUTE T_attr, POINTFLOAT pos, RECT rc, int zLvl) {
		_img = img;
		_terImgNum = terImgNum;
		_frameX = frameX;
		_frameY = frameY;
		_idx = idx;
		_pickIdx = pickIdx;

		_terAttr = T_attr;
		_pos = pos;
		_rc = rc;

		_zLevel = zLvl;

		return S_OK;
	}

	void setTileInfo(tagTileInfo tileInfo) {
		this->_terImgNum = tileInfo.terImgNum;
		this->_frameX = tileInfo.frameX;
		this->_frameY = tileInfo.frameY;

		this->_idx = tileInfo.idx;
		this->_pickIdx = tileInfo.pickIdx;
		this->_terAttr = tileInfo.terAttr;

		this->_pos = tileInfo.pos;
		this->_rc = tileInfo.rc;
		this->_zLevel = tileInfo.zLevel;
		
		this->_img = IMAGEMANAGER->findImage(_terrainImageKey[_terImgNum]);

	}
	tagTileInfo getTileInfo() {
		tagTileInfo tileInfo;
		tileInfo.terImgNum = this->_terImgNum;
		tileInfo.frameX = this->_frameX;
		tileInfo.frameY = this->_frameY;
		
		tileInfo.idx = this->_idx;
		tileInfo.pickIdx = this->_pickIdx;
		tileInfo.terAttr = this->_terAttr;

		tileInfo.pos = this->_pos;
		tileInfo.rc = this->_rc;
		tileInfo.zLevel = this->_zLevel;

		return tileInfo;

	}



	//
	////----------------------------------------------------
	////------------------O P E R A T O R-------------------
	////----------------------------------------------------

	//tileNode& operator = (const tileNode& tile)
	void operator = (const tileNode& tile)
	{
		//this->_terImg = tile._terImg;
		//this->_terImgNum = tile._terImgNum;
		//this->_terFrameX = tile._terFrameX;
		//this->_terFrameY = tile._terFrameY;
		//
		//this->_terAttr = tile._terAttr;
		//this->_pos = tile._pos;
		//this->_rc = tile._rc;


	}
	bool operator == (const tileNode& tile)
	{
		//if (this->_terImg == tile._terImg	&&
		//	this->_terImgNum == tile._terImgNum		&&
		//	this->_terFrameX == tile._terFrameX		&&
		//	this->_terFrameY == tile._terFrameY		&&
		//	this->_terAttr == tile._terAttr			
		//	//this->_pos.x == tile._pos.x				&&
		//	//this->_pos.y == tile._pos.y				&&
		//	//this->_rc.left == tile._rc.left			&&
		//	//this->_rc.top == tile._rc.top				&&
		//	//this->_rc.right == tile._rc.right			&&
		//	//this->_rc.bottom == tile._rc.bottom		
		//	)
		//{
		//	return true;
		//}
		//else
		//{
		//	return false;
		//}
	}
	bool operator != (const tileNode& tile)
	{
		//if (this->_terImg == tile._terImg	&&
		//	this->_terImgNum == tile._terImgNum		&&
		//	this->_terFrameX == tile._terFrameX		&&
		//	this->_terFrameY == tile._terFrameY		&&
		//	this->_terAttr == tile._terAttr			
		//	//this->_pos.x == tile._pos.x				&&
		//	//this->_pos.y == tile._pos.y				&&
		//	//this->_rc.left == tile._rc.left			&&
		//	//this->_rc.top == tile._rc.top				&&
		//	//this->_rc.right == tile._rc.right			&&
		//	//this->_rc.bottom == tile._rc.bottom
		//	)
		//{
		//	return false;
		//}
		//else
		//{
		//	return true;
		//}
	}

	//image* getImg() { return _terImg; }
	//void setImg(image* img) { _terImg = img; }
	//
	//TERNUM getTerImgNum() { return _terImgNum; }
	//void setTerImgNum(TERNUM imgNum) { _terImgNum = imgNum; }
	//
	//POINT getPos() { return _pos; }
	//void setPos(POINT pos) { _pos = pos; }
	//
	//RECT getRc() { return _rc; }
	//void setRc(RECT rc) { _rc = rc; }



}TILE;



typedef vector<TILE*> vLine;
typedef vector<vLine> vvMap;
typedef vector<OBJ*> vObj;