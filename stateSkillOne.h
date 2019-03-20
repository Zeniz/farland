#pragma once
#include "charStatePattern.h"

class stateSkillOne : public charStatePattern
{
public:
	stateSkillOne();
	~stateSkillOne();

public:
	void onIdle(Character* character) override;
	void onMove(Character* character) override;
	void onCast(Character* character) override;
	void onDead(Character* character) override;
	void onGetHit(Character* character) override;
	void onStone(Character* character) override;
	void onFrozen(Character* character) override;
	void onGetHit2(Character* character) override;
	void onBlock(Character* character) override;

	void onBasicAtk(Character* character) override;
	void onSkillOne(Character* character) override;
	void onSkillTwo(Character* character) override;
	void onSkillThree(Character* character) override;
	void onSkillFour(Character* character) override;

	void update(Character* character) override;

	SKILL_DIR ConvertCharDirToSkillDir(Character* chara) {
		SKILL_DIR skillDir = SKILL_DIR::SKILL_DIR_NONE;
		CHAR_DIR charDir = chara->_dir;
		if (charDir == CHAR_DIR::LT) {
			skillDir = SKILL_DIR::SKILL_DIR_LT;
		}
		else if (charDir == CHAR_DIR::LB) {
			skillDir = SKILL_DIR::SKILL_DIR_LB;
		}
		else if (charDir == CHAR_DIR::RT) {
			skillDir = SKILL_DIR::SKILL_DIR_RT;
		}
		else if (charDir == CHAR_DIR::RB) {
			skillDir = SKILL_DIR::SKILL_DIR_RB;
		}
		return skillDir;
	}
};

