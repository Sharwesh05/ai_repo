#include <bits/stdc++.h>
using namespace std;

vector<char> tochar = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};

bool beam(vector<vector<pair<int,int>>> &graph, vector<int> &hill_approx, int start, int goal, size_t beam_width) {
    unordered_set<int> visited;
    auto compare_nodes = [&](const pair<int, vector<int>> &a, const pair<int, vector<int>> &b) {
        return hill_approx[a.first] > hill_approx[b.first];
    };

    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, decltype(compare_nodes)> current_level(compare_nodes);
    current_level.push({start, {start}});
    visited.insert(start);

    while (!current_level.empty()) {
        priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, decltype(compare_nodes)> next_level(compare_nodes);

        while (!current_level.empty()) {
            auto current = current_level.top();
            current_level.pop();

            int current_id = current.first;
            vector<int> current_path = current.second;

            if (current_id == goal) {
                for (int n : current_path) {
                    cout << tochar[n] << " ";
                }
                cout << "\n";
                return true;
            }

            for (auto &neighbor : graph[current_id]) {
                if (!visited.count(neighbor.first)) {
                    auto new_path = current_path;
                    new_path.push_back(neighbor.first);
                    next_level.push({neighbor.first, new_path});
                }
            }
        }

        vector<pair<int, vector<int>>> pruned_nodes;
        while (!next_level.empty() && pruned_nodes.size() < beam_width) {
            auto node = next_level.top();
            next_level.pop();
            pruned_nodes.push_back(node);
            visited.insert(node.first);
        }

        for (const auto &node : pruned_nodes) {
            current_level.push(node);
        }

        if (current_level.empty()) {
            break;
        }
    }

    return false;
}

int main() {
    vector<vector<pair<int,int>>> graph = {
        {{1,3}, {2,5}},
        {{4,3}, {2,4}, {0,3}},
        {{1,4}, {3,4}, {0,5}},
        {{5,6}, {2,6}},
        {{1,3}, {6,5}},
        {{3,6}},
        {{4,5}}
    };

    vector<int> hill_approx = {10, 7, 6, 7, 5, 6, 0};

    size_t beam_width = 2;
    if (!beam(graph, hill_approx, 0, 6, beam_width)) {
        cout << "no path\n";
    }

    return 0;
}
