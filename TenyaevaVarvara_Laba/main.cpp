#include <iostream> 
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include "utils.h"

using namespace std;

const int MAX_PIPE_LENGTH = 1000;
const int MAX_PIPE_DIAMETER = 1000;
const int MAX_STATION_WORKSHOP = 1000;

/* Structs */
struct PIPE
{
	string title = "Untitled";
	double length;
	int diameter;
	bool repair;

	void EditPIPE()
	{
		cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
		repair = GetCorrectNumber<int>(0, 1);
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
		if (workshop == inOperation)
		{
			cout << "All workshops are in operation" << endl;
			return;
		}

		cout << "Launch of compressor station workshops: ";
		int i = GetCorrectNumber<int>(0, (workshop - inOperation));
		inOperation += i;
		cout << "Workshops launched: " << i << "; total launched:" << inOperation << endl;
	}

	void StopWorkshopsSTATION()
	{
		if (inOperation == 0)
		{
			cout << "All workshops are stopped" << endl;
			return;
		}
		cout << "Stop of compressor station workshops: ";
		int i = GetCorrectNumber<int>(0, inOperation);
		inOperation -= i;
		cout << "Workshops stopped: " << i << "; total launched:" << inOperation << endl;
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

PIPE NewPIPE()
{
	PIPE A;
	cout << "Pipe kilometer mark (name): ";
	INPUT_LINE(cin, A.title);
	cout << "Pipe length (metre): ";
	A.length = GetCorrectNumber<int>(1, MAX_PIPE_LENGTH);
	cout << "Pipe diameter (centimetre): ";
	A.diameter = GetCorrectNumber<int>(1, MAX_PIPE_DIAMETER);
	cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
	A.repair = GetCorrectNumber<int>(0, 1);
	return A;
}

STATION NewSTATION()
{
	STATION Y;
	cout << "Name of the compressor station: ";
	INPUT_LINE(cin, Y.name);
	cout << "Number of workshops in the compressor station: ";
	Y.workshop = GetCorrectNumber<int>(1, MAX_STATION_WORKSHOP);
	cout << "Number of workshops in operation at the compressors station: ";
	Y.inOperation = GetCorrectNumber<int>(0, Y.workshop);
	cout << "Compressor station effiency: ";
	Y.effectiveness = GetCorrectNumber<double>(0, 1);
	return Y;
}

void WaitForENTER()
{
	string inputLine;
	cout << "Press enter to continue..." << endl;
	std::cin.ignore(10000, '\n');
	getline(cin, inputLine);
}


void DownloadPipes(vector<PIPE>& pipes) {
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
			//fin >> ws;
			//getline(fin, pipe.title);
			//fin >> pipe.title;
			INPUT_LINE(fin, pipe.title);
			fin >> pipe.length;
			fin >> pipe.diameter;
			fin >> pipe.repair;
			pipes.push_back(pipe);
		}
	}
}

void DownloadStations(vector<STATION>& stations) {
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
		for (int i = 0; i < size * 4 + 1; ++i) {
			string str;
			getline(fin, str);
		}
		fin >> size;
		for (int i = 0; i < size; i++)
		{
			STATION station;
			//fin >> ws;
			//getline(fin, station.name);
			//fin >> station.name;
			INPUT_LINE(fin, station.name);
			fin >> station.workshop;
			fin >> station.inOperation;
			fin >> station.effectiveness;
			stations.push_back(station);
		}
	}
}

void SavePipes(vector<PIPE>& pipes) {
	vector<STATION> stations;
	DownloadStations(stations);
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
	}
	fout.close();
}

void SaveStations(vector<STATION>& stations) {
	vector<PIPE> pipes;
	DownloadPipes(pipes);
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
	}
	fout.close();
}

void PrintMENU()
{
	cout << "[MENU]" << endl
		<< "0.  Exit" << endl
		<< "1.  Add a pipe" << endl
		<< "2.  Add a compressor station" << endl
		<< "3.  Viewing all objects" << endl
		<< "4.  Edit a pipe" << endl
		<< "5.  Starting the station workshop" << endl
		<< "6.  Stopping the station workshop" << endl
		<< "7.  Save pipes to file" << endl
		<< "8.  Load pipes from file" << endl
		<< "9.  Save stations to file" << endl
		<< "10. Load stations from file" << endl << endl;
}

