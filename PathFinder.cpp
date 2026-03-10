#include "PathFinder.h"
#include <fstream>
#include <direct.h>


void Graph::loadFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        cerr << "Current working directory: " << cwd << endl;
        return;
    }

    string u, v;
    int w;
    int count = 0;

    while (file >> u >> v >> w) {
        if (w <= 0 || w > 100000) {
            cerr <<  "Skipping invalid line: "<< u << " " << v << " " << w << endl;
            continue;
        }
        addEdge(u, v, w);
        count++;

        if (count % 100 == 0) cout << "Loaded " << count << " edges...\r";
        if (count > 100000) {
            cerr << "\n Too many edges — possible infinite loop. Aborting.\n";
            break;
        }
    }

    file.close();
    cout << "Loaded " << count << " connections from file.\n";
}


void Graph::addEdge(string u, string v, int w) {
    if (!adj.count(u)) adj[u] = {};
    if (!adj.count(v)) adj[v] = {};

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

void Graph::displayMap() {
    cout << "\n=========== CITY MAP ==========\n";
    cout << "Total Cities: " << adj.size() << "\n\n";

    int cityCount = 0;
    for (auto &nodes: adj) {
        cout << "[" << ++cityCount << "] " << nodes.first << " connects to:\n";

        auto edges = nodes.second;
        sort(edges.begin(), edges.end());

        int count = 0;
        for (auto &edge: edges) {
            cout << "   ->  " << setw(15) << left << edge.first
                    << " (" << edge.second << " km)";
            if (++count % 3 == 0) cout << "\n"; //
        }
        cout << "\n---------------------------------\n";
    }

    cout << "=================================\n";
}


void Graph::dijkstra(string src) {
    if (adj.find(src) == adj.end()) {
        cout << "Source city '" << src << "' not found in the map.\n";
        return;
    }

    unordered_map<string, int> dist;
    unordered_map<string, string> parent;
    set<pair<int, string> > s;

    for (auto &nodes: adj) {
        dist[nodes.first] = INT_MAX;
    }

    dist[src] = 0;
    s.insert({0, src});

    while (!s.empty()) {
        auto temp = *(s.begin());
        string TempNode = temp.second;
        int TempDist = temp.first;
        s.erase(s.begin());

        if (TempDist > dist[TempNode]) continue;

        for (auto &neighbour: adj[TempNode]) {
            string NeighbourNode = neighbour.first;
            int NeighbourDist = neighbour.second;

            if (NeighbourDist + TempDist < dist[NeighbourNode]) {
                auto rec = s.find({dist[NeighbourNode], NeighbourNode});
                if (rec != s.end()) s.erase(rec);

                dist[NeighbourNode] = NeighbourDist + TempDist;
                parent[NeighbourNode] = TempNode;
                s.insert({dist[NeighbourNode], NeighbourNode});
            }
        }
    }

    cout << "\nShortest Distances from " << src << ":\n";
    for (auto &n: dist) {
        cout << "  " << src << " -> " << n.first << " = ";
        if (n.second == INT_MAX) cout << "INF\n";
        else cout << n.second << " km\n";
    }

    cout << "\nEnter Destination city to view path: ";
    string dest;
    cin >> dest;

    if (adj.find(dest) == adj.end()) {
        cout << "Destination city '" << dest << "' not found in the map.\n";
        return;
    }

    if (dist.find(dest) == dist.end() || dist[dest] == INT_MAX) {
        cout << "No path exists between " << src << " and " << dest << ".\n";
        return;
    }

    vector<string> path;
    string temp = dest;
    while (temp != src) {
        path.push_back(temp);
        if (parent.find(temp) == parent.end()) {
            cout << "Error: Cannot reconstruct full path.\n";
            return;
        }
        temp = parent[temp];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());

    cout << "\nPath: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Distance: " << dist[dest] << " km\n";
}

