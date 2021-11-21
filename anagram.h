#ifndef ANAGRAM_H
#define ANAGRAM_H

#include <vector>       // std::vector
#include <string>       // std::string
#include <QString>      // QString

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    // including lengths lower than it
    std::vector<std::vector<QString>> read_permutations(QString letters);
}

#endif // ANAGRAM_H
