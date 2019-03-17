#pragma once
#include "gameNode.h"
class UIObjects : public gameNode
{
	
public:
	UIObjects();
	~UIObjects();

	virtual HRESULT init()	abstract;
	virtual void release()	abstract;
	virtual void update()	abstract;
	virtual void render()	abstract;

};

