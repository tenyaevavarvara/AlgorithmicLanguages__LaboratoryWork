#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

struct PIPE
{
	string title = "Untitled";
	double lenght;
	int diameter;
	bool repair;
};

struct STATION
{
	string name = "Untitled";
	int workshop;
	int inOperation;
	double effectiveness;
};

PIPE NewPIPE()
{
	PIPE A;
	cout << "Pipe kilometer mark (name): ";
	cin.ignore();
	getline(cin, A.title);
	cout << "Pipe lenght (metre): ";
	cin >> A.lenght;
	while (cin.fail() || A.lenght <= 0)
	{
		cout << "Please enter the correct value (greater than 0): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> A.lenght;
	}
	cout << "Pipe diameter (centimetre): ";
	cin >> A.diameter;
	while (cin.fail() || A.diameter <= 0)
	{
		cout << "Please enter the correct value (greater than 0): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> A.diameter;
	}
	cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
	cin >> A.repair;
	while (cin.fail())
	{
		cout << "Please enter the correct value (0 or 1): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> A.repair;
	}
	return A;
}

STATION NewSTATION()
{
	STATION Y;
	cout << "Name of the compressor station: ";
	cin.ignore();
	getline(cin, Y.name);
	cout << "Number of workshops in the compressor station: ";
	cin >> Y.workshop;
	while (cin.fail() || Y.workshop <= 0)
	{
		cout << "Please enter the correct value (greater than 0): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> Y.workshop;
	}
	cout << "Number of workshops in operation at the compressos station: ";
	cin >> Y.inOperation;
	while (cin.fail() || Y.inOperation > Y.workshop || Y.inOperation < 0)
	{
		cout << "Please enter the correct value (greater than 0,but less than Number of workshops): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> Y.inOperation;
	}
	cout << "Compressor station effiency: ";
	cin >> Y.effectiveness;
	while (cin.fail() || Y.effectiveness > 1 || Y.effectiveness < 0)
	{
		cout << "Please enter the correct value (in the range from 0 to 1): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> Y.effectiveness;
	}
	return Y;
}

PIPE DownloadPIPE()
{
	PIPE A;
	ifstream fin;
	fin.open("PIPE.txt", ios::in);
	if (fin.is_open())
	{
		fin >> A.title;
		fin >> A.lenght;
		fin >> A.diameter;
		fin >> A.repair;
		fin.close();	
	}
	return A;
}

STATION DownloadSTATION()
{
	STATION Y;
	ifstream fin;
	fin.open("STATION.txt", ios::in);
	if (fin.is_open())
	{
		fin >> Y.name;
		fin >> Y.workshop;
		fin >> Y.inOperation;
		fin >> Y.effectiveness;
		fin.close();
	}
	return Y;
}

void PrintPIPE(const PIPE& A)
{
	if (A.title != "Untitled")
	{
		cout << "Pipe kilometer mark: " << A.title << endl;
		cout << "Pipe lenght: " << A.lenght << endl;
		cout << "Pipe diameter: " << A.diameter << endl;
		if (A.repair == 0)//!!
		{
			cout << "Pipe sign 'under repair': " << "repairing" << endl;
		}
		else
		{
			cout << "Pipe sign 'under repair': " << "works" << endl;
		}
	}
	else
	{
		cout << "Pipe not added" << endl;
	}
}

void PrintSTATION(const STATION& Y)
{
	if (Y.name != "Untitled")
	{
		cout << "Name of the compressor station: " << Y.name << endl;
		cout << "Number of workshops in the compressor station: " << Y.workshop << endl;
		cout << "Number of workshops in operation at the compressos station: " << Y.inOperation << endl;
		cout << "Compressor station effiency: " << Y.effectiveness << endl;
	}
	else
	{
		cout << "Station not added" << endl;
	}
}

void SavePIPE(const PIPE& A)
{
	ofstream fout;
	fout.open("PIPE.txt", ios::out);
	if (fout.is_open() && A.title != "Untitled")
	{
		fout << A.title << endl;
		fout << A.lenght << endl;
		fout << A.diameter << endl;
		fout << A.repair;
		fout.close();
	}
}

void SaveSTATION(const STATION& Y)
{
	ofstream fout;
	fout.open("STATION.txt", ios::out);
	if (fout.is_open() && Y.name != "Untitled")
	{
		fout << Y.name << endl;
		fout << Y.workshop << endl;
		fout << Y.inOperation << endl;
		fout << Y.effectiveness;
		fout.close();
	}
}

void EditPIPE(PIPE &A)
{
	cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
	cin >> A.repair;
	while (cin.fail() || cin.peek() != '\n')
	{
		cout << "Please enter the correct value (0 or 1): ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> A.repair;
	}
}

void StartWorkshopsSTATION(STATION& Y)
{
	int i;
	cout << "Launch of compressor station workshops: ";
	cin >> i;
	while (cin.fail() || cin.peek() != '\n' || i <= 0 || i>(Y.workshop-Y.inOperation))
	{
		cout << "Please enter the correct value: ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> i;
	}
	Y.inOperation += i;
}

void StopWorkshopsSTATION(STATION& Y)
{
	int j;
	cout << "Stop of compressor station workshops: ";
	cin >> j;
	while (cin.fail() || cin.peek() != '\n' ||j <= 0||j>Y.inOperation)
	{
		cout << "Please enter the correct value: ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> j;
	}
	Y.inOperation -= j;
}

void MENU()
{
	cout << "1. Add a pipe" << endl
		<< "2. Add a compressor station" << endl
		<< "3. Viewing all objects" << endl
		<< "4. Edit a pipe" << endl
		<< "5. Starting the station workshop" << endl
		<< "6. Stopping the station workshop" << endl
		<< "7. Save to file" << endl
		<< "8. Upload from file" << endl
		<< "0. Exit" << endl;
}

int Choice()
{
	int i = 1;
	cin >> i;
	while (cin.fail() || cin.peek() != '\n')
	{
		cout << "Please enter the correct value: ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> i;
	}
	return i;
}

int main()
{
	PIPE One;
	STATION S1;
	while (1)
	{
		MENU();
		switch (Choice())
		{
		case 1:
		{
			One = NewPIPE();
			PrintPIPE(One);
			break;
		}
		case 2:
		{
			S1 = NewSTATION();
			PrintSTATION(S1);
			break;
		}
		case 3:
		{
			PrintPIPE(One);
			PrintSTATION(S1);
			break;
		}
		case 4:
		{
			EditPIPE(One);
			PrintPIPE(One);
			break;
		}
		case 5:
		{
			StartWorkshopsSTATION(S1);
			PrintSTATION(S1);
			break;
		}
		case 6:
		{
			StopWorkshopsSTATION(S1);
			PrintSTATION(S1);
			break;
		}
		case 7:
		{
			SavePIPE(One);
			SaveSTATION(S1);
			break;
		}
		case 8:
		{
			//DownloadPIPE();
			//DownloadSTATION();
			PrintPIPE(DownloadPIPE());
			PrintSTATION(DownloadSTATION());
			break;
		}
		case 0:
		{
			return 0;
		}
		default:
		{
			cout << "Wrong action" << endl;
		}
		
		}
	}
	
	return 0;
}