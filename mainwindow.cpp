#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"          // fill_board_array()
#include "anagram.h"        // anagram::read_permutations()

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
    QString letters = ui->letterBox->toPlainText();
    // Start the async to find anagrams from letters
    std::future<std::vector<QString>> permutation_async = std::async(anagram::read_permutations, letters);

    // Get board and available positions
    QString** boardArray = board::fill_board_array(ui); // A 15x15 array
    std::future<bool**> positions_async = std::async(board::find_positions, boardArray);

    std::vector<QString> permutations = permutation_async.get();
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
}

