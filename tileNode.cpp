#include "stdafx.h"
#include "tileNode.h"


bool compareObj(OBJ* obj1, OBJ* obj2) {
	if (obj1->_mapIdx.y != obj2->_mapIdx.y) {
		return (obj1->_mapIdx.y < obj2->_mapIdx.y);
	}
	else {
		return (obj1->_mapIdx.x < obj2->_mapIdx.x);
	}

};

