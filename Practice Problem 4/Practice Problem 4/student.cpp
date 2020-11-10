#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cassert>
#include <cstdlib>
#include "student.h"

Student::Student(std::string name) {
	student_name = name;
}

void Student::AddSchool(std::string school_name){

	bool name_found = false;
	for (std::list<std::string>::iterator itr = students_list_of_schools.begin(); itr != students_list_of_schools.end(); ++itr) {
		if (*itr == school_name) {
			std::cerr << "could not add school named " << school_name << ", this school already exists." << std::endl;
			name_found = true;
		}
	}
	if (name_found == false) {
		students_list_of_schools.push_back(school_name);
	}
}

std::string Student::GetName() const {
	return student_name;
}

void Student::PrintStudentPreferenceList(std::ostream& ostr) const{
	int counter = 1;
		for (std::list<std::string>::const_iterator student_itr = students_list_of_schools.begin(); student_itr != students_list_of_schools.end(); ++student_itr) {
		std::string school_name = *student_itr;
		ostr << "  " << counter << ". " << school_name << std::endl;
		counter++;
	}
	ostr << std::endl;
}

void Student::PrepareToReceiveOffers() {
	student_itr = students_list_of_schools.begin();
}

bool Student::HasOffer() {
	if (best_offer != "") {
		has_offer = true;
	}
	return has_offer;
}

std::string Student::GetBestOffer() {
	return best_offer;
}

bool Student::IsOfferTentativelyAccepted(std::string school_name) {
	bool best_offer_found = false;
	bool tentative_offer_found = false;
	bool tenative_offer = false;
	for (std::list<std::string>::reverse_iterator tent_itr = students_list_of_schools.rbegin(); tent_itr != students_list_of_schools.rend(); ++tent_itr) {
		if (*tent_itr == best_offer) {
			best_offer_found = true;
		}
		if (*tent_itr == school_name && best_offer_found == true) {
			best_offer = school_name;
			tentative_offer_found = true;
			tenative_offer = true;
		}
		else if (*tent_itr == school_name && best_offer == "") {
			best_offer = school_name;
			tentative_offer_found = true;
			tenative_offer = true;
		}
	}
	return tenative_offer;
}

void Student::PrintStudentDecision(std::ofstream& ostr) const{
	if (best_offer != ""){
		ostr << student_name << " will be attending " << best_offer << std::endl;
	}
	else {
		ostr << student_name << " has not received an acceptable offer" << std::endl;
	}
}

void Student::RemoveSchoolName(std::string school) {
	for (std::list<std::string>::iterator itr = students_list_of_schools.begin(); itr != students_list_of_schools.end(); ++itr) {
		if (*itr == school) {
			students_list_of_schools.remove(*itr);
			break;
		}
	}
}


bool alpha_by_student_name(Student s1, Student s2) {
	if (s1.GetName() < s2.GetName()) {
		return true;
	}
	else {
		return false;
	}
}
