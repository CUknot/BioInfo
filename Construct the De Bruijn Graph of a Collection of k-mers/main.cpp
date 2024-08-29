#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;

unordered_map<string, vector<string>> buildDeBruijnGraph(const vector<string>& kmers) {
    unordered_map<string, vector<string>> adjList;
    for (const string& kmer : kmers) {
        string prefix = kmer.substr(0, kmer.length() - 1);
        string suffix = kmer.substr(1);
        adjList[prefix].push_back(suffix);
    }
    return adjList;
}

void sortAdjacencyList(unordered_map<string, vector<string>>& adjList) {
    for (auto& entry : adjList) {
        sort(entry.second.begin(), entry.second.end());
    }
}

void printAdjacencyList(const unordered_map<string, vector<string>>& adjList) {
    // Use a map to automatically sort the keys in lexicographical order
    map<string, vector<string>> sortedAdjList(adjList.begin(), adjList.end());

    for (const auto& entry : sortedAdjList) {
        cout << entry.first << " -> ";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            if (i > 0) cout << ",";
            cout << entry.second[i];
        }
        cout << endl;
    }
}

int main() {
    vector<string> kmers;
    string kmer;

    ifstream inputFile("data.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << endl;
        return 1;
    }

    while (getline(inputFile, kmer)) {
        kmers.push_back(kmer);
    }

    inputFile.close();

    unordered_map<string, vector<string>> adjList = buildDeBruijnGraph(kmers);
    sortAdjacencyList(adjList);
    printAdjacencyList(adjList);

    return 0;
}
