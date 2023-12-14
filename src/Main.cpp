#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

#include "WordGraph.h"
#include "WordGraph.cpp"

WordGraph constructGraph(const std::vector<std::string>& dictionary) {
    WordGraph graph;

    // Iterate through the dictionary to add edges
    for (const auto& word : dictionary) {
        for (const auto& otherWord : dictionary) {
            if (word != otherWord && word.length() == otherWord.length()) {
                // Check if words differ by only one letter
                int diffCount = 0;
                for (size_t i = 0; i < word.length(); ++i) {
                    if (word[i] != otherWord[i]) {
                        diffCount++;
                    }
                }
                if (diffCount == 1) {
                    graph.addEdge(word, otherWord);
                }
            }
        }
    }

    return graph;
}
// Function to read the dictionary from a file
std::vector<std::string> readDictionary(const std::string& filename) {
    std::vector<std::string> dictionary;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            dictionary.push_back(word);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open the dictionary file.\n";
    }

    return dictionary;
}




int main() {
    // Load the dictionary
    std::vector<std::string> dictionary = readDictionary("dictionary.txt");

    // Construct the graph from the dictionary
    WordGraph wordGraph = constructGraph(dictionary);

    // Example: Play the word puzzle game
    std::string startWord = "Abi";
    std::string targetWord = "Ada";

    // Play the game
    playWordPuzzle(wordGraph, startWord, targetWord);

    return 0;
}