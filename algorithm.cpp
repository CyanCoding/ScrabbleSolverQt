#include "algorithm.h"

namespace algorithm {
    // Get positions to be played in
    std::vector<std::vector<MainWindow::xy>> find_positions(QString** boardArray, MainWindow::xy pos, int maxLength) {
        std::vector<std::vector<MainWindow::xy>> all_positions;

        for (int i = 0; i < maxLength; i++) {
            std::vector<MainWindow::xy> found;
            found.push_back(pos); // This is sufficient for length 1
            all_positions.push_back(found);

            // This is for VERTICAL movement
            for (int j = 2; j < maxLength + 1; j++) {
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
                int up = j - 1;
                for (int k = 0; k < j; k++) {
                    // Add the intial point
                    struct MainWindow::xy newPos = { pos.x, pos.y };
                    found.push_back(newPos);

                    int hypothetical = pos.y;

                    for (int l = 0; l < up; l++) { // This moves up
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
                    for (int l = 0; l < down; l++) {
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
            for (int j = 2; j < maxLength + 1; j++) {
                found.clear();

                // Theres num + 1 positions for each letter amount
                /*
                 * 4 3 2 1 0
                 * ← - - - -
                 * 0 1 2 3 4
                 * - - - - →
                 */
                int left = 0;
                int right = j - 1;
                for (int k = 0; k < j; k++) {
                    // Add the intial point
                    struct MainWindow::xy newPos = { pos.x, pos.y };
                    found.push_back(newPos);

                    int hypothetical = pos.x;

                    for (int l = 0; l < right; l++) { // This moves right
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
                    for (int l = 0; l < left; l++) {
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
        }

        return all_positions;
    }

    // Generates valid board positions
    std::vector<QString**> generate_boards(std::vector<MainWindow::xy> positions,
                                           QString** boardArray,
                                           std::vector<QString> dictionary,
                                           std::vector<QString> permutations) {

        // Operate on every position
        for (int i = 0; i < positions.size(); i++) {
            // First we generate a new baord
            QString** newBoard = new QString*[15];
            for (int j = 0; j < 15; j++) {
                newBoard[j] = new QString[15];
            }

            // Then copy from the old board to the new board
            for (int j = 0; j < 15; j++) {
                for (int k = 0; k < 15; k++) {
                    // I have a hypothesis that if we simply copied every value
                    // over, it would change boardArray whenever we loaded
                    // new letters
                    if (boardArray[j][k] != "") {
                        newBoard[j][k] = boardArray[j][k];
                    }
                }
            }

            // Then we calculate the letter positions for this spot



        }



    }
}
