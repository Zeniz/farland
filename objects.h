#pragma once
#include "gameNode.h"
#include <algorithm>

enum OBJ_KINDS {
	OBJKIND_NONE = -1,
	OBJKIND_TILE,
	OBJKIND_OBJ,
	OBJKIND_UNIT,
	OBJKIND_CHAR,
};

class objects : public gameNode
{
public:
	image* _img;
	int _frameX;
	int _frameY;

	POINT _mapIdx;
	POINTFLOAT _pos;
	RECT _rc;
	int _zLevel;
	OBJ_KINDS _objKinds;
	
	


public:
	objects();
	~objects();

	//	zorder sort용 operator
	bool operator<(objects target) {		// 연산자 오버로드
		return this->_pos.y < target._pos.y;
	}



	image* getImg() { return _img; }
	void setImg(image* img) { _img = img; }
	int getFrameX() { return _frameX; }
	void setFrameX(int frameX) { _frameX = frameX; }
	int getFrameY() { return _frameY; }
	void setFrameY(int frameY) { _frameY = frameY; }

	POINTFLOAT getPos() { return _pos; }
	void setPos(POINTFLOAT pos) { _pos = pos; }
	RECT getRc() { return _rc; }
	void setRc(RECT rc) { _rc = rc; }
	int getZLevel() { return _zLevel; }
	void setZLevel(int zLvl) { _zLevel = zLvl; }
};

