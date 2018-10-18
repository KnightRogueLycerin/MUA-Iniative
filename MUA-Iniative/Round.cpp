#include "stdafx.h"
#include "Round.h"

#include <algorithm>

#include "IO.h"

Round::Round() {

}
Round::~Round() {
	reset();
}

bool Round::addAction(Action& a) {
	if (a.Actor.empty())
		return false;
	round.push_back(a);
	return true;
}

void Round::sort() {
	if (amount() == 0)
		return;
	// Sort action highest to lowest iniative
	std::sort(	// O(N Log(N))
		round.begin(), round.end(),
		[](const Action a, const Action b)
		-> bool { return a.Initiative > b.Initiative; }
	);
}

void Round::reset() {
	if (amount() == 0)
		return;
	round.clear();
}

std::vector<Action>& Round::Get() {
	return round;
}

int Round::amount() {
	return round.size();
}
