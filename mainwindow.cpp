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

/*
 * When the solve button is pressed
 *
 * We need to do the following:
 * [x] Get the board array
 * [x] Find anagrams of the letters in their hand
 * [x] Initialize or use a pre-made dictionary for comparing words
 * [ ] Get positions that letters can be played in
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

    QString** boardArray = board::fill_board_array(ui); // A 15x15 array

    // dict_async only runs once, so we only need to update the dictionary once
    if (dictionary.size() == 0) {
        dictionary = dict_async.get();
    }

    std::vector<QString> permutations = permutation_async.get();
}