int main()
{
	vector<PIPE> pipes;
	vector<STATION> stations;

	while (1)
	{
		system("cls");
		PrintMENU();
		cout << "Select a menu item: ";
		int i = GetCorrectNumber<int>(0, 10);
		switch (i)
		{
			/* Add pipe */
		case 1:
		{
			system("cls");
			cout << "[Add pipe]" << endl;
			PIPE pipe = NewPIPE();
			pipes.push_back(pipe);
			cout << endl << "Added new pipe:" << endl;
			pipe.Print();
			WaitForENTER();
			break;
		}
		/* Add a compressor station */
		case 2:
		{
			system("cls");
			cout << "[Add a compressor station]" << endl;
			STATION station = NewSTATION();
			stations.push_back(station);
			cout << endl << "Added new compressor station:" << endl;
			station.Print();
			WaitForENTER();
			break;
		}
		/* Viewing all objects */
		case 3:
		{
			system("cls");
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
			WaitForENTER();
			break;
		}
		/* Edit a pipe */
		case 4:
		{
			system("cls");
			cout << "[Edit a pipe]" << endl;
			if (pipes.size() == 0)
			{
				cout << "There are no pipes" << endl;
				WaitForENTER();
				break;
			}
			cout << "Pipes:" << endl;
			for (int i = 0; i < pipes.size(); i++)
			{
				cout << '[' << i + 1 << "] ";
				pipes[i].PrintSimplified();
			}
			cout << "Choose pipe number: ";
			int i = GetCorrectNumber<int>(1, pipes.size());
			pipes[i - 1].EditPIPE();
			pipes[i - 1].Print();
			WaitForENTER();
			break;
		}
		/* Starting the station workshop */
		case 5:
		{
			system("cls");
			cout << "[Starting the station workshop]" << endl;
			if (stations.size() == 0)
			{
				cout << "There are no stations!" << endl;
				WaitForENTER();
				break;
			}
			cout << "Stations:" << endl;
			for (int i = 0; i < stations.size(); i++)
			{
				cout << '[' << i + 1 << "] ";
				stations[i].PrintSimplified();
			}
			cout << "Station number to start: ";
			int i = GetCorrectNumber<int>(1, stations.size());
			stations[i - 1].StartWorkshopsSTATION();
			WaitForENTER();
			break;
		}
		/* Stopping the station workshop */
		case 6:
		{
			system("cls");
			cout << "[Stopping the station workshop]" << endl;
			if (stations.size() == 0)
			{
				cout << "There are no stations!" << endl;
				WaitForENTER();
				break;
			}
			cout << "Stations:" << endl;
			for (int i = 0; i < stations.size(); i++)
			{
				cout << '[' << i + 1 << "] ";
				stations[i].PrintSimplified();
			}
			cout << "Station number to stop: ";
			int i = GetCorrectNumber<int>(1, stations.size());
			stations[i - 1].StopWorkshopsSTATION();
			WaitForENTER();
			break;
		}
		/* Save pipes to file */
		case 7:
		{
			system("cls");
			cout << "[Save pipes to file]" << endl;
			SavePipes(pipes);
			cout << "Pipes successfully saved!" << endl;
			WaitForENTER();
			break;
		}
		/* Load pipes from file */
		case 8:
		{
			system("cls");
			cout << "[Load pipes from file]" << endl;
			pipes.clear();
			DownloadPipes(pipes);
			cout << "Loaded pipes:" << endl;
			for (int i = 0; i < pipes.size(); i++)
			{
				cout << "| " << i + 1 << " ";
				pipes[i].PrintSimplified();
			}
			WaitForENTER();
			break;
		}
		/* Save stations to file */
		case 9:
		{
			system("cls");
			cout << "[Save stations to file]" << endl;
			SaveStations(stations);
			cout << "Stations successfully saved!" << endl;
			WaitForENTER();
			break;
		}
		/* Load stations from file */
		case 10:
		{
			system("cls");
			cout << "[Load stations from file]" << endl;
			stations.clear();
			DownloadStations(stations);
			cout << "Loaded stations:" << endl;
			for (int i = 0; i < stations.size(); i++)
			{
				cout << "| " << i + 1 << " ";
				stations[i].PrintSimplified();
			}
			WaitForENTER();
			break;
		}
		/* Exit */
		case 0:
		{
			return 0;
		}
		default:
		{
			system("cls");
			cout << "Wrong action!" << endl;
			WaitForENTER();
			break;
		}
		}
	}

	return 0;
}