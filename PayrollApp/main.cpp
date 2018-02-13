#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>

#include "extras.h"
using namespace std;
const int MAX_ROWS = 136;
const int MAX_COLUMNS = 11;
const int MAX_S = 2;

int wHold[MAX_S][MAX_ROWS][MAX_COLUMNS];

int FillArray(int (&myarray)[MAX_S][MAX_ROWS][MAX_COLUMNS])
{
	ifstream singleFile("IT_Withholding_Single_Weekly_2018.txt");
	if (!singleFile) {
		cout << "Single File Load Fail" << endl;
		return 1;
	}
	ifstream marriedFile("IT_Withholding_Married_Weekly_2018.txt");
	if (!marriedFile) {
		cout << "Married File Load Fail" << endl;
		return 1;
	}

	for (int i = 0; i < 135; i++) {
		for (int p = 0; p < 11; p++) {
			singleFile >> myarray[0][i][p];
			if (!singleFile) {
				cout << "Error reading file for element " << i << "," << p << endl;
				return 1;
			}
		}
	}
	for (int i = 0; i < 136; i++) {
		for (int p = 0; p < 11; p++) {
			marriedFile >> myarray[1][i][p];
			if (!marriedFile) {
				cout << "Error reading file for element " << i << "," << p << endl;
				return 1;
			}
		}
	}
	return 0;
}
void PrintArray(int(&myarray)[MAX_S][MAX_ROWS][MAX_COLUMNS])
{
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int p = 0; p < MAX_COLUMNS; p++)
		{
			cout << myarray[1][i][p] << " ";
		}
		cout << endl;
	}
}
int FindSelector(float gPay,bool married)
{
	int counter = 1;
	int inc = 5;
	
	int start = 75;
	int start2 = 80;
	int endv = 1290;
	int switchlimit = 200;


	if (married == false)
	{
		start = 75;
		start2 = 80;
		switchlimit = 200;
		endv = 1290;
		inc = 5;
	}
	else
	{
		start = 225;
		start2 = 235;
		switchlimit = 0;
		endv = 1575;
		inc = 10;
	}



	if (gPay >= 0 && gPay < start)
	{return 0;}

	for (int i = start2; i <= endv; i += inc)
	{
		if (i >= switchlimit)
			inc = 10;
		if (gPay >= i - inc && gPay < i)
		{
			//cout << "\nBetween: " << i - inc << "-"<< i;
			//cout << "\nCounter: " << counter << endl;
			return counter;
		}
		counter++;
	}

	return -1;
}
float FindFICA(float gPay, int nAllow, bool single)
{
	int answer = 0;
	answer = wHold[single][FindSelector(gPay, single)][nAllow];//wHold[nAllow][FindSelector(gPay)];
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
	float totDed,netPay;

	int nAllow;
	bool married;

	string name;

	Employee()
	{
		name = "N/A";
		hWeek = 0; oWeek = 0; pHour = 0; totalPay = 0; underPay = 0; overPay = 0; tSS = 0; tMC = 0; tFICA = 0;
		nAllow = 0; married = false;
		totDed = 0; netPay = 0;
	}
	Employee(string name)
	{
		this->name = name;
		hWeek = 0; oWeek = 0; pHour = 0; totalPay = 0; underPay = 0; overPay = 0; tSS = 0; tMC = 0; tFICA = 0;
		nAllow = 0; married = false;
		totDed = 0; netPay = 0;
	}
	Employee(string name,float pHour,int nAllow,bool married)
	{
		this->name = name;
		hWeek = 0; oWeek = 0; this->pHour = pHour; totalPay = 0; underPay = 0; overPay = 0; tSS = 0; tMC = 0; tFICA = 0;
		this->nAllow = nAllow; this->married = married;
		totDed = 0; netPay = 0;
	}
	void update(float SS, float MC)
	{
		underPay = hWeek * pHour;
		overPay = oWeek * pHour*1.5;
		totalPay = underPay + overPay;

		tFICA = FindFICA(totalPay, nAllow, married);
		tSS = totalPay * SS;
		tMC = totalPay * MC;

		totDed = -(tFICA + tSS + tMC);

		netPay = totalPay + totDed;

	}

	~Employee()
	{

	}
};

int main()
{
	//HWND console = GetConsoleWindow();
	//HDC dc = GetDC(console);
	bool quit = false;
	FillArray(wHold);
	float SS = .062, MC = .0145;
	float overTimeLimit = 40;

	Employee e("Bob Winkersmear");

	//
	//PrintArray(wHold);
	while (quit != true)
	{
		//Create Employee
		cout << "Please enter " << e.name << "'s hourly income: \n";
		cin >> e.pHour;
		cout << "\nPlease enter " << e.name << "'s total hours this week: \n";
		cin >> e.hWeek;
		cout << "\nPlease enter " << e.name << "'s marital status: \n";
		cin >> e.married;
		cout << "\nPlease enter " << e.name << "'s allowances: \n";
		cin >> e.nAllow;

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
		cout << "Gross Pay: $" << e.totalPay << endl << endl;
		cout << "FICA: " << e.tFICA << endl;
		cout << "SS: " << e.tSS << endl;
		cout << "MC: " << e.tMC << endl << endl;
		cout << "Total Deductions: " << e.totDed << endl << endl;
		cout << "Net Pay: $" << e.netPay << endl << endl;
		cout << setprecision(0);
		cout << "-[ESC] to quit-" << endl;
		cout << "Press any button..." << endl;
		if (_getch() == 0x1B)
		{
			quit = true;
		}
		cout << endl;
		//cls(&dc);
	}

	return 0;
}

