#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S','A','B','C','D','E','G'};

int british_museum_recursive(vector<vector<pair<int,int>>> &graph, int current, int goal, vector<int> &path, int cost) {
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

using State = pair<int, pair<int, pair<int, vector<int>>>>;

int a_star_search(vector<vector<pair<int,int>>> &graph, vector<int> &heuristic, int start, int goal, int bound) {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({heuristic[start], {0, {start, {start}}}});
    unordered_set<int> visited;
    int best_cost = INT_MAX;
    while (!pq.empty()) {
        auto [f_cost, state_data] = pq.top();
        auto [g_cost, node_data] = state_data;
        auto [current, path] = node_data;
        pq.pop();
        if (g_cost > best_cost || f_cost > bound) continue;
        if (current == goal) {
            if (g_cost < best_cost) best_cost = g_cost;
            cout << "Path found: ";
            for (int node : path) cout << tochar[node] << " ";
            cout << "| Distance: " << g_cost << "\n";
            continue;
        }
        if (visited.count(current)) continue;
        visited.insert(current);
        for (auto &neighbor : graph[current]) {
            int next_node = neighbor.first;
            int edge_weight = neighbor.second;
            if (!visited.count(next_node)) {
                int new_g = g_cost + edge_weight;
                int new_h = heuristic[next_node];
                int new_f = new_g + new_h;
                if (new_g < best_cost) {
                    vector<int> new_path = path;
                    new_path.push_back(next_node);
                    pq.push({new_f, {new_g, {next_node, new_path}}});
                }
            }
        }
    }
    return (best_cost == INT_MAX) ? -1 : best_cost;
}

int main() {
    vector<vector<pair<int,int>>> graph = {
        {{1,3},{2,5}},
        {{4,3},{2,4}},
        {{1,4},{3,4}},
        {{5,6}},
        {{1,3},{6,5}},
        {{3,6}},
        {{4,5}}
    };
    vector<int> heuristic = {10,7,6,7,5,6,0};
    int start_node = 0;
    int goal_node = 6;
    cout << "--- BMS (Oracle) ---\n";
    vector<int> path = {start_node};
    int oracle_distance = british_museum_recursive(graph, start_node, goal_node, path, 0);
    if (oracle_distance == INT_MAX) {
        cout << "no path.\n";
        return -1;
    } else {
        cout << "oracle: " << oracle_distance << "\n";
    }
    cout << "\n--- A* Search ---\n";
    int result = a_star_search(graph, heuristic, start_node, goal_node, oracle_distance);
    if (result == -1) cout << "no path by A*.\n";
    else cout << "Best path cost via A* search: " << result << "\n";
}
