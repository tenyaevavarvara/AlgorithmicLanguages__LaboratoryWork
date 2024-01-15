#include "station.h"

Station::Station()
    : Object("Default Station", -1)
{
    this->workshop = 0;
    this->inOperation = 0;
    this->effectiveness = 0.0;
}

Station::Station(string title, int workshop, int inOperation, double effectiveness, int id)
    : Object(title, id)
{
    this->workshop = workshop;
    this->inOperation = inOperation;
    this->effectiveness = effectiveness;
}

Station Station::newStation()
{
    string title;
    int workshop;
    int inOperation = 0;
    double effectiveness;
    cout << "Name of the compressor station: ";
    INPUT_LINE(cin, title);
    cout << "Number of workshops in the compressor station: ";
    workshop = GetCorrectNumber<int>(1, MAX_STATION_WORKSHOP);
    cout << "Compressor station effiency: ";
    effectiveness = GetCorrectNumber<double>(0, 1);
    return Station(title, workshop, inOperation, effectiveness);
}

void Station::startWorkshops()
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

void Station::stopWorkshops()
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

void Station::print()
{
    cout << "[" << id << "] "
        << "Station Name: " << title << "; "
        << "Workshops: " << workshop << "; "
        << "In operation: " << inOperation << "; "
        << "Effiency: " << effectiveness << endl;
}