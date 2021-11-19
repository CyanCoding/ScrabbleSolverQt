/*
 * Author: CyanCoding, Camden Mac Leod
 * File created on Nov 18, 2021
 *
 * Used for operations with the board itself
 */

#include "board.h"

namespace board {
    // Fills in boardArray[15][15]
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

    // Designates playable positions on a 15x15 array with true/false
    bool** find_positions(QString** boardArray) {
        // Creates a two dimensional array
        bool** newBoard = new bool*[15];
        for (int i = 0; i < 15; i++) {
            newBoard[i] = new bool[15];
        }

        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                // Make sure it's an available spot and we haven't already found it
                if (!newBoard[i][j] && boardArray[i][j] != "") {
                    if (i > 0 && boardArray[i - 1][j] != "") {
                        newBoard[i - 1][j] = true;
                    }
                    if (i < 14 && boardArray[i + 1][j] == "") {
                        newBoard[i + 1][j] = true;
                    }
                    if (j > 0 && boardArray[i][j - 1] == "") {
                        newBoard[i][j - 1] = true;
                    }
                    if (j < 14 && boardArray[i][j + 1] == "") {
                        newBoard[i][j + 1] = true;
                    }
                }
            }
        }

        return newBoard;
    }
}
