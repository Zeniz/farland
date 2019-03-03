#pragma once
#include "gameNode.h"
#include "objects.h"

const int TILESIZE_WID = 128;
const int TILESIZE_HEI = 64;

//Ÿ�� �Ӽ�
enum T_ATTRIBUTE
{
	T_ATTR_NONE = 0x00000000UL,
	T_ATTR_UNMOVE = 0x00000001UL
};

enum O_ATTRIBUTE
{
	O_ATTR_NONE = 0x00000000UL,
};

//���� �̹��� Ű�� �迭 ��ȣ
typedef enum TERRAIN_ARRAY_NUM
{
	TERNUM_NONE = -1,



}TERNUM;
//���� �̹��� Ű��
static string _terrainImageKey[10] = { "","","","","","","","","","" };


//������Ʈ �̹��� Ű�� �迭 ��ȣ
typedef enum OBJECT_ARRAY_NUM
{
	OBJNUM_NONE = -1,



}OBJNUM;
//������Ʈ �̹��� Ű��
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

	objNode& operator = (const objNode& obj) 
	{
		this->_img = obj._img;
		this->_imgNum = obj._imgNum;
		this->_frameX = obj._frameX;
		this->_frameY = obj._frameY;

		this->_pos = obj._pos;
		this->_rc = obj._rc;
		this->_attr = obj._attr;
		this->_zLevel = obj._zLevel;

	}

	bool operator == (const objNode& obj)
	{
		if (this->_img == obj._img						&&
			this->_imgNum == obj._imgNum				&&
			this->_frameX == obj._frameX				&&
			this->_frameY == obj._frameY				&&
			this->_pos.x == obj._pos.x					&&
			this->_pos.y == obj._pos.y					&&
			this->_rc.left == obj._rc.left				&&
			this->_rc.top == obj._rc.top				&&
			this->_rc.right == obj._rc.right			&&
			this->_rc.bottom == obj._rc.bottom			&&
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
			this->_pos.x == obj._pos.x					&&
			this->_pos.y == obj._pos.y					&&
			this->_rc.left == obj._rc.left				&&
			this->_rc.top == obj._rc.top				&&
			this->_rc.right == obj._rc.right			&&
			this->_rc.bottom == obj._rc.bottom			&&
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

typedef class tileNode
{
public:
	image* _terImg;
	TERNUM _terImgNum;
	int _terFrameX;
	int _terFrameY;


	T_ATTRIBUTE _terAttr;
	POINT _pos;
	RECT _rc;
	
public:
	//������
	tileNode() :
		_terImg(nullptr), _terImgNum(TERNUM_NONE), _terFrameX(NULL), _terFrameY(NULL),
		_terAttr(T_ATTR_NONE), _pos({ NULL,NULL }), _rc({ NULL,NULL,NULL,NULL }) {};
		
	tileNode(const tileNode& tile) :
		_terImg(tile._terImg), _terImgNum(tile._terImgNum), _terFrameX(tile._terFrameX), _terFrameY(tile._terFrameY),
		_terAttr(tile._terAttr), _pos(tile._pos), _rc(tile._rc) {};
	
	~tileNode() {};

	//�ʱ�ȭ
	HRESULT init()
	{
		_terImg = nullptr;
		_terImgNum = TERNUM_NONE;
		_terFrameX = NULL;
		_terFrameY = NULL;

		_terAttr = T_ATTR_NONE;
		_pos = { NULL,NULL };
		_rc = { NULL,NULL,NULL,NULL };

		return S_OK;
	}
	//
	////----------------------------------------------------
	////------------------O P E R A T O R-------------------
	////----------------------------------------------------

	tileNode& operator = (const tileNode& tile)
	{
		this->_terImg = tile._terImg;
		this->_terImgNum = tile._terImgNum;
		this->_terFrameX = tile._terFrameX;
		this->_terFrameY = tile._terFrameY;

		this->_terAttr = T_ATTR_NONE;
		this->_pos = tile._pos;
		this->_rc = tile._rc;


	}
	bool operator == (const tileNode& tile)
	{
		if (this->_terImg == tile._terImg	&&
			this->_terImgNum == tile._terImgNum		&&
			this->_terFrameX == tile._terFrameX		&&
			this->_terFrameY == tile._terFrameY		&&
			this->_terAttr == tile._terAttr			&&
			this->_pos.x == tile._pos.x				&&
			this->_pos.y == tile._pos.y				&&
			this->_rc.left == tile._rc.left			&&
			this->_rc.top == tile._rc.top				&&
			this->_rc.right == tile._rc.right			&&
			this->_rc.bottom == tile._rc.bottom		)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator != (const tileNode& tile)
	{
		if (this->_terImg == tile._terImg	&&
			this->_terImgNum == tile._terImgNum		&&
			this->_terFrameX == tile._terFrameX		&&
			this->_terFrameY == tile._terFrameY		&&
			this->_terAttr == tile._terAttr			&&
			this->_pos.x == tile._pos.x				&&
			this->_pos.y == tile._pos.y				&&
			this->_rc.left == tile._rc.left			&&
			this->_rc.top == tile._rc.top				&&
			this->_rc.right == tile._rc.right			&&
			this->_rc.bottom == tile._rc.bottom)
		{
			return false;
		}
		else
		{
			return true;
		}
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