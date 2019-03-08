#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar() 
{
}

HRESULT aStar::init()
{
	//_vvMap = nullptr;
	_vvMap.clear();
	_tileNum = { NULL, NULL };


	_vOpenList.clear();
	_vClosedList.clear();

	return S_OK;
}

void aStar::release()
{
}

void aStar::PathFind(POINT startIdx, POINT destIdx, POINT curIdx, list<POINT>& wayList)
{
	//	��������
	{

		//	����˻�Ÿ���� ���Ÿ�ϵ� �ƴѵ�,(�˻����ε�) ����Ÿ�ϸ���Ʈ ������
		if ((startIdx.x != curIdx.x || startIdx.y != curIdx.y) && _vOpenList.size() == 0) {
			wayList.clear();
			wayList.push_back(PointMake(-1, -1));

			//	Ÿ���ʱ�ȭ + ����Ʈ �ʱ�ȭ
			for (int i = 0; i < _vOpenList.size(); i++) {
				ResetTile(_vOpenList[i]);
			}
			_vOpenList.clear();
			for (int i = 0; i < _vClosedList.size(); i++) {
				ResetTile(_vClosedList[i]);
			}
			_vClosedList.clear();

			return;
		}


		//	����!
		else if (destIdx.x == curIdx.x && destIdx.y == curIdx.y) {
			wayList.clear();
			//ASTARTILE* trackTile = (*_vvMap)[curIdx.y][curIdx.x];
			ASTARTILE* trackTile = (_vvMap)[curIdx.y][curIdx.x];
			//	waylist�� Ǫ��Ǫ��
			while (trackTile->idx.x != startIdx.x || trackTile->idx.y != startIdx.y) {
				wayList.push_front(PointMake(trackTile->idx.x, trackTile->idx.y));
				POINT nextIdx = trackTile->parentIndex;
				//trackTile = (*_vvMap)[nextIdx.y][nextIdx.x];
				trackTile = (_vvMap)[nextIdx.y][nextIdx.x];
			}
			//	Ÿ���ʱ�ȭ + ����Ʈ �ʱ�ȭ
			for (int i = 0; i < _vOpenList.size(); i++) {
				ResetTile(_vOpenList[i]);
			}
			_vOpenList.clear();
			for (int i = 0; i < _vClosedList.size(); i++) {
				ResetTile(_vClosedList[i]);
			}
			_vClosedList.clear();

			return;
		}

	


		
	}
	//	����Func End.
	
	//	�����¿� ��ġ�� ����
	{
		enum OPEN_DIR {	UP = 0,	DOWN, LEFT, RIGHT, DIR_END,	};
		bool isOpenTile[OPEN_DIR::DIR_END] = { false, };
		
		//for (int i = -1; i < 2; i += 2) {
		//	for (int j = -1; j < 2; j += 2) {
		//
		//	}
		//}
		//	�����ִ� Ÿ�� üũ
		{
			if (curIdx.y - 1 >= 0) {
				if (!IsInClosedList(curIdx.x, curIdx.y - 1)) {
//					if ((*_vvMap)[curIdx.y - 1][curIdx.x]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
					if ((_vvMap)[curIdx.y - 1][curIdx.x]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
						isOpenTile[OPEN_DIR::UP] = true;
					}

				}
			}
		//	if (curIdx.y + 1 < _vvMap->size()) {
			if (curIdx.y + 1 < _vvMap.size()) {
				if (!IsInClosedList(curIdx.x, curIdx.y + 1)) {
		//			if ((*_vvMap)[curIdx.y + 1][curIdx.x]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
					if ((_vvMap)[curIdx.y + 1][curIdx.x]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
						isOpenTile[OPEN_DIR::DOWN] = true;
					}
				}
			}
			if (curIdx.x - 1 >= 0) {
				if (!IsInClosedList(curIdx.x - 1, curIdx.y)) {
		//			if ((*_vvMap)[curIdx.y][curIdx.x - 1]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
					if ((_vvMap)[curIdx.y][curIdx.x - 1]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
						isOpenTile[OPEN_DIR::LEFT] = true;
					}
				}
			}
			if (curIdx.x + 1 < _vvMap[0].size()) {
				if (!IsInClosedList(curIdx.x + 1, curIdx.y)) {
		//			if ((*_vvMap)[curIdx.y][curIdx.x - 1]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
					if ((_vvMap)[curIdx.y][curIdx.x + 1]->nodeType != ASTARTILE::ASTAR_NODE_TYPE::BLOCK) {
						isOpenTile[OPEN_DIR::RIGHT] = true;
					}
				}
			}
		}
		
		//	������� + ������� ����
		for (int i = 0; i < OPEN_DIR::DIR_END; i++) {
			if (isOpenTile[i]) {
				ASTARTILE* tmpTile;
				switch (i) {
				case OPEN_DIR::UP:
					//tmpTile = (*_vvMap)[curIdx.y - 1][curIdx.x];
					tmpTile = (_vvMap)[curIdx.y - 1][curIdx.x];
					//tmpTile->g = 10;
					tmpTile->g = (_vvMap)[curIdx.y][curIdx.x]->g + 10;
					tmpTile->h = CalHPoint(tmpTile->idx.x, tmpTile->idx.y, destIdx.x, destIdx.y);
					tmpTile->f = tmpTile->g + tmpTile->h;
					tmpTile->parentIndex = curIdx;
					_vOpenList.push_back(tmpTile);
					break;
				case OPEN_DIR::DOWN:
					//tmpTile = (*_vvMap)[curIdx.y + 1][curIdx.x];
					tmpTile = (_vvMap)[curIdx.y + 1][curIdx.x];
					//tmpTile->g = 10;
					tmpTile->g = (_vvMap)[curIdx.y][curIdx.x]->g + 10;
					tmpTile->h = CalHPoint(tmpTile->idx.x, tmpTile->idx.y, destIdx.x, destIdx.y);
					tmpTile->f = tmpTile->g + tmpTile->h;
					tmpTile->parentIndex = curIdx;
					_vOpenList.push_back(tmpTile);
					break;
				case OPEN_DIR::LEFT:
					//tmpTile = (*_vvMap)[curIdx.y][curIdx.x - 1];
					tmpTile = (_vvMap)[curIdx.y][curIdx.x - 1];
					//tmpTile->g = 10;
					tmpTile->g = (_vvMap)[curIdx.y][curIdx.x]->g + 10;
					tmpTile->h = CalHPoint(tmpTile->idx.x, tmpTile->idx.y, destIdx.x, destIdx.y);
					tmpTile->f = tmpTile->g + tmpTile->h;
					tmpTile->parentIndex = curIdx;
					_vOpenList.push_back(tmpTile);
					break;
				case OPEN_DIR::RIGHT:
					//tmpTile = (*_vvMap)[curIdx.y][curIdx.x + 1];
					tmpTile = (_vvMap)[curIdx.y][curIdx.x + 1];
					//tmpTile->g = 10;
					tmpTile->g = (_vvMap)[curIdx.y][curIdx.x]->g + 10;
					tmpTile->h = CalHPoint(tmpTile->idx.x, tmpTile->idx.y, destIdx.x, destIdx.y);
					tmpTile->f = tmpTile->g + tmpTile->h;
					tmpTile->parentIndex = curIdx;
					_vOpenList.push_back(tmpTile);
					break;

				}
			}
		}	
		//	��������ؼ� openlist pusback end
	}
	//	����Ÿ�� closeList�� �߰� + openlist���� ����
	{
		//_vClosedList.push_back((*_vvMap)[curIdx.y][curIdx.x]);
		_vClosedList.push_back((_vvMap)[curIdx.y][curIdx.x]);
		for (int i = 0; i < _vOpenList.size(); i++) {
			if (_vOpenList[i]->idx.x == curIdx.x && _vOpenList[i]->idx.y == curIdx.y) {
				_vOpenList.erase(_vOpenList.begin() + i);
			}
		}
	}	
	//	������ ���� ������ ����
	int minPoint = 99999999;
	POINT minTileIdx = { -1,-1 };
	{
		for (int i = 0; i < _vOpenList.size(); i++) {
			if (minPoint > _vOpenList[i]->f) {
				minPoint = _vOpenList[i]->f;
				minTileIdx = _vOpenList[i]->idx;
			}
		}

	}

	//	�̵�!
	if (minTileIdx.x != -1 && minTileIdx.y != -1) {
		this->PathFind(startIdx, destIdx, minTileIdx, wayList);
	}

		
}

bool aStar::IsInClosedList(int targetX, int targetY)
{
	for (int i = 0; i < _vClosedList.size(); i++) {
		if (_vClosedList[i]->idx.x == targetX &&
			_vClosedList[i]->idx.y == targetY) {
			return true;
		}
	}
	return false;
}

int aStar::CalHPoint(int curIdxX, int curIdxY, int destIdxX, int destIdxY)
{
	int point = 0;
	point += abs(curIdxX - destIdxX) * 10;
	point += abs(curIdxY - destIdxY) * 10;

	return point;
}

void aStar::ResetTile(ASTARTILE * tile)
{
	tile->f = 0.f;
	tile->g = 0.f;
	tile->h = 0.f;
	tile->parentIndex = { -1, -1 };
}
