#include "stdafx.h"
#include "Manager.h"

#include "Menus.h"
#include "IO.h"

Manager::Manager() : filePath("deafult.txt") {
	rounds = new std::vector<Round*>();
	roster = new Roster();

	abort = useFile = false;

	rounds->push_back(new Round());
}
Manager::Manager(const std::string & path) : filePath(path) {
	useFile = IO::File::Read(filePath, file);
	abort = !useFile;
	if (abort) {	// Error handeling
		IO::Console::Out("> File could not be loaded!!", IO::Console::RED);
		IO::Console::WaitKey();
		return;
	}

	rounds = new std::vector<Round*>();
	roster = new Roster(file);

	rounds->push_back(new Round());
}
Manager::~Manager() {
	for (auto ptr : (*rounds))
		delete ptr;
	rounds->clear();
	delete roster, rounds;
	file.clear();
}

void Manager::run() {
	if (abort)	// Something went wrong in setup
		return;
	char input = 'M';
	do {
		IO::Console::Clear();
		switch (input) {
		default:
			IO::Console::Out("Could not resolve input: " + input, IO::Console::RED);
			IO::Console::WaitKey();
			input = 'q';	// Naïve
			break;
		case 'm':
		case 'M':
			input = UI::mainMenu();
			break;
		case 'r':
		case 'R':
			input = UI::displayRoster(roster);
			break;
		case 'a':
		case 'A':
			input = UI::displayActions(rounds->back());
			break;
		case 'c':
		case 'C':
			input = UI::startCombat(rounds->back());
			break;
		case 'e':
		case 'E':
			input = UI::editRoster(roster);
			break;
		case 's':
		case 'S':
			input = 'M';
			save();
			break;
		}
	} while (input != 'q' && input != 'Q');
	return;
}

void Manager::save() {
	std::vector<std::string> saveFile;
	// Update Roster
	bool omitting = false;
	/*****************************************************
	**					File format						**
	******************************************************
	**	name(string),positive integer(>=0),bool(0/1)	**
	*****************************************************/
	for (std::string s : file) {
		if (s == "#EndOfRoster")
			omitting = false;

		if (!omitting)
			saveFile.push_back(s);

		if (s == "#StartOfRoster") {
			omitting = true;
			for (std::string name : roster->getRoster()) {
				std::string ch = name+","+std::to_string(roster->getCharacter(name)->IniativeBonus)+",";
				ch += (roster->getCharacter(name)->ExtraAction) ? "1" : "0";

				saveFile.push_back(ch);
			}
		}
	}
	// Indexing
	if (saveFile.back().find("Times saved: ") != std::string::npos) {
		std::string s = saveFile.back();
		s.erase(0, 12);
		int version = std::stoi(s) + 1;
		saveFile.back() = "Times saved: " + std::to_string(version);
	}
	else
		file.push_back("Times saved: 1");
	// Save
	IO::File::Write(filePath, saveFile, false);
	file = saveFile;
	// Output
	IO::Console::Out(" Data have been ", false);
	IO::Console::Out("SAVED", IO::Console::GREEN, false);
	IO::Console::Out("!");
	IO::Console::WaitKey("");
}
