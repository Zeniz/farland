#pragma once
#include "gameNode.h"
class mainmenu : public gameNode
{
private:
	image* _bgImg;
	float _bgAlpha;
	struct tagButton {
		image* img;
		POINT pos;
		RECT rc;
		
		int frameX;
		int frameY;
	};

	enum BUTTON_KINDS {
		BUTTON_NONE = -1,
		NEWGAME,
		MAPTOOL,
		EXIT,
		BUTTON_END,
	};

	tagButton _buttons[BUTTON_END];

	bool _isTitleAlphaFin;

	const float ALPHA_AUGSPD = 0.05f;
	const int BUTTON_START_Y = 200;
	const int BUTTON_END_Y = WINSIZEY - 200;
	const int BUTTON_START_X = 1408;

public:
	mainmenu();
	~mainmenu();

	HRESULT init();
	void release();
	void update();
	void render();
};

