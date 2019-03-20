#include "stdafx.h"
#include "skillManager.h"


skillManager::skillManager()
{
}


skillManager::~skillManager()
{
}

HRESULT skillManager::init()
{
	_mSkills.clear();

	slashOne* tmpSlashOne = new slashOne;
	tmpSlashOne->init();
	_mSkills.insert(make_pair("slashOne", tmpSlashOne));

	doubleSlash* tmpDoubleSlash = new doubleSlash;
	tmpDoubleSlash->init();
	_mSkills.insert(make_pair("doubleSlash", tmpDoubleSlash));




	return S_OK;
}

void skillManager::release()
{
}

skillNode* skillManager::FindSkill(string skillName)
{
	_miSkills = _mSkills.find(skillName);
	return _miSkills->second;
}
