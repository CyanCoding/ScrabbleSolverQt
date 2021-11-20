#include "algorithm.h"

namespace algorithm {
    // Generates valid board positions
    std::vector<QString**> generate_boards(std::vector<MainWindow::xy> positions,
                                           QString** boardArray,
                                           std::vector<QString> dictionary) {

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


        }



    }
}
