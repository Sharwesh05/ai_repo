#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S','A','B','C','D','E','G'};

bool hill(vector<vector<pair<int,int>>> &graph,vector<int> &hill_approx,int current_node, int goal, unordered_set<int> &visited,vector<int> &path) {
    path.push_back(current_node);
    if (current_node == goal) return true;
    visited.insert(current_node);
    vector<pair<int,int>> neighbors = graph[current_node];
    sort(neighbors.begin(), neighbors.end(),
         [&](auto &a, auto &b) {
             return hill_approx[a.first] < hill_approx[b.first];
         });
    for (auto &n : neighbors) {
        int next_node = n.first;
        if (!visited.count(next_node)) {
            if (hill(graph, hill_approx, next_node, goal, visited, path)) return true;
        }
    }
    path.pop_back();
    return false;
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
    vector<int> hill_approx = {10,7,6,7,5,6,0};
    unordered_set<int> visited;
    vector<int> path;
    if (hill(graph, hill_approx, 0, 6, visited, path)) {
        for (int idx : path) cout << tochar[idx] << " ";
        cout << "\n";
    } else {
        cout << "no path\n";
    }
}
