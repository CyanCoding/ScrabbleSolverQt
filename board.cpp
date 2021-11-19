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

    // Writes a value to a specific box on the board
    // Columns and rows start at 0, not 1.
    void write_single(Ui::MainWindow* ui, QString value, int column, int row) {

        // This might be super long and untidy, but it's probably the fastest
        // way to accomplish our task since we don't have to run
        // over the board every time to update a single spot
        switch (column) {
            case 0:
                switch (row) {
                    case 0:     ui->box0x0->setText(value); break;
                    case 1:     ui->box0x1->setText(value); break;
                    case 2:     ui->box0x2->setText(value); break;
                    case 3:     ui->box0x3->setText(value); break;
                    case 4:     ui->box0x4->setText(value); break;
                    case 5:     ui->box0x5->setText(value); break;
                    case 6:     ui->box0x6->setText(value); break;
                    case 7:     ui->box0x7->setText(value); break;
                    case 8:     ui->box0x8->setText(value); break;
                    case 9:     ui->box0x9->setText(value); break;
                    case 10:    ui->box0x10->setText(value); break;
                    case 11:    ui->box0x11->setText(value); break;
                    case 12:    ui->box0x12->setText(value); break;
                    case 13:    ui->box0x13->setText(value); break;
                    case 14:    ui->box0x14->setText(value); break;
                }
            break;
            case 1:
                switch (row) {
                    case 0:     ui->box1x0->setText(value); break;
                    case 1:     ui->box1x1->setText(value); break;
                    case 2:     ui->box1x2->setText(value); break;
                    case 3:     ui->box1x3->setText(value); break;
                    case 4:     ui->box1x4->setText(value); break;
                    case 5:     ui->box1x5->setText(value); break;
                    case 6:     ui->box1x6->setText(value); break;
                    case 7:     ui->box1x7->setText(value); break;
                    case 8:     ui->box1x8->setText(value); break;
                    case 9:     ui->box1x9->setText(value); break;
                    case 10:    ui->box1x10->setText(value); break;
                    case 11:    ui->box1x11->setText(value); break;
                    case 12:    ui->box1x12->setText(value); break;
                    case 13:    ui->box1x13->setText(value); break;
                    case 14:    ui->box1x14->setText(value); break;
                }
            break;
            case 2:
                switch (row) {
                    case 0:     ui->box2x0->setText(value); break;
                    case 1:     ui->box2x1->setText(value); break;
                    case 2:     ui->box2x2->setText(value); break;
                    case 3:     ui->box2x3->setText(value); break;
                    case 4:     ui->box2x4->setText(value); break;
                    case 5:     ui->box2x5->setText(value); break;
                    case 6:     ui->box2x6->setText(value); break;
                    case 7:     ui->box2x7->setText(value); break;
                    case 8:     ui->box2x8->setText(value); break;
                    case 9:     ui->box2x9->setText(value); break;
                    case 10:    ui->box2x10->setText(value); break;
                    case 11:    ui->box2x11->setText(value); break;
                    case 12:    ui->box2x12->setText(value); break;
                    case 13:    ui->box2x13->setText(value); break;
                    case 14:    ui->box2x14->setText(value); break;
                }
            break;
            case 3:
                switch (row) {
                    case 0:     ui->box3x0->setText(value); break;
                    case 1:     ui->box3x1->setText(value); break;
                    case 2:     ui->box3x2->setText(value); break;
                    case 3:     ui->box3x3->setText(value); break;
                    case 4:     ui->box3x4->setText(value); break;
                    case 5:     ui->box3x5->setText(value); break;
                    case 6:     ui->box3x6->setText(value); break;
                    case 7:     ui->box3x7->setText(value); break;
                    case 8:     ui->box3x8->setText(value); break;
                    case 9:     ui->box3x9->setText(value); break;
                    case 10:    ui->box3x10->setText(value); break;
                    case 11:    ui->box3x11->setText(value); break;
                    case 12:    ui->box3x12->setText(value); break;
                    case 13:    ui->box3x13->setText(value); break;
                    case 14:    ui->box3x14->setText(value); break;
                }
            break;
            case 4:
                switch (row) {
                    case 0:     ui->box4x0->setText(value); break;
                    case 1:     ui->box4x1->setText(value); break;
                    case 2:     ui->box4x2->setText(value); break;
                    case 3:     ui->box4x3->setText(value); break;
                    case 4:     ui->box4x4->setText(value); break;
                    case 5:     ui->box4x5->setText(value); break;
                    case 6:     ui->box4x6->setText(value); break;
                    case 7:     ui->box4x7->setText(value); break;
                    case 8:     ui->box4x8->setText(value); break;
                    case 9:     ui->box4x9->setText(value); break;
                    case 10:    ui->box4x10->setText(value); break;
                    case 11:    ui->box4x11->setText(value); break;
                    case 12:    ui->box4x12->setText(value); break;
                    case 13:    ui->box4x13->setText(value); break;
                    case 14:    ui->box4x14->setText(value); break;
                }
            break;
            case 5:
                switch (row) {
                    case 0:     ui->box5x0->setText(value); break;
                    case 1:     ui->box5x1->setText(value); break;
                    case 2:     ui->box5x2->setText(value); break;
                    case 3:     ui->box5x3->setText(value); break;
                    case 4:     ui->box5x4->setText(value); break;
                    case 5:     ui->box5x5->setText(value); break;
                    case 6:     ui->box5x6->setText(value); break;
                    case 7:     ui->box5x7->setText(value); break;
                    case 8:     ui->box5x8->setText(value); break;
                    case 9:     ui->box5x9->setText(value); break;
                    case 10:    ui->box5x10->setText(value); break;
                    case 11:    ui->box5x11->setText(value); break;
                    case 12:    ui->box5x12->setText(value); break;
                    case 13:    ui->box5x13->setText(value); break;
                    case 14:    ui->box5x14->setText(value); break;
                }
            break;
            case 6:
                switch (row) {
                    case 0:     ui->box6x0->setText(value); break;
                    case 1:     ui->box6x1->setText(value); break;
                    case 2:     ui->box6x2->setText(value); break;
                    case 3:     ui->box6x3->setText(value); break;
                    case 4:     ui->box6x4->setText(value); break;
                    case 5:     ui->box6x5->setText(value); break;
                    case 6:     ui->box6x6->setText(value); break;
                    case 7:     ui->box6x7->setText(value); break;
                    case 8:     ui->box6x8->setText(value); break;
                    case 9:     ui->box6x9->setText(value); break;
                    case 10:    ui->box6x10->setText(value); break;
                    case 11:    ui->box6x11->setText(value); break;
                    case 12:    ui->box6x12->setText(value); break;
                    case 13:    ui->box6x13->setText(value); break;
                    case 14:    ui->box6x14->setText(value); break;
                }
            break;
            case 7:
                switch (row) {
                    case 0:     ui->box7x0->setText(value); break;
                    case 1:     ui->box7x1->setText(value); break;
                    case 2:     ui->box7x2->setText(value); break;
                    case 3:     ui->box7x3->setText(value); break;
                    case 4:     ui->box7x4->setText(value); break;
                    case 5:     ui->box7x5->setText(value); break;
                    case 6:     ui->box7x6->setText(value); break;
                    case 7:     ui->box7x7->setText(value); break;
                    case 8:     ui->box7x8->setText(value); break;
                    case 9:     ui->box7x9->setText(value); break;
                    case 10:    ui->box7x10->setText(value); break;
                    case 11:    ui->box7x11->setText(value); break;
                    case 12:    ui->box7x12->setText(value); break;
                    case 13:    ui->box7x13->setText(value); break;
                    case 14:    ui->box7x14->setText(value); break;
                }
            break;
            case 8:
                switch (row) {
                    case 0:     ui->box8x0->setText(value); break;
                    case 1:     ui->box8x1->setText(value); break;
                    case 2:     ui->box8x2->setText(value); break;
                    case 3:     ui->box8x3->setText(value); break;
                    case 4:     ui->box8x4->setText(value); break;
                    case 5:     ui->box8x5->setText(value); break;
                    case 6:     ui->box8x6->setText(value); break;
                    case 7:     ui->box8x7->setText(value); break;
                    case 8:     ui->box8x8->setText(value); break;
                    case 9:     ui->box8x9->setText(value); break;
                    case 10:    ui->box8x10->setText(value); break;
                    case 11:    ui->box8x11->setText(value); break;
                    case 12:    ui->box8x12->setText(value); break;
                    case 13:    ui->box8x13->setText(value); break;
                    case 14:    ui->box8x14->setText(value); break;
                }
            break;
            case 9:
                switch (row) {
                    case 0:     ui->box9x0->setText(value); break;
                    case 1:     ui->box9x1->setText(value); break;
                    case 2:     ui->box9x2->setText(value); break;
                    case 3:     ui->box9x3->setText(value); break;
                    case 4:     ui->box9x4->setText(value); break;
                    case 5:     ui->box9x5->setText(value); break;
                    case 6:     ui->box9x6->setText(value); break;
                    case 7:     ui->box9x7->setText(value); break;
                    case 8:     ui->box9x8->setText(value); break;
                    case 9:     ui->box9x9->setText(value); break;
                    case 10:    ui->box9x10->setText(value); break;
                    case 11:    ui->box9x11->setText(value); break;
                    case 12:    ui->box9x12->setText(value); break;
                    case 13:    ui->box9x13->setText(value); break;
                    case 14:    ui->box9x14->setText(value); break;
                }
            break;
            case 10:
                switch (row) {
                    case 0:     ui->box10x0->setText(value); break;
                    case 1:     ui->box10x1->setText(value); break;
                    case 2:     ui->box10x2->setText(value); break;
                    case 3:     ui->box10x3->setText(value); break;
                    case 4:     ui->box10x4->setText(value); break;
                    case 5:     ui->box10x5->setText(value); break;
                    case 6:     ui->box10x6->setText(value); break;
                    case 7:     ui->box10x7->setText(value); break;
                    case 8:     ui->box10x8->setText(value); break;
                    case 9:     ui->box10x9->setText(value); break;
                    case 10:    ui->box10x10->setText(value); break;
                    case 11:    ui->box10x11->setText(value); break;
                    case 12:    ui->box10x12->setText(value); break;
                    case 13:    ui->box10x13->setText(value); break;
                    case 14:    ui->box10x14->setText(value); break;
                }
            break;
            case 11:
                switch (row) {
                    case 0:     ui->box11x0->setText(value); break;
                    case 1:     ui->box11x1->setText(value); break;
                    case 2:     ui->box11x2->setText(value); break;
                    case 3:     ui->box11x3->setText(value); break;
                    case 4:     ui->box11x4->setText(value); break;
                    case 5:     ui->box11x5->setText(value); break;
                    case 6:     ui->box11x6->setText(value); break;
                    case 7:     ui->box11x7->setText(value); break;
                    case 8:     ui->box11x8->setText(value); break;
                    case 9:     ui->box11x9->setText(value); break;
                    case 10:    ui->box11x10->setText(value); break;
                    case 11:    ui->box11x11->setText(value); break;
                    case 12:    ui->box11x12->setText(value); break;
                    case 13:    ui->box11x13->setText(value); break;
                    case 14:    ui->box11x14->setText(value); break;
                }
            break;
            case 12:
                switch (row) {
                    case 0:     ui->box12x0->setText(value); break;
                    case 1:     ui->box12x1->setText(value); break;
                    case 2:     ui->box12x2->setText(value); break;
                    case 3:     ui->box12x3->setText(value); break;
                    case 4:     ui->box12x4->setText(value); break;
                    case 5:     ui->box12x5->setText(value); break;
                    case 6:     ui->box12x6->setText(value); break;
                    case 7:     ui->box12x7->setText(value); break;
                    case 8:     ui->box12x8->setText(value); break;
                    case 9:     ui->box12x9->setText(value); break;
                    case 10:    ui->box12x10->setText(value); break;
                    case 11:    ui->box12x11->setText(value); break;
                    case 12:    ui->box12x12->setText(value); break;
                    case 13:    ui->box12x13->setText(value); break;
                    case 14:    ui->box12x14->setText(value); break;
                }
            break;
            case 13:
                switch (row) {
                    case 0:     ui->box13x0->setText(value); break;
                    case 1:     ui->box13x1->setText(value); break;
                    case 2:     ui->box13x2->setText(value); break;
                    case 3:     ui->box13x3->setText(value); break;
                    case 4:     ui->box13x4->setText(value); break;
                    case 5:     ui->box13x5->setText(value); break;
                    case 6:     ui->box13x6->setText(value); break;
                    case 7:     ui->box13x7->setText(value); break;
                    case 8:     ui->box13x8->setText(value); break;
                    case 9:     ui->box13x9->setText(value); break;
                    case 10:    ui->box13x10->setText(value); break;
                    case 11:    ui->box13x11->setText(value); break;
                    case 12:    ui->box13x12->setText(value); break;
                    case 13:    ui->box13x13->setText(value); break;
                    case 14:    ui->box13x14->setText(value); break;
                }
            break;
            case 14:
                switch (row) {
                    case 0:     ui->box14x0->setText(value); break;
                    case 1:     ui->box14x1->setText(value); break;
                    case 2:     ui->box14x2->setText(value); break;
                    case 3:     ui->box14x3->setText(value); break;
                    case 4:     ui->box14x4->setText(value); break;
                    case 5:     ui->box14x5->setText(value); break;
                    case 6:     ui->box14x6->setText(value); break;
                    case 7:     ui->box14x7->setText(value); break;
                    case 8:     ui->box14x8->setText(value); break;
                    case 9:     ui->box14x9->setText(value); break;
                    case 10:    ui->box14x10->setText(value); break;
                    case 11:    ui->box14x11->setText(value); break;
                    case 12:    ui->box14x12->setText(value); break;
                    case 13:    ui->box14x13->setText(value); break;
                    case 14:    ui->box14x14->setText(value); break;
                }
        }
    }

}
