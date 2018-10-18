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
	char legalSet[] = "YyNn";
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
bool fillAction(Action& a) {
	// Set Type
	// "Select action type"
	{	// Offensive, Extended, Indipendent, Movement
		IO::Console::Out(" O", IO::Console::WHITE, false);
		IO::Console::Out("ffensive, ", IO::Console::DARK_GREY, false);
		IO::Console::Out("E", IO::Console::WHITE, false);
		IO::Console::Out("xtended, ", IO::Console::DARK_GREY, false);
		IO::Console::Out("I", IO::Console::WHITE, false);
		IO::Console::Out("ndipendent, or ", IO::Console::DARK_GREY, false);
		IO::Console::Out("M", IO::Console::WHITE, false);
		IO::Console::Out("ovement", IO::Console::DARK_GREY); }
	char legalSet[] = "OoEeIiMm";
	auto input = getInput(legalSet);
	switch (input) {
	case 'O':
	case 'o':
		a.Type = Action::Offensive;
		break;
	case 'E':
	case 'e':
		IO::Console::Out(" Extended action will purge all other action for this character ", IO::Console::DARK_RED, false);
		if(YesNo())
			a.Type = Action::Extended;
		else false;
		break;
	case 'I':
	case 'i':
		a.Type = Action::Indipendent;
		break;
	case 'M':
	case 'm':
		a.Type = Action::Movement;
		break;
	default:
		a.Type = Action::Undefined;
	}
	// Set Name
	UI::printSeperator();
	std::string name = "UNSET";
	IO::Console::Out(" What's the name of the action: ", false);
	IO::Console::In(name);
	a.Name = name;
	// Set Target
	UI::printSeperator();
	IO::Console::Out(" Does the action have a target ", false);
	if (YesNo()) {
		std::string target = "UNSET";
		IO::Console::Out(" What's the target of the action: ", false);
		IO::Console::In(target);
		a.Target = target;
		a.hasTarget = true;
	}
	return true;
}
void initativeLogic(Character* c) {
	// Check for extended actions
	for (auto e : c->Actions) {
		if (e.Type == Action::Extended) {
			Action a = e;
			c->Actions.clear();
			c->Actions.push_back(a);
			return;
		}
	}
	// Fill iniative by ordering (Could also apply stacking penalties here)
	for (auto i = 0; i < c->Actions.size(); i++) {
		if (i == 0) {	// First action
			c->Actions[i].Initiative = c->getIniative();
			continue;
		}
		// exeption
		if (c->Actions[i].Type == Action::Indipendent || c->Actions[i].Type == Action::Movement)
			c->Actions[i].Initiative = c->Actions[i - 1].Initiative;
		else {
			c->Actions[i].Initiative = c->Actions[i - 1].Initiative - 5;
		}
	}
	// Purge action bellow 0 iniative
	while (c->Actions.back().Initiative < 0) {
		c->Actions.pop_back();
		IO::Console::Out(" Removed a action with iniative lower than 0...", IO::Console::DARK_RED);
	}
	// Check action limit
	int limit = c->ExtraAction ? 5 : 4;
	int amount = 0;
	for (auto e : c->Actions) {
		if (e.Type != Action::Indipendent || e.Type != Action::Movement)
			amount++;
	}
	amount -= limit;
	if(amount > 0)
		for (int i = 0; i < amount; i++) {
			c->Actions.pop_back();
			IO::Console::Out(" To many action, removed last action", IO::Console::DARK_RED);
		}

}
bool characterActions(Character* c) {
	do
	{
		IO::Console::Clear();
		Title(c->Name +  "'s action editor");
		// Character info
		UI::printCharacter(c);
		IO::Console::Out("  Iniative base: " + std::to_string(c->IniativeBonus));
		IO::Console::Out("  Iniative roll: " + std::to_string(c->IniativeRoll));
		IO::Console::Out("  Iniative item: " + std::to_string(c->IniativeItem));
		UI::printSeperator();
		// Action list
		int index = 0;
		if (!c->Actions.empty()) {
			initativeLogic(c);
			for (auto a : c->Actions) {
				IO::Console::Out(" [", IO::Console::DARK_GREY, false);
				IO::Console::Out(std::to_string(index), IO::Console::WHITE, false);
				IO::Console::Out("] ", IO::Console::DARK_GREY, false);
				UI::printAction(a);
				index++;
			}
			UI::printSeperator();
		}
			
		// Quit, Initiative, Add, Delete, Swap 
		{	IO::Console::Out(" Q", IO::Console::WHITE, false);
		IO::Console::Out("uit, ", IO::Console::DARK_GREY, false);
		IO::Console::Out("I", IO::Console::WHITE, false);
		IO::Console::Out("nitiative, ", IO::Console::DARK_GREY, false);
		IO::Console::Out("A", IO::Console::WHITE, false);
		IO::Console::Out("dd, ", IO::Console::DARK_GREY, false);
		IO::Console::Out("D", IO::Console::WHITE, false);
		IO::Console::Out("elete, or ", IO::Console::DARK_GREY, false);
		IO::Console::Out("S", IO::Console::WHITE, false);
		IO::Console::Out("wap", IO::Console::DARK_GREY); }

		char legalSet[] = "QqIiAaDdSs";
		auto input = getInput(legalSet);
		if (input == 'Q' || input == 'q')
			return true;

		UI::printSeperator();
		bool selected = false;
		int choice, second, init = -1;
		Action a;
		switch (input) {
		case 'I':	// Set roll iniative
		case 'i':
			// Roll
			IO::Console::Out(" What did they roll [1-10]:\t", IO::Console::GREY, false);
			while (!selected) {
				selected = IO::Console::In(init);
				if (!selected || (init < 1 || init > 10)) {
					IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
					selected = false;
					IO::Console::Out(" What did they roll [1-10]:\t", false);
				}
			}
			c->IniativeRoll = init;
			// Item
			selected = false;
			IO::Console::Out(" What's their item bonus:\t", IO::Console::GREY, false);
			while (!selected) {
				selected = IO::Console::In(init);
				if (!selected || init <= 0) {
					IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
					selected = false;
					IO::Console::Out(" What's their item bonus:\t", false);
				}
			}
			c->IniativeItem = init;
			break;
		case 'A':	// Add new action
		case 'a':
			a.Actor = c->Name;
			if (fillAction(a))
				c->Actions.push_back(a);
			break;
		case 'D':	// Delete action
		case 'd':
			// Action selection
			IO::Console::Out(" Select Action [index]:\t", false);
			while (!selected) {
				selected = IO::Console::In(choice);
				if (!selected || (choice <= 0 && choice > c->Actions.size())) {
					IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
					selected = false;
					IO::Console::Out(" Select Action [index]:\t", false);
				}
			}
			// Action removal
			c->Actions.erase(c->Actions.begin() + choice);
			break;
		case 'S':	// Swap two actions
		case 's':
			// First index
			IO::Console::Out(" Select first action [index]:\t", false);
			while (!selected) {
				selected = IO::Console::In(choice);
				if (!selected || (choice <= 0 && choice > c->Actions.size())) {
					IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
					selected = false;
					IO::Console::Out(" Select first action [index]:\t", false);
				}
			}
			// Second index
			selected = false;
			IO::Console::Out(" Select second action [index]:\t", false);
			while (!selected) {
				selected = IO::Console::In(second);
				if (!selected || (second <= 0 && second > c->Actions.size())) {
					IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
					selected = false;
					IO::Console::Out(" Select second action [index]:\t", false);
				}
			}
			// Swap
			c->swapActions(choice, second);
			break;
		}
	} while (true);
	return false;
}
void displayRound(Round * r) {
	int iniative = INT16_MAX; int index = 0;
	IO::Console::Clear();
	for (auto a : r->Get()) {
		if (a.Initiative < iniative) {
			iniative = a.Initiative;
			IO::Console::Out("///////////////" + std::to_string(iniative) + "///////////////", 0x60);
		}
		IO::Console::Out("[", IO::Console::DARK_GREY, false);
		IO::Console::Out(std::to_string(index++), IO::Console::WHITE, false);
		IO::Console::Out("] ", IO::Console::DARK_GREY, false);
		UI::printAction(a);
	}
	UI::printSeperator();
	IO::Console::WaitKey("");
}
char UI::startCombat(Roster* rr, std::vector<Round*>* rd) {
	auto names = rr->getRoster();
	int linebreaker = 3, choice;
	bool done = false, selected = false;
	Round* round;
	// Main loop
	do{
		IO::Console::Clear();
		Title("Start Combat");
		// Display roster
		for (auto i = 0; i < names.size(); i++) {
			// "[i] name1	[i + 1] name2"
			if (rr->getCharacter(names[i])->IniativeRoll == 0) {	// No yet set
				IO::Console::Out("[", IO::Console::DARK_GREY, false);
				IO::Console::Out(std::to_string(i), IO::Console::WHITE, false);
				IO::Console::Out("] ", IO::Console::DARK_GREY, false);
				IO::Console::Out(names[i] + "\t", IO::Console::GREY, false);
			}
			else{	// Asigned acctions
				IO::Console::Out("[", IO::Console::DARK_GREY, false);
				IO::Console::Out(std::to_string(i), IO::Console::WHITE, false);
				IO::Console::Out("] ", IO::Console::DARK_GREY, false);
				IO::Console::Out(names[i] + "\t", IO::Console::DARK_GREEN, false);
			}
			if ((i + 1) % linebreaker == 0 && (i + 1) != names.size())
				IO::Console::Out("");
		}
		// Select action
		IO::Console::Out("");
		UI::printSeperator();
		// " Quit, Select, Select, Compile round"	
		{	IO::Console::Out(" Q", IO::Console::WHITE, false);
			IO::Console::Out("uit, ", IO::Console::DARK_GREY, false);
			IO::Console::Out("S", IO::Console::WHITE, false);
			IO::Console::Out("elect, ", IO::Console::DARK_GREY, false);
			IO::Console::Out("C", IO::Console::WHITE, false);
			IO::Console::Out("ompile round", IO::Console::DARK_GREY);}	
		
		char legalSet[] = "QqSsCc";
		auto input = getInput(legalSet);
		if (input == 'Q' || input == 'q')
			return 'M';

		UI::printSeperator();

		// Select character
		if (input == 'S' || input == 's') {
			selected = false;
			IO::Console::Out(" Select characater [index]:\t", false);
			while (!selected) {
				selected = IO::Console::In(choice);
				if (!selected || choice >= names.size()) {
					IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
					selected = false;
					IO::Console::Out(" Select characater [index]:\t", false);
				}
			}
			// Go to character action editor
			characterActions(rr->getCharacter(names[choice]));
		}
		else{	// Compile round
			round = new Round();
			// Fill round
			for (auto n : names) {
				for (auto a : rr->getCharacter(n)->Actions)
					round->addAction(a);
				// Clear characters
				rr->getCharacter(n)->clearActions();
				rr->getCharacter(n)->setIniative(0, 0);
			}
			// Sort
			round->sort();
			// Display
			displayRound(round);
			// Achive
			rd->push_back(round);
			round = NULL;
		}
	} while (true);
	return 'M';
}

