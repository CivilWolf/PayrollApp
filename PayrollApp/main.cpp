#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

float FindFICA(float tPay, int nDep, bool single)
{
	float answer = 0;

	int wHold[11][130] =
	{
		0,0,0,0,2,0,0,0,0,0,0,
		1,0,0,0,0,0,0,0,0,0,0,
		1,0,0,0,0,0,0,0,0,0,0,
		2,0,0,0,0,0,0,0,0,0,0,
	};



	return answer;
}
class Employee
{
public:
	//Times
	float hWeek, oWeek;
	//Pay
	float pHour;

	//Totals
	float totalPay, underPay, overPay, tSS, tMC, tFICA;

	int nAllow;
	bool single;

	string name;

	Employee()
	{
		name = "N/A";
		hWeek = 0; oWeek = 0; pHour = 0; totalPay = 0; underPay = 0; overPay = 0; tSS = 0; tMC = 0; tFICA = 0;
		nAllow = 0; single = false;
	}
	Employee(string name)
	{
		this->name = name;
		hWeek = 0; oWeek = 0; pHour = 0; totalPay = 0; underPay = 0; overPay = 0; tSS = 0; tMC = 0; tFICA = 0;
		nAllow = 0; single = false;
	}
	void update(float SS, float MC)
	{


		underPay = hWeek * pHour;
		overPay = oWeek * pHour*1.5;
		totalPay = underPay + overPay;

		tFICA = FindFICA(totalPay, nAllow, single);
		tSS = totalPay * SS;
		tMC = totalPay * MC;

	}

	~Employee()
	{

	}
};


int main()
{
	float SS = .062, MC = .0145;
	float overTimeLimit = 40;

	Employee e("Billy");

	//Enter Hours
	cout << "\nPlease enter " << e.name << "'s hourly income: \n";
	cin >> e.pHour;
	cout << "\nPlease enter " << e.name << "'s total hours this week: \n";
	cin >> e.hWeek;
	if (e.hWeek > overTimeLimit)
	{
		e.oWeek = e.hWeek - overTimeLimit;
		e.hWeek = overTimeLimit;
	}

	//Totals Screen

	cout << "\n" << e.name << "'s Totals\n----------\n";
	e.update(SS, MC);


	cout << "Regular Hours: " << e.hWeek << endl;
	cout << "Overtime Hours: " << e.oWeek << endl << endl;
	cout << fixed << setprecision(2);
	cout << "Week Pay: $" << e.underPay << endl;
	cout << "Overtime Pay: $" << e.overPay << endl;
	cout << "Total Pay: $" << e.totalPay << endl << endl;


	cout << "FICA: " << e.tFICA << endl;
	cout << "SS: " << e.tSS << endl;
	cout << "MC: " << e.tMC << endl;

	cout << setprecision(0);

	cout << "test";
	_getch();

	return 0;
}

