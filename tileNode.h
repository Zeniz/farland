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
};

//지형 이미지 키값 배열 번호
typedef enum TERRAIN_ARRAY_NUM
{
	TERNUM_NONE = -1,
	TERNUM_BASIC,

	TERNUM_END,



}TERNUM;
//지형 이미지 키값
static string _terrainImageKey[10] = { "","","","","","","","","","" };


//오브젝트 이미지 키값 배열 번호
typedef enum OBJECT_ARRAY_NUM
{
	OBJNUM_NONE = -1,



}OBJNUM;
//오브젝트 이미지 키값
static string _objectImageKey[10] = { "","","","","","","","","","" };

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
private:
	
	OBJNUM			_imgNum;
	O_ATTRIBUTE		_attr;

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

		_pos = { NULL, NULL };
		_rc = { NULL,NULL,NULL,NULL };
		_attr = O_ATTR_NONE;
		_zLevel = NULL;

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

}OBJ;

typedef class tileNode : public objects
{
public:
	//image* _terImg;
	TERNUM _terImgNum;
	//int _terFrameX;
	//int _terFrameY;
	POINT _idx;

	T_ATTRIBUTE _terAttr;
	//POINT _pos;
	//RECT _rc;
	
public:
	//생성자
	tileNode() :
		//_terImg(nullptr), _terImgNum(TERNUM_NONE), _terFrameX(NULL), _terFrameY(NULL), _idx({ NULL,NULL }),
		//_terAttr(T_ATTR_NONE), _pos({ NULL,NULL }), _rc({ NULL,NULL,NULL,NULL }) {};
		_terImgNum(TERNUM_NONE), _idx({ NULL,NULL }), _terAttr(T_ATTR_NONE) {};
		
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
		_terAttr = T_ATTR_NONE;
		_pos = { NULL,NULL };
		_rc = { NULL,NULL,NULL,NULL };
		_zLevel = NULL;


		return S_OK;
	}
	
	HRESULT init(image* img, TERRAIN_ARRAY_NUM terImgNum, int frameX, int frameY, POINT idx, T_ATTRIBUTE T_attr, POINT pos, RECT rc) {
		_img = img;
		_terImgNum = terImgNum;
		_frameX = frameX;
		_frameY = frameY;
		_idx = idx;

		_terAttr = T_attr;
		POINTFLOAT tmpPos;
		tmpPos.x = pos.x;
		tmpPos.y = pos.y;
		_pos = tmpPos;
		_rc = rc;

		return S_OK;
	}
	HRESULT init(image* img, TERRAIN_ARRAY_NUM terImgNum, int frameX, int frameY, POINT idx, T_ATTRIBUTE T_attr, POINTFLOAT pos, RECT rc) {
		_img = img;
		_terImgNum = terImgNum;
		_frameX = frameX;
		_frameY = frameY;
		_idx = idx;

		_terAttr = T_attr;
		_pos = pos;
		_rc = rc;

		return S_OK;
	}
	HRESULT init(image* img, TERRAIN_ARRAY_NUM terImgNum, int frameX, int frameY, POINT idx, T_ATTRIBUTE T_attr, POINTFLOAT pos, RECT rc, int zLvl) {
		_img = img;
		_terImgNum = terImgNum;
		_frameX = frameX;
		_frameY = frameY;
		_idx = idx;

		_terAttr = T_attr;
		_pos = pos;
		_rc = rc;

		_zLevel = zLvl;

		return S_OK;
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