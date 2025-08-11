#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

bool dfs(vector<vector<int>> &graph, int node, int goal, vector<int> &path, unordered_set<int> &visited) {
    if (node == goal) {
        for (int i = 0; i < path.size(); i++) {
            cout << tochar[path[i]];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\n";
        return true;
    }

    vector<int> neigh = graph[node];
    sort(neigh.begin(), neigh.end());

    for (int n : neigh) {
        if (!visited.count(n)) {
            visited.insert(n);
            path.push_back(n);
            if (dfs(graph, n, goal, path, visited)) return true;
            path.pop_back();
            visited.erase(n);
        }
    }
    return false;
}

int main() {

    vector<int> path;
    unordered_set<int> visited;

    vector<vector<int>> graph = {
        {1, 2},
        {4, 2, 0},
        {1, 3, 0},
        {5, 2},
        {1, 6},
        {3},
        {4}
    };

    visited.insert(0);
    path.push_back(0);

    dfs(graph, 0, 6, path, visited);

}
