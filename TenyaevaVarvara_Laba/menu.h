#include <set>
#include <iostream>
#include <algorithm>
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
    logValue(filename);
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
        << "13. Find stations" << endl
        << "14. Batch pipes editing" << endl << endl;
}

void mainLoop() {
    unordered_map<int, Pipe> pipesMap;
    unordered_map<int, Station> stationsMap;
    while (1)
    {
        system("cls");
        printMenu();
        cout << "Select a menu item: ";
        int i = GetCorrectNumber<int>(0, 14);
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
            }
            else if (stationsMap.find(i) != stationsMap.end())
            {
                stationsMap.erase(i);
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
        /* Batch pipes editing */
        case 14:
        {
            system("cls");
            if (pipesMap.size() == 0)
            {
                cout << "Pipes not found!" << endl;
                waitForEnter();
                break;
            }
            cout << "[Batch editing]" << endl;
            cout << "Choose action:" << endl;
            cout << "0. Back" << endl;
            cout << "1. Choose pipes to edit by ids" << endl;
            cout << "2. Choose pipes to edit by string" << endl;
            cout << "3. Choose pipes to edit by repair" << endl;
            cout << "4. Choose pipes to delete by ids" << endl;
            cout << "5. Choose pipes to delete by string" << endl;
            cout << "6. Choose pipes to delete by repair" << endl << endl;
            cout << "Choose option: ";
            int i = GetCorrectNumber<int>(0, 6);
            system("cls");
            if (i == 1)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
                cout << endl;
                vector<int> ids;
                int id = -1;
                while (id != 0)
                {
                    cout << "Enter id (0 to stop): ";
                    id = GetCorrectNumber<int>(0, INT_MAX);
                    if (id != 0)
                    {
                        if (pipesMap.find(id) != pipesMap.end())
                        {
                            bool contains = false;
                            for (auto it = ids.begin(); it != ids.end(); it++)
                            {
                                if (*it == id)
                                {
                                    contains = true;
                                    break;
                                }
                            }
                            if (!contains)
                            {
                                ids.push_back(id);
                            }
                            else
                            {
                                cout << "Pipe already in list!" << endl;
                            }
                        }
                        else
                        {
                            cout << "Pipe not found!" << endl;
                        }
                    }
                }
                system("cls");
                if (ids.size() == 0)
                {
                    cout << "Nothing to edit!" << endl;
                    waitForEnter();
                    break;
                }
                cout << "Pipes to edit: ";
                for (auto id : ids)
                {
                    cout << id << " ";
                }
                cout << endl;
                editPipes(ids, pipesMap);
                system("cls");
                cout << "Edited " << ids.size() << " pipes!" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                cout << endl;
                waitForEnter();
                break;
            }
            else if (i == 2)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
                cout << endl;
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
                system("cls");
                cout << "Found " << ids.size() << " pipes:" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                cout << endl;
                editPipes(ids, pipesMap);
                system("cls");
                cout << "Edited " << ids.size() << " pipes!" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                waitForEnter();
                break;
            }
            else if (i == 3)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
                cout << endl;
                cout << "Enter repair (0 - repairing, 1 - works): ";
                int repair = GetCorrectNumber<int>(0, 1);
                auto ids = findPipesByRepair(pipesMap, repair);
                system("cls");
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
                cout << endl;
                editPipes(ids, pipesMap);
                system("cls");
                cout << "Edited " << ids.size() << " pipes!" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                waitForEnter();
                break;
            }
            else if (i == 4)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
                cout << endl;
                vector<int> ids;
                int id = -1;
                while (id != 0)
                {
                    cout << "Enter id (0 to stop): ";
                    id = GetCorrectNumber<int>(0, INT_MAX);
                    if (id != 0)
                    {
                        if (pipesMap.find(id) != pipesMap.end())
                        {
                            bool contains = false;
                            for (auto it = ids.begin(); it != ids.end(); it++)
                            {
                                if (*it == id)
                                {
                                    contains = true;
                                    break;
                                }
                            }
                            if (!contains)
                            {
                                ids.push_back(id);
                            }
                            else
                            {
                                cout << "Pipe already in list!" << endl;
                            }
                        }
                        else
                        {
                            cout << "Pipe not found!" << endl;
                        }
                    }
                }
                system("cls");
                if (ids.size() == 0)
                {
                    cout << "Nothing to edit!" << endl;
                    waitForEnter();
                    break;
                }
                cout << "Pipes to delete: ";
                for (auto id : ids)
                {
                    cout << id << " ";
                }
                cout << endl;
                cout << "Deleted " << ids.size() << " pipes!" << endl;
                for (auto id : ids)
                {
                    pipesMap.erase(id);
                }
                cout << endl;
                waitForEnter();
                break;
            }
            else if (i == 5)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
                cout << endl;
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
                system("cls");
                cout << "Found " << ids.size() << " pipes:" << endl;
                for (auto id : ids)
                {
                    pipesMap[id].print();
                }
                cout << endl;
                cout << "Deleted " << ids.size() << " pipes!" << endl;
                for (auto id : ids)
                {
                    pipesMap.erase(id);
                }
                waitForEnter(false);
                break;
            }
            else if (i == 6)
            {
                cout << "Pipes:" << endl;
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    it->second.print();
                }
                cout << endl;
                cout << "Enter repair (0 - repairing, 1 - works): ";
                int repair = GetCorrectNumber<int>(0, 1);
                auto ids = findPipesByRepair(pipesMap, repair);
                system("cls");
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
                cout << endl;
                cout << "Deleted " << ids.size() << " pipes!" << endl;
                for (auto id : ids)
                {
                    pipesMap.erase(id);
                }
                waitForEnter();
                break;
            }
            else
            {
                break;
            }
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