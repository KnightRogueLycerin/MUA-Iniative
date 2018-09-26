#pragma once

#include <string>
#include <vector>

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

struct Character {
	Character();
	Character(std::string name, int iniativeBonus, bool extraAction = false);
	Character(std::string name, int iniativeBonus, int itemBonus, bool extraAction = false);

	~Character();

	// Help functions
	int getIniative();
	void setIniative(int roll);
	void setIniative(int roll, int item);

	void addAction(Action & a);
	void addAction(
		Action::Category type, 
		std::string name, std::string description);
	void addAction(
		Action::Category type, 
		std::string name, std::string description,
		std::string target);
	std::vector<Action> & getActions();
	void swapActions(int IndexA, int IndexB);
	void clearActions();

	// Data block
	bool Active;
	bool ExtraAction;
	std::string Name;
	int IniativeRoll;
	int IniativeBonus;
	int IniativeItem;
	std::vector<Action> Actions;
};