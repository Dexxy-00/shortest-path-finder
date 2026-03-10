#include <bits/stdc++.h>
#include "PathFinder.h"
using namespace std;

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    Graph g;
    string filename = "../AetheriaMap.txt";

    cout << "Loading data from " << filename << "...\n";
    g.loadFromFile(filename);

    int choice = 0;

    while (true) {
        cout << "\n==========================";
        cout << "\n     PATH FINDER SYSTEM";
        cout << "\n==========================\n";
        cout << "\n1. Add Road";
        cout << "\n2. Display City Map";
        cout << "\n3. Find Shortest Path";
        cout << "\n4. Exit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string u, v;
                int w;
                cout << "Enter first city: ";
                getline(cin, u);
                cout << "Enter second city: ";
                getline(cin, v);
                cout << "Enter distance (in km): ";
                cin >> w;
                g.addEdge(u, v, w);
                cout << "\nRoad added successfully!\n";
                pauseScreen();
                break;
            }

            case 2:
                g.displayMap();
                pauseScreen();
                break;

            case 3: {
                string src;
                cout << "Enter source city: ";
                getline(cin, src);
                if (src.empty()) getline(cin, src);
                g.dijkstra(src);
                pauseScreen();
                break;
            }

            case 4:
                cout << "\nExiting Path Finder...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                pauseScreen();
        }
    }
    return 0;
}