#pragma once
#include "gameNode.h"
#include "mapEditor.h"


class playGround : public gameNode
{
private:
	mapEditor* _mapEditor;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};