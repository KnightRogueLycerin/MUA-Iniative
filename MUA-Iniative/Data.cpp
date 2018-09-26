#include "stdafx.h"
#include "Data.h"

Character::Character() {
	Name = "UNSET";
	Active = false;
	IniativeRoll = 0;
	IniativeBonus = 0;
	ExtraAction = false;
}
Character::Character(std::string name, int iniativeBonus, bool extraAction) {
	Name = name;
	Active = true;
	IniativeRoll = 0;
	IniativeBonus = iniativeBonus;
	ExtraAction = extraAction;
}
Character::~Character() {}
int Character::getIniative() { return IniativeBonus + IniativeRoll; }

Action::Action() {
	Type = Category::Undefined;
	Initiative = 0;
	Name = "undefined";
	Description = "undefined";
	Actor = "UNSET";
	Target = "UNSET";
	hasTarget = false;
}
Action::Action(Category type, int initiative, std::string name, std::string description, std::string actor) {
	Type = type;
	Initiative = initiative;
	Name = name;
	Description = description;
	Actor = actor;
	Target = "UNSET";
	hasTarget = false;
}
Action::Action(Category type, int initiative, std::string name, std::string description, std::string actor, std::string target) {
	Type = type;
	Initiative = initiative;
	Name = name;
	Description = description;
	Actor = actor;
	Target = target;
	hasTarget = true;
}
Action::~Action() {}
