// MUA-Iniative.cpp : Defines the entry point for the console application.
#include "stdafx.h"

#include "IO.h"
#include "Menus.h"
#include "Manager.h"

/*********************
**	The TODO List	****
**************************
** Goal
**	Finnish the character edditor
**
** Bugs & Errors
**	Handle when file fail to load
**	Can't save/load names with white space
**  Name changes aren't updated in the roster/charactes
**  Crasch when character is removed!
*/

void fetchFile(std::string& input) {
	input.clear();
	UI::printSeperator();
	IO::Console::Out(" Load character data", IO::Console::TC::TEAL);
	UI::printSeperator();
	IO::Console::Out(" From which file do you wish to load form?");
	IO::Console::Out("\tencounter_test.txt\n\t", IO::Console::DARK_GREY, false);
	IO::Console::In(input);
}

int main() {

	std::string input = "encounter_test.txt";
	if(false)
		fetchFile(input);

	Manager* manager = new Manager(input);

	manager->run();

	delete manager;

	return 0;
}