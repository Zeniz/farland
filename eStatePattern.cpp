#include "stdafx.h"
#include "eStatePattern.h"
#include "enemy.h"
#include "character.h"


eStatePattern::eStatePattern()
{
}


eStatePattern::~eStatePattern()
{
}

void eStatePattern::Idle(enemy * enemy)
{
	enemy->_tileForRender = enemy->_pCurTile;
	enemy->_isAtkFin = false;
	bool isNearChar = false;
	int targetCharIdx = -1;
	int targetCharDistance = 999999;
	int nearCharIdx = -1;
	
	//	isNoticeTrue,
	if (enemy->_isNotice) {

		//	�ڱ� �ֺ��� ĳ���� �ֳ� �˻�
		for (int i = 0; i < enemy->_vChara->size(); i++) {
			int differIdxSize = abs(enemy->getChara(i)->mapIdx.x - enemy->_mapIdx.x) + abs(enemy->getChara(i)->mapIdx.y - enemy->_mapIdx.y);
			//	idx���̰� 1,0 �̶��, (��ĭ�������ų�, �����ֵ簡)
			if (differIdxSize < 2) {
				targetCharIdx = i;
				isNearChar = true;
			}

			//	idx���̰� ���̳���, ���� ������ ����
			else {
				if (differIdxSize < targetCharDistance) {
					targetCharDistance = differIdxSize;
					nearCharIdx = i;
				}
			}
		}

		//	��ó ĳ���� ������ ����
		if (isNearChar) {
			enemy->_atkCount++;
			if (enemy->_atkCount > enemy->ATKCOUNT_MAX) {
				enemy->_atkCount = 0;
				enemy->_targetCharIdx = targetCharIdx;
				enemy->_state = E_STATE::E_ATK1;
				enemy->_isStateChanged = true;
			}

		}

		//	ĳ���� ������ �̵�
		else {
			enemy->_targetCharIdx = nearCharIdx;
			enemy->_state = E_STATE::E_MOVE;
			enemy->_isStateChanged = true;
			ASTARFUNC->PathFind(enemy->_mapIdx, enemy->getChara(nearCharIdx)->mapIdx, enemy->_mapIdx, enemy->_lWayIdxList);
			//	�˻��� �ư�, -1,-,1 �� �ƴ϶�� -> ��������ǥ(�÷��̾�)�� ����.
			if (enemy->_lWayIdxList.size() != 0 && enemy->_lWayIdxList.begin()->x != -1) {
				enemy->_lWayIdxList.pop_back();
			}

		}
	}
		


}

void eStatePattern::Dead(enemy * enemy)
{
	enemy->_deleteDelayCount++;
}

void eStatePattern::GetDmg(enemy * enemy)
{
	if (!enemy->_ani->isPlay()) {
		enemy->_state = enemy->_preState;
		enemy->_isStateChanged = true;
	}
}

void eStatePattern::Stoned(enemy * enemy)
{
}

void eStatePattern::Frozen(enemy * enemy)
{
}

void eStatePattern::GetCriDmg(enemy * enemy)
{
}

void eStatePattern::Stunned(enemy * enemy)
{
	enemy->_abnormalConditionCount++;
	if (enemy->_abnormalConditionCount > enemy->STUNNED_COUNTMAX) {
		enemy->_abnormalConditionCount = 0;
		enemy->_state = enemy->_preState;
		enemy->_isStateChanged = true;
	}
}

void eStatePattern::Deffence(enemy * enemy)
{
}

