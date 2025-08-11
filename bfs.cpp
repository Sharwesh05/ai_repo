#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

void bfs(vector<vector<int>> &graph, int start, int goal) {
    queue<pair<int, vector<int>>> q;
    q.push({start, {start}});
    bool found = false;

    while (!q.empty()) {
        int level = q.size();
        vector<vector<int>> levelPath;

        for (int i = 0; i < level; i++) {
            auto [node, path] = q.front();
            q.pop();

            if (node == goal) {
                found = true;
                levelPath.push_back(path);
                continue;
            }

            if (!found) {
                for (int neigh : graph[node]) {
                    if (find(path.begin(), path.end(), neigh) == path.end()) {
                        vector<int> npath = path;
                        npath.push_back(neigh);
                        q.push({neigh, npath});
                    }
                }
            }
        }

        if (found) {
            for (auto &p : levelPath) {
                for (int i = 0; i < p.size(); i++) {
                    cout << tochar[p[i]];
                    if (i != p.size() - 1) cout << " -> ";
                }
                cout << "\n";
            }
            break;
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

    bfs(graph, 0, 6);
}

