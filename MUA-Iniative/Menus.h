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
	char startCombat(Round* r);
	/* Editor */
	char editRoster(Roster* r);
	/* Display functions */
	char displayRoster(Roster* r);
	char displayActions(Round* r);
	/* Parts */
	void printCharacter(const Character* c);
	void printAction(const Action* a);
	void printSeperator();
}