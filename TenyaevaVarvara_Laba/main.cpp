#include <iostream>
#include <fstream>

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

PIPE One;
STATION S1;

PIPE NewPIPE()
{
	PIPE A;
	cout << "Pipe kilometer mark (name): ";
	cin >> A.title;
	cout << "Pipe lenght (metre): ";
	cin >> A.lenght;
	while (A.lenght <= 0)
	{
	//	cout << "Please enter the correct value: ";
		cin >> A.lenght;
	}
	cout << "Pipe diameter (centimetre): ";
	cin >> A.diameter;
	while (A.diameter <= 0)
	{
	//	cout << "Please enter the correct value: ";
		cin >> A.diameter;
	}
	cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
	cin >> A.repair;
	//while (A.repair != 0 and A.repair != 1)
	//{
	//	cout << "Please enter the correct value: ";
	//	cin >> A.repair;
	//}
	return A;
}

STATION NewSTATION()
{
	STATION Y;
	cout << "Name of the compressor station: ";
	cin >> Y.name;
	cout << "Number of workshops in the compressor station: ";
	cin >> Y.workshop;
	while (Y.workshop <= 0)
	{
		cout << "Please enter the correct value: ";
		cin >> Y.workshop;
	}
	cout << "Number of workshops in operation at the compressos station: ";
	cin >> Y.inOperation;
	while (Y.inOperation > Y.workshop or Y.inOperation < 0)
	{
		cout << "Please enter the correct value: ";
		cin >> Y.inOperation;
	}
	cout << "Compressor station effiency: ";
	cin >> Y.effectiveness;
	while (Y.effectiveness > 1 or Y.effectiveness < 0)
	{
		cout << "Please enter the correct value: ";
		cin >> Y.effectiveness;
	}
	return Y;
}

PIPE DownloadPIPE()
{
	ifstream fin;
	fin.open("PIPE.txt", ios::in);
	PIPE A;
	fin >> A.title;
	fin >> A.lenght;
	fin >> A.diameter;
	fin >> A.repair;
	fin.close();
	return A;
}

STATION DownloadSTATION()
{
	ifstream fin;
	fin.open("STATION.txt", ios::in);
	STATION Y;
	fin >> Y.name;
	fin >> Y.workshop;
	fin >> Y.inOperation;
	fin >> Y.effectiveness;
	fin.close();
	return Y;
}


void PrintPIPE(const PIPE& A)
{
	cout << "Pipe kilometer mark: " << A.title<<endl;
	cout << "Pipe lenght: "<< A.lenght<<endl;
	cout << "Pipe diameter: "<< A.diameter<<endl;
	if (A.repair == 0)
	{
		cout << "Pipe sign 'under repair': " << "repairing" << endl;
	}
	else
	{
		cout << "Pipe sign 'under repair': " << "works" << endl;
	}
}

void PrintSTATION(const STATION& Y)
{
	cout << "Name of the compressor station: " << Y.name<<endl;
	cout << "Number of workshops in the compressor station: "<< Y.workshop<<endl;
	cout << "Number of workshops in operation at the compressos station: "<<Y.inOperation<<endl;
	cout << "Compressor station effiency: "<< Y.effectiveness<<endl;
}

void SavePIPE(const PIPE& A)
{
	ofstream fout;
	fout.open("PIPE.txt", ios::out);
	//cout << "Pipe kilometer mark: " << endl;
	fout << A.title << endl;
	//cout << "Pipe lenght: " << endl;
	fout<< A.lenght << endl;
	//cout << "Pipe diameter: " << endl;
	fout<< A.diameter << endl;
	//if (A.repair == 0)
	//{
	//	fout << "Pipe sign 'under repair': " << "repairing" << endl;
	//}
	//else
	//{
	//	fout << "Pipe sign 'under repair': " << "works" << endl;
	//}
	//cout << "Pipe sign 'under repair': " << endl;
	fout << A.repair;
	fout.close();
}

void SaveSTATION(const STATION& Y)
{
	ofstream fout;
	fout.open("STATION.txt", ios::out);
	//cout << "Name of the compressor station: " << endl;
	fout<< Y.name << endl;
	//cout << "Number of workshops in the compressor station: " << endl;
	fout<< Y.workshop << endl;
	//cout << "Number of workshops in operation at the compressos station: " << endl;
	fout<< Y.inOperation << endl;
	//cout << "Compressor station effiency: " << endl;
	fout<< Y.effectiveness;
	fout.close();
}

void EditPIPE(PIPE &A)
{
	cout << "Pipe sign 'under repair' (0 if repairing, 1 if works): ";
	cin >> A.repair;
}

void StartWorkshopsSTATION(STATION& Y)
{
	int i;
	cout << "Launch of compressor station workshops: ";
	cin >> i;
	while (i <= 0)
	{
		cout << "Please enter the correct value: ";
		cin >> i;
	}
	Y.inOperation += i;
}

void StopWorkshopsSTATION(STATION& Y)
{
	int j;
	cout << "Stop of compressor station workshops: ";
	cin >> j;
	while (j <= 0)
	{
		cout << "Please enter the correct value: ";
		cin >> j;
	}
	Y.inOperation -= j;
}

int main()
{
	//One = NewPIPE();
	//S1 = NewSTATION();
	//DownloadPIPE();
	//DownloadSTATION();
	//PrintPIPE(One);
	//SavePIPE(One);
	PrintPIPE(DownloadPIPE());
	//PrintSTATION(S1);
	//SaveSTATION(S1);
	PrintSTATION(DownloadSTATION());
	//EditPIPE(One);
	//PrintPIPE(One);
	//StartWorkshopsSTATION(S1);
	//StopWorkshopsSTATION(S1);
	//PrintSTATION(S1);
	return 0;
}