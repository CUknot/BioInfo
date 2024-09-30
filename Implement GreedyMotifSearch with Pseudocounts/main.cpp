#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <fstream>

using namespace std;

// Function to generate the profile matrix with pseudocounts
vector<vector<double>> profileWithPseudocounts(const vector<string>& motifs, int k) {
    vector<vector<double>> profile(4, vector<double>(k, 1.0)); // Initialize with pseudocounts (1)
    unordered_map<char, int> nucleotideIndex = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    
    for (const string& motif : motifs) {
        for (int i = 0; i < k; ++i) {
            profile[nucleotideIndex[motif[i]]][i] += 1.0;
        }
    }
    
    // Normalize each column
    for (int i = 0; i < k; ++i) {
        double total = 0;
        for (int j = 0; j < 4; ++j) {
            total += profile[j][i];
        }
        for (int j = 0; j < 4; ++j) {
            profile[j][i] /= total;
        }
    }
    
    return profile;
}

// Function to calculate the probability of a k-mer given a profile matrix
double scoreKmer(const string& kmer, const vector<vector<double>>& profile) {
    unordered_map<char, int> nucleotideIndex = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    double score = 1.0;
    
    for (int i = 0; i < kmer.size(); ++i) {
        score *= profile[nucleotideIndex[kmer[i]]][i];
    }
    
    return score;
}

// Function to find the most probable k-mer in a string according to the profile
string profileMostProbableKmer(const string& dna, int k, const vector<vector<double>>& profile) {
    double maxProb = -1.0;
    string mostProbableKmer = dna.substr(0, k);
    
    for (int i = 0; i <= dna.size() - k; ++i) {
        string kmer = dna.substr(i, k);
        double prob = scoreKmer(kmer, profile);
        
        if (prob > maxProb) {
            maxProb = prob;
            mostProbableKmer = kmer;
        }
    }
    
    return mostProbableKmer;
}

// Function to calculate the score of motifs
int scoreMotifs(const vector<string>& motifs) {
    int score = 0;
    int k = motifs[0].size();
    
    for (int i = 0; i < k; ++i) {
        unordered_map<char, int> count = {{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};
        for (const string& motif : motifs) {
            count[motif[i]]++;
        }
        int maxCount = max({count['A'], count['C'], count['G'], count['T']});
        score += motifs.size() - maxCount; // Non-consensus characters
    }
    
    return score;
}

// Greedy Motif Search with Pseudocounts
vector<string> greedyMotifSearchWithPseudocounts(const vector<string>& dna, int k, int t) {
    vector<string> bestMotifs(t);
    for (int i = 0; i < t; ++i) {
        bestMotifs[i] = dna[i].substr(0, k);
    }
    int bestScore = numeric_limits<int>::max();
    
    for (int i = 0; i <= dna[0].size() - k; ++i) {
        vector<string> motifs;
        motifs.push_back(dna[0].substr(i, k));
        
        for (int j = 1; j < t; ++j) {
            vector<vector<double>> profile = profileWithPseudocounts(motifs, k);
            string nextMotif = profileMostProbableKmer(dna[j], k, profile);
            motifs.push_back(nextMotif);
        }
        
        int currentScore = scoreMotifs(motifs);
        if (currentScore < bestScore) {
            bestScore = currentScore;
            bestMotifs = motifs;
        }
    }
    
    return bestMotifs;
}

int main() {
    // File input/output
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Read input from file
    int k, t;
    inputFile >> k >> t;
    
    vector<string> dna(t);
    for (int i = 0; i < t; ++i) {
        inputFile >> dna[i];
    }
    
    // Run the algorithm
    vector<string> bestMotifs = greedyMotifSearchWithPseudocounts(dna, k, t);
    
    // Write the output to file
    for (const string& motif : bestMotifs) {
        outputFile << motif << endl;
    }

    // Close the files
    inputFile.close();
    outputFile.close();
    
    return 0;
}
