#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

// Function to perform the inverse Burrows-Wheeler Transform
std::string inverseBWT(const std::string& bwt) {
    int n = bwt.size();
    
    // Initialize a vector of strings with the same length as BWT
    std::vector<std::string> table(n, "");
    
    // Repeat the process n times
    for (int i = 0; i < n; ++i) {
        // Append BWT characters to the front of each string in the table
        for (int j = 0; j < n; ++j) {
            table[j] = bwt[j] + table[j];
        }
        // Sort the table
        std::sort(table.begin(), table.end());
    }
    
    // Find the row that ends with the special '$' character
    for (const auto& row : table) {
        if (row.back() == '$') {
            return row;
        }
    }
    
    return "";
}


int main() {
    // File input and output
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string bwt;
    inputFile >> bwt;

    std::string result = inverseBWT(bwt);
    outputFile << result << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
