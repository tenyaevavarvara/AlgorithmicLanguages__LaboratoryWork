#pragma once
#include <vector>
#include <iostream>
#include "logger.h"

#define INPUT_LINE(in, str) getline(in>>std::ws, str); logValue(str);

template <typename T>
inline T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()	// check type
        || std::cin.peek() != '\n'	// is buffer empty (int/float check)
        || x < min || x > max)		// check range
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type number (" << min << "-" << max << "):";
    }
    logValue(x);
    return x;
}

inline int inputExistingId(std::vector<int>& ids)
{
    if (ids.empty()) return 0;
    int maxId = *(max_element(ids.begin(), ids.end()));
    while (true)
    {
        int id = GetCorrectNumber<int>(0, maxId);
        if (id == 0) return id;
        if (std::find(ids.begin(), ids.end(), id) != ids.end())
        {
            return id;
        }
        else std::cout << "ID doesn't exist, try again: ";
    }
}


inline std::string inputFilename()
{
    std::string filename;
    std::cout << "Input filename (enter for tenyaeva.txt): ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, filename);
    if (filename == "") filename = "tenyaeva.txt";
    logValue(filename);
    return filename;
}

inline void waitForEnter(bool ignore = true)
{
    std::string inputLine;
    std::cout << "Press enter to continue..." << std::endl;
    if (ignore) std::cin.ignore(10000, '\n');
    std::getline(std::cin, inputLine);
    return;
}