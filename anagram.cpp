#include "anagram.h"
#include "algorithm.h"  // algorithm::compare_with_dictionaries

#include <algorithm>    // std::sort
#include <string>       // std::string
#include <iostream>     // std::cout

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    // including lengths lower than it
    std::vector<std::unordered_set<QString>> read_permutations(
            std::vector<std::unordered_set<QString>> dictionary,
            QString letters) {

        std::unordered_set<QString> permutations;

        std::sort(letters.begin(), letters.end());
        do {
            if (algorithm::compare_with_dictionaries(dictionary, letters)) {
                std::cout << "!" << letters.toStdString() << std::endl;
                permutations.insert(letters);
            }
        } while (std::next_permutation(letters.begin(), letters.end()));

        // There aren't duplicates in our permutation list, but if
        // we are only taking from the first few letters there will
        // be, but we don't want duplicate boards at all costs.
        std::vector<std::unordered_set<QString>> all_lengths;
        std::unordered_set<QString>::const_iterator list;

        for (int i = 0; i < letters.length(); i++) {
            std::unordered_set<QString> permutations_used;
            for (QString anagram : permutations) {
                QString createdLetters = "";
                for (int j = 0; j < i; j++) {
                    createdLetters += anagram[j];
                }

                list = permutations_used.find(createdLetters);
                if (list != permutations_used.end()) {
                    continue; // It's not in the set already
                }
                if (createdLetters.toStdString() == "fir") {
                    std::cout << "SCORE" << std::endl;
                }
                if (algorithm::compare_with_dictionaries(dictionary, createdLetters)) {
                    permutations_used.insert(createdLetters);
                }
            }
            all_lengths.push_back(permutations_used);
        }

        all_lengths.push_back(permutations);

        return all_lengths;
    }
}
