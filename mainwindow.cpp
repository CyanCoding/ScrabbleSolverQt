#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"          // fill_board_array()

#include <future>           // std::async
#include <fstream>          // std::file

// Runs when the window is opened
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

// Runs when the window is closed
MainWindow::~MainWindow() {
    delete ui;
}

/*
 * When the solve button is pressed
 *
 * We need to do the following:
 * - Get the board array
 * - Find anagrams of the letters in their hand
 * - Initialize or use a pre-made dictionary for comparing words
 * - Get positions that letters can be played in
 * - - For each position, find letter positions that can be played there
 * - - Compile those positions into a list
 * - - Check to see which of those form valid words
 * - - Calculate how many points each is worth
 * - - Resort by the amount of points
 *
 */
void MainWindow::on_pushButton_clicked() {
    QString letters = ui->letterBox->toPlainText();

    QString** boardArray = fill_board_array(ui); // A 15x15 array

    //std::vector<QString> dictionary = dictAsync.get();
    // TODO: Dictionary isn't loading?? and the async function is crashing when we wait
    auto dictionary = read_dictionary(5);

    ui->letterBox->setText(dictionary[30]);
}