/* Roster Edidtor */
bool deleteCharacter(Character* c) {
	Title("Delete " + c->Name);
	// Display chararacter
	UI::printCharacter(c);
	UI::printSeperator();
	// Confirmation
	IO::Console::Out(" Are you sure you want to permanently remove ", false);
	IO::Console::Out(c->Name, IO::Console::RED + " ");
	return YesNo();
}
bool newCharacter(Character* c) {
	Title("New Character");
	// Data block
	std::string name; int init; // bool extra;
	// Name
	IO::Console::Out(" Name: ", false);
	while (!IO::Console::In(name)) {
		IO::Console::Out(" Invalid name!", IO::Console::RED);
		IO::Console::Out(" Name: ", false);
	}
	c->Name = name;
	// Iniative Bonus
	UI::printSeperator();
	bool legal = true;
	IO::Console::Out(" Iniative bonus: ", false);
	do {
		IO::Console::In(init);
		if (init < 1) {
			legal = false;
			IO::Console::Out(" Invalid number!", IO::Console::RED);
			IO::Console::Out(" Iniative bonus: ", false);
		}
	} while (!legal);
	c->IniativeBonus = init;
	// Extra Action
	UI::printSeperator();
	IO::Console::Out(" Extra action ", false);
	c->ExtraAction = YesNo();
	// Display character
	Title(" Character block");
	UI::printCharacter(c);
	UI::printSeperator();
	IO::Console::Out(" Do you wish to add this character to the roster ", IO::Console::GREY, false);
	// Confirmation
	return YesNo();
}
bool changeName(std::string& name) {
	IO::Console::Out("New name: ", IO::Console::GREY, false);
	if (!IO::Console::In(name)) {
		IO::Console::Out("NAME COULD NOT BE UNDERSTOD...\n Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn!", IO::Console::RED);
		return false;
	}
	IO::Console::Out(" It's recomended to change names in the _roster.txt file", IO::Console::DARK_RED);
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
		char legalSet[] = "QqNnIiEe";
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
	Character* c;
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
		IO::Console::Out("");
		UI::printSeperator();
		// " Quit, Select, Delete, or New character "
		{	IO::Console::Out(" Q", IO::Console::WHITE, false);
			IO::Console::Out("uit, ", IO::Console::DARK_GREY, false);
			IO::Console::Out("E", IO::Console::WHITE, false);
			IO::Console::Out("dit, ", IO::Console::DARK_GREY, false);
			IO::Console::Out("D", IO::Console::WHITE, false);
			IO::Console::Out("elete, or ", IO::Console::DARK_GREY, false);
			IO::Console::Out("N", IO::Console::WHITE, false);
			IO::Console::Out("ew character", IO::Console::DARK_GREY); }
		
		char legalSet[] = "EeQqDdNn";
		auto input = getInput(legalSet);
		if (input == 'Q' || input == 'q')
			return 'M';
		// New character
		if (input == 'N' || input == 'n') {
			IO::Console::Clear();
			c = new Character();
			if (newCharacter(c)) {
				r->add(c);
				names = r->getRoster();
			}
			else
				delete c;
			IO::Console::Clear();
			continue;
		}
		// Selection
		selected = false;
		IO::Console::Out(" Select characater [index]:\t", false);
		while (!selected) {
			selected = IO::Console::In(choice);
			if (!selected || choice > names.size()) {
				IO::Console::Out("\tInvalid choice!", IO::Console::DARK_RED);
				selected = false;
				IO::Console::Out(" Select characater [index]:\t", false);
			}
		}
		// Character edit
		switch (input) {
		case 'E':
		case 'e':	// Edit character
			IO::Console::Clear();
			editCharacter(r->getCharacter(names[choice]));
			break;
		case 'D':
		case 'd':	// Delete character
			IO::Console::Clear();
			if (deleteCharacter(r->getCharacter(names[choice]))) {
				r->remove(r->getCharacter(names[choice]));
				names = r->getRoster();
			}
			break;
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

void UI::printCharacter(const Character * c) {
	std::string out; int init = c->IniativeBonus + c->IniativeRoll + c->IniativeItem;
	out += " Name.......: " + c->Name + "\n";
	out += "  Initiative: " + std::to_string(init) + " | ";
	if (c->ExtraAction)
		out += "Extra action: yes";
	else
		out += "Extra action: no";
	IO::Console::Out(out);
}
void UI::printAction(const Action& a) {
	IO::Console::Out(" " + a.Name, false);
	switch (a.Type) {
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
	IO::Console::Out(a.Actor, 0x0c, false);
	/* Iniative */
	IO::Console::Out(" with an initative of " + std::to_string(a.Initiative), false);
	/* Target */
	if (a.hasTarget) {
		IO::Console::Out(" against ", false);
		IO::Console::Out(a.Target, 0x0c, false);;
	}
	IO::Console::Out("");
	return;
}

void UI::printSeperator() {
	IO::Console::Out("///////////////////////////////////////////", 0x60);
}