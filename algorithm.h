#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>       // std::vector
#include <QString>      // QString
#include "mainwindow.h" // struct xy

namespace algorithm {
    // Generates valid board positions
    std::vector<QString**> generate_boards(std::vector<MainWindow::xy> positions,
                                           QString** boardArray,
                                           std::vector<QString>,
                                           std::vector<QString> permutations);
}

#endif // ALGORITHM_H
