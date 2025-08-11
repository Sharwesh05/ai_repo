#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

bool dls(vector<vector<int>> &graph, int current, int goal, int limit, vector<int> &path) {
    path.push_back(current);
    if (current == goal) return true;
    if (limit <= 0) {
        path.pop_back();
        return false;
    }
    vector<int> neighbors = graph[current];
    sort(neighbors.begin(), neighbors.end());
    for (int neighbor : neighbors) {    
        if (find(path.begin(), path.end(), neighbor) == path.end()) {
            if (dls(graph, neighbor, goal, limit - 1, path)) return true;
        }
    }
    path.pop_back();
    return false;
}

void iddfs(vector<vector<int>> &graph, int start, int goal) {
    int depth = 0;
    while (true) {
        vector<int> path;
        if (dls(graph, start, goal, depth, path)) {
            for (int idx : path) cout << tochar[idx] << " ";
            cout << "\n";
            return;
        }
        depth++;
    }
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
    iddfs(graph, 0, 6);
}
