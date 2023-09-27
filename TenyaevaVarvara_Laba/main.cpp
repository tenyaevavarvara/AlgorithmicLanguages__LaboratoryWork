#include <iostream>

using namespace std;

struct PIPE
{
	string title;
	double lenght;
	int diameter;
	bool repair;
};

struct STATION
{
	string name;
	int workshop;
	int inOperation;
	double effectiveness;
};

PIPE NewPIPE()
{
	PIPE A;
	cout << "Pipe kilometer mark (name): ";
	cin >> A.title;
	cout << "Pipe lenght (metre): ";
	cin >> A.lenght;
	cout << "Pipe diameter (centimetre): ";
	cin >> A.diameter;
	cout << "Pipe sign 'under repair' (true or false): ";
    cin >> A.repair;
	return A;
}

void PrintPIPE(PIPE A)
{
	cout << "Pipe kilometer mark (name): " << A.title<<endl;
	cout << "Pipe lenght (metre): "<< A.lenght<<endl;
	cout << "Pipe diameter (centimetre): "<< A.diameter<<endl;
	cout << "Pipe sign 'under repair' (true or false): "<< A.repair<<endl;
}

int main()
{
	PIPE One = NewPIPE();
	PrintPIPE(One);
	return 0;
}