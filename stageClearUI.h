#pragma once
#include "UIObjects.h"
#include "enemyMgr.h"
#include "CharMgr.h"
class stageClearUI : public UIObjects
{
private:
	bool _isClear;
	bool _isGameOver;
	image* _clearImg;
	image* _failImg;
	RECT _clearRc;
	string _curStage;
	string _nextStage;
	vEnemy*	_vpEnemy;
	vChara* _vpChara;


public:
	stageClearUI();
	~stageClearUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCurStage(string str) { _curStage = str.c_str(); }
	void CalNextStage(string curStageName);
	void setIsClear(bool value) { _isClear = value; }

	char* getCurStage() { _curStage.c_str(); }
	char* getNextStage() { _nextStage.c_str(); }

	void LinkToVEnemy(vEnemy* vpEnemy) { _vpEnemy = vpEnemy; }
	void LinkToVChara(vChara* vpChara) { _vpChara = vpChara; }
};

