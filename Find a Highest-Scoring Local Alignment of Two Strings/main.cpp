#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define the PAM250 matrix as an unordered map
unordered_map<char, unordered_map<char, int>> pam250;

void loadPAM250(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return;
    }

    string line;
    vector<char> amino_acids;

    // First, read the header line to get the amino acids
    if (getline(file, line)) {
        istringstream iss(line);
        char amino;
        while (iss >> amino) {
            amino_acids.push_back(amino);
        }
    }

    // Now, read the matrix values
    while (getline(file, line)) {
        istringstream iss(line);
        char row_amino;
        iss >> row_amino;  // Read the row's amino acid character

        int score;
        for (size_t i = 0; i < amino_acids.size(); ++i) {
            iss >> score;
            pam250[row_amino][amino_acids[i]] = score;  // Fill the unordered map
        }
    }

    file.close();
}

// Smith-Waterman algorithm for local alignment
pair<int, pair<string, string>> smithWaterman(const string& s1, const string& s2, int gap_penalty) {
    int m = s1.length();
    int n = s2.length();
    
    // DP table and traceback table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<pair<int, int>>> traceback(m + 1, vector<pair<int, int>>(n + 1, {-1, -1}));
    
    int max_score = 0;
    pair<int, int> max_pos = {0, 0};

    // Fill DP and traceback table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int match_score = pam250[s1[i - 1]][s2[j - 1]];
            int score_diag = dp[i - 1][j - 1] + match_score;
            int score_up = dp[i - 1][j] - gap_penalty;
            int score_left = dp[i][j - 1] - gap_penalty;
            dp[i][j] = max({0, score_diag, score_up, score_left});

            // Keep track of where the score came from (traceback)
            if (dp[i][j] == score_diag) {
                traceback[i][j] = {i - 1, j - 1};
            } else if (dp[i][j] == score_up) {
                traceback[i][j] = {i - 1, j};
            } else if (dp[i][j] == score_left) {
                traceback[i][j] = {i, j - 1};
            }

            // Update the maximum score position
            if (dp[i][j] > max_score) {
                max_score = dp[i][j];
                max_pos = {i, j};
            }
        }
    }

    // Traceback to get the aligned strings
    string aligned_s1 = "", aligned_s2 = "";
    int i = max_pos.first;
    int j = max_pos.second;

    while (i > 0 && j > 0 && dp[i][j] > 0) {
        int prev_i = traceback[i][j].first;
        int prev_j = traceback[i][j].second;
        
        if (prev_i == i - 1 && prev_j == j - 1) {
            aligned_s1 = s1[i - 1] + aligned_s1;
            aligned_s2 = s2[j - 1] + aligned_s2;
        } else if (prev_i == i - 1) {
            aligned_s1 = s1[i - 1] + aligned_s1;
            aligned_s2 = "-" + aligned_s2;
        } else {
            aligned_s1 = "-" + aligned_s1;
            aligned_s2 = s2[j - 1] + aligned_s2;
        }
        
        i = prev_i;
        j = prev_j;
    }

    return {max_score, {aligned_s1, aligned_s2}};
}


int main() {
    // Load the PAM250 matrix from the file
    string filename = "PAM250.txt";
    loadPAM250(filename);

    // Test: Print the PAM250 matrix stored in the unordered_map
    // for (const auto& row : pam250) {
    //     char row_amino = row.first;
    //     cout << row_amino << ": ";
    //     for (const auto& col : row.second) {
    //         cout << col.first << "=" << col.second << " ";
    //     }
    //     cout << endl;
    // }

    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    string str1, str2;
    getline(inputFile, str1);
    getline(inputFile, str2);

    int gap_penalty = 5;

    auto result = smithWaterman(str1, str2, gap_penalty);
    outputFile << result.first << endl;
    outputFile << result.second.first << endl;
    outputFile << result.second.second << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}
