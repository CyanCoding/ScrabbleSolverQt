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
    // Creates a two dimensional array 15x15
    QString** boardArray = new QString*[15];
    for (int i = 0; i < 15; i++) {
        boardArray[i] = new QString[15];
    }

    // Populates the array for each column and row
    for (int i = 0; i < ui->gridLayout->columnCount(); i++) {
      for (int j = 0; j < ui->gridLayout->rowCount(); j++) {
          if (ui->gridLayout->itemAtPosition(i, j) != nullptr) {
              // If the position cell isn't empty we get the widget
              auto* textEdit = (ui->gridLayout->itemAtPosition(i, j)->widget());
              if (textEdit->objectName() != "") {
                  // If the widget has an objectName, (only the TextEdits)
                  // cast it and work with it
                  QTextEdit* text = static_cast<QTextEdit*>(textEdit);
                  text->setText(text->toPlainText().toUpper());
                  boardArray[i][j] = text->toPlainText();
              }
          }
      }
    }

    return boardArray;
}

// When the "Solve" button is pressed
void MainWindow::on_pushButton_clicked() {
    QString letters = ui->letterBox->toPlainText();
    fill_board_array(ui);
}
