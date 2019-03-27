#pragma once
#include "gameNode.h"
#include "mapEditor.h"
#include "testMap.h"
#include "stage1.h"
#include "bossStage.h"
#include "mainmenu.h"
#include "gameover.h"


class playGround : public gameNode
{
private:
	mapEditor* _mapEditor;
	testMap* _testMap;
	stage1* _stage1;
	mainmenu* _mainmenu;
	bossStage* _bossStage;
	gameover* _gameover;
	

public:
	playGround();
	~playGround();

	HRESULT init();
	void release();
	void update();
	void render();


};