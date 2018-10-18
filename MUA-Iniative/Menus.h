#pragma once

#include "Roster.h"
#include "Round.h"

/*****************
**	Menu codes	****
**********************
**	m - Main menu		q - quit
**	r - dislpay roster	a - display actions
**	e - edit roster		s - start combat
*/

namespace UI {
	/* Menues */
	char mainMenu();
	char startCombat(Roster* rr, std::vector<Round*>* rd);
	/* Editor */
	char editRoster(Roster* r);
	/* Display functions */
	char displayRoster(Roster* r);
	/* Parts */
	void printCharacter(const Character* c);
	void printAction(const Action& a);
	void printSeperator();
}