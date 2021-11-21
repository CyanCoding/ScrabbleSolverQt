#include "anagram.h"

#include <algorithm>    // std::sort
#include <string>       // std::string
#include <iostream>     // std::cout

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    // including lengths lower than it
    std::vector<std::vector<QString>> read_permutations(QString letters) {
        std::vector<QString> permutations;

        std::sort(letters.begin(), letters.end());
        do {
            permutations.push_back(letters);
        } while (std::next_permutation(letters.begin(), letters.end()));

        // There aren't duplicates in our permutation list, but if
        // we are only taking from the first few letters there will
        // be, but we don't want duplicate boards at all costs.
        std::vector<std::vector<QString>> all_lengths;
        for (int i = 0; i < letters.length(); i++) {
            std::vector<QString> permutations_used;
            for (QString anagram : permutations) {
                QString createdLetters = "";
                for (int j = 0; j < i; j++) {
                    createdLetters += anagram[j];
                }

                if (std::find(permutations_used.begin(), permutations_used.end(), createdLetters)
                        != permutations_used.end()) {
                    // permutations_used contains createdLetters
                    continue;
                }
                else {
                    permutations_used.push_back(createdLetters);
                }
            }
            all_lengths.push_back(permutations_used);
        }

        all_lengths.push_back(permutations);

        return all_lengths;
    }
}
