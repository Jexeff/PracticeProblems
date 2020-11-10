#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cassert>
#include <cstdlib>
#include "school.h"


School::School(std::string name,int slots){
	school_name = name;
	num_slots = slots;
}

void School::AddStudent(std::string student_name){
	bool name_found = false;
	for (std::list<std::string>::iterator itr = schools_list_of_students.begin(); itr != schools_list_of_students.end(); ++itr) {
		if (*itr == student_name) {
			std::cerr << "could not add " << student_name << " into school preference list, this student is already in the list" << std::endl;
			name_found = true;
		}
	}
	if (name_found != true) {
		schools_list_of_students.push_back(student_name);
	}
}

std::string School::GetName() const{
	return school_name;
}

void School::PrintSchoolPreferenceList(std::ostream& ostr) const{
	int counter = 1;
	for (std::list<std::string>::const_iterator pref_itr = schools_list_of_students.begin(); pref_itr != schools_list_of_students.end(); ++pref_itr) {
		std::string name = *pref_itr;
		ostr << "  " << counter << ". " << name << std::endl;
		counter++;
	}
	ostr << std::endl;
}

void School::PrepareToMakeOffers() {
	school_itr = schools_list_of_students.begin();
}

int School::MaxAcceptedStudents() {
	return num_slots;
}

std::string School::MakeNextOffer() {
	std::string offer;
	if (school_itr != schools_list_of_students.end()) {
		offer = *school_itr;
		school_itr++;
	}
	else {
		offer = "";
	}
	return offer;

	/*if (firstOffer == true) {
		firstOffer = false;
		return *school_itr;
	}
	else if (school_itr != schools_list_of_students.end()){
		return *++school_itr;
	}
	else {
		std::cout << "fuck we did it";
		return "";
	}*/
}

void School::StudentTentativelyAcceptsOffer(std::string student) {
	list_of_accepted_students.push_back(student);
	total_accepted += 1;
}

void School::StudentDeclinesTentativeAcceptance(std::string student) {
	for (std::list<std::string>::iterator acc_itr = list_of_accepted_students.begin(); acc_itr != list_of_accepted_students.end(); ++acc_itr) {
		if (*acc_itr == student) { 
			list_of_accepted_students.remove(*acc_itr);
			total_accepted -= 1;
			break;
		}
	}
}

int School::NumAcceptedStudents() {
	return total_accepted;
}

void School::PrintSchoolEnrollment(std::ofstream& ostr) {

	int num_of_slots_remaining = num_slots;

	list_of_accepted_students.sort();
	ostr << "student(s) who will be attending " << school_name << ":" << std::endl;
		//Add tracking of remaining slots of enrollment.
		for (std::list<std::string>::iterator it = list_of_accepted_students.begin(); it != list_of_accepted_students.end(); ++it) {
			 ostr << "  " << *it << std::endl;
			num_of_slots_remaining--;
		}
		if (num_of_slots_remaining > 0) {
			ostr << "  [" << num_of_slots_remaining << " remaining slot(s) in enrollment]" << std::endl;
		} 
}

void School::InsertStudentName(std::string student, std::string insert_before) {
	for (std::list<std::string>::iterator itr = schools_list_of_students.begin(); itr != schools_list_of_students.end(); ++itr) {
		if (*itr == insert_before) {
			schools_list_of_students.insert(itr, student);
			break;
		}
	}
}

bool alpha_by_school_name(School s1, School s2) {
	if (s1.GetName() < s2.GetName()) {
		return true;
	}
	else {
		return false;
	}
	
}





