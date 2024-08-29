#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

void dfs(int u, unordered_map<int, vector<int>>& graph, stack<int>& path) {
    while (!graph[u].empty()) {
        int v = graph[u].back();
        graph[u].pop_back();
        dfs(v, graph, path);
    }
    path.push(u);
}

vector<int> findEulerianPath(unordered_map<int, vector<int>>& graph) {
    unordered_map<int, int> in_degree, out_degree;
    for (const auto& pair : graph) {
        out_degree[pair.first] += pair.second.size();
        for (int v : pair.second) {
            in_degree[v]++;
        }
    }

    int start = -1, end = -1;
    for (const auto& pair : out_degree) {
        if (out_degree[pair.first] == in_degree[pair.first] + 1) {
            start = pair.first;
        } else if (in_degree[pair.first] == out_degree[pair.first] + 1) {
            end = pair.first;
        }
    }

    if (start == -1) start = graph.begin()->first;

    stack<int> path;
    dfs(start, graph, path);

    vector<int> eulerian_path;
    while (!path.empty()) {
        eulerian_path.push_back(path.top());
        path.pop();
    }

    return eulerian_path;
}

int main() {
    unordered_map<int, vector<int>> graph;
    ifstream inputFile("data.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int u;
        char arrow;
        ss >> u >> arrow >> arrow;  // Read the source vertex
        int v;
        while (ss >> v) {
            graph[u].push_back(v);
            if (ss.peek() == ',') {
                ss.ignore(); // Ignore the comma
            }
        }
    }

    inputFile.close();

    vector<int> path = findEulerianPath(graph);

    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << "->";
        cout << path[i];
    }
    cout << endl;

    return 0;
}
