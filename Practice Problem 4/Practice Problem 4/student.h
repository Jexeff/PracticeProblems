#pragma once
#include <string>


class Student
{
public:
	//Constructor
	Student(std::string name);

	//Accessors
	std::string GetName() const;

	//Modifiers
	//void Set_Student_Name(std::string name);

	//Other Member Functions
	void AddSchool(std::string school_name);
	void PrintStudentPreferenceList(std::ostream& ostr) const;
	void PrepareToReceiveOffers();
	bool HasOffer();
	std::string GetBestOffer();
	bool IsOfferTentativelyAccepted(std::string school_name);
	void PrintStudentDecision(std::ofstream& ostr) const;
	void RemoveSchoolName(std::string school);

private:
	bool has_offer = false;
	std::string temp_offer = "";
	std::string best_offer = "";
	std::string student_name;
	std::list<std::string> students_list_of_schools;
	std::list<std::string>::iterator student_itr;

	//std::list<std::string> students_preference_list_of_schools;
	//std::list<std::string>::iterator preference_itr;
	
};

bool alpha_by_student_name(Student s1, Student s2);

