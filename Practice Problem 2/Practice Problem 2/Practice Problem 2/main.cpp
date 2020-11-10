#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include "Football.h"
#include "Team.h"

std::string teamName;

int main(int argc, char* argv[]){

	//Date Variables
	std::string DOW, month, visName, homeName;
	int day, year, vQ1, vQ2, vQ3, vQ4, vOT, vFinal, hQ1, hQ2, hQ3, hQ4, hOT, hFinal;

	std::string longest;
	std::string aTeamName;

	//Visitor Variables
	//std::string vis_name;
	//int vis_q1, vis_q2, vis_q3, vis_q4, vis_ot, vis_Final;

	//Home Variables
	//std::string home_name;
	//int home_q1, home_q2, home_q3, home_q4, home_ot, home_final;


	std::ifstream example(argv[1]);
	if (!example){
		std::cerr << "Can't open " << argv[1] << " to read. \n";
		exit(1);
	}

	std::vector<Football> Football_Vec;
	while (example >> DOW >> month >> day >> year
		>> visName >> vQ1 >> vQ2 >> vQ3 >> vQ4 >> vOT >> vFinal
		>> homeName >> hQ1 >> hQ2 >> hQ3 >> hQ4 >> hOT >> hFinal) {
		Football Test(DOW, month, day, year, visName, vQ1, vQ2, vQ3, vQ4, vOT, vFinal, homeName, hQ1, hQ2, hQ3, hQ4, hOT, hFinal);
		Football_Vec.push_back(Test);
	}

	sort(Football_Vec.begin(), Football_Vec.end(), isLessThan);

	longest = Football_Vec[0].getVisName();

	for (int i = 0; i < Football_Vec.size(); i++) {
		if (longest.size() < Football_Vec[i].getHomeName().size())
		{
			longest == Football_Vec[i].getHomeName();
		}

	}

	aTeamName = Football_Vec[0].getVisName();
	Team newTeam(aTeamName);

	std::vector<Team> Teams_Vec;
	Teams_Vec.push_back(newTeam);

	bool nameFound;

	for (int i = 0; i < Football_Vec.size(); i++) {
		nameFound = false;
		for (int j = 0; j < Teams_Vec.size(); j++) {
			if (Football_Vec[i].getVisName() == Teams_Vec[j].getTeam()) {
				nameFound = true;
			}
		}

		if (!nameFound) {
			aTeamName = Football_Vec[i].getVisName();
			Teams_Vec.push_back(aTeamName);
		}

		nameFound = false;
		for (int j = 0; j < Teams_Vec.size(); j++) {
			if (Football_Vec[i].getHomeName() == Teams_Vec[j].getTeam()) {
				nameFound = true;
			}
		}

		if (!nameFound) {
			aTeamName = Football_Vec[i].getHomeName();
			Teams_Vec.push_back(aTeamName);
		}
	}

	for (int i = 0; i < Football_Vec.size(); i++) {
		int wins = 0;
		int losses = 0;
		if (Football_Vec[i].getVFin() > Football_Vec[i].getHFin()) {
			for (int j = 0; j < Teams_Vec.size(); j++) {
				if (Football_Vec[i].getVisName() == Teams_Vec[j].getTeam()) {
					wins = Teams_Vec[j].getWin() + 1;
					Teams_Vec[j].setWin(wins);
				}

				if (Football_Vec[i].getHomeName() == Teams_Vec[j].getTeam()) {
					losses = Teams_Vec[j].getLoss() + 1;
					Teams_Vec[j].setLoss(losses);
				}
			}
		}

		if (Football_Vec[i].getVFin() < Football_Vec[i].getHFin()) {
			for (int j = 0; j < Teams_Vec.size(); j++) {
				if (Football_Vec[i].getHomeName() == Teams_Vec[j].getTeam()) {
					wins = Teams_Vec[j].getWin() + 1;
					Teams_Vec[j].setWin(wins);
				}

				if (Football_Vec[i].getVisName() == Teams_Vec[j].getTeam()) {
					losses = Teams_Vec[j].getLoss() + 1;
					Teams_Vec[j].setLoss(losses);
				}
			}
		}
	}

	sort(Teams_Vec.begin(), Teams_Vec.end(), winRateSort);

	for (int i = 0; i < Teams_Vec.size(); i++) {
		std::cout << std::setfill(' ') << std::left << std::setw(longest.size() + 5) << Teams_Vec[i].getTeam()
			<< std::setfill(' ') << std::right << std::setw(2) << Teams_Vec[i].getWin() << " win(s) - "
			<< std::setfill(' ') << std::right << std::setw(2) << Teams_Vec[i].getLoss() << " loss(es)   " << Teams_Vec[i].getRecord() << "\n";
	}

	std::cout << "\n";
		
	for (int i = 0; i < Football_Vec.size(); i++) {

		if (Football_Vec[i].getVFin() > Football_Vec[i].getHFin()) {
			std::cout << std::setfill(' ') << std::left << std::setw(longest.size() + 5) << Football_Vec[i].getVisName()
				<< "defeated  " << std::setfill(' ') << std::left << std::setw(longest.size() + 5) << Football_Vec[i].getHomeName()
				<< std::setfill(' ') << std::right << std::setw(2) <<  Football_Vec[i].getVFin() << " - "
				<< std::setfill(' ') << std::right << std::setw(2) << Football_Vec[i].getHFin()
				<< "  differential =   " << std::setfill(' ') << std::left << std::setw(4)
				<< abs(Football_Vec[i].getVFin() - Football_Vec[i].getHFin()) << "total points =  " << (Football_Vec[i].getVFin() + Football_Vec[i].getHFin()) << "\n";
		}
		else {
			std::cout << std::setfill(' ') << std::left << std::setw(longest.size() + 5) << Football_Vec[i].getVisName()
				<< "lost to   " << std::setfill(' ') << std::left << std::setw(longest.size() + 5) << Football_Vec[i].getHomeName()
				<< std::setfill(' ') << std::right << std::setw(2) << Football_Vec[i].getVFin() << " - "
				<< std::setfill(' ') << std::right << std::setw(2) << Football_Vec[i].getHFin()
				<< "  differential =   " << std::setfill(' ') << std::left << std::setw(4)
				<< abs(Football_Vec[i].getVFin() - Football_Vec[i].getHFin()) << "total points =  " << (Football_Vec[i].getVFin() + Football_Vec[i].getHFin()) << "\n";
		}
		
		

		/*

		std::cout << Football_Vec[i].getDOW() << "\n";
		std::cout << Football_Vec[i].getMonth() << "\n";
		std::cout << Football_Vec[i].getDay() << "\n";
		std::cout << Football_Vec[i].getYear() << "\n";
		std::cout << Football_Vec[i].getVisName() << "\n";
		std::cout << Football_Vec[i].getVQ1() << "\n";
		std::cout << Football_Vec[i].getVQ2() << "\n";
		std::cout << Football_Vec[i].getVQ3() << "\n";
		std::cout << Football_Vec[i].getVQ4() << "\n";
		std::cout << Football_Vec[i].getVOT() << "\n";
		std::cout << Football_Vec[i].getVFin() << "\n";
		std::cout << Football_Vec[i].getHomeName() << "\n";
		std::cout << Football_Vec[i].getHQ1() << "\n";
		std::cout << Football_Vec[i].getHQ2() << "\n";
		std::cout << Football_Vec[i].getHQ3() << "\n";
		std::cout << Football_Vec[i].getHQ4() << "\n";
		std::cout << Football_Vec[i].getHOT() << "\n";
		std::cout << Football_Vec[i].getHFin() << "\n";
		std::cout << "\n";

		for (int i = 0; i < Teams_Vec.size(); i++) {
			std::cout << Teams_Vec[i].getTeam() << "\n";
		}
		*/


    }





	

}

