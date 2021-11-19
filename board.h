#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace board {
    QString** fill_board_array(Ui::MainWindow* ui);
}

#endif // BOARD_H
