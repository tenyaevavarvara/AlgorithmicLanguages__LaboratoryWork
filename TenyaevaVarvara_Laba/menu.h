#include <iostream>
#include <unordered_map>

#include "objects.h"
#include "utils.h"
#include "logger.h"

using namespace std;

string inputFilename()
{
    string filename;
    cout << "Input filename (enter for tenyaeva.txt): ";
    std::cin.ignore(10000, '\n');
    getline(cin, filename);
    if (filename == "") filename = "tenyaeva.txt";
    return filename;
}

void waitForEnter(bool ignore = true)
{
    string inputLine;
    cout << "Press enter to continue..." << endl;
    if (ignore) std::cin.ignore(10000, '\n');
    getline(cin, inputLine);
    return;
}

void printMenu()
{
    cout << "[MENU]" << endl
        << "0.  Exit" << endl
        << "1.  Add a pipe" << endl
        << "2.  Add a compressor station" << endl
        << "3.  Viewing all objects" << endl
        << "4.  Delete object" << endl
        << "5.  Edit a pipe" << endl
        << "6.  Starting the station workshop" << endl
        << "7.  Stopping the station workshop" << endl
        << "8.  Save pipes to file" << endl
        << "9.  Load pipes from file" << endl
        << "10. Save stations to file" << endl
        << "11. Load stations from file" << endl
        << "12. Find pipes" << endl
        << "13. Find stations" << endl << endl;
}

