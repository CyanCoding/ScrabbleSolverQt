#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <vector>       // std::vector
#include <string>       // std::string

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    std::vector<std::string> read_permutations(std::string letters);
}

#endif // ANAGRAM_H
