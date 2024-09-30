#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Function to calculate the edit distance between two strings
int editDistance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a 2D DP table to store the distances
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Base cases
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i; // Cost of deleting characters from str1 to match an empty str2
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j; // Cost of inserting characters into an empty str1 to match str2
    }

    // Fill the DP table using the recurrence relation
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No edit required if characters match
            } else {
                dp[i][j] = min({ dp[i - 1][j] + 1,  // Deletion
                                 dp[i][j - 1] + 1,  // Insertion
                                 dp[i - 1][j - 1] + 1 }); // Substitution
            }
        }
    }

    // The final answer is in dp[m][n]
    return dp[m][n];
}

int main() {
     // File input and output
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    string str1, str2;
    getline(inputFile, str1);
    getline(inputFile, str2);

    // Output the edit distance
    outputFile  << editDistance(str1, str2) << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}
