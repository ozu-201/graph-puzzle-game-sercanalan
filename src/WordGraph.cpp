
#include "WordGraph.h"


#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>


// Function to play the word puzzle game
bool playWordPuzzle(const WordGraph& graph, const std::string&
startWord, const std::string& targetWord) {
    std::unordered_set<std::string> visited;
    std::queue<std::stack<std::string>> bfsQueue;

    // Start BFS from the startWord
    bfsQueue.push(std::stack<std::string>({startWord}));

    while (!bfsQueue.empty()) {
        std::stack<std::string> currentPath = bfsQueue.front();
        bfsQueue.pop();

        std::string currentWord = currentPath.top();

        if (currentWord == targetWord) {
            // Found a path to the target word
            std::cout << "Path found: ";
            while (!currentPath.empty()) {
                std::cout << currentPath.top() << " ";
                currentPath.pop();
            }
            std::cout << std::endl;
            return true;
        }

        visited.insert(currentWord);

        // Explore neighbors
        for (const auto& neighbor : graph.getNeighbors(currentWord)) {
            if (visited.count(neighbor) == 0) {
                std::stack<std::string> newPath = currentPath;
                newPath.push(neighbor);
                bfsQueue.push(newPath);
            }
        }
    }

    // No path found
    std::cout << "No path found.\n";
    return false;
}
