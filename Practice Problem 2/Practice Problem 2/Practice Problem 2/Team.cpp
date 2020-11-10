#include <iostream>
#include <string>
#include <cmath>
#include "team.h"

Team::Team() {
	team = "";
	win = 0;
	loss = 0;
}

Team::Team(std::string aTeamName) {
	team = aTeamName;
	win = 0;
	loss = 0;
}

Team::Team(std::string aTeamName, int aWin, int aLoss) {
	team = aTeamName;
	win = aWin;
	loss = aLoss;
}

std::string Team::getTeam() const {
	return team;
}

int Team::getWin() const {
	return win;
}

int Team::getLoss() const {
	return loss;
}

double Team::getRecord() const {
	double record = ((double)win / ((double)win + (double)loss));
	return record;
}

//Modifiers
void Team::setTeam(std::string t) const {
	team == t;
}

void Team::setWin(int w) {
	win = w;
}

void Team::setLoss(int l) {
	loss = l;
}

bool winRateSort(const Team& t1, const Team& t2) {
	if (t1.getRecord() > t2.getRecord()) {
		return true;
	}
	else if (t1.getRecord() == t2.getRecord()) {
		if (t1.getWin() + t1.getLoss() > t2.getWin() + t2.getLoss()) {
			return true;
		}
		else if (t1.getWin() + t1.getLoss() == t2.getWin() + t2.getLoss()) {
			if (t1.getTeam() != t2.getTeam()) {
				int v = t1.getTeam().compare(t2.getTeam());
				if (v < 0) {
					return true;
				}
			}
		}
	}
	return false;
}