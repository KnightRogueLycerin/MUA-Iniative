// MUA-Iniative.cpp : Defines the entry point for the console application.
#include "stdafx.h"

#include "IO.h"
#include "Manager.h"

/*********************
**	The TODO List	****
**************************
** Manager	<-	Working
**	character editior, start 'game', round editor, round display
** Menu 	<-	Working
**	character editior, start 'game', round editor, round display
** IO
**	Console might need more Get-types
** Errors
**	Handle when file fail to load
*/

int main() {
	Manager* manager = new Manager("encounter_test.txt");

	manager->run();

	delete manager;

	return 0;
}