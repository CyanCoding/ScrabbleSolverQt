#ifndef THREAD_DISTRIBUTOR_H
#define THREAD_DISTRIBUTOR_H

#include <vector>       // std::vector
#include <QString>      // QString
#include "mainwindow.h" // MainWindow::xy

namespace td {
    // Splits our work into as many of 100 async threads as we need
    std::vector<std::vector<std::vector<QString>>> distribute(
            std::vector<MainWindow::xy> positions,
            std::vector<std::vector<QString>> boardArray,
            std::vector<std::unordered_set<QString>> dictionary,
            std::vector<std::vector<QString>> permutations,
            int letters);
}

#endif // THREAD_DISTRIBUTOR_H
