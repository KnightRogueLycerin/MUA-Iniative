#pragma once

#include <map>
#include <vector>

#include "Data.h"

class Roster {
public:
	Roster();
	Roster(const std::vector<std::string>& file);
	~Roster();
	// Fetch
	Character* getCharacter(std::string name);	// Rethink? return ptr?
	const std::vector<std::string>& getRoster();
	// Manipulation
	bool add(Character * character);
	bool add(std::string name, unsigned int iniativeBonus);
	bool add(std::string name, unsigned int iniativeBonus, bool extraAction);

	bool remove(const std::string& name);
	bool remove(Character * character);

	void clear();

	// Others
	int size();
private:
	// Data block
	std::map<std::string, Character*> characters;
	std::vector<std::string> roster;
	// Help functions
	bool inRoster(const std::string& name);
	bool inCharacters(const std::string& name);
	bool verifyExistance(const std::string& name);
	bool readFile(const std::vector<std::string>& file);
};

