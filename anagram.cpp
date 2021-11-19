#include "anagram.h"

#include <algorithm>    // std::sort
#include <string>       // std::string

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    std::vector<QString> read_permutations(QString letters) {
        std::vector<QString> permutations;

        std::sort(letters.begin(), letters.end());
        do {
            permutations.push_back(letters);
        } while (std::next_permutation(letters.begin(), letters.end()));

        return permutations;
    }
}
