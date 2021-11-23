#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"          // fill_board_array()
#include "anagram.h"        // anagram::read_permutations()
#include "algorithm.h"       // algorithm::generate_boards()
#include "thread_distributor.h" //

#include <future>           // std::async
#include <QFile>            // QFile
#include <QTextStream>      // QTextStream
#include <iostream>         // std::cout


// Reads :/dictionaries into a vector
std::vector<std::unordered_set<QString>> read_dictionary() {
    std::vector<std::unordered_set<QString>> full_dictionary;

    // Initialize the dictionary into dictionary_words
    QString dictionary_paths[8] = {
        ":/dictionaries/3.txt",
        ":/dictionaries/4.txt",
        ":/dictionaries/5.txt",
        ":/dictionaries/6.txt",
        ":/dictionaries/7.txt",
        ":/dictionaries/8.txt",
        ":/dictionaries/9.txt",
        ":/dictionaries/10up.txt"
    };

    for (int i = 0; i < 8; i++) {
        std::unordered_set<QString> dictionary_words;

        QFile file(dictionary_paths[i]);
        if (!file.open(QIODevice::ReadOnly)) {
            std::cout << "ERROR: Dictionary " << i << " did not open properly!" << std::endl;
            continue;
        }

        QTextStream instream(&file);
        while (!instream.atEnd()) {
            dictionary_words.insert(instream.readLine());
        }
        full_dictionary.push_back(dictionary_words);
    }

    return full_dictionary;
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
        std::cout << "We've reached the height limit!" << std::endl;
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
    std::vector<std::vector<QString>> boardArray = board::fill_board_array(ui); // A 15x15 array

    std::cout << "Finding positions..." << std::endl;
    std::future<std::vector<std::vector<bool>>> positions_async
            = std::async(board::find_positions, boardArray);

    std::cout << "Creating permutations..." << std::endl;
    QString letters = ui->letterBox->toPlainText();
    // Start the async to find anagrams from letters
    std::future<std::vector<std::vector<QString>>> permutation_async = std::async(anagram::read_permutations, letters);

    std::vector<std::vector<bool>> positions = positions_async.get();

    // We split the positions into four groups
//    std::vector<xy> group1;
//    std::vector<xy> group2;
//    std::vector<xy> group3;
//    std::vector<xy> group4;

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

//    for (unsigned long i = 0; i < allPoints.size(); i++) {
//        if (i < allPoints.size() / 3) {
//            group1.push_back(allPoints[i]);
//        }
//        else if (i < allPoints.size() / 2) {
//            group2.push_back(allPoints[i]);
//        }
//        else if (i < allPoints.size() / 2 * 1.5) {
//            group3.push_back(allPoints[i]);
//        }
//        else {
//            group4.push_back(allPoints[i]);
//        }
//    }

    // dict_async only runs once, so we only need to update the dictionary once
    if (dictionary.size() == 0) {
        dictionary = dict_async.get();
    }

//    // The meat of our program! This finds new boards based on free positions
    std::vector<std::vector<QString>> permutations = permutation_async.get();

//    std::cout << "Starting first group (" << group1.size() << ")..." << std::endl;
//    std::future<std::vector<std::vector<std::vector<QString>>>> group1_async = std::async(
//                algorithm::generate_boards, group1, boardArray, dictionary, permutations, letterLength);
//    std::future<std::vector<std::vector<std::vector<QString>>>> group2_async = std::async(
//                algorithm::generate_boards, group2, boardArray, dictionary, permutations, letterLength);
//    std::future<std::vector<std::vector<std::vector<QString>>>> group3_async = std::async(
//                algorithm::generate_boards, group3, boardArray, dictionary, permutations, letterLength);
//    std::future<std::vector<std::vector<std::vector<QString>>>> group4_async = std::async(
//                algorithm::generate_boards, group4, boardArray, dictionary, permutations, letterLength);

//    std::vector<std::vector<std::vector<QString>>> group1_boards = group1_async.get();
//    std::cout << "Finished the first group" << std::endl;
//    std::vector<std::vector<std::vector<QString>>> group2_boards = group2_async.get();
//    std::cout << "Finished the second group" << std::endl;
//    std::vector<std::vector<std::vector<QString>>> group3_boards = group3_async.get();
//    std::cout << "Finished the third group" << std::endl;
//    std::vector<std::vector<std::vector<QString>>> group4_boards = group4_async.get();
//    std::cout << "Finished the fourth group" << std::endl;

//    for (std::vector<std::vector<QString>> board : group1_boards) {
//        all_boards.push_back(board);
//    }
//    for (std::vector<std::vector<QString>> board : group2_boards) {
//        all_boards.push_back(board);
//    }
//    for (std::vector<std::vector<QString>> board : group3_boards) {
//        all_boards.push_back(board);
//    }
//    for (std::vector<std::vector<QString>> board : group4_boards) {
//        all_boards.push_back(board);
//    }

    all_boards = td::distribute(allPoints, boardArray, dictionary, permutations, letterLength);

    std::cout << "DONE! ";
    std::cout << all_boards.size() << std::endl;
    ui->label->setText("Options: " + QString::number(all_boards.size()));
}


void MainWindow::on_prune_clicked() {
    if (dictionary.size() == 0) {
        std::cout << "The dictionary is 0!" << std::endl;
    }

//    bool valid = algorithm::valid_word(all_boards[all_boards.size() - 1], dictionary);
//    if (!valid) {
//        all_boards.pop_back();
//    }

    for (int i = 0; i < 20; i++) {
        bool valid = algorithm::valid_word(all_boards[i], dictionary);
        if (!valid) {
            all_boards.pop_back();
        }
    }

    ui->label->setText("Options: " + QString::number(all_boards.size()));
}

