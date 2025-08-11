#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S','A','B','C','D','E','G'};

int british_museum_recursive(vector<vector<pair<int,int>>> &graph,
                              int current, int goal,
                              vector<int> &path, int cost)
{
    if (current == goal) {
        for (int node : path) cout << tochar[node] << " ";
        cout << "| Dist: " << cost << "\n";
        return cost;
    }
    int best = INT_MAX;
    for (auto &neighbor : graph[current]) {
        if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
            path.push_back(neighbor.first);
            best = min(best, british_museum_recursive(graph, neighbor.first, goal, path, cost + neighbor.second));
            path.pop_back();
        }
    }
    return best;
}

int main() {
    vector<vector<pair<int,int>>> graph = {
        {{1,3},{2,5}},
        {{4,3},{2,4},{0,3}},
        {{1,4},{3,4},{0,5}},
        {{5,6},{2,6}},
        {{1,3},{6,5}},
        {{3,6}},
        {{4,5}}
    };
    vector<int> path = {0};
    int oracle_distance = british_museum_recursive(graph, 0, 6, path, 0);
    if (oracle_distance == INT_MAX) {
        cout << "no path\n";
    } else {
        cout << "oracle: " << oracle_distance << "\n";
    }
}
