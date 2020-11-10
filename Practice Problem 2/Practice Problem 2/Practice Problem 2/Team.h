#pragma once
#include <string>

class Team {

public:

	Team();
	Team(std::string aTeamName);
	Team(std::string aTeamName, int aWin, int aLoss);

	//Accessors:
	std::string getTeam() const;
	int getWin() const;
	int getLoss() const;
	double getRecord() const;

	//Modifiers
	void setTeam(std::string t) const;
	void setWin(int w);
	void setLoss(int l);

private:
	std::string team;
	int win;
	int loss;
	double record;

};

bool winRateSort(const Team& t1, const Team& t2);