#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>       // std::vector
#include <QString>      // QString
#include "mainwindow.h" // struct xy

namespace algorithm {
    std::vector<QString**> generate_boards(std::vector<MainWindow::xy> positions, QString** boardArray);
}

#endif // ALGORITHM_H
