#include "WordGraph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>  // Include for std::reverse

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


// Function to perform Breadth-First Search
void bfs(const WordGraph& graph, const std::string& startWord, const
std::string& targetWord) {
    std::queue<std::string> bfsQueue;
    std::unordered_set<std::string> visited;

    bfsQueue.push(startWord);
    visited.insert(startWord);

    while (!bfsQueue.empty()) {
        std::string currentWord = bfsQueue.front();
        bfsQueue.pop();

        // Process the current node (e.g., print it)
        std::cout << currentWord << " ";

        // Check if the target word is reached
        if (currentWord == targetWord) {
            std::cout << "\nTarget word reached!\n";
            return;
        }

        // Explore neighbors
        for (const auto& neighbor : graph.getNeighbors(currentWord)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                bfsQueue.push(neighbor);
            }
        }
    }

    std::cout << "\nTarget word not found.\n";
}


struct PathInfo {
    int distance;
    std::string previousWord;
};

// Dijkstra's algorithm to find the shortest path
std::unordered_map<std::string, PathInfo> dijkstra(const WordGraph&
graph, const std::string& startWord, const std::string& targetWord) {
    std::priority_queue<std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>, std::greater<>> pq;
    std::unordered_map<std::string, PathInfo> pathInfo;

    pathInfo[startWord] = {0, ""};
    pq.push({0, startWord});

    while (!pq.empty()) {
        std::string currentWord = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        for (const auto& neighbor : graph.getNeighbors(currentWord)) {
            int newDistance = currentDistance + 1;  // Assuming each edge has a weight of 1

            if (newDistance < pathInfo[neighbor].distance) {
                pathInfo[neighbor] = {newDistance, currentWord};
                pq.push({newDistance, neighbor});
            }
        }
    }

    return pathInfo;
}

// Function to retrieve the shortest path
std::vector<std::string> getShortestPath(const std::unordered_map<std::string, PathInfo>& pathInfo,
                                         const std::string& startWord,
                                         const std::string& targetWord) {
    std::vector<std::string> path;
    std::string currentWord = targetWord;

    while (!currentWord.empty()) {
        path.push_back(currentWord);
        currentWord = pathInfo.at(currentWord).previousWord;
    }

    // Reverse the path
    std::reverse(path.begin(), path.end());

    return path;
}