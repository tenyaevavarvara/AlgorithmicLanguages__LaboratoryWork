#pragma once

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "pipe.h"
#include "station.h"
#include "utils.h"

void downloadStations(string filename, unordered_map<int, Station>& stations)
{
    ifstream fin(filename);
    if (fin.is_open())
    {
        int size;
        fin >> size;
        if (fin.fail())
        {
            fin.close();
            return;
        }
        // Пропускаем лишние строки
        for (int i = 0; i < size * 7 + 1; ++i)
        {
            string str;
            getline(fin, str);
        }
        fin >> size;
        if (fin.fail()) {
            fin.close();
            return;
        }
        for (int i = 0; i < size; i++)
        {
            int id, workshop, inOperation;
            double effectiveness;
            string title;
            fin >> id;
            getline(fin >> std::ws, title);
            fin >> workshop >> inOperation >> effectiveness;
            stations[id] = Station(title, workshop, inOperation, effectiveness, id);
        }
        fin.close();
    }
}

void downloadPipes(string filename, unordered_map<int, Pipe>& pipes)
{
    ifstream fin(filename);
    if (fin.is_open())
    {
        int size;
        fin >> size;
        if (fin.fail())
        {
            fin.close();
            return;
        }
        for (int i = 0; i < size; i++)
        {
            int id, diameter, first, second;
            string title;
            double length;
            bool repair;
            fin >> id;
            getline(fin >> std::ws, title);
            fin >> length >> diameter >> repair >> first >> second;
            pipes[id] = Pipe(title, length, diameter, repair, id, first, second);
        }
        fin.close();
    }
}

void saveStations(string filename, unordered_map<int, Station>& stations)
{
    unordered_map<int, Pipe> pipes;
    downloadPipes(filename, pipes);
    ofstream fout(filename);
    if (fout.is_open())
    {
        fout << pipes.size() << endl;
        for (const auto& pair : pipes)
        {
            const Pipe& pipe = pair.second;
            fout << pipe.id << endl;
            fout << pipe.title << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.repair << endl;
            fout << pipe.nodes.first << endl;
            fout << pipe.nodes.second << endl;
        }
        fout << stations.size() << endl;
        for (const auto& pair : stations)
        {
            const Station& station = pair.second;
            fout << station.id << endl;
            fout << station.title << endl;
            fout << station.workshop << endl;
            fout << station.inOperation << endl;
            fout << station.effectiveness << endl;
        }
        fout.close();
    }
}

void savePipes(string filename, unordered_map<int, Pipe>& pipes)
{
    unordered_map<int, Station> stations;
    downloadStations(filename, stations);
    ofstream fout(filename);
    if (fout.is_open())
    {
        fout << pipes.size() << endl;
        for (const auto& pair : pipes)
        {
            const Pipe& pipe = pair.second;
            fout << pipe.id << endl;
            fout << pipe.title << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.repair << endl;
            fout << pipe.nodes.first << endl;
            fout << pipe.nodes.second << endl;
        }
        fout << stations.size() << endl;
        for (const auto& pair : stations)
        {
            const Station& station = pair.second;
            fout << station.id << endl;
            fout << station.title << endl;
            fout << station.workshop << endl;
            fout << station.inOperation << endl;
            fout << station.effectiveness << endl;
        }
        fout.close();
    }
}

vector<int> findPipesByString(const unordered_map<int, Pipe>& pipes, const string& str)
{
    vector<int> ids;
    for (const auto& pair : pipes)
    {
        if (pair.second.title.find(str) != string::npos)
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}

vector<int> findPipesByRepair(const unordered_map<int, Pipe>& pipes, bool repair)
{
    vector<int> ids;
    for (const auto& pair : pipes)
    {
        if (pair.second.repair == repair)
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}

vector<int> findStationsByString(const unordered_map<int, Station>& stations, const string& str)
{
    vector<int> ids;
    for (const auto& pair : stations)
    {
        if (pair.second.title.find(str) != string::npos)
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}

vector<int> findStationsByFreeWorkshopProcent(const unordered_map<int, Station>& stations, int procent)
{
    vector<int> ids;
    for (const auto& pair : stations)
    {
        if ((pair.second.workshop - pair.second.inOperation) / (float)pair.second.workshop >= procent / 100.0)
        {
            ids.push_back(pair.first);
        }
    }
    return ids;
}

void editPipes(vector<int>& ids, unordered_map<int, Pipe>& pipes)
{
    cout << "Pipe sign 'under repair' (0 - repairing, 1 - works): ";
    bool repair = GetCorrectNumber<int>(0, 1);
    for (auto id : ids)
    {
        pipes[id].repair = repair;
    }
}