#include "anagram.h"
#include "algorithm.h"  // algorithm::compare_with_dictionaries

#include <algorithm>    // std::sort
#include <string>       // std::string
#include <iostream>     // std::cout
#include <set>          // std::set

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    // including lengths lower than it
    std::unordered_set<QString> read_permutations(
            std::unordered_set<QString> dictionary,
            QString letters) {

        // Send letters to a word map
        std::map wordMap = std::map<QChar, int>{};

        for (QChar c : letters) {
            wordMap[c]++;
        }

        std::unordered_set<QString> validWords;

        for (QString dict : dictionary) {
            if (dict == "") {
                continue;
            }

            // Send word to test to word map
            std::map word2Map = std::map<QChar, int>{};
            for (QChar c : dict) {
                word2Map[c]++;
            }

            // Check if word to test is made up of word map
            bool valid = true;
            for (std::pair<QChar, int> p : word2Map) {
                if (p.second > wordMap[p.first]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                validWords.insert(dict);
            }
        }

        std::cout << "Finished creating permutations ("
                  << validWords.size() << ")" << std::endl;
        return validWords;
    }
}
