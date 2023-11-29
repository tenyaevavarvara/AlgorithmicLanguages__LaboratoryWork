#include <iostream> 
#include <fstream>
#include <string>
#include <climits>
#include <vector>

using namespace std;

/* Functions declarations */
int InputInt(const char text[], int minValue, int maxValue);
string InputString(const char text[], int maxLength);
double InputDouble(const char text[], double minValue, double maxValue);

/* Structs */
struct PIPE
{
	string title = "Untitled";
	double length;
	int diameter;
	bool repair;

	void EditPIPE()
	{
		repair = InputInt("Pipe sign 'under repair' (0 - repairing, 1 - works): ", 0, 1);
	}

	void Print()
	{
		cout << "| Pipe kilometer mark: " << title << endl;
		cout << "| Pipe length: " << length << endl;
		cout << "| Pipe diameter: " << diameter << endl;
		cout << "| Pipe sign 'under repair': " << ((repair == 0) ? "repairing" : "works") << endl;
	}

	void PrintSimplified()
	{
		cout << "Kilometer mark: " << title << "; "
			<< "length: " << length << "; "
			<< "diameter: " << diameter << "; "
			<< ((repair == 0) ? "repairing" : "works") << endl;
	}
};

struct STATION
{
	string name = "Untitled";
	int workshop;
	int inOperation;
	double effectiveness;

	void StartWorkshopsSTATION()
	{
		int i;
		cout << "Launch of compressor station workshops: ";
		cin >> i;
		while (cin.fail() || cin.peek() != '\n' || i <= 0 || i > (workshop - inOperation))
		{
			cout << "Please enter the correct value: ";
			cin.clear();
			cin.ignore(1i64, '\n');
			cin >> i;
		}
		inOperation += i;
	}

	void StopWorkshopsSTATION()
	{
		int j;
		cout << "Stop of compressor station workshops: ";
		cin >> j;
		while (cin.fail() || cin.peek() != '\n' || j <= 0 || j > inOperation)
		{
			cout << "Please enter the correct value: ";
			cin.clear();
			cin.ignore(1i64, '\n');
			cin >> j;
		}
		inOperation -= j;
	}

	void Print()
	{
		cout << "| Name of the compressor station: " << name << endl;
		cout << "| Number of workshops in the compressor station: " << workshop << endl;
		cout << "| Number of workshops in operation at the compressos station: " << inOperation << endl;
		cout << "| Compressor station effiency: " << effectiveness << endl;
	}

	void PrintSimplified()
	{
		cout << "Name: " << name << "; "
			<< "workshops count: " << workshop << "; "
			<< "workshops in operation: " << inOperation << "; "
			<< "effectiveness: " << effectiveness << endl;
	}
};

/* Functions */
// TODO: Првоерять длину строки
string InputString(const char text[], int maxLength)
{
	string value;
	cout << text;
	cin.ignore();
	getline(cin, value);
	while (value.length() > maxLength || cin.fail() || value.length() == 0)
	{
		cout << text;
		getline(cin, value);
	}
	return value;
}

double InputDouble(const char text[], double minValue = DBL_MIN, double maxValue = DBL_MAX)
{
	double value;
	cout << text;
	cin >> value;
	while (cin.fail() || value < minValue || value > maxValue)
	{
		cout << text;
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> value;
	}
	return value;
}

int InputInt(const char text[], int minValue = INT_MIN, int maxValue = INT_MAX)
{
	int value;
	cout << text;
	cin >> value;
	while (cin.fail() || value < minValue || value > maxValue)
	{
		cout << text;
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> value;
	}
	return value;
}

PIPE NewPIPE()
{
	PIPE A;
	A.title = InputString("Pipe kilometer mark (name): ", 32);
	A.length = InputInt("Pipe length (metre): ", 0);
	A.diameter = InputInt("Pipe diameter (centimetre): ", 0);
	A.repair = InputInt("Pipe sign 'under repair' (0 - repairing, 1 - works): ", 0, 1);
	return A;
}

STATION NewSTATION()
{
	STATION Y;
	Y.name = InputString("Name of the compressor station: ", 32);
	Y.workshop = InputInt("Number of workshops in the compressor station: ", 0);
	Y.inOperation = InputInt("Number of workshops in operation at the compressors station: ", 0, Y.workshop);
	Y.effectiveness = InputDouble("Compressor station effiency: ", 0, 1);
	return Y;
}

void SaveObjects(vector<PIPE>& pipes, vector<STATION>& stations)
{
	ofstream fout;
	fout.open("tenyaeva.txt", ios::out);
	if (fout.is_open())
	{
		fout << pipes.size() << endl;
		for (int i = 0; i < pipes.size(); i++)
		{
			fout << pipes[i].title << endl;
			fout << pipes[i].length << endl;
			fout << pipes[i].diameter << endl;
			fout << pipes[i].repair << endl;
		}
		fout << stations.size() << endl;
		for (int i = 0; i < stations.size(); i++)
		{
			fout << stations[i].name << endl;
			fout << stations[i].workshop << endl;
			fout << stations[i].inOperation << endl;
			fout << stations[i].effectiveness << endl;
		}
		fout.close();
	}
}

