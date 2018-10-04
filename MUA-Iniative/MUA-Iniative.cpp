// MUA-Iniative.cpp : Defines the entry point for the console application.
#include "stdafx.h"

#include "IO.h"
#include "Menus.h"
#include "Manager.h"

/*********************
**	The TODO List	****
**************************
** Manager
**	character editior, start 'game', round editor, round display
** Menu
**	character editior, start 'game', round editor, round display
** IO
**	Console might need more Get-types
** Errors
**	Handle when file fail to load
**	String in response to menues leads to 'chain of input'
**	Save roster edits to file
**
** Goal
**	Finnish the character edditor
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