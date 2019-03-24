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

	heal1* tmpHeal1 = new heal1;
	tmpHeal1->init();
	_mSkills.insert(make_pair("heal1", tmpHeal1));

	heal2* tmpHeal2 = new heal2;
	tmpHeal2->init();
	_mSkills.insert(make_pair("heal2", tmpHeal2));

	buff1* tmpBuff1 = new buff1;
	tmpBuff1->init();
	_mSkills.insert(make_pair("buff1", tmpBuff1));

	resurrection* tmpResurrection = new resurrection;
	tmpResurrection->init();
	_mSkills.insert(make_pair("resurrection", tmpResurrection));


	bossAtk1* tmpBossAtk1 = new bossAtk1;
	tmpBossAtk1->init();
	_mSkills.insert(make_pair("bossAtk1", tmpBossAtk1));

	bossAtk2* tmpBossAtk2 = new bossAtk2;
	tmpBossAtk2->init();
	_mSkills.insert(make_pair("bossAtk2", tmpBossAtk2));

	bossBuff* tmpBossBuff = new bossBuff;
	tmpBossBuff->init();
	_mSkills.insert(make_pair("bossBuff", tmpBossBuff));

	snatch* tmpSnatch = new snatch;
	tmpSnatch->init();
	_mSkills.insert(make_pair("snatch", tmpSnatch));
	

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
