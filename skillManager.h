#pragma once
#include "singletonBase.h"
#include <map>
#include "slashOne.h"
#include "doubleSlash.h"
#include "roundSlash.h"
#include "slashUlti.h"

#include "thunder.h"
#include "flameBurst.h"
#include "flameNova.h"
#include "meteor.h"

#include "heal1.h"
#include "heal2.h"
#include "buff1.h"
#include "resurrection.h"

#include "bossAtk1.h"
#include "bossAtk2.h"
#include "bossBuff.h"
#include "snatch.h"

class skillNode;



class skillManager : public singletonBase<skillManager>
{
private:
	map<string, skillNode*>				_mSkills;
	map<string, skillNode*>::iterator	_miSkills;



public:
	skillManager();
	~skillManager();

	HRESULT init();
	void release();

	//void LinkToVEnemy(vEnemy* vEnemyAddr) { _pvEnemy = vEnemyAddr; }
	//void LinkToVChara(vChara* vCharaAddr) { _pvChara = vCharaAddr; }

	skillNode* FindSkill(string skillName);

};

