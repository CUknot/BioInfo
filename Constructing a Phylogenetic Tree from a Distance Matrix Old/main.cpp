#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>

// Function to find the minimum distance
std::pair<int, int> findMinDistance(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    double minDist = std::numeric_limits<double>::max();
    std::pair<int, int> minPair = {0, 0};

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] < minDist) {
                minDist = matrix[i][j];
                minPair = {i, j};
            }
        }
    }
    return minPair;
}

// Function to generate Newick format
std::string generateNewick(const std::vector<std::vector<double>>& distMatrix, const std::vector<std::string>& labels) {
    int n = distMatrix.size();
    std::vector<std::string> currentLabels = labels;
    
    std::vector<std::vector<double>> matrix = distMatrix;
    
    while (matrix.size() > 1) {
        auto[min1, min2] = findMinDistance(matrix);

        std::vector<std::vector<double>> newMatrix(matrix.size() - 1, std::vector<double>(matrix.size() - 1));
        std::vector<std::string> newLabels;

        for (int i = 0, ni = 0; i < matrix.size(); ++i) {
            if (i == min1 || i == min2) continue;
            for (int j = 0, nj = 0; j < matrix.size(); ++j) {
                if (j == min1 || j == min2) continue;
                newMatrix[ni][nj++] = matrix[i][j];
            }
            ++ni;
        }
        
        newLabels = currentLabels;
        newLabels.erase(newLabels.begin() + std::max(min1, min2));
        newLabels.erase(newLabels.begin() + std::min(min1, min2));
        std::string newLabel = "(" + currentLabels[min1] + ":" + std::to_string(matrix[min1][min2] / 2) +
                               "," + currentLabels[min2] + ":" + std::to_string(matrix[min1][min2] / 2) + ")";
        newLabels.push_back(newLabel);

        for (int i = 0; i < newMatrix.size(); ++i) {
            for (int j = i; j < newMatrix.size(); ++j) {
                if (i == j) {
                    newMatrix[i][j] = 0.0;
                } else {
                    newMatrix[i][j] = (matrix[i][min1] + matrix[i][min2] - matrix[min1][min2]) / 2;
                    newMatrix[j][i] = newMatrix[i][j];
                }
            }
        }
        
        matrix = newMatrix;
        currentLabels = newLabels;
    }
    
    return currentLabels.front() + ";";
}

int main() {
    std::vector<std::vector<double>> distMatrix = {
        {0, 226, 249, 436, 958, 916, 730, 787, 785},
        {226, 0, 292, 436, 903, 905, 744, 802, 813},
        {249, 292, 0, 426, 927, 907, 735, 795, 791},
        {436, 436, 426, 0, 917, 946, 725, 767, 782},
        {958, 903, 927, 917, 0, 706, 730, 844, 846},
        {916, 905, 907, 946, 706, 0, 736, 840, 836},
        {730, 744, 735, 725, 730, 736, 0, 763, 760},
        {787, 802, 795, 767, 844, 840, 763, 0, 16},
        {785, 813, 791, 782, 846, 836, 760, 16, 0}
    };

    std::vector<std::string> labels = {"Cow", "Pig", "Horse", "Mouse", "Dog", "Cat", "Turkey", "Civet", "Human"};

    std::string newick = generateNewick(distMatrix, labels);

    std::cout << "Newick Format: " << newick << std::endl;

    return 0;
}