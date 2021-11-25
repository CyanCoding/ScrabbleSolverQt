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

    bool compare_with_dictionaries(std::vector<std::unordered_set<QString>> dictionary, QString word) {
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

        int dictionaryToUse;
        switch(word.length()) {
            case 3:
                list = dictionary[0].find(word);
                dictionaryToUse = 0;
                break;
            case 4:
                list = dictionary[1].find(word);
                dictionaryToUse = 1;
                break;
            case 5:
                list = dictionary[2].find(word);
                dictionaryToUse = 2;
                break;
            case 6:
                list = dictionary[3].find(word);
                dictionaryToUse = 3;
                break;
            case 7:
                list = dictionary[4].find(word);
                dictionaryToUse = 4;
                break;
            case 8:
                list = dictionary[5].find(word);
                dictionaryToUse = 5;
                break;
            case 9:
                list = dictionary[6].find(word);
                dictionaryToUse = 6;
                break;
            default: // 10+
                list = dictionary[7].find(word);
                dictionaryToUse = 7;
                break;
        }

        if (list == dictionary[dictionaryToUse].end()) {
            // The word is not in the dictionary
            invalid_words.insert(word);
            return false;
        }
        valid_words.insert(word);
        return true;
    }


    bool valid_word(std::vector<std::vector<QString>> board, std::vector<std::unordered_set<QString>> dictionary) {
        std::vector<QString> words;
        for (unsigned long i = 0; i < 15; i++) {
            for (unsigned long j = 0; j < 15; j++) {
                if (board[i][j] != "") {
                    // We found a letter, so we assemble nearby letters and see if it's a word
                    // Remember i = y, j = x
                    QString horizontalWord = "";
                    QString verticalWord = "";

                    // We have to go from left to right since that's how
                    // words are spelled
                    int currentX = static_cast<int>(j);
                    int currentY = static_cast<int>(i);
                    if (currentX > 0 && board[currentY][currentX - 1] != "") {
                        currentX = j - 1;
                    }


                    // Navigate all the way to the left
                    if (currentX < 0) {
                        currentX = 0;
                    }
                    while (board[currentY][currentX] != "") {
                        currentX--;

                        if (currentX < 0) {
                            // We've reached the left side of the board
                            currentX = 0;
                            break;
                        }
                    }
                    // We just moved to a blank spot so move back
                    currentX++;

                    // Go from left to right and fill in horizontalWord
                    while (board[currentY][currentX] != "") {
                        horizontalWord += board[currentY][currentX];
                        currentX++;

                        if (currentX > 14) {
                            // We've reached the right side of the board
                            break;
                        }
                    }

                    if (horizontalWord.length() > 1) {
                        if (!compare_with_dictionaries(dictionary, horizontalWord)) {
                            return false;
                        }
                    }

                    // VERTICAL WORD


                    // Reset X so we can use it in calculating verticalWord
                    currentX = static_cast<int>(j);
                    currentY = static_cast<int>(i);
                    if (currentY > 0 && board[currentY - 1][currentX] != "") {
                        currentY = static_cast<int>(i) - 1;
                    }

                    // Navigate all the way to the top
                    if (currentY < 0) {
                        currentY = 0;
                    }
                    while (board[currentY][currentX] != "") {
                        currentY--;

                        if (currentY < 0) {
                            // We've reached the top of the board
                            currentY = 0;
                            break;
                        }
                    }

                    // We just moved from a blank spot so move up
                    currentY++;

                    // Go from top to bottom and fill verticalWord
                    while (board[currentY][currentX] != "") {
                        verticalWord += board[currentY][currentX];
                        currentY++;

                        if (currentY > 14) {
                            // We've reached the bottom of the board
                            break;
                        }
                    }

                    if (verticalWord.length() > 1) {
                        if (!compare_with_dictionaries(dictionary, verticalWord)) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }


    // Generates valid board positions
    std::unordered_set<std::vector<std::vector<QString>>> generate_boards(
            std::vector<MainWindow::xy> positions,
            std::vector<std::vector<QString>> boardArray,
            std::vector<std::unordered_set<QString>> dictionary,
            std::vector<std::vector<QString>> permutations,
            int letters) {

        std::customSet boards;


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

                std::vector<QString> length_permutations = permutations[pos.size()];

                // For each valid permutation of that length, fill into positions
                for (QString s : length_permutations) {
                    s = s.toLower();
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
                    boards.insert(newBoard);
                }
            }
        }

        return boards;
    }
}
