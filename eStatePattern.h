#pragma once
#include "gameNode.h"



class enemy;

class eStatePattern : public gameNode
{
public:
	eStatePattern();
	~eStatePattern();

public:
	void Idle(enemy* enemy);
	void Dead(enemy* enemy);
	void GetDmg(enemy* enemy);
	void Stoned(enemy* enemy);
	void Frozen(enemy* enemy);
	void GetCriDmg(enemy* enemy);
	void Stunned(enemy* enemy);
	void Deffence(enemy* enemy);
	void Move(enemy* enemy);

	void Atk1(enemy* enemy);
	void Atk2(enemy* enemy);
	void Atk3(enemy* enemy);

	void Skill1Cast(enemy* enemy);
	void Skill1Shot(enemy* enemy);
	void Skill2Cast(enemy* enemy);
	void Skill2Shot(enemy* enemy);
	void Skill3Cast(enemy* enemy);
	void Skill3Shot(enemy* enemy);
	void Skill4Cast(enemy* enemy);
	void Skill4Shot(enemy* enemy);


	//move용
	void CalDirFunc(enemy* enemy);
	void CalTileForRender(enemy* enemy);

	//방향세팅용
	void CalDirToPlayer(enemy* enemy);



	//	Kaiser용
	void ChooseSkill(enemy* enemy);

	SKILL_DIR ConvertCharDirToSkillDir(enemy* enemy);
	

	void TargetSelectFunc(enemy* enemy);
	
	/*
	{
		SKILL_DIR skillDir = SKILL_DIR::SKILL_DIR_NONE;
		E_DIR dir = enemy->_dir;
		if (dir == E_DIR::DIR_LT) {
			skillDir = SKILL_DIR::SKILL_DIR_LT;
		}
		else if (dir == E_DIR::DIR_LB) {
			skillDir = SKILL_DIR::SKILL_DIR_LB;
		}
		else if (dir == E_DIR::DIR_RT) {
			skillDir = SKILL_DIR::SKILL_DIR_RT;
		}
		else if (dir == E_DIR::DIR_RB) {
			skillDir = SKILL_DIR::SKILL_DIR_RB;
		}
		return skillDir;
	}
	*/

};

