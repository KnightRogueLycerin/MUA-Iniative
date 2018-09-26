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
		IO::Console::Print("> File could not be loaded!!", IO::Console::RED);
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
			IO::Console::Print("Could not resolve input: " + input, IO::Console::RED);
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

void Manager::save(bool append) {
	// Indexing
	if (file.back().find("Times saved: ") != std::string::npos) {
		std::string s = file.back();
		s.erase(0, 12);
		int version = std::stoi(s) + 1;
		file.back() = "Times saved: " + std::to_string(version);
	}
	else
		file.push_back("Times saved: 1");
	// Save
	IO::File::Write(filePath, file, false);
	// Output
	IO::Console::Print(" Data have been ");
	IO::Console::Print(" Saved", IO::Console::GREEN, false);
	IO::Console::Print("!");
	IO::Console::WaitKey("");
}
