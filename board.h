#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace board {
    // Converts the board into a 15x15 array
    QString** fill_board_array(Ui::MainWindow* ui);

    // Designates playable positions on a 15x15 array with true/false
    bool** find_positions(QString** boardArray);

    // Writes a value to a specific box on the board
    void write_single(Ui::MainWindow* ui, QString value, int column, int row);
}

#endif // BOARD_H
