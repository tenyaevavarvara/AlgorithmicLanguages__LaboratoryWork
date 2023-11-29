#include <iostream> 
#include <fstream>
#include <string>
#include <climits>
#include <vector>

using namespace std;

const int MAX_PIPE_NAME_LENGTH = 32;
const int MAX_PIPE_LENGTH = 1000;
const int MAX_PIPE_DIAMETER = 1000;
const int MAX_STATION_NAME_LENGTH = 32;
const int MAX_STATION_WORKSHOP = 1000;

/* Functions declarations */
string InputString(const char text[], int maxLength);
double InputDouble(const char text[], double minValue, double maxValue);
int InputInt(const char text[], int minValue, int maxValue);

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
		if (workshop == inOperation)
		{
			cout << "All workshops are in operation" << endl;
			return;
		}
		int i = InputInt("Launch of compressor station workshops: ", 0, (workshop - inOperation));
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
		int i = InputInt("Stop of compressor station workshops: ", 0, inOperation);
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

/* Functions */
string InputString(const char text[], int maxLength)
{
	string value;
	cout << text;
	getline(cin, value);
	while (value.length() > maxLength || cin.fail() || value.length() == 0)
	{
		cout << text;
		getline(cin, value);
		if (value.length() > maxLength)
		{
			cout << "! Please enter a string with length less than " << maxLength << " !" << endl;
		}
		if (value.length() == 0)
		{
			cout << "! Please enter non empty string !" << endl;
		}
	}
	return value;
}

double InputDouble(const char text[], double minValue = DBL_MIN, double maxValue = DBL_MAX)
{
	double value;
	string inputLine;
	bool validInput = false;

	do {
		cout << text;
		getline(cin, inputLine);

		try
		{
			value = stod(inputLine);
			validInput = true;
		}
		catch (invalid_argument&)
		{
			validInput = false;
		}
		catch (out_of_range&)
		{
			validInput = false;
		}

		if (!validInput)
		{
			cout << "! Please enter a valid double value !" << endl;
		} else if (value < minValue || value > maxValue)
		{
			cout << "! Please enter a value between " << minValue << " and " << maxValue << " !" << endl;
		}
	} while (!validInput || value < minValue || value > maxValue);

	return value;
}

int InputInt(const char text[], int minValue = INT_MIN, int maxValue = INT_MAX)
{
	int value;
	string inputLine;
	bool validInput = false;

	do {
		cout << text;
		getline(cin, inputLine);

		try
		{
			value = stoi(inputLine);
			validInput = true;
		}
		catch (invalid_argument&)
		{
			validInput = false;
		}
		catch (out_of_range&)
		{
			validInput = false;
		}

		if (!validInput)
		{
			cout << "! Please enter a valid integer value !" << endl;
		}
		else if (value < minValue || value > maxValue)
		{
			cout << "! Please enter a value between " << minValue << " and " << maxValue << " !" << endl;
		}
	} while (!validInput || value < minValue || value > maxValue);

	return value;
}

PIPE NewPIPE()
{
	PIPE A;
	A.title = InputString("Pipe kilometer mark (name): ", MAX_PIPE_NAME_LENGTH);
	A.length = InputInt("Pipe length (metre): ", 1, MAX_PIPE_LENGTH);
	A.diameter = InputInt("Pipe diameter (centimetre): ", 1, MAX_PIPE_DIAMETER);
	A.repair = InputInt("Pipe sign 'under repair' (0 - repairing, 1 - works): ", 0, 1);
	return A;
}

STATION NewSTATION()
{
	STATION Y;
	Y.name = InputString("Name of the compressor station: ", MAX_STATION_NAME_LENGTH);
	Y.workshop = InputInt("Number of workshops in the compressor station: ", 1, MAX_STATION_WORKSHOP);
	Y.inOperation = InputInt("Number of workshops in operation at the compressors station: ", 0, Y.workshop);
	Y.effectiveness = InputDouble("Compressor station effiency: ", 0, 1);
	return Y;
}

void WaitForENTER()
{
	string inputLine;
	cout << "Press enter to continue..." << endl;
	getline(cin, inputLine);
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
		system("cls");
		PrintMENU();
		int i = InputInt("Select a menu item: ", 0, 8);
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
			int i = InputInt("Choose pipe number: ", 1, pipes.size());
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
			int i = InputInt("Station number to start: ", 1, stations.size());
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
			int i = InputInt("Station number to stop: ", 1, stations.size());
			stations[i - 1].StopWorkshopsSTATION();
			WaitForENTER();
			break;
		}
		/* Save to file */
		case 7:
		{
			system("cls");
			cout << "[Save to file]" << endl;
			SaveObjects(pipes, stations);
			cout << "Objects successfully saved!" << endl;
			WaitForENTER();
			break;
		}
		/* Upload from file */
		case 8:
		{
			system("cls");
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
		}
		}
	}

	return 0;
}