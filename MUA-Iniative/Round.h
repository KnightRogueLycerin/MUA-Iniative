#pragma once

#include <vector>

#include "Data.h"

class Round {
	// Data block
	std::vector<Action*> round;
public:
	Round();
	~Round();

	// Manipulation
	bool addAction(Action * a);
	void sort();
	void reset();
	// Get
	std::vector<Action*>& Get();
	// Information
	int amount();
};

