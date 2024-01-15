#include "pipe.h"

Pipe::Pipe()
    : Object("Default Pipe", -1)
{
    this->length = 0;
    this->diameter = 0;
    this->repair = false;
}

Pipe::Pipe(string title, int length, int diameter, int repair, int id, int first, int second)
    : Object(title, id)
{
    this->length = length;
    this->diameter = diameter;
    this->repair = repair;
    this->nodes.first = first;
    this->nodes.second = second;
}

Pipe Pipe::newPipe(int diameter)
{
    string title;
    double length;
    bool repair;
    cout << "Pipe kilometer mark (name): ";
    INPUT_LINE(cin, title);
    cout << "Pipe length (metre): ";
    length = GetCorrectNumber<int>(1, MAX_PIPE_LENGTH);
    if (diameter == -1) {
        cout << "Pipe diameter (500, 700, 1000 or 1400 mm): ";
        diameter = GetCorrectNumber<int>(1, MAX_PIPE_DIAMETER);
        while (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
            cout << "Diameter should be 500, 700, 1000 or 1400 mm!" << endl;
            cout << "Pipe diameter (500, 700, 1000 or 1400 mm): ";
            diameter = GetCorrectNumber<int>(1, MAX_PIPE_DIAMETER);
        }
    }
    else {
        cout << "Pipe diameter (500, 700, 1000 or 1400 mm): " << diameter << endl;
    }
    cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
    repair = GetCorrectNumber<int>(0, 1);
    return Pipe(title, length, diameter, repair);
}

void Pipe::print()
{
    cout << "[" << id << "] "
        << "Kilometer mark: " << title << "; "
        << "Length: " << length << "; "
        << "Diameter: " << diameter << "; "
        << ((repair == 0) ? "Repairing" : "Works") << "; "
        << "Weight: " << getWeight() << "; "
        << "Nodes: " << nodes.first << " - " << nodes.second << endl;
}

int Pipe::getWeight()
{
    return sqrt(std::pow(diameter / 100.0, 5) / (double)length) * 10;
}

void Pipe::edit()
{
    cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
    repair = GetCorrectNumber<int>(0, 1);
}