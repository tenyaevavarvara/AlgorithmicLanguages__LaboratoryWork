#pragma once

#include "math.h"
#include "object.h"
#include "utils.h"

using namespace std;

const int MAX_STATION_WORKSHOP = 100;

class Station : public Object
{
public:
    Station();
    Station(string title, int workshop, int inOperation, double effectiveness, int id = 0);

    static Station newStation();
    void startWorkshops();
    void stopWorkshops();
    void print();

public:
    int verticeId;
    int workshop;
    int inOperation;
    double effectiveness;
};
