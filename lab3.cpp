#include "graph.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

int main() {

    WOrGraph G(10, 0.5, 1, 20);
    G.Print();

    pair<double, string> pair;
    pair = G.Dijkstra(1, 10);
    cout << "distance = " << pair.first << endl
         << "route = " << pair.second << endl;

    G.PrintFullDijkstra(G.FullDijkstra());

    cout << "======================\n";
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (i != j) {
                pair = G.Dijkstra(i, j);
                cout << pair.second << "\t\t";
            } else {
                cout << 0 << "\t";
            }
        }
        cout << endl;
    }
    cout << "======================";
}
