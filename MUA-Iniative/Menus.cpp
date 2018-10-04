#include "stdafx.h"
#include "Menus.h"

#include "IO.h"

/* Local Help Functions */
void NotDoneYet() {
	IO::Console::Out("This Function is not done yet!", IO::Console::RED);
	IO::Console::WaitKey("");
	IO::Console::Clear();
}

void Title(std::string title) {
	UI::printSeperator();
	IO::Console::Out(" " + title, IO::Console::TC::TEAL);
	UI::printSeperator();
}

/* Navigation Functions */
bool inputLegality(const char c, char* set) {
	auto index = 0;
	while (set[index] != '\0') {
		if (c == set[index])
			return true;
		index++;
	}
	return false;
}
char getInput(char* set) {
	char input; bool first = true;
	do {
		if (!first)
			IO::Console::Out(">Input not recognized, try again...", IO::Console::DARK_RED);
		first = false;

		IO::Console::Out(" What do you want to do: ", IO::Console::GREY, false);
		while (!IO::Console::In(input));

	} while (!inputLegality(input, set));
	IO::Console::Out("" + input);
	return input;
}
bool YesNo(){
	// (Yes/No)
	IO::Console::Out("(", IO::Console::DARK_GREY, false);
	IO::Console::Out("Y", IO::Console::WHITE, false);
	IO::Console::Out("/", IO::Console::DARK_GREY, false);
	IO::Console::Out("N", IO::Console::WHITE, false);
	IO::Console::Out(")", IO::Console::DARK_GREY);
	// Get input
	char legalSet[] = { 'Y', 'y', 'N', 'n' };
	auto input = getInput(legalSet);
	if (input == 'Y' || input == 'y')
		return true;
	return false;
}

/* Main Menu */
char UI::mainMenu() {
	/* Title */
	Title("Main Menu");
	/* Options */
	IO::Console::Out(" Q", IO::Console::WHITE, false);
	IO::Console::Out("uit | ", IO::Console::DARK_GREY, false);
	IO::Console::Out("S", IO::Console::WHITE, false);
	IO::Console::Out("ave | Start ", IO::Console::DARK_GREY, false);
	IO::Console::Out("C", IO::Console::WHITE, false);
	IO::Console::Out("ombat", IO::Console::DARK_GREY, true);

	IO::Console::Out(" Display ", IO::Console::DARK_GREY, false);
	IO::Console::Out("r", IO::Console::WHITE, false);
	IO::Console::Out("oster | ", IO::Console::DARK_GREY, false);
	IO::Console::Out("E", IO::Console::WHITE, false);
	IO::Console::Out("dit roster", IO::Console::DARK_GREY, true);

	/* Input */
	char legalSet[] = { 'Q', 'q', 'C', 'c', 'S', 's', 'R', 'r', 'E', 'e' };
	return getInput(legalSet);
}

/* Start Combat */
char UI::startCombat(Round* r) {
	Title("Start Combat");
	NotDoneYet();
	return 'M';
}

