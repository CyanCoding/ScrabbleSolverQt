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

// When the "Solve" button is pressed
void MainWindow::on_pushButton_clicked() {

}

