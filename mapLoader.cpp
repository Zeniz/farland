#include "stdafx.h"
#include "mapLoader.h"
#pragma warning(disable: 4996)

mapLoader::mapLoader()
{
}


mapLoader::~mapLoader()
{
}

void mapLoader::LoadMap(int mapIdx, vvMap * vvMapAddr, POINT* tileNum, vEnemy * vEnemyAddr)
{
	
	vvMapAddr->clear();
	vEnemyAddr->clear();

	HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData, fileForEnemySize, fileForEnemyData;
	DWORD readForMapSize, readForMapData, readForObjSize, readForObjData, readForEnemySize, readForEnemyData;

	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForEnemy[20] = "enemyData";
	char fileNameForMapSize[20] = "mapSize";
	char fileNameForEnemySize[20] = "enemySize";


	char idxBuffer[5] = {};		//	�� �ε��� �����
	char mapSizeStr[20] = {};		//	�� ũ�� str�����
	char enemySizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa�ӽ� �����
	char objNumBuffer[10] = {};		//	itoa�ӽ� �����
	char enemyNumBuffer[10] = {};		//	itoa�ӽ� �����

	char* token;
	char* context;
	int tmpInt;
	int vObjSize;
	int vEnemySize;

	//	�����̸� ����
	itoa(mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");


	strcat_s(fileNameForObj, sizeof(fileNameForObj), idxBuffer);
	strcat_s(fileNameForObj, sizeof(fileNameForObj), ".map");

	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), idxBuffer);
	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), ".map");
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), idxBuffer);
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), ".map");


	//	��ũ�� �ε�
	fileForMapSize = CreateFile(fileNameForMapSize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapSize, mapSizeStr, 20, &readForMapSize, NULL);
	CloseHandle(fileForMapSize);

	//	enemy ũ�� �ε�
	fileForEnemySize = CreateFile(fileNameForEnemySize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemySize, enemySizeStr, 20, &readForEnemySize, NULL);
	CloseHandle(fileForEnemySize);


	//	�� ũ�� �־���
	token = strtok_s(mapSizeStr, ",", &context);
	tmpInt = atoi(token);
	tileNum->x = tmpInt;

	token = strtok_s(NULL, ",", &context);
	tmpInt = atoi(token);
	tileNum->y = tmpInt;

	//	enemy ũ�� �־���
	token = strtok_s(enemySizeStr, ",", &context);
	tmpInt = atoi(token);
	vEnemySize = tmpInt;


	//	�ʵ����� �ε�
	tagTileInfo* savedTileAry = new tagTileInfo[tileNum->x * tileNum->y];
	ZeroMemory(savedTileAry, sizeof(tagTileInfo) * (tileNum->x * tileNum->y));

	fileForMapData = CreateFile(fileNameForMap, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapData, savedTileAry, sizeof(tagTileInfo) * tileNum->x * tileNum->y, &readForMapData, NULL);
	CloseHandle(fileForMapData);

	//	vv�ʿ� ������ ����
	for (int i = 0; i < tileNum->y; i++) {
		vLine tmpVLine;
		tmpVLine.clear();
		tmpVLine.reserve(tileNum->x);
		for (int j = 0; j < tileNum->x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->setTileInfo(savedTileAry[i*tileNum->x + j]);
			tmpTile->_tileInfo.img = IMAGEMANAGER->findImage(_terrainImageKey[tmpTile->_tileInfo.terImgNum].c_str());		//	�̹��� ��Ƴ־������
			tmpTile->setObjectiveVal(j, i);
			tmpTile->_zLevel = tmpTile->_tileInfo.zlvl;
			tmpVLine.push_back(tmpTile);
		}
		vvMapAddr->push_back(tmpVLine);
	}


	//	obj������ �ε�
	tagObjInfo* savedObjAry = new tagObjInfo[tileNum->x * tileNum->y];
	ZeroMemory(savedObjAry, sizeof(tagObjInfo) * (tileNum->x * tileNum->y));

	fileForObjData = CreateFile(fileNameForObj, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjData, savedObjAry, sizeof(tagObjInfo) * (tileNum->x * tileNum->y), &readForObjData, NULL);
	CloseHandle(fileForObjData);

	//	vObj�� ������ ����
	for (int i = 0; i < tileNum->y; i++) {
		for (int j = 0; j < tileNum->x; j++) {
			(*vvMapAddr)[i][j]->setObjInfo(savedObjAry[i*tileNum->x + j]);
			(*vvMapAddr)[i][j]->_objInfo.img = IMAGEMANAGER->findImage(_objectImageKey[(*vvMapAddr)[i][j]->_objInfo.objNum].c_str());	//	�̹��� ��Ƴ־������
		}
	}

	//	==== aStar�� �ۼ����� ========
	ASTARFUNC->init();
	vvMapAstar vvMapAStar;
	vvMapAStar.clear();

	for (int i = 0; i < tileNum->y; i++) {
		vLineAstar vLineAStar;
		vLineAStar.clear();
		for (int j = 0; j < tileNum->x; j++) {
			ASTARTILE* tmpTile = new ASTARTILE;
			ASTARTILE::ASTAR_NODE_TYPE nodeType;
			if ((*vvMapAddr)[i][j]->_tileInfo.terAttr == T_ATTRIBUTE::T_ATTR_UNMOVE) {
				nodeType = ASTARTILE::ASTAR_NODE_TYPE::BLOCK;
			}
			else {
				nodeType = ASTARTILE::ASTAR_NODE_TYPE::EMPTY;
			}
			//else if ((*vvMapAddr)[i][j]->_terAttr == T_ATTRIBUTE::T_ATTR_NONE) {
			//	
			//}

			tmpTile->setAstarTile((*vvMapAddr)[i][j]->_mapIdx, (*vvMapAddr)[i][j]->_zLevel, nodeType);

			vLineAStar.push_back(tmpTile);
		}
		vvMapAStar.push_back(vLineAStar);
	}
	ASTARFUNC->setMap(vvMapAStar);


	//	���ʹ� ������ ������
	/*
	//	enemy������ �ε�
	enemyForMapEditor* savedEnemyAry = new enemyForMapEditor[vEnemySize];
	ZeroMemory(savedEnemyAry, sizeof(enemyForMapEditor) * (vEnemySize));

	fileForEnemyData = CreateFile(fileNameForEnemy, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemyData, savedEnemyAry, sizeof(enemyForMapEditor) * vEnemySize, &readForEnemyData, NULL);
	CloseHandle(fileForEnemyData);

	//	vEnemyInfo�� ������ ����			//	===========================���ʹ� ����!!! �ٽ��ؾ��ҵ�====================
	for (int i = 0; i < vEnemySize; i++) {
		enemyForMapEditor loadEnemyInfo;
		loadEnemyInfo = savedEnemyAry[i];
		loadEnemyInfo.spriteImg = IMAGEMANAGER->findImage("mobSprite");
		switch (loadEnemyInfo.name) {
		case MOB_SKEL:
			_vEnemyInfo.push_back(loadEnemyInfo);

			break;
			//	�� �߰��ɋ����� ���⼭ ��!!!
		}

	}
	*/
	//=================================

	/*
	HANDLE fileForMapSize, fileForMapData, fileForObjSize, fileForObjData, fileForEnemySize, fileForEnemyData;
	DWORD readForMapSize, readForMapData, readForObjSize, readForObjData, readForEnemySize, readForEnemyData;

	char fileNameForMap[20] = "mapData";
	char fileNameForObj[20] = "objData";
	char fileNameForEnemy[20] = "enemyData";
	char fileNameForMapSize[20] = "mapSize";
	
	char fileNameForEnemySize[20] = "enemySize";


	char idxBuffer[5] = {};		//	�� �ε��� �����
	char mapSizeStr[20] = {};		//	�� ũ�� str�����
	
	char enemySizeStr[20] = {};
	char tileNumBuffer[10] = {};		//	itoa�ӽ� �����
	char objNumBuffer[10] = {};		//	itoa�ӽ� �����
	char enemyNumBuffer[10] = {};		//	itoa�ӽ� �����

	char* token;
	char* context;
	int tmpInt;
	int vObjSize;
	int vEnemySize;

	//	�����̸� ����
	itoa(mapIdx, idxBuffer, 10);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), idxBuffer);
	strcat_s(fileNameForMapSize, sizeof(fileNameForMapSize), ".map");
	strcat_s(fileNameForMap, sizeof(fileNameForMap), idxBuffer);
	strcat_s(fileNameForMap, sizeof(fileNameForMap), ".map");

	
	strcat_s(fileNameForObj, sizeof(fileNameForObj), idxBuffer);
	strcat_s(fileNameForObj, sizeof(fileNameForObj), ".map");

	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), idxBuffer);
	strcat_s(fileNameForEnemySize, sizeof(fileNameForEnemySize), ".map");
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), idxBuffer);
	strcat_s(fileNameForEnemy, sizeof(fileNameForEnemy), ".map");


	//	��ũ�� �ε�
	fileForMapSize = CreateFile(fileNameForMapSize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapSize, mapSizeStr, 20, &readForMapSize, NULL);
	CloseHandle(fileForMapSize);

	//	enemy ũ�� �ε�
	fileForEnemySize = CreateFile(fileNameForEnemySize, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemySize, enemySizeStr, 20, &readForEnemySize, NULL);
	CloseHandle(fileForEnemySize);


	//	�� ũ�� �־���
	token = strtok_s(mapSizeStr, ",", &context);
	tmpInt = atoi(token);
	tileNum->x = tmpInt;

	token = strtok_s(NULL, ",", &context);
	tmpInt = atoi(token);
	tileNum->y = tmpInt;

	//	enemy ũ�� �־���
	token = strtok_s(enemySizeStr, ",", &context);
	tmpInt = atoi(token);
	vEnemySize = tmpInt;

	//	�ʵ����� �ε�
	tagTileInfo* savedTileAry = new tagTileInfo[tileNum->x * tileNum->y];
	ZeroMemory(savedTileAry, sizeof(tagTileInfo) * (tileNum->x * tileNum->y));

	fileForMapData = CreateFile(fileNameForMap, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForMapData, savedTileAry, sizeof(tagTileInfo) * tileNum->x * tileNum->y, &readForMapData, NULL);
	CloseHandle(fileForMapData);

	//	vv�ʿ� ������ ����
	for (int i = 0; i < tileNum->y; i++) {
		vLine tmpVLine;
		tmpVLine.clear();
		tmpVLine.reserve(tileNum->x);
		for (int j = 0; j < tileNum->x; j++) {
			TILE* tmpTile = new TILE;
			tmpTile->setTileInfo(savedTileAry[i*tileNum->x + j]);
			tmpVLine.push_back(tmpTile);
		}
		vvMapAddr->push_back(tmpVLine);
	}
	

	//	obj������ �ε�
	tagObjSpriteInfo* savedObjAry = new tagObjSpriteInfo[vObjSize];
	ZeroMemory(savedObjAry, sizeof(tagObjSpriteInfo) * (vObjSize));

	fileForObjData = CreateFile(fileNameForObj, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForObjData, savedObjAry, sizeof(tagObjSpriteInfo) * vObjSize, &readForObjData, NULL);
	CloseHandle(fileForObjData);

	//	vObj�� ������ ����
	for (int i = 0; i < vObjSize; i++) {
		OBJ* tmpObj = new OBJ;
		tmpObj->setObjFromSpriteInfo(savedObjAry[i]);
		vObjAddr->push_back(tmpObj);
	}
	   
	//	enemy������ �ε�
	tagEnemySpriteInfoForMapEditor* savedEnemyAry = new tagEnemySpriteInfoForMapEditor[vEnemySize];
	ZeroMemory(savedEnemyAry, sizeof(tagEnemySpriteInfoForMapEditor) * (vEnemySize));

	fileForEnemyData = CreateFile(fileNameForEnemy, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(fileForEnemyData, savedEnemyAry, sizeof(tagEnemySpriteInfoForMapEditor) * vEnemySize, &readForEnemyData, NULL);
	CloseHandle(fileForEnemyData);

	//	vEnemyInfo�� ������ ����
	for (int i = 0; i < vEnemySize; i++) {
		tagEnemySpriteInfoForMapEditor loadEnemyInfo;
		loadEnemyInfo = savedEnemyAry[i];
		switch (loadEnemyInfo.imgNum) {
		case MOB_SKEL:
			enemy* tmpSkel = new skeleton;
			tmpSkel->setEnemyInfo(
				loadEnemyInfo.tileCenterPosAtSprite,
				loadEnemyInfo.sampleRc,
				loadEnemyInfo.pos,
				loadEnemyInfo.mobTileSize,
				loadEnemyInfo.imgNum,
				loadEnemyInfo.zLvl,
				loadEnemyInfo.mapIdx,
				loadEnemyInfo.rc
			);
			vEnemyAddr->push_back(tmpSkel);

			break;
			//	�� �߰��ɋ����� ���⼭ ��!!!
		}

	}

	//	========= vvMap, tileNum, vObj, vEnemy �Ϸ� =========

	//	==== aStar�� �ۼ����� ========
	ASTARFUNC->init();
	vvMapAstar vvMapAStar;
	vvMapAStar.clear();

	for (int i = 0; i < tileNum->y; i++) {
		vLineAstar vLineAStar;
		vLineAStar.clear();
		for (int j = 0; j < tileNum->x; j++) {
			ASTARTILE* tmpTile = new ASTARTILE;
			ASTARTILE::ASTAR_NODE_TYPE nodeType;
			if ((*vvMapAddr)[i][j]->_terAttr == T_ATTRIBUTE::T_ATTR_UNMOVE) {
				nodeType = ASTARTILE::ASTAR_NODE_TYPE::BLOCK;
			}
			else {
				nodeType = ASTARTILE::ASTAR_NODE_TYPE::EMPTY;
			}
			//else if ((*vvMapAddr)[i][j]->_terAttr == T_ATTRIBUTE::T_ATTR_NONE) {
			//	
			//}

			tmpTile->setAstarTile((*vvMapAddr)[i][j]->_idx, (*vvMapAddr)[i][j]->_zLevel, nodeType);
			
			vLineAStar.push_back(tmpTile);
		}
		vvMapAStar.push_back(vLineAStar);
	}
	ASTARFUNC->setMap(vvMapAStar);
	*/

}
