#pragma once
#include <string>


class School
{
public:
	//Constructor
	School(std::string name, int slots);

	//Accessors
	std::string GetName() const;

	//Other Member Functions
	void AddStudent(std::string student_name);
	void PrintSchoolPreferenceList(std::ostream& ostr) const;
	void PrepareToMakeOffers();
	int MaxAcceptedStudents();
	std::string MakeNextOffer();
	void StudentTentativelyAcceptsOffer(std::string student);
	void StudentDeclinesTentativeAcceptance(std::string student);
	int NumAcceptedStudents();
	void PrintSchoolEnrollment(std::ofstream& ostr);
	void InsertStudentName(std::string student, std::string insert_before);

	//void StudentDeclinesTentativeAcceptance(std::string student);
	//void PrintSchoolEnrollment(std::ofstream& ostr);

private:

	std::string school_name;
	int num_slots;
	int total_accepted = 0;
	bool firstOffer = true;
	//int num_pref;
	//int max_accepted;
	//int num_accepted;

	std::list<std::string> schools_list_of_students;
	std::list<std::string>::iterator school_itr;
	std::list<std::string> list_of_accepted_students;
	std::list<std::string>::iterator accepted_itr;
};

bool alpha_by_school_name(School s1, School s2);




