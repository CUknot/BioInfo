#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<std::string, char> codon_map = {
        {"UUU", 'F'}, {"CUU", 'L'}, {"AUU", 'I'}, {"GUU", 'V'},
        {"UUC", 'F'}, {"CUC", 'L'}, {"AUC", 'I'}, {"GUC", 'V'},
        {"UUA", 'L'}, {"CUA", 'L'}, {"AUA", 'I'}, {"GUA", 'V'},
        {"UUG", 'L'}, {"CUG", 'L'}, {"AUG", 'M'}, {"GUG", 'V'},
        {"UCU", 'S'}, {"CCU", 'P'}, {"ACU", 'T'}, {"GCU", 'A'},
        {"UCC", 'S'}, {"CCC", 'P'}, {"ACC", 'T'}, {"GCC", 'A'},
        {"UCA", 'S'}, {"CCA", 'P'}, {"ACA", 'T'}, {"GCA", 'A'},
        {"UCG", 'S'}, {"CCG", 'P'}, {"ACG", 'T'}, {"GCG", 'A'},
        {"UAU", 'Y'}, {"CAU", 'H'}, {"AAU", 'N'}, {"GAU", 'D'},
        {"UAC", 'Y'}, {"CAC", 'H'}, {"AAC", 'N'}, {"GAC", 'D'},
        {"UAA", '*'}, {"CAA", 'Q'}, {"AAA", 'K'}, {"GAA", 'E'},
        {"UAG", '*'}, {"CAG", 'Q'}, {"AAG", 'K'}, {"GAG", 'E'},
        {"UGU", 'C'}, {"CGU", 'R'}, {"AGU", 'S'}, {"GGU", 'G'},
        {"UGC", 'C'}, {"CGC", 'R'}, {"AGC", 'S'}, {"GGC", 'G'},
        {"UGA", '*'}, {"CGA", 'R'}, {"AGA", 'R'}, {"GGA", 'G'},
        {"UGG", 'W'}, {"CGG", 'R'}, {"AGG", 'R'}, {"GGG", 'G'}
    };

    string sequence;
    string protein = "";

    cin >> sequence;

    for (size_t i = 0; i < sequence.size(); i += 3) {
        std::string codon = sequence.substr(i, 3);
        if (codon_map.find(codon) != codon_map.end()) {
            char amino_acid = codon_map[codon];
            if (amino_acid == '*') break;
            protein += amino_acid;
        } else {
            std::cerr << "Invalid codon: " << codon << std::endl;
        }
    }

    std::cout << protein << std::endl;
    return 0;
}
