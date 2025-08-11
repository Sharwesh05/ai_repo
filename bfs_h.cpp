#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

void bfsLevelGlobalVisited(vector<vector<int>> &graph, int start, int goal) {
    queue<vector<int>> q;
    unordered_set<int> visited;

    q.push({start});
    visited.insert(start);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            auto path = q.front();
            q.pop();

            int node = path.back();

            if (node == goal) {
                for (int idx : path) {
                    cout << tochar[idx] << " ";
                }
                cout << "\n";
                return;
            }

            for (int neigh : graph[node]) {
                if (!visited.count(neigh)) {
                    visited.insert(neigh);
                    auto newPath = path;
                    newPath.push_back(neigh);
                    q.push(newPath);
                }
            }
        }
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

    bfsLevelGlobalVisited(graph, 0, 6);
}
