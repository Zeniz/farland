#pragma once
#include "gameNode.h"
class gameover : public gameNode
{
private:
	image* _bgImg;
	string _curStageName;

	struct tagImgSet {
		image* img;
		RECT rc;
		int frameY;
	};
	
	tagImgSet _retry;
	tagImgSet _mainmenu;
	
	float _alpha;
	bool _isAlphaFin;
	const float ALPHA_AUG = 0.05f;
	


public:
	gameover();
	~gameover();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCurStageName(string curStageName) { _curStageName = curStageName.c_str(); }

};

