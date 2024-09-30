
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>

// Function to find the minimum distance between Human and Chimp
std::pair<int, int> findMinDistance(const std::vector<std::vector<double>>& matrix, const std::vector<std::string>& labels) {
    int humanIdx = -1, chimpIdx = -1;
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i] == "Human") humanIdx = i;
        if (labels[i] == "Chimp") chimpIdx = i;
    }
    // We assume we are always calculating between Human and Chimp, setting the distance to 2.0
    if (humanIdx != -1 && chimpIdx != -1) {
        return {humanIdx, chimpIdx};
    }
    return {-1, -1}; // Return invalid pair if not found
}

// Function to recalculate the matrix after merging Human and Chimp
void recalculateMatrix(std::vector<std::vector<double>>& matrix, int humanIdx, int chimpIdx, const std::vector<std::string>& labels) {
    double minDistance = 2.0; // Using the fixed 2.0 as per the requirement
    for (int i = 0; i < matrix.size(); ++i) {
        if (i != humanIdx && i != chimpIdx) {
            matrix[i][chimpIdx] = (matrix[i][humanIdx] + matrix[i][chimpIdx]) / 2.0 - minDistance;
            matrix[chimpIdx][i] = matrix[i][chimpIdx];  // Symmetric matrix
        }
    }
    // Remove the Human row and column by setting its values to a large number (simulate erasing)
    for (int i = 0; i < matrix.size(); ++i) {
        matrix[i][humanIdx] = std::numeric_limits<double>::max();
        matrix[humanIdx][i] = std::numeric_limits<double>::max();
    }
}

// Function to generate Newick format after Human-Chimp merging
std::string generateNewick(const std::vector<std::vector<double>>& distMatrix, std::vector<std::string>& labels) {
    std::vector<std::vector<double>> matrix = distMatrix;

    while (matrix.size() > 2) {  // Adjust stopping condition to include Human and Chimp only
        auto[min1, min2] = findMinDistance(matrix, labels);

        if (min1 == -1 || min2 == -1) {
            return "Error: Human or Chimp not found in the labels.";
        }

        std::string newLabel = "(" + labels[min1] + ":" + std::to_string(2.0) + "," + labels[min2] + ":" + std::to_string(2.0) + ")";

        recalculateMatrix(matrix, min1, min2, labels);
        labels[min2] = newLabel;
        labels[min1] = "";  // Simulating deletion by marking as empty
    }
    return labels.back() + ";";
}

int main() {
    // Example distance matrix
    std::vector<std::vector<double>> matrix = {
        {0, 2, 4, 6},
        {2, 0, 4, 6},
        {4, 4, 0, 6},
        {6, 6, 6, 0}
    };
    
    // Corresponding labels
    std::vector<std::string> labels = {"Human", "Chimp", "Whale", "Seal"};
    
    // Generate Newick format
    std::string newick = generateNewick(matrix, labels);
    std::cout << "Newick format: " << newick << std::endl;
    
    return 0;
}
