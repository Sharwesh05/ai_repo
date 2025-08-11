#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

bool dfsRec(vector<vector<int>> &graph, int node, int goal, vector<int> &path, unordered_set<int> &visited, unordered_set<int> &deadEnd) {
    if (deadEnd.count(node) || visited.count(node)) return false;
    
    visited.insert(node);
    path.push_back(node);

    if (node == goal) {
        for (int idx : path) cout << tochar[idx] << " ";
        cout << "\n";
        return true;
    }

    bool found = false;
    for (int neigh : graph[node]) {
        if (!visited.count(neigh)) {
            if (dfsRec(graph, neigh, goal, path, visited, deadEnd)) {
                found = true;
                break;
            }
        }
    }

    if (!found) deadEnd.insert(node);

    path.pop_back();
    return found;
}

void dfsWithDeadEnds(vector<vector<int>> &graph, int start, int goal) {
    vector<int> path;
    unordered_set<int> visited;
    unordered_set<int> deadEnd;
    dfsRec(graph, start, goal, path, visited, deadEnd);
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},
        {4, 2, 0},
        {1, 3, 0},
        {5, 2},
        {1, 6},
        {3},
        {4}
    };

    dfsWithDeadEnds(graph, 0, 6);
}
