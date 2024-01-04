#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <iostream>
#include <unistd.h>

#include "WordGraph.h"
#include "WordGraph.cpp"

WordGraph constructGraph(const std::vector<std::string>& dictionary,
                         const std::string& targetWord) {
    WordGraph graph;

    // Add the target word to the graph
    graph.addEdge(targetWord, targetWord);

    // Iterate through the dictionary to add edges
    for (const auto& word : dictionary) {
        // Connect words with the same prefix and suffix as the target word
        if (word.length() == targetWord.length()) {
            int diffCount = 0;
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] != targetWord[i]) {
                    diffCount++;
                }
            }
            if (diffCount == 1) {
                graph.addEdge(word, targetWord);
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
    // Test Case: Adding Edges with One-Letter Difference (3 letter words)
    WordGraph graph3;
    graph3.addEdge("cat", "cot");
    graph3.addEdge("cot", "cog");
    graph3.addEdge("cog", "dog");

    std::cout << "Test Case: Adding Edges with One-Letter Difference(3 letter words)\n";
    std::cout << "Shortest Path from 'cat' to 'dog' (BFS):\n";
    bfs(graph3, "cat", "dog");
    std::cout << "Shortest Path from 'cat' to 'dog' (Dijkstra):\n";
    auto pathInfo3 = dijkstra(graph3, "cat", "dog");
    std::vector<std::string> shortestPath3 =
            getShortestPath(pathInfo3, "cat", "dog");
    for (const auto& word : shortestPath3) {
        std::cout << word << " ";
    }
    std::cout << "\n------------------------------------------\n";

    // Test Case: Adding Edges with One-Letter Difference (4 letter words)
    WordGraph graph4;
    graph4.addEdge("dark", "bark");
    graph4.addEdge("bark", "barn");

    std::cout << "Test Case: Adding Edges with One-Letter Difference(4 letter words)\n";
    std::cout << "Shortest Path from 'dark' to 'barn' (BFS):\n";
    bfs(graph4, "dark", "barn");
    std::cout << "Shortest Path from 'dark' to 'barn' (Dijkstra):\n";
    auto pathInfo4 = dijkstra(graph4, "dark", "barn");
    std::vector<std::string> shortestPath4 =
            getShortestPath(pathInfo4, "dark", "barn");
    for (const auto& word : shortestPath4) {
        std::cout << word << " ";
    }
    std::cout << "\n------------------------------------------\n";

    // Test Case: Adding Edges with One-Letter Difference (5 letter words)
    WordGraph graph5;
    graph5.addEdge("stone", "store");
    graph5.addEdge("store", "score");

    std::cout << "Test Case: Adding Edges with One-Letter Difference (5 letter words)\n";
    std::cout << "Shortest Path from 'stone' to 'score' (BFS):\n";
    bfs(graph5, "stone", "score");
    std::cout << "Shortest Path from 'stone' to 'score' (Dijkstra):\n";
    auto pathInfo5 = dijkstra(graph5, "stone", "score");
    std::vector<std::string> shortestPath5 =
            getShortestPath(pathInfo5, "stone", "score");
    for (const auto& word : shortestPath5) {
        std::cout << word << " ";
    }
    std::cout << "\n------------------------------------------\n";


    char buffer[FILENAME_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        std::cout << "Current working directory: " << buffer << std::endl;
    } else {
        std::cerr << "Error getting current working directory." << std::endl;
    }

    return 0;
}