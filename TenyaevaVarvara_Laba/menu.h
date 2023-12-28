#include <set>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "objects.h"
#include "utils.h"
#include "logger.h"

using namespace std;

// Stopping on 0
int inputExistingId(vector<int>& ids)
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
        else cout << "ID doesn't exist, try again: ";
    }
}


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
        << "6.  Save pipes to file" << endl
        << "7.  Load pipes from file" << endl
        << "8. Save stations to file" << endl
        << "9. Load stations from file" << endl
        << "10. Find pipes" << endl
        << "11. Find stations" << endl
        << "12. Batch pipes editing" << endl
        << "13. Connect stations" << endl
        << "14. Disconnect stations" << endl
        << "15. View topological sorted graph" << endl
        << "16. Shortest way" << endl
        << "17. Max flow" << endl << endl;
}

void mainLoop() {
    unordered_map<int, Pipe> pipesMap;
    unordered_map<int, Station> stationsMap;
    while (1)
    {
        system("cls");
        printMenu();
        cout << "Select a menu item: ";
        int i = GetCorrectNumber<int>(0, 17);
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
                if (pipesMap[i].nodes.first == 0 and pipesMap[i].nodes.second == 0)
                {
                    pipesMap.erase(i);
                }
                else
                {
                    cout << "Object is used! First exclude this object from the network." << endl;
                }
            }
            else if (stationsMap.find(i) != stationsMap.end())
            {
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    if (it->second.nodes.first == i or it->second.nodes.second == i)
                    {
                        cout << "Object is used! First exclude this object from the network." << endl;
                        break;
                    }
                }
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
        /* Save pipes to file */
        case 6:
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
        case 7:
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
        case 8:
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
        case 9:
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
        case 10:
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
        case 11:
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
        case 12:
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
        /* Connect stations */
        case 13:
        {
            bool running = true;
            bool ignore = true;
            while (running)
            {
                vector<int> freeStations;
                vector<int> freePipes;
                /* Adding only free stations (has stopped workshop) */
                for (auto it = stationsMap.begin(); it != stationsMap.end(); it++)
                {
                    if ((it->second.workshop - it->second.inOperation) > 0)
                    {
                        freeStations.push_back(it->first);
                    }
                }
                /* Adding only free pipes (has no nodes) */
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    if ((it->second.nodes.first == 0) && (it->second.nodes.second == 0))
                    {
                        freePipes.push_back(it->first);
                    }
                }
                /* Nothing to connect */
                if (freeStations.size() < 2)
                {
                    cout << "Nothing to connect!" << endl;
                    waitForEnter(ignore);
                    break;
                }
                /* Print free stations */
                cout << "List of free stations:" << endl;
                for (auto _id : freeStations)
                {
                    stationsMap[_id].print();
                }
                cout << endl;
                /* Ask user to write stations to connect */
                cout << "Type first station id to connect (0 - exit): ";
                // int id1 = GetCorrectNumber<int>(0, freeStations.size());
                int id1 = inputExistingId(freeStations);
                freeStations.erase(std::remove(freeStations.begin(), freeStations.end(), id1), freeStations.end());
                if (id1 == 0) { running == false; break; waitForEnter(); }
                cout << "Type second station id to connect (0 - exit): ";
                // int id2 = GetCorrectNumber<int>(0, freeStations.size());
                int id2 = inputExistingId(freeStations);
                if (id2 == 0) { running == false; break; waitForEnter(); }
                // ids are the same
                if (id1 == id2)
                {
                    cout << "Ids are the same!" << endl;
                    waitForEnter();
                    break;
                }
                /* Choose free pipe */
                system("cls");
                cout << "Stations to connect: " << endl;
                stationsMap[id1].print();
                stationsMap[id2].print();
                cout << endl;
                // Choose pipe diameter
                cout << "Choose pipe diameter (500, 700, 1000 or 1400 mm): ";
                int diameter = GetCorrectNumber<int>(1, MAX_PIPE_DIAMETER);
                while (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
                    cout << "Diameter should be 500, 700, 1000 or 1400 mm!" << endl;
                    cout << "Pipe diameter (500, 700, 1000 or 1400 mm): ";
                    diameter = GetCorrectNumber<int>(1, MAX_PIPE_DIAMETER);
                }
                // List of free pipes
                int count = 0;
                cout << "List of free pipes:" << endl;
                for (auto _id : freePipes)
                {
                    if (pipesMap[_id].diameter == diameter) {
                        pipesMap[_id].print();
                        count++;
                    }
                }
                int pipeId = -1;
                // Creating new pipe
                if (count == 0)
                {
                    cout << "Pipes not found! Creating new one..." << endl;
                    Pipe pipe = Pipe::newPipe(diameter);
                    pipesMap[pipe.id] = pipe;
                    pipeId = pipe.id;
                }
                else
                {
                    cout << "Choose pipe id (0 - exit): ";
                    pipeId = inputExistingId(freePipes);
                    if (pipeId == 0) { running == false; break; }
                }
                /* Connect stations */
                pipesMap[pipeId].nodes = make_pair(id1, id2);
                stationsMap[id1].inOperation++;
                stationsMap[id2].inOperation++;
                /* Print result */
                system("cls");
                cout << "Stations successfully connected! " << endl;
                stationsMap[id1].print();
                stationsMap[id2].print();
                pipesMap[pipeId].print();
                cout << endl;
                waitForEnter();
                ignore = false;
            }
            break;
        }
        /* Disconnect stations */
        case 14:
        {
            bool running = true;
            bool ignore = true;
            while (running)
            {
                vector<int> edgesIds;
                /* Searching for connected to pipes stations */
                for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
                {
                    if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0))
                    {
                        edgesIds.push_back(it->first);
                    }
                }
                /* Nothing to delete */
                if (edgesIds.size() == 0)
                {
                    cout << "Nothing to delete!" << endl;
                    waitForEnter(ignore);
                    break;
                }
                /* Choose edge to delete */
                system("cls");
                cout << "List of edges (pipes):" << endl;
                for (auto id : edgesIds)
                {
                    pipesMap[id].print();
                }
                cout << "Type edge id to delete (0 - exit): ";
                int id = inputExistingId(edgesIds);
                if (id == 0) { running == false; break; waitForEnter(); }
                /* Delete edge */
                system("cls");
                stationsMap[pipesMap[id].nodes.first].inOperation--;
                stationsMap[pipesMap[id].nodes.second].inOperation--;
                pipesMap[id].nodes = make_pair(0, 0);
                cout << "Edge successfully deleted! " << endl;
                waitForEnter();
                ignore = false;
            }
            break;
        }
        /* View topological sorted graph */
        case 15:
        {
            vector<pair<int, int>> edges;
            set<int> verticesSet;
            for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
            {
                if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0))
                {
                    edges.push_back(make_pair(it->second.nodes.first, it->second.nodes.second));
                    verticesSet.insert(it->second.nodes.first);
                    verticesSet.insert(it->second.nodes.second);
                }
            }

            int i = 0;
            map<int, int> fromToMap;
            map<int, int> toFromMap;
            for (auto vertice : verticesSet)
            {
                fromToMap[vertice] = i;
                toFromMap[i] = vertice;
                i++;
            }

            vector<vector<int>> adj(verticesSet.size(), vector<int>());
            for (auto edge : edges) {
                int u = fromToMap[edge.first];
                int v = fromToMap[edge.second];
                adj[u].push_back(v);
            }


            auto result = topologicalSort(adj, verticesSet.size());
            cout << "Vertices order: " << endl;
            i = 0;
            for (auto id : result)
            {
                cout << "[" << ++i << "] " << toFromMap[id] << " " << stationsMap[toFromMap[id]].title << endl;
            }
            cout << endl;

            cout << "Topological sorted graph: " << endl;
            for (auto id : result)
            {
                for (auto edge : edges)
                {
                    int realId = toFromMap[id];
                    if (edge.first == realId)
                    {
                        cout << edge.first << " -> " << edge.second << endl;
                    }
                }
            }

            cout << endl;
            waitForEnter();
            break;
        }
        /* Shortest way */
        case 16:
        {
            vector<Edge> edges;
            set<int> verticesSet;
            for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
            {
                if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0) && (it->second.repair))
                {
                    Edge edge = { it->second.nodes.first, it->second.nodes.second, it->second.length };
                    edges.push_back(edge);
                    verticesSet.insert(it->second.nodes.first);
                    verticesSet.insert(it->second.nodes.second);
                }
            }

            int i = 0;
            int vertices = verticesSet.size();
            map<int, int> fromToMap;
            map<int, int> toFromMap;
            for (auto vertice : verticesSet)
            {
                fromToMap[vertice] = i;
                toFromMap[i] = vertice;
                i++;
            }
            vector<int> verticesVector = vector<int>(verticesSet.begin(), verticesSet.end());
            verticesVector.push_back(0);

            i = 0;
            cout << "List of edges:" << endl;
            for (auto id : pipesMap)
            {
                if ((id.second.nodes.first != 0) && (id.second.nodes.second != 0) && (id.second.repair))
                {
                    cout << "[" << id.second.nodes.first << "] " << stationsMap[id.second.nodes.first].title << " -> " << "[" << id.second.nodes.second << "] " << stationsMap[id.second.nodes.second].title << endl;
                    i++;
                }
            }

            if (i == 0) {
                cout << "Nothing to choose!" << endl;
                waitForEnter();
                break;
            }

            cout << endl;

            cout << "Choose two stations: " << endl;
            cout << "Type first station id (0 - exit): ";
            int first = inputExistingId(verticesVector);
            if (first == 0) break;
            cout << "Type second station id (0 - exit): ";
            int second = inputExistingId(verticesVector);
            if (second == 0 or first == second) break;

            first = fromToMap[first];
            second = fromToMap[second];

            vector<vector<int>> adj(vertices, vector<int>(vertices));
            for (int i = 0; i < adj.size(); i++) {
                for (int j = 0; j < adj.size(); j++) {
                    adj[i][j] = INT_MAX;
                }
            }
            for (auto edge : edges) {
                int u = fromToMap[edge.first];
                int v = fromToMap[edge.second];
                adj[u][v] = edge.weight;
                // adj[v][u] = edge.weight;
            }

            vector<int> path = getShortestPath(adj, first, second);
            if (path.size() < 2) {
                cout << "Path doesn't exist!" << endl;
                waitForEnter();
                break;
            }
            if (path[0] != first && path[path.size() - 1] != second) {
                cout << "Path doesn't exist!" << endl;
                waitForEnter();
                break;
            }

            cout << "Shortest way: " << endl;
            for (auto id : path)
            {
                cout << "[" << toFromMap[id] << "] " << stationsMap[toFromMap[id]].title << endl;
            }
            int length = 0;
            for (int i = 0; i < path.size() - 1; i++) {
                length = length + adj[path[i]][path[i + 1]];
            }
            cout << "Length: " << length << endl;


            cout << endl;
            waitForEnter();
            break;
        }
        /* Max flow */
        case 17:
        {
            vector<Edge> edges;
            set<int> verticesSet;
            for (auto it = pipesMap.begin(); it != pipesMap.end(); it++)
            {
                if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0) && (it->second.repair))
                {
                    Edge edge = { it->second.nodes.first, it->second.nodes.second, it->second.getWeight() };
                    edges.push_back(edge);
                    verticesSet.insert(it->second.nodes.first);
                    verticesSet.insert(it->second.nodes.second);
                }
            }

            int i = 0;
            int vertices = verticesSet.size();
            map<int, int> fromToMap;
            map<int, int> toFromMap;
            for (auto vertice : verticesSet)
            {
                fromToMap[vertice] = i;
                toFromMap[i] = vertice;
                i++;
            }
            vector<int> verticesVector = vector<int>(verticesSet.begin(), verticesSet.end());
            verticesVector.push_back(0);

            i = 0;
            cout << "List of edges:" << endl;
            for (auto id : pipesMap)
            {
                if ((id.second.nodes.first != 0) && (id.second.nodes.second != 0) && (id.second.repair))
                {
                    cout << "[" << id.second.nodes.first << "] " << stationsMap[id.second.nodes.first].title << " -> " << "[" << id.second.nodes.second << "] " << stationsMap[id.second.nodes.second].title << endl;
                    i++;
                }
            }

            if (i == 0) {
                cout << "Nothing to choose!" << endl;
                waitForEnter();
                break;
            }

            cout << endl;

            cout << "Choose two stations: " << endl;
            cout << "Type first station id (0 - exit): ";
            int first = inputExistingId(verticesVector);
            if (first == 0) break;
            cout << "Type second station id (0 - exit): ";
            int second = inputExistingId(verticesVector);
            if (second == 0 or first == second) break;

            first = fromToMap[first];
            second = fromToMap[second];

            vector<vector<int>> adj(vertices, vector<int>(vertices));
            for (int i = 0; i < adj.size(); i++) {
                for (int j = 0; j < adj.size(); j++) {
                    adj[i][j] = INT_MAX;
                }
            }
            for (auto edge : edges) {
                int u = fromToMap[edge.first];
                int v = fromToMap[edge.second];
                adj[u][v] = edge.weight;
                // adj[v][u] = edge.weight;
            }

            int flow = maxFlow(adj, first, second);
            if (flow < 0 || flow > 100000) {
                cout << "Path doesn't exist!" << endl;
                waitForEnter();
                break;
            }
            cout << "Max flow: " << flow << endl;
            cout << endl;
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