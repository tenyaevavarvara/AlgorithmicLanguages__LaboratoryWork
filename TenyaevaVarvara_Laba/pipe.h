#pragma once

#include <math.h>

#include "object.h"
#include "utils.h"

using namespace std;

const int MAX_PIPE_LENGTH = 1000;
const int MAX_PIPE_DIAMETER = 1400;

class Pipe : public Object
{
public:
    Pipe();
    Pipe(string title, int length, int diameter, int repair, int id = 0, int first = 0, int second = 0);

    static Pipe newPipe(int diameter = -1);

    void edit();
    void print();
    int getWeight();

public:
    pair<int, int> nodes;
    double length = 0;
    int diameter = 0;
    bool repair = 0;
};