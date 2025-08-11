#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S','A','B','C','D','E','G'};

int british_museum_recursive(vector<vector<pair<int,int>>> &graph,  int current, int goal, vector<int> &path, int cost) {
    if (current == goal) {
        cout << "Path found: ";
        for (int node : path) cout << tochar[node] << " ";
        cout << "| Distance: " << cost << "\n";
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

int branch_and_bound_pq(vector<vector<pair<int,int>>> &graph, int start, int goal, int bound) {
    using State = pair<int, pair<int, vector<int>>>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, {start, {start}}});
    unordered_set<int> visited;
    while (!pq.empty()) {
        auto [cost, nodePath] = pq.top();
        auto [current, path] = nodePath;
        pq.pop();
        if (cost > bound) return -1;
        if (current == goal) {
            for (int node : path) cout << tochar[node] << " ";
            cout << "| Dist: " << cost << "\n";
            return cost;
        }
        visited.insert(current);
        for (auto &neighbor : graph[current]) {
            if (!visited.count(neighbor.first)) {
                vector<int> newPath = path;
                newPath.push_back(neighbor.first);
                pq.push({cost + neighbor.second, {neighbor.first, newPath}});
            }
        }
    }
    return -1;
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
        return -1;
    } else {
        cout << "oracle: " << oracle_distance << "\n";
    }
    cout << "\n--- Branch and Bound ---\n";
    int result = branch_and_bound_pq(graph, 0, 6, oracle_distance);
    if (result == INT_MAX) cout << "Goal not reachable.\n";
    else cout << "Best path cost via Branch and Bound (EL): " << result << "\n";
}
