#pragma once
#include "gameNode.h"
#include "character.h"

class Characters;

class charSkills : public gameNode
{
protected:

	string _name;
	string _aniKeyName;


public:
	charSkills();
	~charSkills();
};

