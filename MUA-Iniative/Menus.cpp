#include "stdafx.h"
#include "Menus.h"

#include "IO.h"

void NotDoneYet() {
	IO::Console::Print("This Function is not done yet!", IO::Console::RED);
	IO::Console::WaitKey("");
	IO::Console::Clear();
}

void Title(std::string title) {
	UI::printSeperator();
	IO::Console::Print(" " + title, IO::Console::TC::TEAL);
	UI::printSeperator();
}

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
			IO::Console::Print(">Input not recognized, try again...", IO::Console::DARK_RED);
		first = false;

		IO::Console::Print(" What do you want to do: ", IO::Console::GREY, false);
		while (!IO::Console::Get(input));

	} while (!inputLegality(input, set));
	IO::Console::Print("" + input);
	return input;
}

char UI::mainMenu() {
	/* Title */
	Title("Main Menu");
	/* Options */
	IO::Console::Print(" Q", IO::Console::WHITE, false);
	IO::Console::Print("uit | ", IO::Console::DARK_GREY, false);
	IO::Console::Print(" S", IO::Console::WHITE, false);
	IO::Console::Print("ave | Start ", IO::Console::DARK_GREY, false);
	IO::Console::Print("C", IO::Console::WHITE, false);
	IO::Console::Print("ombat", IO::Console::DARK_GREY, true);

	IO::Console::Print(" Display ", IO::Console::DARK_GREY, false);
	IO::Console::Print("r", IO::Console::WHITE, false);
	IO::Console::Print("oster | ", IO::Console::DARK_GREY, false);
	IO::Console::Print("E", IO::Console::WHITE, false);
	IO::Console::Print("dit roster", IO::Console::DARK_GREY, true);

	/* Input */
	char legalSet[] = { 'Q', 'q', 'C', 'c', 'S', 's', 'R', 'r', 'E', 'e' };
	return getInput(legalSet);
}

char UI::startCombat(Round* r) {
	Title("Start Combat");
	NotDoneYet();
	return 'M';
}

char UI::editRoster(Roster * r) {
	Title("Edit Roster");
	NotDoneYet();
	return 'M';
}

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
	IO::Console::Print(out);
}
void UI::printAction(const Action * a) {
	IO::Console::Print(" " + a->Name, false);
	switch (a->Type) {
	case (Action::Category::Undefined):
		IO::Console::Print("  (An undefined action)", 0x08);
		break;
	case (Action::Category::Offensive):
		IO::Console::Print("  (An offensive action)", 0x08);
		break;
	case (Action::Category::Defensive):
		IO::Console::Print("  (An defensive action)", 0x08);
		break;
	case (Action::Category::Extended):
		IO::Console::Print("  (An extended action)", 0x08);
		break;
	case (Action::Category::Indipendent):
		IO::Console::Print("  (An indipendent action)", 0x08);
		break;
	case (Action::Category::Movement):
		IO::Console::Print("  (An movement action)", 0x08);
		break;
	}
	/* Player*/
	IO::Console::Print(" By ", false);
	IO::Console::Print(a->Actor, 0x0c, false);
	/* Iniative */
	IO::Console::Print(" with an initative of " + std::to_string(a->Initiative), false);
	/* Target */
	if (a->hasTarget) {
		IO::Console::Print(" against ", false);
		IO::Console::Print(a->Target, 0x0c, false);;
	}
	/* Description, flavor text */
	IO::Console::Print("\n  " + a->Description, 0x08);
	return;
}

void UI::printSeperator() {
	IO::Console::Print("///////////////////////////////////////////", 0x60);
}