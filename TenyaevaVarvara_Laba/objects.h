#include <iostream> 
#include <fstream>
#include <string>
#include <climits>
#include <unordered_map>

#include "utils.h"
#include <vector>

using namespace std;

const int MAX_STATION_WORKSHOP = 1000;
const int MAX_PIPE_LENGTH = 1000;
const int MAX_PIPE_DIAMETER = 1000;

class Object 
{
protected:
    Object(string title, int id = 0) 
    {
        this->title = title;
        if (id == 0) 
            this->id = nextId();
        else 
            this->id = id;
    }

    static int nextId() 
    {
        loadId();
        idCounter++;
        saveId();
        return idCounter;
    }

    static int loadId() 
    {
        fstream fin;
        fin.open("last_id.txt", ios::in);
        if (fin.is_open()) {
            fin >> idCounter;
            if (fin.fail()) {
                idCounter = 10000;
            }
            fin.close();
        } else {
            idCounter = 1000;
        }
        return idCounter;
    }

    static void saveId() 
    {
        fstream fout;
        fout.open("last_id.txt", ios::out);
        if (fout.is_open()) 
        {
            fout << idCounter;
            fout.close();
        }
    }

public:
    string title;
    int id;

private:
    inline static int idCounter = 0;
};

class Pipe : public Object 
{
public:
    Pipe() 
        : Object("Default Pipe", -1) {
        this->length = 0;
        this->diameter = 0;
        this->repair = false;
    }

    Pipe(string title, int length, int diameter, int repair, int id = 0) 
        : Object(title, id) 
    {
        this->length = length;
        this->diameter = diameter;
        this->repair = repair;
    }

    static Pipe newPipe()
    {
        string title;
        double length;
        int diameter;
        bool repair;
        cout << "Pipe kilometer mark (name): ";
        INPUT_LINE(cin, title);
        cout << "Pipe length (metre): ";
        length = GetCorrectNumber<int>(1, MAX_PIPE_LENGTH);
        cout << "Pipe diameter (centimetre): ";
        diameter = GetCorrectNumber<int>(1, MAX_PIPE_DIAMETER);
        cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
        repair = GetCorrectNumber<int>(0, 1);
        return Pipe(title, length, diameter, repair);
    }

    void print() {
        cout << "[" << id << "] "
            << "Kilometer mark: " << title << "; "
            << "Length: " << length << "; "
            << "Diameter: " << diameter << "; "
            << ((repair == 0) ? "Repairing" : "Works") << endl;
    }

    void edit()
	{
		cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
		repair = GetCorrectNumber<int>(0, 1);
	}

public:
    double length = 0;
    int diameter = 0;
    bool repair = 0;
};

class Station : public Object 
{
public:
    Station() 
        : Object("Default Station", -1) 
    {
        this->workshop = 0;
        this->inOperation = 0;
        this->effectiveness = 0.0;
    }

    Station(string title, int workshop, int inOperation, double effectiveness, int id = 0) 
        : Object(title, id) 
    {
        this->workshop = workshop;
        this->inOperation = inOperation;
        this->effectiveness = effectiveness;
    }

    static Station newStation()
    {
        string title;
        int workshop;
        int inOperation;
        double effectiveness;
        cout << "Name of the compressor station: ";
        INPUT_LINE(cin, title);
        cout << "Number of workshops in the compressor station: ";
        workshop = GetCorrectNumber<int>(1, MAX_STATION_WORKSHOP);
        cout << "Number of workshops in operation at the compressors station: ";
        inOperation = GetCorrectNumber<int>(0, workshop);
        cout << "Compressor station effiency: ";
        effectiveness = GetCorrectNumber<double>(0, 1);
        return Station(title, workshop, inOperation, effectiveness);
    }

    void startWorkshops()
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

	void stopWorkshops()
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

    void print() 
    {
        cout << "[" << id << "] "
            << "Station Name: " << title << "; "
            << "Workshops: " << workshop << "; "
            << "In operation: " << inOperation << "; "
            << "Effiency: " << effectiveness << endl;
    }

public:
    int workshop;
    int inOperation;
    double effectiveness;
};

