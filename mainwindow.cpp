#include "mainwindow.h"
#include "ui_mainwindow.h"

// Runs when the window is opened
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

// Runs when the window is closed
MainWindow::~MainWindow() {
    delete ui;
}

// Fills in boardArray
QString** fill_board_array(Ui::MainWindow* ui) {
    QString** boardArray = new QString*[15];
    for (int i = 0; i < 15; i++) {
        boardArray[i] = new QString[15];
    }

    boardArray[0][0] = ui->box0x0->toPlainText();
    ui->box0x10->setText(boardArray[0][0].toUpper());

    return boardArray;
    //MainWindow::boardArray[0][0] = ui->box0x0->toPlainText();
    //ui->box0x3->setText(MainWindow::boardArray[0][0]);
}

// When the "Solve" button is pressed
void MainWindow::on_pushButton_clicked() {
    QString letters = ui->letterBox->toPlainText();
    fill_board_array(ui);
}