/* Roster Edidtor */
bool changeName(std::string& name) {
	IO::Console::Out("New name: ", IO::Console::GREY, false);
	if (!IO::Console::In(name)) {
		IO::Console::Out("NAME COULD NOT BE UNDERSTOD...\n Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn!", IO::Console::RED);
		return false;
	}
	IO::Console::Out(" Are you sure you want to change the name", false);
	return YesNo();
}
bool changeIniative(int& init) {
	IO::Console::Out("New initiative bonus: ", IO::Console::GREY, false);
	if (!IO::Console::In(init)) {
		IO::Console::Out("What madness is this number!", IO::Console::RED);
		return false;
	}
	IO::Console::Out(" Are you sure you want to change the initiative bonus", false);
	return YesNo();
}
bool toggleExtraAction() {
	IO::Console::Out(" Would you like to toggle extra action ",IO::Console::GREY, false);
	return YesNo();
}
bool editCharacter(Character* c) {
	// Data
	char input;	int init;
	std::string name;
	bool done = false;
	do
	{
		// Header
		Title(" Editing " + c->Name);
		UI::printCharacter(c);
		UI::printSeperator();
		// What would you like to change (Quit)?
		IO::Console::Out("What would you like to change (", IO::Console::GREY, false);
		IO::Console::Out("Q", IO::Console::WHITE, false);
		IO::Console::Out("uit)?", IO::Console::GREY);
		// Name, Iniative, Extra Action
		IO::Console::Out(" N", IO::Console::WHITE, false);
		IO::Console::Out("ame, ", IO::Console::DARK_GREY, false);
		IO::Console::Out("I", IO::Console::WHITE, false);
		IO::Console::Out("niative or ", IO::Console::DARK_GREY, false);
		IO::Console::Out("E", IO::Console::WHITE, false);
		IO::Console::Out("xtra action", IO::Console::DARK_GREY);
		// Register input
		char legalSet[] = { 'Q', 'q', 'N', 'n', 'I', 'i', 'E', 'e' };
		input = getInput(legalSet);
		done = (input == 'q' || input == 'Q') ? true : false;
		UI::printSeperator();
		if (!done)
			switch (input) {
			case 'N':
			case 'n':
				// Name change
				if (changeName(name))
					c->Name = name;
				break;
			case 'I':
			case 'i':
				if (changeIniative(init))
					c->IniativeBonus = init;
				// Iniative change
				break;
			case 'E':
			case 'e':
				// Extra action toggle
				if (toggleExtraAction())
					c->ExtraAction = !c->ExtraAction;
				break;
			}
		IO::Console::Clear();
	} while (!done);
	return true;
}
char UI::editRoster(Roster * r) {
	// Data block
	auto names = r->getRoster();
	int linebreaker = 3, choice;
	bool done = false, selected = false;
	char input;
	do{
		// Display inital menu
		Title("Edit Roster");
		for (auto i = 0; i < names.size(); i++) {
			// "[i] name1	[i + 1] name2"
			IO::Console::Out("[", IO::Console::DARK_GREY, false);
			IO::Console::Out(std::to_string(i), IO::Console::WHITE, false);
			IO::Console::Out("] ", IO::Console::DARK_GREY, false);
			IO::Console::Out(names[i] + "\t", IO::Console::GREY, false);

			if ((i + 1) % linebreaker == 0 && (i + 1) != names.size())
				IO::Console::Out("");
		}
		// Which Action
		// " Select Character or Quit"
		IO::Console::Out("\n S", IO::Console::WHITE, false);
		IO::Console::Out("elect character or ", IO::Console::DARK_GREY, false);
		IO::Console::Out("Q", IO::Console::WHITE, false);
		IO::Console::Out("uit", IO::Console::DARK_GREY);
		char legalSet[] = { 'S', 's', 'Q', 'q' };
		auto input = getInput(legalSet);
		if (input == 'Q' || input == 'q')
			return 'M';
		// Selection
		selected = false;
		IO::Console::Out(" Select characater:\t", false);
		while (!selected) {
			selected = IO::Console::In(choice);
			if (!selected || choice >= names.size()) {
				IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
				selected = false;
				IO::Console::Out("Select characater:\t", false);
			}
		}
		// Character edit
		UI::printSeperator();
		UI::printCharacter(r->getCharacter(names[choice]));
		UI::printSeperator();
		IO::Console::Out("Is this the right character ", IO::Console::GREY, false);
		if (YesNo()) {
			IO::Console::Clear();
			editCharacter(r->getCharacter(names[choice]));
		}
		IO::Console::Clear();
	} while (!done);
	return 'M';
}

/* Help Functions */
char UI::displayRoster(Roster* r) {
	/* Title */
	Title("Display Roster");
	/* Function */
	int index = 0;
	for (auto e : r->getRoster()) {
		printCharacter(r->getCharacter(e));
		UI::printSeperator();
	}
	IO::Console::WaitKey("");
	return 'M';
}

char UI::displayActions(Round* rd) {
	Title("Display Actions");
	NotDoneYet();
	return 'Q';
}

void UI::printCharacter(const Character * c) {
	std::string out;
	out += " Name.......: " + c->Name + "\n";
	out += "  Initiative: " + std::to_string(c->IniativeBonus) + " | ";
	if (c->ExtraAction)
		out += "Extra action: yes";
	else
		out += "Extra action: no";
	IO::Console::Out(out);
}
void UI::printAction(const Action * a) {
	IO::Console::Out(" " + a->Name, false);
	switch (a->Type) {
	case (Action::Category::Undefined):
		IO::Console::Out("  (An undefined action)", 0x08);
		break;
	case (Action::Category::Offensive):
		IO::Console::Out("  (An offensive action)", 0x08);
		break;
	case (Action::Category::Defensive):
		IO::Console::Out("  (An defensive action)", 0x08);
		break;
	case (Action::Category::Extended):
		IO::Console::Out("  (An extended action)", 0x08);
		break;
	case (Action::Category::Indipendent):
		IO::Console::Out("  (An indipendent action)", 0x08);
		break;
	case (Action::Category::Movement):
		IO::Console::Out("  (An movement action)", 0x08);
		break;
	}
	/* Player*/
	IO::Console::Out(" By ", false);
	IO::Console::Out(a->Actor, 0x0c, false);
	/* Iniative */
	IO::Console::Out(" with an initative of " + std::to_string(a->Initiative), false);
	/* Target */
	if (a->hasTarget) {
		IO::Console::Out(" against ", false);
		IO::Console::Out(a->Target, 0x0c, false);;
	}
	/* Description, flavor text */
	IO::Console::Out("\n  " + a->Description, 0x08);
	return;
}

void UI::printSeperator() {
	IO::Console::Out("///////////////////////////////////////////", 0x60);
}