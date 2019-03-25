#pragma once
#include "gameNode.h"
#include "mapEditor.h"
#include "testMap.h"
#include "stage1.h"
#include "mainmenu.h"


class playGround : public gameNode
{
private:
	mapEditor* _mapEditor;
	testMap* _testMap;
	stage1* _stage1;
	mainmenu* _mainmenu;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};