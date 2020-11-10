#include <iostream>
#include <string>
#include "Football.h"
#include <cmath>

Football::Football() {

	DOW = "";
	month = "";
	day = 0;
	year = 0;

	visName = "";
	vQ1 = 0;
	vQ2 = 0;
	vQ3 = 0;
	vQ4 = 0;
	vOT = 0;
	vFinal = 0;

	homeName = "";
	hQ1 = 0;
	hQ2 = 0;
	hQ3 = 0;
	hQ4 = 0;
	hOT = 0;
	hFinal = 0;
}

Football::Football(std::string aDOW, std::string aMonth, int aDay, int aYear,
				   std::string vis_name, int vis_q1, int vis_q2, int vis_q3, int vis_q4, int vis_ot, int vis_Final,
				   std::string home_name, int home_q1, int home_q2, int home_q3, int home_q4, int home_ot, int home_final) {

	DOW = aDOW;
	month = aMonth;
	day = aDay;
	year = aYear;

	visName = vis_name;
	vQ1 = vis_q1;
	vQ2 = vis_q2;
	vQ3 = vis_q3;
	vQ4 = vis_q4;
	vOT = vis_ot;
	vFinal = vis_Final;

	homeName = home_name;
	hQ1 = home_q1;
	hQ2 = home_q2;
	hQ3 = home_q3;
	hQ4 = home_q4;
	hOT = home_ot;
	hFinal = home_final;
}

//ACCESSOR FUNCTIONS
std::string Football::getDOW() const {
	return DOW;
}

std::string Football::getMonth() const {
	return month;
}

int Football::getDay() const {
	return day;
}

int Football::getYear() const {
	return year;
}

std::string Football::getVisName() const {
	return visName;
}

int Football::getVQ1() const {
	return vQ1;
}

int Football::getVQ2() const {
	return vQ2;
}

int Football::getVQ3() const {
	return vQ3;
}

int Football::getVQ4() const {
	return vQ4;
}

int Football::getVOT() const {
	return vOT;
}

int Football::getVFin() const {
	return vFinal;
}

std::string Football::getHomeName() const {
	return homeName;
}

int Football::getHQ1() const {
	return hQ1;
}

int Football::getHQ2() const {
	return hQ2;
}

int Football::getHQ3() const {
	return hQ3;
}

int Football::getHQ4() const {
	return hQ4;
}

int Football::getHOT() const {
	return hOT;
}

int Football::getHFin() const {
	return hFinal;
}

//MODIFIER FUNCTIONS

void Football::setDow(std::string d_o_w) const {
	DOW == d_o_w;
}

void Football::setMonth(std::string m) const {
	month == m;
}

void Football::setDay(int d) const {
	day == d;
}

void Football::setYear(int y) const {
	year == y;
}



void Football::setVisName(std::string vis_name) const {
	visName == vis_name;
	//Not sure if this works
}

void Football::setVQ1(int vis_q1) {
	vQ1 = vis_q1;
}

void Football::setVQ2(int vis_q2) {
	vQ2 = vis_q2;
}

void Football::setVQ3(int vis_q3) {
	vQ3 = vis_q3;
}

void Football::setVQ4(int vis_q4) {
	vQ4 = vis_q4;
}

void Football::setVOT(int vis_ot) {
	vOT = vis_ot;
}

void Football::setVFin(int vis_final) {
	vFinal = vis_final;
}

void Football::setHomeName(std::string home_name) const {
	homeName == home_name;
}

void Football::setHQ1(int home_q1) {
	hQ1 = home_q1;
}

void Football::setHQ2(int home_q2) {
	hQ2 = home_q2;
}

void Football::setHQ3(int home_q3) {
	hQ3 = home_q3;
}

void Football::setHQ4(int home_q4) {
	hQ4 = home_q4;
}

void Football::setHOT(int home_ot) {
	hOT = home_ot;
}

void Football::setHFin(int home_final) {
	hFinal = home_final;
}

bool isLessThan(const Football& f1, const Football& f2) {
	//Compares the differential of 2 games
	if (abs(f1.getHFin() - f1.getVFin()) < abs(f2.getHFin() - f2.getVFin())) {
		return true;
	}
	//Compares if the differential is the same
	else if (abs(f1.getHFin() - f1.getVFin()) == abs(f2.getHFin() - f2.getVFin())) {

		//Compares the total points scored in the games
		if (f1.getHFin() + f1.getVFin() > f2.getHFin() + f2.getVFin()) {
			return true;
		}
		//Compares if the total points scored in the games are equal
		else if (f1.getHFin() + f1.getVFin() == f2.getHFin() + f2.getVFin()) {

			//Compares if the visitor is the same in both games.
			if (f1.getVisName() != f2.getVisName()) {
				int v = f1.getVisName().compare(f2.getVisName());
				if (v < 0) {
					return true;
				}
			}
			else if (f1.getVisName() == f2.getVisName()) {
				//If the names are of the visiting teams are the same, compare will return a "0"
				int h = f1.getHomeName().compare(f2.getHomeName());
				
				//If the names of the home teams are the same, compare will return a "0"
				if (h < 0) {
					return true;
				}
			
			}
		}
	}
	return false;
}