void mainLoop() {
    unordered_map<int, Pipe> pipesMap;
    unordered_map<int, Station> stationsMap;
    while (1)
    {
        system("cls");
        printMenu();
        cout << "Select a menu item: ";
        int i = GetCorrectNumber<int>(0, 13);
        switch (i)
        {
            /* Add pipe */
        case 1:
        {
            system("cls");
            cout << "[Add pipe]" << endl;
            Pipe pipe = Pipe::newPipe();
            pipesMap[pipe.id] = pipe;
            cout << endl << "Added new pipe:" << endl;
            log("Added new pipe: " + to_string(pipe.id));
            pipe.print();
            waitForEnter();
            break;
        }
        /* Add a compressor station */
        case 2:
        {
            system("cls");
            cout << "[Add a compressor station]" << endl;
            Station station = Station::newStation();
            stationsMap[station.id] = station;
            cout << endl << "Added new compressor station:" << endl;
            log("Added new compressor station: " + to_string(station.id));
            station.print();
            waitForEnter();
            break;
        }
        /* Viewing all objects */
        case 3:
        {
            system("cls");
            cout << "[Viewing all objects]" << endl;
            if (pipesMap.size() == 0 and stationsMap.size() == 0) {
                cout << "No objects" << endl;
            }
            if (pipesMap.size() > 0)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
            }
            if (stationsMap.size() > 0)
            {
                cout << "Stations:" << endl;
                for (auto it = stationsMap.begin(); it != stationsMap.end(); it++)
                {
                    it->second.print();
                }
            }
            waitForEnter();
            break;
        }
        /* Delete object */
        case 4:
        {
            system("cls");
            cout << "[Delete object]" << endl;
            if (pipesMap.size() == 0 and stationsMap.size() == 0)
            {
                cout << "No objects" << endl;
                waitForEnter();
                break;
            }
            cout << "Pipes:" << endl;
            for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
            {
                it->second.print();
            }
            cout << "Stations:" << endl;
            for (auto it = stationsMap.begin(); it != stationsMap.end(); it++)
            {
                it->second.print();
            }
            cout << "Choose object number: ";
            int i = GetCorrectNumber<int>(1, INT_MAX);
            if (pipesMap.find(i) != pipesMap.end())
            {
                pipesMap.erase(i);
                log("Deleted pipe: " + to_string(i));
            }
            else if (stationsMap.find(i) != stationsMap.end())
            {
                stationsMap.erase(i);
                log("Deleted station: " + to_string(i));
            }
            else
            {
                cout << "Object not found!" << endl;
            }
            waitForEnter();
            break;
        }
        /* Edit a pipe */
        case 5:
        {
            system("cls");
            cout << "[Edit a pipe]" << endl;
            if (pipesMap.size() == 0)
            {
                cout << "There are no pipes" << endl;
                waitForEnter();
                break;
            }
            cout << "Pipes:" << endl;
            for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
            {
                it->second.print();
            }
            cout << "Choose pipe number: ";
            int i = GetCorrectNumber<int>(1, INT_MAX);
            if (pipesMap.find(i) == pipesMap.end())
            {
                cout << "Pipe not found!" << endl;
                waitForEnter();
                break;
            }
            pipesMap[i].edit();
            pipesMap[i].print();
            log("Edited pipe: " + to_string(pipesMap[i].id));
            waitForEnter();
            break;
        }
        /* Starting the station workshop */
        case 6:
        {
            system("cls");
            cout << "[Starting the station workshop]" << endl;
            if (stationsMap.size() == 0)
            {
                cout << "There are no stations!" << endl;
                waitForEnter();
                break;
            }
            cout << "Stations:" << endl;
            for (auto it = stationsMap.begin(); it != stationsMap.end(); it++)
            {
                it->second.print();
            }
            cout << "Choose station number: ";
            int i = GetCorrectNumber<int>(1, INT_MAX);
            if (stationsMap.find(i) == stationsMap.end())
            {
                cout << "Station not found!" << endl;
                waitForEnter();
                break;
            }
            stationsMap[i].startWorkshops();
            log("Edited station: " + to_string(stationsMap[i].id));
            waitForEnter();
            break;
        }
        /* Stopping the station workshop */
        case 7:
        {
            system("cls");
            cout << "[Stopping the station workshop]" << endl;
            if (stationsMap.size() == 0)
            {
                cout << "There are no stations!" << endl;
                waitForEnter();
                break;
            }
            for (auto it = stationsMap.begin(); it != stationsMap.end(); it++)
            {
                it->second.print();
            }
            cout << "Choose station number: ";
            int i = GetCorrectNumber<int>(1, INT_MAX);
            if (stationsMap.find(i) == stationsMap.end())
            {
                cout << "Station not found!" << endl;
                waitForEnter();
                break;
            }
            stationsMap[i].stopWorkshops();
            log("Edited station: " + to_string(stationsMap[i].id));
            waitForEnter();
            break;
        }
        /* Save pipes to file */
        case 8:
        {
            system("cls");
            cout << "[Save pipes to file]" << endl;
            string filename = inputFilename();
            savePipes(filename, pipesMap);
            cout << "Pipes successfully saved!" << endl;
            log("Saved " + to_string(pipesMap.size()) + " pipes to file: " + filename);
            waitForEnter(false);
            break;
        }
        /* Load pipes from file */
        case 9:
        {
            system("cls");
            unordered_map<int, Pipe> map;
            cout << "[Load pipes from file]" << endl;
            string filename = inputFilename();
            downloadPipes(filename, map);
            cout << "Loaded Pipes:" << endl;
            for (auto it = map.begin(); it != map.end(); it++)
            {
                it->second.print();
                pipesMap[it->first] = it->second;
            }
            log("Loaded " + to_string(map.size()) + " pipes from file: " + filename);
            waitForEnter(false);
            break;
        }
        /* Save stations to file */
        case 10:
        {
            system("cls");
            cout << "[Save stations to file]" << endl;
            string filename = inputFilename();
            saveStations(filename, stationsMap);
            cout << "Stations successfully saved!" << endl;
            log("Saved " + to_string(stationsMap.size()) + " stations to file: " + filename);
            waitForEnter(false);
            break;
        }
        /* Load stations from file */
        case 11:
        {
            system("cls");
            unordered_map<int, Station> map;
            cout << "[Load stations from file]" << endl;
            string filename = inputFilename();
            downloadStations(filename, map);
            cout << "Loaded Stations:" << endl;
            for (auto it = map.begin(); it != map.end(); it++)
            {
                it->second.print();
                stationsMap[it->first] = it->second;
            }
            log("Loaded " + to_string(map.size()) + " stations from file: " + filename);
            waitForEnter(false);
            break;
        }
        /* Find pipes */
        case 12:
        {
            system("cls");
            cout << "[Find pipes]" << endl;
            cout << "Searching Options:" << endl;
            cout << "1. Search by string" << endl;
            cout << "2. Search by repair" << endl << endl;
            cout << "Choose option: ";
            int i = GetCorrectNumber<int>(1, 2);
            if (i == 1)
            {
                string str;
                cout << "Enter string: ";
                INPUT_LINE(cin, str);
                auto ids = findPipesByString(pipesMap, str);
                if (ids.size() == 0)
                {
                    cout << "Pipes not found!" << endl;
                    waitForEnter(false);
                    break;
                }
                cout << "Found " << ids.size() << " pipes:" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                waitForEnter(false);
                break;
            }
            else if (i == 2)
            {
                cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
                int repair = GetCorrectNumber<int>(0, 1);
                auto ids = findPipesByRepair(pipesMap, repair);
                if (ids.size() == 0)
                {
                    cout << "Pipes not found!" << endl;
                    waitForEnter();
                    break;
                }
                cout << "Found " << ids.size() << " pipes:" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                waitForEnter();
                break;
            }
            waitForEnter();
            break;
        }
        /* Find stations */
        case 13:
        {
            system("cls");
            cout << "[Find stations]" << endl;
            cout << "Searching Options:" << endl;
            cout << "1. Search by string" << endl;
            cout << "2. Search by free workshop procent" << endl << endl;
            cout << "Choose option: ";
            int i = GetCorrectNumber<int>(1, 2);
            if (i == 1)
            {
                string str;
                cout << "Enter string: ";
                INPUT_LINE(cin, str);
                auto ids = findStationsByString(stationsMap, str);
                if (ids.size() == 0)
                {
                    cout << "Stations not found!" << endl;
                    waitForEnter(false);
                    break;
                }
                cout << "Found " << ids.size() << " stations:" << endl;
                for (auto id : ids)
                {
                    stationsMap[id].print();
                }
                waitForEnter(false);
                break;
            }
            else if (i == 2)
            {
                cout << "Enter free workshop procent (0-100): ";
                int procent = GetCorrectNumber<int>(0, 100);
                auto ids = findStationsByFreeWorkshopProcent(stationsMap, procent);
                if (ids.size() == 0)
                {
                    cout << "Stations not found!" << endl;
                    waitForEnter();
                    break;
                }
                cout << "Found " << ids.size() << " stations:" << endl;
                for (auto id : ids)
                {
                    stationsMap[id].print();
                }
                waitForEnter();
                break;
            }
            waitForEnter();
            break;
        }
        /* Exit */
        case 0:
        {
            return;
        }
        default:
        {
            system("cls");
            cout << "Wrong action!" << endl;
            waitForEnter();
            break;
        }
        }
    }
}