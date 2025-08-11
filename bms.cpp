#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph = {
    {1, 2},
    {4},
    {1, 3},
    {5},
    {6},
    {},
    {}
};

vector<char> tochar = {'s', 'a', 'b', 'c', 'd', 'e', 'g'};

void bms(int curr, int goal, vector<int> &visited, vector<string> &sol) {
    visited.push_back(curr);

    if (curr == goal) {
        string path;
        for (int node : visited) path += tochar[node];
        sol.push_back(path);
        visited.pop_back();
        return;
    }

    for (int neighbour : graph[curr]) {
        if (find(visited.begin(), visited.end(), neighbour) == visited.end()) {
            bms(neighbour, goal, visited, sol);
        }
    }

    visited.pop_back();
}

int main() {
    int startNode = 0;
    int endNode = 6;

    vector<int> visited;
    vector<string> sol;

    bms(startNode, endNode, visited, sol);

    if (!sol.empty()) {
        for (auto &path : sol) {
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i != path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    } else {
    }
}
