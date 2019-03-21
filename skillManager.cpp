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

	roundSlash* tmpRoundSlash = new roundSlash;
	tmpRoundSlash->init();
	_mSkills.insert(make_pair("roundSlash", tmpRoundSlash));

	slashUlti* tmpSlashUlti = new slashUlti;
	tmpSlashUlti->init();
	_mSkills.insert(make_pair("slashUlti", tmpSlashUlti));

	thunder* tmpThunder = new thunder;
	tmpThunder->init();
	_mSkills.insert(make_pair("thunder", tmpThunder));

	flameBurst* tmpFlameBurst = new flameBurst;
	tmpFlameBurst->init();
	_mSkills.insert(make_pair("flameBurst", tmpFlameBurst));

	flameNova* tmpFlameNova = new flameNova;
	tmpFlameNova->init();
	_mSkills.insert(make_pair("flameNova", tmpFlameNova));

	meteor* tmpMeteor = new meteor;
	tmpMeteor->init();
	_mSkills.insert(make_pair("meteor", tmpMeteor));
	

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
