#pragma once


enum ENEMY_NAME {
	E_NAME_NONE = -1,
	MOB_SKEL,

	E_NAME_END,
};

struct enemyForMapEditor
{
	
	image* spriteImg;
	RECT sampleRc;
	POINT centerPosInImg;
	POINT mobTileSize;


	ENEMY_NAME name;
	POINT mapIdx;
	RECT rc;

	enemyForMapEditor();
	~enemyForMapEditor();
	
	void init();

	int getWid() {
		return this->sampleRc.right - this->sampleRc.left;
	}
	int getHei() {
		return this->sampleRc.bottom - this->sampleRc.top;
	}

	int getHeiPosToTop() {
		return this->centerPosInImg.y - this->sampleRc.top;
	}
	int getWidPosToLeft() {
		return this->centerPosInImg.x - this->sampleRc.left;
	}

	enemyForMapEditor getEnemyInfo() {
		enemyForMapEditor tmpEnemy;
		tmpEnemy.spriteImg = this->spriteImg;
		tmpEnemy.sampleRc = this->sampleRc;
		tmpEnemy.centerPosInImg = this->centerPosInImg;
		tmpEnemy.mobTileSize = this->mobTileSize;

		tmpEnemy.name = this->name;
		tmpEnemy.mapIdx = this->mapIdx;
		tmpEnemy.rc = this->rc;

		return tmpEnemy;

	}
};

