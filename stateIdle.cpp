#include "stdafx.h"
#include "stateIdle.h"


stateIdle::stateIdle()
{
}


stateIdle::~stateIdle()
{
}

void stateIdle::onIdle(Character* character)
{
}

void stateIdle::onMove(Character* character)
{
}

void stateIdle::onCast(Character* character)
{
}

void stateIdle::onDead(Character* character)
{
}

void stateIdle::onGetHit(Character* character)
{
}

void stateIdle::onStone(Character* character)
{
}

void stateIdle::onFrozen(Character* character)
{
}

void stateIdle::onGetHit2(Character* character)
{
}

void stateIdle::onBlock(Character* character)
{
}

void stateIdle::onBasicAtk(Character * character)
{
}

void stateIdle::onSkillOne(Character * character)
{
}

void stateIdle::onSkillTwo(Character * character)
{
}

void stateIdle::onSkillThree(Character * character)
{
}

void stateIdle::onSkillFour(Character * character)
{
}

void stateIdle::update(Character* character)
{
	character->_tileForRender = character->_curTile;

	//	오더리스트가 있다면,
	if (character->_lOrderList.size() != 0) {
		ORDER_KINDS order = *(character->_lOrderList.begin());
		switch (order)
		{
		case ORDER_KINDS::NONE:
			break;
		case ORDER_KINDS::HOLD:
			break;
		case ORDER_KINDS::MOVE:
			character->_state = CHAR_STATE::MOVE;
			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
			character->_isStateChanged = true;
			break;
		case ORDER_KINDS::ATK:
			break;
		case ORDER_KINDS::SKILL1:
			break;
		case ORDER_KINDS::SKILL2:
			break;
		case ORDER_KINDS::SKILL3:
			break;
		case ORDER_KINDS::SKILL4:
			break;
		default:
			break;
		}

	}

	
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
	//	vvMap* pvvMap = character->_vvMap;
	//	POINT ClickedIdx;
	//	ClickedIdx = ConvertPosToIdx(_ptMouse.x, _ptMouse.y, TILESIZE_WID, TILESIZE_HEI);
	//
	//	if (0 <= ClickedIdx.x && ClickedIdx.x < (*pvvMap)[0].size() &&
	//		0 <= ClickedIdx.y && ClickedIdx.y < (*pvvMap).size()) {
	//		if ((*pvvMap)[ClickedIdx.y][ClickedIdx.x]->_terAttr == T_ATTRIBUTE::T_ATTR_NONE) {
	//			character->_targetTile = ((*pvvMap)[ClickedIdx.y][ClickedIdx.x]);
	//			ASTARFUNC->PathFind(character->mapIdx, PointMake(ClickedIdx.x, ClickedIdx.y), character->mapIdx, character->_lWayIdxList);
	//			character->_state = CHAR_STATE::MOVE;
	//			character->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::MOVE)];
	//			character->_isStateChanged = true;
	//
	//		}
	//	}
	//	
	//}
}
