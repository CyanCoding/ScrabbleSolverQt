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
            std::vector<std::unordered_set<QString>> dictionary,
            QString letters) {

        std::unordered_set<QString> permutations;

        // This bit of magic creates every permutation from length 1
        // to letters.length()
        std::vector<int> l;

        l.push_back(-1);
        for (long long i = 0; i < letters.length(); i++) {
            l.push_back(i);
        }

        do {
            QString temp = "";
            for (auto e : l) {
                if (e != -1) {
                    temp += letters[e];
                }
                else break;
            }

            if (algorithm::compare_with_dictionaries(dictionary, temp)) {
                permutations.insert(temp);
            }


        } while(std::next_permutation(l.begin(), l.end()));

        std::cout << permutations.size() << std::endl;

        return permutations;
    }
}
