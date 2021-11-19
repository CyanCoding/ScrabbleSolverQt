#include "anagram.h"

#include <algorithm>    // std::sort

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    std::vector<std::string> read_permutations(std::string letters) {
        std::vector<std::string> permutations;

        std::sort(letters.begin(), letters.end());
        do {
            permutations.push_back(letters);
        } while (std::next_permutation(letters.begin(), letters.end()));

        return permutations;
    }
}
