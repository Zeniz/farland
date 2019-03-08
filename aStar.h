#pragma once
#include "singletonBase.h"
#include <vector>
#include <list>
#include "aStarTileNode.h"


class aStar : public singletonBase<aStar>
{
private:
	vvMapAstar _vvMap;
	POINT _tileNum;
	

	vector<ASTARTILE*> _vOpenList;
	vector<ASTARTILE*> _vClosedList;

public:
	aStar();
	~aStar();

	HRESULT init();
	void release();

	void setMap(vvMapAstar vvMapAstarAddr) { 
		_vvMap = vvMapAstarAddr;
		//_tileNum.x = (*_vvMap)[0].size();
		//_tileNum.y = (*_vvMap).size();
		_tileNum.x = (_vvMap)[0].size();
		_tileNum.y = (_vvMap).size();
	}

	void PathFind(POINT startIdx, POINT destIdx, POINT curIdx, list<POINT>& wayList);
	bool IsInClosedList(int targetX, int targetY);
	int CalHPoint(int curIdxX, int curIdxY, int destIdxX, int destIdxY);
	void ResetTile(ASTARTILE* tile);
};

