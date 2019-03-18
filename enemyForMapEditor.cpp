#include "stdafx.h"
#include "enemyForMapEditor.h"


enemyForMapEditor::enemyForMapEditor()
{
}


enemyForMapEditor::~enemyForMapEditor()
{
}

void enemyForMapEditor::init()
{
	spriteImg = nullptr;
	sampleRc = { NULL,NULL,NULL,NULL };
	centerPosInImg = { NULL,NULL };
	mobTileSize = { NULL, NULL };

	name = ENEMY_NAME::E_NAME_NONE;
	mapIdx = { NULL,NULL };
	rc = { NULL,NULL,NULL,NULL };
}
