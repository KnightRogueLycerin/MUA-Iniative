#pragma once

#include <vector>
#include <string>

#include "Roster.h"
#include "Round.h"

class Manager {
	Roster* roster;
	std::vector<Round*>* rounds;

	bool useFile, abort;
	const std::string filePath;
	std::vector<std::string> file;
public:
	Manager();
	Manager(const std::string& path);
	~Manager();

	void run();
private:
	void save(bool append = false);
};