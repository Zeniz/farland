#include "stdafx.h"
#include "character.h"

#include "charStatePattern.h"
#include "stateIdle.h"
#include "stateMove.h"
#include "stateCast.h"
#include "stateDead.h"
#include "stateGetHit.h"
#include "stateStone.h"
#include "stateFrozen.h"
#include "stateGetHit2.h"
#include "stateBlock.h"


Character::Character()
{
	//	<objects> : public
	_img = nullptr;
	_frameX = NULL;
	_frameY = NULL;
	
	_pos = { NULL,NULL };
	_rc = { NULL,NULL,NULL,NULL };
	_zLevel = NULL;	
	_objKinds = OBJ_KINDS::OBJKIND_CHAR;

	_ani = nullptr;
	_isStateChanged = true;
	_frontTile = nullptr;
	_curTile = nullptr;
	_targetTile = nullptr;

	for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
		for (int j = 0; j < CHAR_VALUE_KINDS::CHAR_VALUE_NONE; j++) {
			_charValue[i][j] = NULL;
		}
	}
	
	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };
	

	_name = CHAR_NAME::NONE;
	_dir = CHAR_DIR::NONE;
	_state = CHAR_STATE::NONE;
	//_statePattern = nullptr;
	for (int i = 0; i < static_cast<const int>(CHAR_STATE::CHAR_STATE_END); i++)
		_arrStatePattern[i] = nullptr;

	_portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
	_portraitFrameIdx = { NULL,NULL };
	_curSkill = CUR_SKILL::NONE;
	_lOrderList.clear();
	_lWayIdxList.clear();

}


Character::~Character()
{
}

HRESULT Character::init()
{
	_img = NULL;
	_frameX = NULL;
	_frameY = NULL;

	_pos = { NULL,NULL };
	_rc = { NULL,NULL,NULL,NULL };
	_zLevel = NULL;
	_objKinds = OBJ_KINDS::OBJKIND_CHAR;

	_ani = nullptr;
	_frontTile = nullptr;
	_curTile = nullptr;
	_targetTile = nullptr;


	for (int i = 0; i < CHAR_VALUE_CURAUG::CURAUG_END; i++) {
		for (int j = 0; j < CHAR_VALUE_KINDS::CHAR_VALUE_NONE; j++) {
			_charValue[i][j] = NULL;
		}
	}

	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };

	_name = CHAR_NAME::NONE;
	_dir = CHAR_DIR::NONE;
	_state = CHAR_STATE::NONE;
	//_statePattern = nullptr;
	for (int i = 0; i < static_cast<const int>(CHAR_STATE::CHAR_STATE_END); i++)
		_arrStatePattern[i] = nullptr;

	_portraitKinds = CHAR_PORTRAIT_KINDS::NONE;
	_portraitFrameIdx = { NULL,NULL };
	_curSkill = CUR_SKILL::NONE;
	_lOrderList.clear();
	_lWayIdxList.clear();


	

	return S_OK;
}

void Character::aniRender()
{
	_img->aniRender(_rc.left, _rc.top, this->_ani);
}

void Character::InitObjectiveVal(image* img, POINTFLOAT pos, int zlvl, animation * ani, TILE * curTile)
{
	_img = img;
	_frameX = 0;
	_frameY = 0;

	_pos = pos;
	_rc = RectMake(_pos.x - 128, _pos.y - 160, _img->GetFrameWidth(), _img->GetFrameHeight());
	_zLevel = zlvl;

	_ani = ani;
	_curTile = curTile;
	_frontTile = nullptr;
	_targetTile = nullptr;

}

void Character::InitCharacteristicVal(float maxHp, float curHp, float regenHp,
	float maxMp, float curMp, float regenMp,
	float moveSpd, float castSpd, float atk, float def,
	float mAtk, float mDef,
	CHAR_NAME charName, CHAR_DIR charDir, CHAR_STATE charState)
{
	_charValue[CUR][MAX_HP] = maxHp;
	_charValue[CUR][CUR_HP] = curHp;
	_charValue[CUR][REGEN_HP] = regenHp;
	_charValue[CUR][MAX_MP] = maxMp;
	_charValue[CUR][CUR_MP] = curMp;
	_charValue[CUR][REGEN_MP] = regenMp;
	_charValue[CUR][MOVE_SPD] = moveSpd;
	_charValue[CUR][CASTING_SPD] = castSpd;
	_charValue[CUR][ATK] = atk;
	_charValue[CUR][DEF] = def;
	_charValue[CUR][M_ATK] = mAtk;
	_charValue[CUR][M_DEF] = mDef;


	_moveVec = { NULL,NULL };
	_probePos = { NULL,NULL };	//	¾÷µ«ÇÊ¿ä,

	_name = charName;
	_dir = charDir;
	_state = charState;
	


}

void Character::InitCharacteristicAugVal(float augMaxHp, float augCurHp, float augRegenHp, float augMaxMp, float augCurMp, float augRegenMp, float augMoveSpd, float augCastSpd, float augAtk, float augDef, float augMAtk, float augMDef)
{
	_charValue[AUG][MAX_HP] = augMaxHp;
	_charValue[AUG][CUR_HP] = augCurHp;
	_charValue[AUG][REGEN_HP] = augRegenHp;
	_charValue[AUG][MAX_MP] = augMaxMp;
	_charValue[AUG][CUR_MP] = augCurMp;
	_charValue[AUG][REGEN_MP] = augRegenMp;
	_charValue[AUG][MOVE_SPD] = augMoveSpd;
	_charValue[AUG][CASTING_SPD] = augCastSpd;
	_charValue[AUG][ATK] = augAtk;
	_charValue[AUG][DEF] = augDef;
	_charValue[AUG][M_ATK] = augMAtk;
	_charValue[AUG][M_DEF] = augMDef;
}

void Character::InitCharacteristicAugVal()
{
	_charValue[AUG][MAX_HP] = NULL;
	_charValue[AUG][CUR_HP] = NULL;
	_charValue[AUG][REGEN_HP] = NULL;
	_charValue[AUG][MAX_MP] = NULL;
	_charValue[AUG][CUR_MP] = NULL;
	_charValue[AUG][REGEN_MP] = NULL;
	_charValue[AUG][MOVE_SPD] = NULL;
	_charValue[AUG][CASTING_SPD] = NULL;
	_charValue[AUG][ATK] = NULL;
	_charValue[AUG][DEF] = NULL;
	_charValue[AUG][M_ATK] = NULL;
	_charValue[AUG][M_DEF] = NULL;
}