/*
 * This is a test to see if I could split each position
 * into a separate thread and make the program run faster.
 * Unfortunately, I didn't see any real performance increase.
 */

#include "thread_distributor.h"
#include "algorithm.h"          // anagram::generate_boards

#include <iostream>             // std::cout

namespace td {
    // Splits our work into as many of 100 async threads as we need
    std::unordered_set<std::vector<std::vector<QString>>> distribute(
            std::vector<MainWindow::xy> positions,
            std::vector<std::vector<QString>> boardArray,
            std::vector<std::unordered_set<QString>> dictionary,
            std::vector<std::vector<QString>> permutations,
            int letters) {

        std::vector<std::vector<MainWindow::xy>> groups(100);
        const double original_size = positions.size();
        std::cout << original_size << " !!" << std::endl;

        unsigned long groupNumber = 0;
        while (positions.size() > 0) {
            groups[groupNumber].push_back(positions[positions.size() - 1]);
            positions.pop_back();
            groupNumber++;

            // Restart when we hit max
            if (groupNumber == groups.size()) {
                groupNumber = 0;
            }
        }

        std::vector<std::future<algorithm::customSet>> asyncs(100);

        // Start all of our async processes
        for (unsigned long i = 0; i < asyncs.size(); i++) {
            asyncs[i] = std::async(algorithm::generate_boards, groups[i], boardArray, dictionary, permutations, letters);
        }

        algorithm::customSet all_results;
        for (unsigned long i = 0; i < asyncs.size(); i++) {
            algorithm::customSet results = asyncs[i].get();
            std::cout << "group " << i << " finished" << std::endl;

            for (std::vector<std::vector<QString>> result : results) {
                all_results.insert(result);
            }
        }

        return all_results;
    }
}
