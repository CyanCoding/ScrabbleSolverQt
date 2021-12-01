#include "algorithm.h"

#include <algorithm>        // std::find
#include <iostream>         // std::cout FOR DEBUG

namespace algorithm {
    // Get positions to be played in
    std::vector<std::vector<MainWindow::xy>> find_positions(
            std::vector<std::vector<QString>> boardArray,
            MainWindow::xy pos, int maxLength) {

        std::vector<std::vector<MainWindow::xy>> all_positions;

        std::vector<MainWindow::xy> found;
        found.push_back(pos); // This is sufficient for length 1
        all_positions.push_back(found);

        // This is for VERTICAL movement
        for (int i = 2; i < maxLength + 1; i++) {
            found.clear();

            // Theres num + 1 positions for each letter amount
            /*
             * 0 | 4 ↑
             * 1 | 3 |
             * 2 | 2 |
             * 3 | 1 |
             * 4 ↓ 0 |
             */
            int down = 0;
            int up = i - 1;
            for (int j = 0; j < i; j++) {
                // Add the intial point
                struct MainWindow::xy newPos = { pos.x, pos.y };
                found.push_back(newPos);

                int hypothetical = pos.y;

                for (int k = 0; k < up; k++) { // This moves up
                    while (hypothetical < 14) { // We do 14 instead of 15 because we add to it right after
                        hypothetical++; // Move lower on the board
                        if (boardArray[hypothetical][pos.x] == "") {
                            struct MainWindow::xy newPos = { pos.x, hypothetical };
                            found.push_back(newPos);
                            break; // We found a match so we exit
                        }
                    }
                }
                hypothetical = pos.y; // Reset hypothetical so we can move down
                for (int k = 0; k < down; k++) {
                    while (hypothetical > 1) { // We do 1 instead of 0 because we subtract from it right after
                        hypothetical--; // Move higher on the board
                        if (boardArray[hypothetical][pos.x] == "") {
                            struct MainWindow::xy newPos = { pos.x, hypothetical };
                            found.push_back(newPos);
                            break; // We found a match so we exit
                        }
                    }
                }

                all_positions.push_back(found);
                found.clear();
                down++;
                up--;
            }
        }

        // This is for HORIZONTAL movement
        for (int i = 2; i < maxLength + 1; i++) {
            found.clear();

            // Theres num + 1 positions for each letter amount
            /*
             * 4 3 2 1 0
             * ← - - - -
             * 0 1 2 3 4
             * - - - - →
             */
            int left = 0;
            int right = i - 1;
            for (int j = 0; j < i; j++) {
                // Add the intial point
                struct MainWindow::xy newPos = { pos.x, pos.y };
                found.push_back(newPos);

                int hypothetical = pos.x;

                for (int k = 0; k < right; k++) { // This moves right
                    while (hypothetical < 14) { // We do 14 instead of 15 because we add to it right after
                        hypothetical++; // Move righter on the board
                        if (boardArray[pos.y][hypothetical] == "") {
                            struct MainWindow::xy newPos = { hypothetical, pos.y };
                            found.push_back(newPos);
                            break; // We found a match so we exit
                        }
                    }
                }
                hypothetical = pos.x; // Reset hypothetical so we can move left
                for (int k = 0; k < left; k++) {
                    while (hypothetical > 1) { // We do 1 instead of 0 because we subtract from it right after
                        hypothetical--; // Move lefter on the board
                        if (boardArray[pos.y][hypothetical] == "") {
                            struct MainWindow::xy newPos = { hypothetical, pos.y };
                            found.push_back(newPos);
                            break; // We found a match so we exit
                        }
                    }
                }

                all_positions.push_back(found);
                found.clear();
                left++;
                right--;
            }
        }

        return all_positions;
    }

    bool compare_with_dictionaries(std::unordered_set<QString> dictionary, QString word) {
        std::unordered_set<QString>::const_iterator list;
        word = word.toLower();

        list = invalid_words.find(word);
        if (list != invalid_words.end()) {
            // It's in the invalid list
            return false;
        }

        list = valid_words.find(word);
        if (list != valid_words.end()) {
            // It's in the valid list
            return true;
        }

        list = dictionary.find(word);

        if (list == dictionary.end()) {
            // The word is not in the dictionary
            invalid_words.insert(word);
            return false;
        }
        valid_words.insert(word);
        return true;
    }


    bool valid_word(std::vector<std::vector<QString>> board, std::unordered_set<QString> dictionary) {
        std::unordered_set<QString> words;

        // Run once for horizontal, once for vertical

        for (int x = 0; x < 2; x++) {
            for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                    if (board[i][j] != "") {
                        QString temp;

                        // Horizontal words
                        while (board[i][j] != "") {
                            temp += board[i][j];

                            // During horizontal movement, we increase j since
                            // that is our x dimension. The opposite is true
                            // during vertical movement.
                            if (x == 1) j++;
                            else        i++;
                        }

                        // Our dictionary only consists of 3+ letter words
                        // so we don't want to iterate over 1 or 2 length words
                        if (temp.length() >= 3) {
                            words.insert (temp);
                        }

                    }
                }
            }
        }

        for (QString word : words) {
            std::cout << word.toStdString() << std::endl;
            // TODO: This algorithm doesn't work if you had two words down or a T shape
            if (!compare_with_dictionaries(dictionary, word.toLower())) {
                return false;
            }
        }

        return true;
    }


    // Generates valid board positions
    std::vector<std::vector<std::vector<QString>>> generate_boards(
            std::vector<MainWindow::xy> positions,
            std::vector<std::vector<QString>> boardArray,
            std::unordered_set<QString> dictionary,
            std::unordered_set<QString> permutations,
            int letters) {

        std::vector<std::vector<std::vector<QString>>> boards;


        // Operate on every position
        for (unsigned long i = 0; i < positions.size(); i++) {
            // Then we calculate the letter positions for this spot
            MainWindow::xy pos = positions[i];

            // found_pos is every position you can play letters in at any length
            std::vector<std::vector<MainWindow::xy>> found_pos = find_positions(boardArray, pos, letters);

            // Then we plug letters into the positions
            for (unsigned long j = 0; j < found_pos.size() - 1; j++) {
                // pos is a specific position out of found_pos
                std::vector<MainWindow::xy> pos = found_pos[j];
                // For each valid permutation of that length, fill into positions
                for (QString s : permutations) {
                    if (static_cast<unsigned long>(s.length()) != pos.size()) {
                        continue;
                    }

                    // Generate a new baord
                    std::vector<std::vector<QString>> newBoard(15, std::vector<QString>(15));

                    // Then copy from the old board to the new board
                    for (int k = 0; k < 15; k++) {
                        for (int l = 0; l < 15; l++) {
                            if (boardArray[k][l] != "") {
                                newBoard[k][l] = boardArray[k][l];
                            }
                        }
                    }

                    for (unsigned long k = 0; k < pos.size(); k++) {
                        // Then modify that board by filling in those positions
                        MainWindow::xy p = pos[k];
                        newBoard[p.y][p.x] = s[static_cast<int>(k)].toUpper(); // s is a (s)ingle permutation
                    }

                    // Check to make sure it's a valid word
                    if (valid_word(newBoard, dictionary)) {
                        boards.push_back(newBoard);
                    }
                }
            }
        }

        return boards;
    }
}