void downloadStations(string filename, unordered_map<int, Station>& stations) 
{
    ifstream fin(filename);
    if (fin.is_open()) 
    {
        int size;
        fin >> size;
        if (fin.fail()) 
        {
            fin.close();
            return;
        }
        // Пропускаем лишние строки
        for (int i = 0; i < size * 5 + 1; ++i) 
        {
            string str;
            getline(fin, str);
        }
        fin >> size;
        if (fin.fail()) {
            fin.close();
            return;
        }
        for (int i = 0; i < size; i++) 
        {
            int id, workshop, inOperation;
            double effectiveness;
            string title;
            fin >> id;
            INPUT_LINE(fin, title);
            fin >> workshop >> inOperation >> effectiveness;
            stations[id] = Station(title, workshop, inOperation, effectiveness, id);
        }
        fin.close();
    }
}

void downloadPipes(string filename, unordered_map<int, Pipe>& pipes) 
{
    ifstream fin(filename);
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
            int id, diameter;
            string title;
            double length;
            bool repair;
            fin >> id;
            INPUT_LINE(fin, title);
            fin >> length >> diameter >> repair;
            pipes[id] = Pipe(title, length, diameter, repair, id);
        }
        fin.close();
    }
}

void saveStations(string filename, unordered_map<int, Station>& stations) 
{
    unordered_map<int, Pipe> pipes;
    downloadPipes(filename, pipes);
    ofstream fout(filename);
    if (fout.is_open()) 
    {
        fout << pipes.size() << endl;
        for (const auto& pair : pipes) 
        {
            const Pipe& pipe = pair.second;
            fout << pipe.id << endl;
            fout << pipe.title << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.repair << endl;
        }
        fout << stations.size() << endl;
        for (const auto& pair : stations) 
        {
            const Station& station = pair.second;
            fout << station.id << endl;
            fout << station.title << endl;
            fout << station.workshop << endl;
            fout << station.inOperation << endl;
            fout << station.effectiveness << endl;
        }
        fout.close();
    }
}

void savePipes(string filename, unordered_map<int, Pipe>& pipes) 
{
    unordered_map<int, Station> stations;
    downloadStations(filename, stations);
    ofstream fout(filename);
    if (fout.is_open()) 
    {
        fout << pipes.size() << endl;
        for (const auto& pair : pipes) 
        {
            const Pipe& pipe = pair.second;
            fout << pipe.id << endl;
            fout << pipe.title << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.repair << endl;
        }
        fout << stations.size() << endl;
        for (const auto& pair : stations)
        {
            const Station& station = pair.second;
            fout << station.id << endl;
            fout << station.title << endl;
            fout << station.workshop << endl;
            fout << station.inOperation << endl;
            fout << station.effectiveness << endl;
        }
        fout.close();
    }
}

vector<int> findPipesByString(const unordered_map<int, Pipe>& pipes, const string& str) 
{
    vector<int> ids;
    for (const auto& pair : pipes) 
    {
        if (pair.second.title.find(str) != string::npos) 
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}

vector<int> findPipesByRepair(const unordered_map<int, Pipe>& pipes, bool repair) 
{
    vector<int> ids;
    for (const auto& pair : pipes) 
    {
        if (pair.second.repair == repair) 
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}
    
vector<int> findStationsByString(const unordered_map<int, Station>& stations, const string& str) 
{
    vector<int> ids;
    for (const auto& pair : stations) 
    {
        if (pair.second.title.find(str) != string::npos) 
        {
            ids.push_back(pair.first);
        }
    }   
    return ids;
}

vector<int> findStationsByFreeWorkshopProcent(const unordered_map<int, Station>& stations, int procent)
{
    vector<int> ids;
    for (const auto& pair : stations)
    {
        if ((pair.second.workshop - pair.second.inOperation) / (float)pair.second.workshop >= procent / 100.0)
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}