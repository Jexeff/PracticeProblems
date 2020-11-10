#pragma once
#include <string>

class Football {

public:
	Football();
	Football(std::string aDOW, std::string aMonth, int aDay, int aYear,
		std::string vis_name, int vis_q1, int vis_q2, int vis_q3, int vis_q4, int vis_ot, int vis_Final,
		std::string home_name, int home_q1, int home_q2, int home_q3, int home_q4, int home_ot, int home_final);

	// ACCESSORES
	std::string getDOW() const;
	std::string getMonth() const;
	int getDay() const;
	int getYear() const;

	std::string getVisName() const;
	int getVQ1() const;
	int getVQ2() const;
	int getVQ3() const;
	int getVQ4() const;
	int getVOT() const;
	int getVFin() const;

	std::string getHomeName() const;
	int getHQ1() const;
	int getHQ2() const;
	int getHQ3() const;
	int getHQ4() const;
	int getHOT() const;
	int getHFin() const;

	//MODIFIERS
	void setDow(std::string d_o_w) const;
	void setMonth(std::string m) const;
	void setDay(int d) const;
	void setYear(int y) const;

	void setVisName(std::string vis_name) const;
	void setVQ1(int vis_q1);
	void setVQ2(int vis_q2);
	void setVQ3(int vis_q3);
	void setVQ4(int vis_q4);
	void setVOT(int vis_ot);
	void setVFin(int vis_final);

	void setHomeName(std::string home_name) const;
	void setHQ1(int home_q1);
	void setHQ2(int home_q2);
	void setHQ3(int home_q3);
	void setHQ4(int home_q4);
	void setHOT(int home_ot);
	void setHFin(int home_final);

private:

	//Date Variables
	std::string DOW;
	std::string month;
	int day;
	int year;

	//Visitor Team Variables
	std::string visName;
	int vQ1;
	int vQ2;
	int vQ3;
	int vQ4;
	int vOT;
	int vFinal;

	//Home Team Variables
	std::string homeName;
	int hQ1;
	int hQ2;
	int hQ3;
	int hQ4;
	int hOT;
	int hFinal;



};

bool isLessThan(const Football& f1, const Football& f2);