void DownloadObjects(vector<PIPE>& pipes, vector<STATION>& stations)
{
	ifstream fin;
	fin.open("tenyaeva.txt", ios::in);
	if (fin.is_open())
	{
		int size;
		fin >> size;
		if (fin.fail())
		{
			fin.close();
			return;
		}
		for (int i = 0; i < size; i++)
		{
			PIPE pipe;
			fin >> pipe.title;
			fin >> pipe.length;
			fin >> pipe.diameter;
			fin >> pipe.repair;
			pipes.push_back(pipe);
		}
		fin >> size;
		if (fin.fail())
		{
			fin.close();
			return;
		}
		for (int i = 0; i < size; i++)
		{
			STATION station;
			fin >> station.name;
			fin >> station.workshop;
			fin >> station.inOperation;
			fin >> station.effectiveness;
			stations.push_back(station);
		}
		fin.close();
	}
}

void PrintMENU()
{
	cout << "[MENU]" << endl
		<< "1. Add a pipe" << endl
		<< "2. Add a compressor station" << endl
		<< "3. Viewing all objects" << endl
		<< "4. Edit a pipe" << endl
		<< "5. Starting the station workshop" << endl
		<< "6. Stopping the station workshop" << endl
		<< "7. Save to file" << endl
		<< "8. Upload from file" << endl
		<< "0. Exit" << endl << endl;
}

int main()
{
	vector<PIPE> pipes;
	vector<STATION> stations;

	while (1)
	{
		cout << endl;
		PrintMENU();
		int i = InputInt("Select a menu item: ", 0, 8);
		cout << endl;
		switch (i)
		{
			/* Add pipe */
		case 1:
		{
			cout << "[Add pipe]" << endl;
			PIPE pipe = NewPIPE();
			pipes.push_back(pipe);
			cout << endl << "Added new pipe:" << endl;
			pipe.Print();
			break;
		}
		/* Add a compressor station */
		case 2:
		{
			cout << "[Add a compressor station]" << endl;
			STATION station = NewSTATION();
			stations.push_back(station);
			cout << endl << "Added new compressor station:" << endl;
			station.Print();
			break;
		}
		/* Viewing all objects */
		case 3:
		{
			cout << "[Viewing all objects]" << endl;
			if (pipes.size() == 0 and stations.size() == 0) {
				cout << "No objects" << endl;
			}
			if (pipes.size() > 0)
			{
				cout << "Pipes:" << endl;
				for (int i = 0; i < pipes.size(); i++)
				{
					cout << '[' << i + 1 << "] ";
					pipes[i].PrintSimplified();
				}
			}
			if (stations.size() > 0)
			{
				cout << "Stations:" << endl;
				for (int i = 0; i < stations.size(); i++)
				{
					cout << '[' << i + 1 << "] ";
					stations[i].PrintSimplified();
				}
			}
			break;
		}
		/* Edit a pipe */
		case 4:
		{
			cout << "[Edit a pipe]" << endl;
			if (pipes.size() == 0)
			{
				cout << "There are no pipes" << endl;
				break;
			}
			cout << "Pipes:" << endl;
			for (int i = 0; i < pipes.size(); i++)
			{
				cout << '[' << i + 1 << "] ";
				pipes[i].PrintSimplified();
			}
			int i = InputInt("Choose pipe number: ", 1, pipes.size());
			pipes[i - 1].EditPIPE();
			pipes[i - 1].Print();
			break;
		}
		/* Starting the station workshop */
		case 5:
		{
			cout << "[Starting the station workshop]" << endl;
			if (stations.size() == 0)
			{
				cout << "There are no stations" << endl;
				break;
			}
			cout << "Stations:" << endl;
			for (int i = 0; i < stations.size(); i++)
			{
				cout << '[' << i + 1 << "] ";
				stations[i].PrintSimplified();
			}
			int i = InputInt("Station number to start: ", 1, pipes.size());
			stations[i - 1].StartWorkshopsSTATION();
			stations[i - 1].Print();
			break;
		}
		/* Stopping the station workshop */
		case 6:
		{
			cout << "[Stopping the station workshop]" << endl;
			if (stations.size() == 0)
			{
				cout << "There are no stations" << endl;
				break;
			}
			cout << "Stations:" << endl;
			for (int i = 0; i < stations.size(); i++)
			{
				cout << '[' << i + 1 << "] ";
				stations[i].PrintSimplified();
			}
			int i = InputInt("Station number to stop: ", 1, pipes.size());
			stations[i - 1].StopWorkshopsSTATION();
			stations[i - 1].Print();
			break;
		}
		/* Save to file */
		case 7:
		{
			cout << "[Save to file]" << endl;
			SaveObjects(pipes, stations);
			break;
		}
		/* Upload from file */
		case 8:
		{
			cout << "[Upload from file]" << endl;
			pipes.clear();
			stations.clear();
			DownloadObjects(pipes, stations);
			cout << "Loaded pipes:" << endl;
			for (int i = 0; i < pipes.size(); i++)
			{
				cout << "| " << i + 1 << " ";
				pipes[i].PrintSimplified();
			}
			cout << "Loaded stations:" << endl;
			for (int i = 0; i < stations.size(); i++)
			{
				cout << "| " << i + 1 << " ";
				stations[i].PrintSimplified();
			}
			break;
		}
		/* Exit */
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