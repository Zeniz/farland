#pragma once
#include "gameNode.h"
#include "mapEditor.h"
#include "testMap.h"


class playGround : public gameNode
{
private:
	mapEditor* _mapEditor;
	testMap* _testMap;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};