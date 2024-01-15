#pragma once

#include <string>
#include <fstream>

using namespace std;

class Object
{
protected:
    Object(string title, int id = 0);

    static int nextId();
    static int loadId();
    static void saveId();

public:
    string title;
    int id;

private:
    static int idCounter;
};