void eStatePattern::Move(enemy * enemy)
{
	CalTileForRender(enemy);
	if (enemy->_lWayIdxList.size() != 0) {
		POINT targetIdx = { enemy->_lWayIdxList.begin()->x, enemy->_lWayIdxList.begin()->y };
		//	������ �� ������ ������, ���̵�� �ٲٰ� ������
		if (targetIdx.x == -1 && targetIdx.y == -1) {
			enemy->_state = E_STATE::E_IDLE;
			//enemy->_curState = character->_arrStatePattern[static_cast<const int>(E_STATE::IDLE)];
			enemy->_isStateChanged = true;
			//if ((enemy->_lOrderList.begin()->kinds) == E_STATE::E_MOVE)
			//	enemy->_lOrderList.pop_front();

		}
		//	���� ���
		//	targetIdx�� ���� ���̴�, x�ʿ��� 1���ų�, y�ʿ��� 1����.
		//	x�ʿ��� +1�̸�, vecX ����, vecY ����,
		//	y�ʿ��� +1�̸�, vecX ����, vecY ����,
		enemy->_moveVec.x = (targetIdx.x - enemy->_mapIdx.x) * TILESIZE_WID / enemy->_statValue[E_STATS::E_MOVESPD]
			+ (-1)*(targetIdx.y - enemy->_mapIdx.y) * TILESIZE_WID / enemy->_statValue[E_STATS::E_MOVESPD];
		enemy->_moveVec.y = (targetIdx.x - enemy->_mapIdx.x) * TILESIZE_HEI / enemy->_statValue[E_STATS::E_MOVESPD]
			+ (targetIdx.y - enemy->_mapIdx.y) * TILESIZE_HEI / enemy->_statValue[E_STATS::E_MOVESPD];

		CalDirFunc(enemy);

		vvMap* pvvMap = enemy->_vvMap;

		//	���������
		if (abs((*pvvMap)[targetIdx.y][targetIdx.x]->_pos.x - enemy->_pos.x) < enemy->FLOAT_ERROR) {
			enemy->_moveVec.x = 0;
			enemy->_pos.x = (*pvvMap)[targetIdx.y][targetIdx.x]->_pos.x;
		}
		if (abs((*pvvMap)[targetIdx.y][targetIdx.x]->_pos.y - enemy->_pos.y) < enemy->FLOAT_ERROR) {
			enemy->_moveVec.y = 0;
			enemy->_pos.y = (*pvvMap)[targetIdx.y][targetIdx.x]->_pos.y;
		}
		//	����Ÿ�Ͽ� �����ߴٸ�,
		if (enemy->_moveVec.x == 0 && enemy->_moveVec.y == 0) {
			enemy->_mapIdx.x = enemy->_lWayIdxList.begin()->x;
			enemy->_mapIdx.y = enemy->_lWayIdxList.begin()->y;
			enemy->_pCurTile = (*pvvMap)[enemy->_mapIdx.y][enemy->_mapIdx.x];
			enemy->_lWayIdxList.pop_front();

			//	MAXCOUNT��ŭ Ÿ���̵�������, idle�� ��ȯ.
			enemy->_moveTileCount++;
			if (enemy->_moveTileCount > enemy->MOVETILECOUNT_MAX) {
				enemy->_moveTileCount = 0;
				enemy->_state = E_STATE::E_IDLE;
				enemy->_lWayIdxList.clear();
				enemy->_isStateChanged = true;
				return;

			}
		}

		//	�̵�����
		enemy->_pos.x += enemy->_moveVec.x;
		enemy->_pos.y += enemy->_moveVec.y;
		//enemy->_rc = RectMake(enemy->_pos.x - 128, enemy->_pos.y - 160,
		//	enemy->_img->GetFrameWidth(), enemy->_img->GetFrameHeight());
		enemy->_rc = RectMake(enemy->_pos.x - 128,
			enemy->_pos.y - 156,
			enemy->_img->GetFrameWidth(),
			enemy->_img->GetFrameHeight());
		
		enemy->_targetedRc = RectMake(enemy->_pos.x - enemy->WID_FROM_CENTERPOS,
			enemy->_pos.y - enemy->LEN_TO_TOP_FROM_CENTERPOS,
			enemy->WID_FROM_CENTERPOS * 2, 
			enemy->LEN_TO_TOP_FROM_CENTERPOS + enemy->LEN_TO_BOTTOM_FROM_CENTERPOS);
		
	
	}
	//	������ ����
	else {
		enemy->_state = E_STATE::E_IDLE;
		//enemy->_curState = character->_arrStatePattern[static_cast<const int>(CHAR_STATE::IDLE)];
		enemy->_isStateChanged = true;
		//if ((enemy->_lOrderList.begin()->kinds) == E_STATE::E_MOVE)
		//	enemy->_lOrderList.pop_front();
	}

}

void eStatePattern::Atk1(enemy * enemy)
{
	//if (!enemy->_isAtkFin) {
	//	enemy->_dir = CalDirToPlayer(enemy);
	//}


	if (!enemy->_isAtkFin && enemy->_ani->isLastFrame()) {
	//if (enemy->_ani->isLastFrame()) {
		enemy->_isAtkFin = true;
		enemy->_ani->stop();
		//	Ÿ��ĳ������ hp�� ���ʹ��� value��, atk��ŭ ��´�. 
		//	��ų��� �߰�����
		enemy->getChara(enemy->_targetCharIdx)->setCurHpAug(-enemy->_statValue[E_STATS::E_ATK]);
	}
}

