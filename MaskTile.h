#pragma once
#include "gameNode.h"
#include "CharMgr.h"
#include "tileNode.h"

//	�ʷε� ���Ŀ� ���ÿ�.�ֳ��ϸ� �ʵ����� �ʿ�

class MaskTile : public gameNode
{
private:
	image* _maskImg;
	POINT _mapIdx;
	POINT _pos;
	RECT _rc;
	vvMap* _vvMap;
	float _alpha;
	bool _isAlphaRise;
	//CharMgr* _charMgrAddr;
	const float ALPHA_MAX = 1.0f;
	const float ALPHA_MIN = 0.f;

	const float ALPHA_AUG_SPD = 0.05f;

public:
	MaskTile();
	~MaskTile();

	HRESULT init();
	HRESULT init(vvMap* vvMapAddr);
	void release();
	void update();
	void render();




	//void LinkToCharMgr(CharMgr* charMgrAddr) { _charMgrAddr = charMgrAddr; }
};

