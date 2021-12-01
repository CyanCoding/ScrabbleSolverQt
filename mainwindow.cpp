#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"              // fill_board_array()
#include "anagram.h"            // anagram::read_permutations()
#include "thread_distributor.h" // td::distribute()
#include "algorithm.h"          // algorithm::customSet


#include <future>               // std::async
#include <QFile>                // QFile
#include <QTextStream>          // QTextStream
#include <iostream>             // std::cout

// Reads :/dictionaries into a vector
std::unordered_set<QString> read_dictionary() {
    std::unordered_set<QString> full_dictionary;

    // Initialize the dictionary into dictionary_words
    QString path = ":/dictionary.txt";

    std::unordered_set<QString> dictionary_words;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << "ERROR: Dictionary did not open properly!" << std::endl;
    }

    QTextStream instream(&file);
    while (!instream.atEnd()) {
        dictionary_words.insert(instream.readLine());
    }

    return dictionary_words;
}

// Runs when the window is opened
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Start the async to read the dictionary and create a vector of words
    dict_async = std::async(read_dictionary);
}

// Runs when the window is closed
MainWindow::~MainWindow() {
    delete ui;
}

// Runs when the "Clear board" action is pressed in the menu
void MainWindow::on_actionClear_board_triggered() {
    // Populates the array for each column and row
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 16; j++) {
            if (ui->gridLayout->itemAtPosition(i, j) != nullptr) {
                // If the position cell isn't empty we get the widget
                auto* textEdit = (ui->gridLayout->itemAtPosition(i, j)->widget());
                if (textEdit->objectName() != "") {
                    // If the widget has an objectName, (only the TextEdits)
                    // cast it and work with it
                    QTextEdit* text = static_cast<QTextEdit*>(textEdit);
                    text->setText("");
                }
            }
        }
    }
}

void display_board(
        Ui::MainWindow* ui,
        std::vector<std::vector<QString>> board) {

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            board::write_single(ui, board[i][j], i, j);
        }
    }
}

void MainWindow::on_nextButton_clicked() {
    if (board_number >= all_boards.size() - 1) {
        std::cout << "We've reached the height limit!" <<
                     board_number << " / " << all_boards.size() << std::endl;
        return;
    }
    board_number += 1;
    display_board(ui, all_boards[board_number]);
}

void MainWindow::on_previousButton_clicked() {
    if (board_number == 0) {
        std::cout << "We're already viewing 0!" << std::endl;
        return;
    }

    board_number--;
    display_board(ui, all_boards[board_number]);
}

void MainWindow::on_pushButton_2_clicked() {
    // dict_async only runs once, so we only need to update the dictionary once
    if (dictionary.size() == 0) {
        dictionary = dict_async.get();
    }

    QString letters = ui->letterBox->toPlainText();
    permutations_async = std::async(anagram::read_permutations, letters);
}

/*
 * When the solve button is pressed
 *
 * We need to do the following:
 * [x] Get the board array
 * [x] Find anagrams of the letters in their hand
 * [x] Initialize or use a pre-made dictionary for comparing words
 * [x] Get positions that letters can be played in
 * - [x] For each position, find letter positions that can be played there
 * - [x] Compile those positions into a list
 * - [x] Check to see which of those form valid words
 * - [ ] Calculate how many points each is worth
 * - [ ] Resort by the amount of points
 *
 */
void MainWindow::on_pushButton_clicked() {
    all_boards.clear();

    int letterLength = ui->letterBox->toPlainText().length();
    if (letterLength == 0) {
        std::cout << "Letter box length must be at least 1!" << std::endl;
        return;
    }

    std::cout << "Assembling board..." << std::endl;
    // Get board and available positions
    std::vector<std::vector<QString>> boardArray = board::fill_board_array(ui); // A 15x15 array

    std::cout << "Finding positions..." << std::endl;
    std::future<std::vector<std::vector<bool>>> positions_async
            = std::async(board::find_positions, boardArray);


    QString letters = ui->letterBox->toPlainText();

    // dict_async only runs once, so we only need to update the dictionary once
    if (dictionary.size() == 0) {
        dictionary = dict_async.get();
    }

    // If the user hasn't already pressed the permutate button
    permutations = permutations_async.get();
    ui->label->setText("Done creating permutations!");

    std::vector<std::vector<bool>> positions = positions_async.get();

    std::vector<xy> allPoints;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (positions[i][j] == true) {
                // We have to switch these because i is y and j is x
                // but our struct is xy (nobody knows why lol)
                struct xy point = { j, i };
                allPoints.push_back(point);
            }
        }
    }

    all_boards = td::distribute(allPoints, boardArray, dictionary, permutations, letterLength);

    std::cout << "DONE! ";
    std::cout << all_boards.size() << std::endl;
    ui->label->setText("Options: " + QString::number(all_boards.size()));
}


void MainWindow::on_prune_clicked() {
    if (dictionary.size() == 0) {
        std::cout << "The dictionary is 0!" << std::endl;
    }

    for (int i = all_boards.size() - 1; i >= 0; i--) {
        bool valid = algorithm::valid_word(all_boards[i], dictionary);
        if (!valid) {
            all_boards.pop_back();
        }
    }

    ui->label->setText("Options: " + QString::number(all_boards.size()));
}

