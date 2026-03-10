#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    map<string, vector<pair<string, int>>> adj;

    void loadFromFile(const string &filename);
    void addEdge(string u, string v, int w);
    void displayMap();
    void dijkstra(string src);
};

#endif //PATHFINDER_H