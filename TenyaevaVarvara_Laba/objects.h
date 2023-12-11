#include <iostream> 
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include "utils.h"

using namespace std;

const int MAX_STATION_WORKSHOP = 1000;
const int MAX_PIPE_LENGTH = 1000;
const int MAX_PIPE_DIAMETER = 1000;

void DownloadPipes(string filename, vector<Pipe>& pipes);
void DownloadStations(string filename, vector<Station>& stations);
void SavePipes(string filename, vector<Pipe>& pipes);
void SaveStations(string filename, vector<Station>& stations);

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
        return ++idCounter;
    }

    static int loadId()
    {
        fstream fin;
        fin.open("last_id.txt", ios::in);
        if (fin.is_open()) {
            fin >> idCounter;
            if (fin.fail()) {
                idCounter = 1000000;
            }
            fin.close();
        }
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

public:
    double length = 0;
    int diameter = 0;
    bool repair = 0;
};

class Station : public Object
{
public:
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

public:
    int workshop;
    int inOperation;
    double effectiveness;
};

void DownloadStations(string filename, vector<Station>& stations)
{
    ifstream fin;
    fin.open(filename, ios::in);
    if (fin.is_open())
    {
        int size;
        fin >> size;
        if (fin.fail())
        {
            fin.close();
            return;
        }
        for (int i = 0; i < size * 4 + 1; ++i)
        {
            string str;
            getline(fin, str);
        }
        fin >> size;
        for (int i = 0; i < size; i++)
        {
            string title;
            int id, workshop, inOperation;
            double effectiveness;
            fin >> id >> title >> workshop >> inOperation >> effectiveness;
            stations.push_back(Station(title, workshop, inOperation, effectiveness, id));
        }
    }
}

void SaveStations(string filename, vector<Station>& stations)
{
    vector<Pipe> pipes;
    DownloadPipes(filename, pipes);
    ofstream fout;
    fout.open(filename, ios::out);
    if (fout.is_open())
    {
        fout << pipes.size() << endl;
        for (auto pipe : pipes)
        {
            fout << pipe.id << " ";
            fout << pipe.title << " ";
            fout << pipe.length << " ";
            fout << pipe.diameter << " ";
            fout << pipe.repair << endl;
        }
        fout << stations.size() << endl;
        for (auto station : stations)
        {
            fout << station.id << " ";
            fout << station.title << " ";
            fout << station.workshop << " ";
            fout << station.inOperation << " ";
            fout << station.effectiveness << endl;
        }
    }
    fout.close();
}

void DownloadPipes(string filename, vector<Pipe>& pipes)
{
    ifstream fin;
    fin.open(filename, ios::in);
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
            fin >> id >> title >> length >> diameter >> repair;
            pipes.push_back(Pipe(title, length, diameter, repair, id));
        }
    }
}

void SavePipes(string filename, vector<Pipe>& pipes)
{
    vector<Station> stations;
    DownloadStations(filename, stations);
    ofstream fout;
    fout.open(filename, ios::out);
    if (fout.is_open())
    {
        fout << pipes.size() << endl;
        for (auto pipe : pipes)
        {
            fout << pipe.id << " ";
            fout << pipe.title << " ";
            fout << pipe.length << " ";
            fout << pipe.diameter << " ";
            fout << pipe.repair << " ";
        }
        fout << stations.size() << endl;
        for (auto station : stations)
        {
            fout << station.id << " ";
            fout << station.title << " ";
            fout << station.workshop << " ";
            fout << station.inOperation << " ";
            fout << station.effectiveness << endl;
        }
    }
    fout.close();
}