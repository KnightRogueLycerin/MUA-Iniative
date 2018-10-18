#include "stdafx.h"
#include "Data.h"

/* Action */
Action::Action() {
	Type = Category::Undefined;
	Initiative = 0;
	Name = "undefined";
	Actor = "UNSET";
	Target = "UNSET";
	hasTarget = false;
}
Action::Action(Category type, int initiative, std::string name, std::string actor) {
	Type = type;
	Initiative = initiative;
	Name = name;
	Actor = actor;
	Target = "UNSET";
	hasTarget = false;
}
Action::Action(Category type, int initiative, std::string name, std::string actor, std::string target) {
	Type = type;
	Initiative = initiative;
	Name = name;
	Actor = actor;
	Target = target;
	hasTarget = true;
}
Action::~Action() {}

/* Character */
Character::Character() {
	Name = "UNSET";
	Active = false;
	IniativeRoll = 0;
	IniativeBonus = 0;
	IniativeItem = 0;
	ExtraAction = false;
}
Character::Character(std::string name, int iniativeBonus, bool extraAction) {
	Name = name;
	Active = true;
	IniativeRoll = 0;
	IniativeBonus = iniativeBonus;
	IniativeItem = 0;
	ExtraAction = extraAction;
}
Character::Character(std::string name, int iniativeBonus, int itemBonus, bool extraAction){
	Name = name;
	Active = true;
	IniativeRoll = 0;
	IniativeBonus = iniativeBonus;
	IniativeItem = itemBonus;
	ExtraAction = extraAction;
}
Character::~Character() {}

int Character::getIniative() { return IniativeBonus + IniativeRoll + IniativeItem; }

void Character::setIniative(int roll){
	IniativeRoll = roll;
}
void Character::setIniative(int roll, int item){
	IniativeRoll = roll;
	IniativeItem = item;
}

std::vector<Action>& Character::getActions(){
	return Actions;
}

void Character::swapActions(int IndexA, int IndexB){
	std::swap(Actions[IndexA], Actions[IndexB]);
}

void Character::clearActions(){
	Actions.clear();
}
