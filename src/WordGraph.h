#ifndef GRAPH_PUZZLE_GAME_SERCANALAN_WORDGRAPH_H
#define GRAPH_PUZZLE_GAME_SERCANALAN_WORDGRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class WordGraph {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>>
            adjacencyList;

public:
    // Function to add an edge between two words
    void addEdge(const std::string& word1, const std::string& word2) {
        adjacencyList[word1].insert(word2);
        adjacencyList[word2].insert(word1);
    }

    // Function to check if two words are connected
    bool areConnected(const std::string& word1, const std::string&
    word2) const {
        auto it = adjacencyList.find(word1);
        return (it != adjacencyList.end() && it->second.count(word2) > 0);
    }

    // Function to get neighbors of a word
    std::unordered_set<std::string> getNeighbors(const std::string&
    word) const {
        auto it = adjacencyList.find(word);
        return (it != adjacencyList.end()) ? it->second :
               std::unordered_set<std::string>();
    }
};


#endif //GRAPH_PUZZLE_GAME_SERCANALAN_WORDGRAPH_H