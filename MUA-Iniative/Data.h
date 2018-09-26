#pragma once

#include <string>

struct Character {
	Character();
	Character(std::string name, int iniativeBonus, bool extraAction = false);

	~Character();

	// Help functions
	int getIniative();

	// Data block
	bool Active;
	bool ExtraAction;
	std::string Name;
	int IniativeRoll;
	int IniativeBonus;
};

struct Action {
	typedef enum Type {
		Undefined, Offensive,
		Defensive, Extended,
		Indipendent, Movement
	}Category;

	Action();
	Action(
		Category type,
		int initiative,
		std::string name, std::string description,
		std::string actor);
	Action(
		Category type,
		int initiative,
		std::string name, std::string description,
		std::string actor, std::string target);

	~Action();

	// Data block
	Category Type;
	int Initiative;
	std::string Name;
	std::string Description;
	std::string Actor;
	std::string Target;
	bool hasTarget;
};