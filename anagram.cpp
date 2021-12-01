#include "anagram.h"
#include "algorithm.h"  // algorithm::compare_with_dictionaries

#include <algorithm>    // std::sort
#include <string>       // std::string
#include <iostream>     // std::cout
#include <set>          // std::set

namespace anagram {
    // This uses a recursive brute-force technique to find all permutations
    void inline crack(unsigned int length, char letters[], int word_length, QString current,
                      std::unordered_set<QString>* permutations, bool* stop) {
        if (length == 0 && *stop == false) {

            permutations->insert(current);

            return;
        }
        if (*stop == false) {
            for (int i = 0; i < word_length; i++) {
                crack(length - 1, letters, word_length, current + letters[i], permutations, stop);
            }
        }
    }

    // Finds every permutation (anagram non-duplicates) of the letters
    // including lengths lower than it
    std::unordered_set<QString> read_permutations(QString letters) {
        QByteArray ba = letters.toLocal8Bit();
        char *charArray = ba.data();

        std::unordered_set<QString> permutations;

        bool stop = false;
        unsigned int length = 1;
        while (stop == false) {
            crack(length, charArray, letters.length(), "", &permutations, &stop);
            length++;

            if (length == letters.length() + 1) {
                stop = true;
            }
        }

        std::cout << "Found " << permutations.size() << " permutations!" << std::endl;

        return permutations;
    }
}
