#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>       // std::vector
#include <QString>      // QString
#include "mainwindow.h" // struct xy

namespace algorithm {
    // Get positions to be played in
    // pos is the current pos we're working with. maxLength is the amount of letters player has
    std::vector<std::vector<MainWindow::xy>> find_positions(
            std::vector<std::vector<QString>> boardArray, MainWindow::xy pos, int maxLength);

    // Checks to see if the board only contains valid words
    bool valid_word(std::vector<std::vector<QString>> board, std::vector<QString> dictionary);

    // Generates valid board positions
    std::vector<std::vector<std::vector<QString>>> generate_boards(std::vector<MainWindow::xy> positions,
                                           std::vector<std::vector<QString>> boardArray,
                                           std::vector<QString>,
                                           std::vector<std::vector<QString>> permutations,
                                           int letters);
}

#endif // ALGORITHM_H
