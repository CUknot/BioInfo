#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

std::string input;

class rotade {
    public:
        int start;

        rotade(int x) : start(x) {}

        bool operator<(const rotade& other) const {
            // Compare the two rotated versions of the string
            std::string rotation1 = input.substr(start) + input.substr(0, start);
            std::string rotation2 = input.substr(other.start) + input.substr(0, other.start);
            return rotation1 < rotation2;
        }
};

int main() {
    // File input and output
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    inputFile >> input;

    std::vector<rotade> v;
    int s = input.size();
    v.reserve(input.size());

    for(int i = 0; i < s; i++) v.push_back(rotade(i));

    std::sort(v.begin(), v.end());

    for (auto &x : v) {
        outputFile << input[(x.start + s - 1) % s];
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