void eStatePattern::Atk2(enemy * enemy)
{
}

void eStatePattern::Atk3(enemy * enemy)
{
}

void eStatePattern::Skill1Cast(enemy * enemy)
{
}

void eStatePattern::Skill1Shot(enemy * enemy)
{
}

void eStatePattern::Skill2Cast(enemy * enemy)
{
}

void eStatePattern::Skill2Shot(enemy * enemy)
{
}

void eStatePattern::Skill3Cast(enemy * enemy)
{
}

void eStatePattern::Skill3Shot(enemy * enemy)
{
}

void eStatePattern::Skill4Cast(enemy * enemy)
{
}

void eStatePattern::Skill4Shot(enemy * enemy)
{
}

void eStatePattern::CalDirFunc(enemy * enemy)
{
	POINTFLOAT moveVec = enemy->_moveVec;
	if (moveVec.x > 0 && moveVec.y > 0) {
		if (enemy->_dir != E_DIR::DIR_RB) {
			enemy->_dir = E_DIR::DIR_RB;
			enemy->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::RB;
	}
	else if (moveVec.x > 0 && moveVec.y < 0) {
		if (enemy->_dir != E_DIR::DIR_RT) {
			enemy->_dir = E_DIR::DIR_RT;
			enemy->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::RB;
	}
	else if (moveVec.x < 0 && moveVec.y > 0) {
		if (enemy->_dir != E_DIR::DIR_LB) {
			enemy->_dir = E_DIR::DIR_LB;
			enemy->_isStateChanged = true;
		}
		//character->_dir = CHAR_DIR::LB;
	}
	else if (moveVec.x < 0 && moveVec.y < 0) {
		if (enemy->_dir != E_DIR::DIR_LT) {
			enemy->_dir = E_DIR::DIR_LT;
			enemy->_isStateChanged = true;
		}

		//character->_dir = CHAR_DIR::LT;
	}
}

void eStatePattern::CalTileForRender(enemy * enemy)
{
	POINT tileIdx;
	vvMap* vvMap = enemy->_vvMap;
	E_DIR dir = enemy->_dir;

	switch (dir)
	{
	case DIR_NONE:
		break;
	case DIR_LT:
		enemy->_probePos.x = enemy->_pos.x - TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y - TILESIZE_HEI / 4;
		break;
	case DIR_RT:
		enemy->_probePos.x = enemy->_pos.x + TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y - TILESIZE_HEI / 4;
		break;
	case DIR_LB:
		enemy->_probePos.x = enemy->_pos.x - TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y + TILESIZE_HEI / 4;
		break;
	case DIR_RB:
		enemy->_probePos.x = enemy->_pos.x + TILESIZE_WID / 4;
		enemy->_probePos.y = enemy->_pos.y + TILESIZE_HEI / 4;
		break;
	case DIR_END:
		break;
	default:
		break;
	}
	tileIdx = ConvertPosToIdx(enemy->_probePos.x, enemy->_probePos.y,
		TILESIZE_WID, TILESIZE_HEI);
	if (0 <= tileIdx.x && tileIdx.x < (*vvMap)[0].size() &&
		0 <= tileIdx.y && tileIdx.y < (*vvMap).size()) {
		enemy->_tileForRender = (*vvMap)[tileIdx.y][tileIdx.x];
	}
	else {
		enemy->_tileForRender = enemy->_pCurTile;
	}
	

}


void eStatePattern::CalDirToPlayer(enemy * enemy)
{
	//E_DIR dir = E_DIR::DIR_LB;
	vChara* _vChara = (enemy->_vChara);
	POINT playerMapIdx = (*_vChara)[enemy->_targetCharIdx]->mapIdx;

	if (enemy->_mapIdx.x - 1 == playerMapIdx.x &&
		enemy->_mapIdx.y == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_LT;
		//*dir = E_DIR::DIR_LT;
	}
	else if(enemy->_mapIdx.x + 1 == playerMapIdx.x &&
		enemy->_mapIdx.y == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_RB;
		//*dir = E_DIR::DIR_RB;
	}
	else if (enemy->_mapIdx.x == playerMapIdx.x &&
		enemy->_mapIdx.y - 1 == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_RT;
		//*dir = E_DIR::DIR_RT;
	}
	else if (enemy->_mapIdx.x + 1 == playerMapIdx.x &&
		enemy->_mapIdx.y + 1 == playerMapIdx.y) {
		enemy->_dir = E_DIR::DIR_LB;
		//*dir = E_DIR::DIR_LB;
	}
	

	//return dir;
}
