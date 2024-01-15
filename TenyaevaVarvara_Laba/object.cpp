#include "object.h"

int Object::idCounter = 0;

Object::Object(string title, int id)
{
    this->title = title;
    if (id == 0)
        this->id = nextId();
    else
        this->id = id;
}

int Object::nextId()
{
    loadId();
    idCounter++;
    saveId();
    return idCounter;
}

int Object::loadId()
{
    fstream fin;
    fin.open("last_id.txt", ios::in);
    if (fin.is_open()) {
        fin >> idCounter;
        if (fin.fail()) {
            idCounter = 10000;
        }
        fin.close();
    }
    else {
        idCounter = 10000;
    }
    return idCounter;
}

void Object::saveId()
{
    fstream fout;
    fout.open("last_id.txt", ios::out);
    if (fout.is_open())
    {
        fout << idCounter;
        fout.close();
    }
}