#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <climits>
#include <fstream>
#include <iostream> 
#include <algorithm>
#include <unordered_map>

#include "math.h"
#include "utils.h"
#include "objects.h"

using namespace std;

const int INF = INT_MAX;

struct Path {
    vector<int> nodes;
    int cost;
};

vector<int> convertVerticesToStations(unordered_map<int, Station>& stations, vector<int> vertices) {
    vector<int> ids;
    for (int i = 0; i < vertices.size(); i++)
    {
        for (auto it = stations.begin(); it != stations.end(); it++)
        {
            if (it->second.verticeId == vertices[i])
            {
                ids.push_back(it->first);
                break;
            }
        }
    }
    return ids;
}

vector<int> getUsedStations(unordered_map<int, Pipe>& pipes) {
    set<int> ids;
    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0) && (it->second.repair))
        {
            ids.insert(it->second.nodes.first);
            ids.insert(it->second.nodes.second);
        }
    }
    return vector<int>(ids.begin(), ids.end());
}

void printGraph(const unordered_map<int, Pipe>& pipes) {
    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0) && (it->second.repair))
        {
            cout << '[' << it->second.nodes.first << ']' << " ---"<< it->first 
                 << "---> " << '[' << it->second.nodes.second << ']' << endl;
        }
    }
}

vector<vector<int>> buildAdjMatrix(unordered_map<int, Station>& stations, unordered_map<int, Pipe>& pipes, bool withWeight = false) {
    vector<vector<int>> adjMatrix = vector<vector<int>>(stations.size(), vector<int>(stations.size(), 0));
    
    int uniqueId = 0;
    for (auto &station : stations) {
        station.second.verticeId = uniqueId++;
    }

    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        if ((it->second.nodes.first != 0) && (it->second.nodes.second != 0) && (it->second.repair))
        {
            int u = stations[it->second.nodes.first].verticeId;
            int v = stations[it->second.nodes.second].verticeId;
            adjMatrix[u][v] = withWeight ? it->second.getWeight() : it->second.length;
        }
    }

    return adjMatrix;
}

vector<int> topologicalSort(vector<vector<int>> adj, int V) { 
    vector<int> in_degree(V, 0); 
    vector<int> result;
  
    for (int u = 0; u < V; u++) { 
        for (int x:adj[u]) 
            in_degree[x]++; 
    } 
  
    queue<int> q; 
    for (int i = 0; i < V; i++) 
        if (in_degree[i] == 0) 
            q.push(i); 

    while (!q.empty()) { 
        int u = q.front(); 
        q.pop(); 
        result.push_back(u);
  
        for (int x: adj[u]) 
            if (--in_degree[x] == 0) 
                q.push(x); 
    } 
    return result;
}

vector<int> getShortestPath(vector<vector<int>> graph, int source, int target) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INF);
    vector<int> prev(numNodes, -1);
    queue<int> q;

    distances[source] = 0;
    q.push(source);

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < numNodes; ++i) {
            if (graph[currentNode][i] != INF && distances[i] == INF) {
                distances[i] = distances[currentNode] + graph[currentNode][i];
                prev[i] = currentNode;
                q.push(i);
            } else if (graph[currentNode][i] != INF && distances[currentNode] + graph[currentNode][i] < distances[i]) {
                distances[i] = distances[currentNode] + graph[currentNode][i];
                prev[i] = currentNode;
            }
        }
    }

    vector<int> path;
    int currentNode = target;
    while (currentNode != -1) {
        path.push_back(currentNode);
        currentNode = prev[currentNode];
    }

    if (path.size() == 1) path.clear();
    reverse(path.begin(), path.end());
    return path;
}

vector<Path> getMaxFlow(vector<vector<int>>& graph, int source, int sink) {
    vector<Path> paths;
    int n = graph.size();
    vector<vector<int>> residualGraph(n, vector<int>(n)); // Остаточная сеть
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            residualGraph[i][j] = graph[i][j]; // Начальная остаточная сеть идентична исходной сети
        }
    }

    while (true) {
        auto path = getShortestPath(residualGraph, source, sink);
        if (path.empty()) {
            break;
        }
        int minFlow = INF;
        for (int i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            minFlow = min(minFlow, residualGraph[u][v]);
        }
        for (int i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            residualGraph[u][v] -= minFlow;
        }
        paths.push_back({path, minFlow});
    }

    return paths;
}