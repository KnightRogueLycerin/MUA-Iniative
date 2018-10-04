#include "stdafx.h"
#include "Roster.h"

#include <algorithm>

#include "IO.h"

Roster::Roster() {
	characters = std::map<std::string, Character*>();
	roster = std::vector<std::string>();

	/* Example roster */
	add(new Character("A", 5));
	add(new Character("B", 8));
	add(new Character("C", 10, true));
}
Roster::Roster(const std::vector<std::string>& file) {
	characters = std::map<std::string, Character*>();
	roster = std::vector<std::string>();

	readFile(file);
}
Roster::~Roster() {
	clear();
}

Character* Roster::getCharacter(std::string name) {
	if (inCharacters(name) && !characters.empty())
		return characters[name];
	return nullptr;
}

const std::vector<std::string>& Roster::getRoster() {
	return roster;
}

bool Roster::add(Character * character) {
	if (!verifyExistance(character->Name)) {
		characters.emplace(character->Name, character);
		roster.push_back(character->Name);
	}
	else
		return false;
	return verifyExistance(character->Name);
}
bool Roster::add(std::string name, unsigned int iniativeBonus) {
	return add(new Character(name, iniativeBonus));
}
bool Roster::add(std::string name, unsigned int iniativeBonus, bool extraAction) {
	return add(new Character(name, iniativeBonus, extraAction));
}

bool Roster::remove(const std::string& name) {
	if (verifyExistance(name)) {
		delete characters[name];	// TODO, ensure this works
		characters.erase(name);
		roster.erase(
			std::remove(
				roster.begin(),
				roster.end(),
				name),
			roster.end());
	}
	else
		return false;
	return !verifyExistance(name);
}

bool Roster::remove(Character * character) {
	return remove(character->Name);
}

void Roster::clear() {
	for (std::string s : roster)
		delete characters[s];
	characters.clear();
	roster.clear();
}

int Roster::size() {
	return roster.size();
}

bool Roster::inRoster(const std::string& name) {
	for (std::string s : roster) {
		if (s == name)
			return true;
	}
	return false;
}

bool Roster::inCharacters(const std::string& name) {
	return characters.count(name);;
}

bool Roster::verifyExistance(const std::string& name) {
	return inCharacters(name) && inRoster(name);
}

bool Roster::readFile(const std::vector<std::string>& file) {
	/*********************************************
	**	File format in the .txt					**
	**********************************************
	**	string,positive integer(>=0),bool(0/1)	**
	**********************************************
	** #StartOfRoster							**
	** exampel_a,14,1							**
	** exampel_b,14,0							**
	** #EndOfRoster								**
	*********************************************/
	// Search for start & end
	bool readingRoster = false;
	for (auto fLine : file) {
		if (readingRoster) {
			if (fLine == "#EndOfRoster")
				return true;
			else {
				std::string line = fLine;
				std::string name = "ERR"; int iniative = 0; bool extra = false;
				// parsing
				size_t pos = 0;
				for (int i = 0; i < 3; i++) {
					switch (i) {
					case 0:	// Name
						pos = line.find(',');
						name = line.substr(0, pos);
						line.erase(0, pos + 1);
						break;
					case 1:	// Iniative
						pos = line.find(',');
						iniative = std::stoi(line.substr(0, pos));
						line.erase(0, pos + 1);
						break;
					case 2:	// Extra action
						if (line != "1" && line != "0") {
							clear();
							IO::Console::Out("Incorect roster formating!", IO::Console::TextColor::RED);
							return false;
						}
						else
							extra = line == "1";
						break;
					default:https://github.com/KnightRogueLycerin/SecretSanta/tree/master/SecretSantaMutant
						clear();
						IO::Console::Out("Should not be able to end up here!", IO::Console::TextColor::RED);
						return false;
						break;
					}

				}
				// Add character
				add(name, iniative, extra);
			}
		}
		if (fLine == "#StartOfRoster")
			readingRoster = true;
	}
	clear();
	IO::Console::Out("End of roster not declared!", IO::Console::TextColor::RED);
	return false;
}