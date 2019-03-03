#pragma once
#include "gameNode.h"
class objects : public gameNode
{
protected:
	image* _img;
	int _frameX;
	int _frameY;

	POINTFLOAT _pos;
	RECT _rc;
	int _zLevel;
	

public:
	objects();
	~objects();

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

