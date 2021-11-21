#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"          // fill_board_array()
#include "anagram.h"        // anagram::read_permutations()
#include "algorithm.h"       // algorithm::generate_boards()

#include <future>           // std::async
#include <QFile>            // QFile
#include <QTextStream>      // QTextStream
#include <iostream>         // std::cout


// Reads :/dictionary.txt into a vector
std::vector<QString> read_dictionary() {
    std::vector<QString> dictionary_words;

    // Initialize the dictionary into dictionary_words

    QFile file(":/dictionary.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        std::cout << "ERROR: The dictionary file did not open properly" << std::endl;

        // We add one so size isn't 0, which would cause an error later
        // when we try to async.get() more than once
        dictionary_words.push_back("error");
        return dictionary_words;
    }

    QTextStream instream(&file);
    while (!instream.atEnd()) {
        dictionary_words.push_back(instream.readLine());
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

void display_board(Ui::MainWindow* ui, QString** board) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board[i][j] != "") {
                board::write_single(ui, board[i][j], i, j);
            }
        }
    }
}

void MainWindow::on_nextButton_clicked() {
    if (board_number == all_boards.size()) {
        std::cout << "We've reached the height limit!" << std::endl;
        return;
    }
    board_number += 250;
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

/*
 * When the solve button is pressed
 *
 * We need to do the following:
 * [x] Get the board array
 * [x] Find anagrams of the letters in their hand
 * [x] Initialize or use a pre-made dictionary for comparing words
 * [x] Get positions that letters can be played in
 * - [ ] For each position, find letter positions that can be played there
 * - [ ] Compile those positions into a list
 * - [ ] Check to see which of those form valid words
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
        void on_previousButton_clicked();
    }

    std::cout << "Assembling board..." << std::endl;
    // Get board and available positions
    QString** boardArray = board::fill_board_array(ui); // A 15x15 array
    std::future<bool**> positions_async = std::async(board::find_positions, boardArray);

    std::cout << "Creating permutations..." << std::endl;
    QString letters = ui->letterBox->toPlainText();
    // Start the async to find anagrams from letters
    std::future<std::vector<std::vector<QString>>> permutation_async = std::async(anagram::read_permutations, letters);

    bool** positions = positions_async.get();

    // We split the positions into four groups
    std::vector<xy> group1;
    std::vector<xy> group2;
    std::vector<xy> group3;
    std::vector<xy> group4;

    std::vector<xy> allPoints;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (positions[i][j] == true) {
                struct xy point = { i, j };
                allPoints.push_back(point);
            }
        }
    }

    for (unsigned long i = 0; i < allPoints.size(); i++) {
        if (i < allPoints.size() / 3) {
            group1.push_back(allPoints[i]);
        }
        else if (i < allPoints.size() / 2) {
            group2.push_back(allPoints[i]);
        }
        else if (i < allPoints.size() / 2 * 1.5) {
            group3.push_back(allPoints[i]);
        }
        else {
            group4.push_back(allPoints[i]);
        }
    }

    // dict_async only runs once, so we only need to update the dictionary once
    if (dictionary.size() == 0) {
        dictionary = dict_async.get();
    }

    // TODO: Try a two-dimensional vector for the board instead of an array

    // The meat of our program! This finds new boards based on free positions
    std::vector<std::vector<QString>> permutations = permutation_async.get();

    std::cout << "Starting first group (" << group1.size() << ")..." << std::endl;
    std::future<std::vector<QString**>> group1_async = std::async(
                algorithm::generate_boards, group1, boardArray, dictionary, permutations, letterLength);
//    std::future<std::vector<QString**>> group2_async = std::async(
//                algorithm::generate_boards, group2, boardArray, dictionary, permutations, letterLength);
//    std::future<std::vector<QString**>> group3_async = std::async(
//                algorithm::generate_boards, group3, boardArray, dictionary, permutations, letterLength);
//    std::future<std::vector<QString**>> group4_async = std::async(
//                algorithm::generate_boards, group4, boardArray, dictionary, permutations, letterLength);

    std::vector<QString**> group1_boards = group1_async.get();
//    std::vector<QString**> group2_boards = group2_async.get();
//    std::vector<QString**> group3_boards = group3_async.get();
//    std::vector<QString**> group4_boards = group4_async.get();

    for (QString** board : group1_boards) {
        all_boards.push_back(board);
    }
//    for (QString** board : group2_boards) {
//        all_boards.push_back(board);
//    }
//    for (QString** board : group3_boards) {
//        all_boards.push_back(board);
//    }
//    for (QString** board : group4_boards) {
//        all_boards.push_back(board);
//    }

    std::cout << "DONE! ";
    std::cout << all_boards.size() << std::endl;

}

