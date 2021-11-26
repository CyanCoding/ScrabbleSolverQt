#ifndef ANAGRAM_H
#define ANAGRAM_H

#include "mainwindow.h"     // Ui::MainWindow

#include <unordered_set>    // std::unordered_set
#include <vector>           // std::vector
#include <string>           // std::string
#include <QString>          // QString

namespace anagram {
    // Finds every permutation (anagram non-duplicates) of the letters
    // including lengths lower than it. ONLY RETURNS REAL WORDS
    std::unordered_set<QString> read_permutations(
            std::unordered_set<QString> dictionary,
            QString letters);
}

#endif // ANAGRAM_H
