/*
207192246
ShayNamir@gmail.com
*/
#pragma once
#include "Graph.hpp" 
#include <vector>
#include <string>

namespace ariel {
    class Algorithms {
    private:
        static void DFS(Graph g, size_t v, std::vector<bool>& visited);
        static bool isPartOfC(size_t vertex, std::vector<bool>& visited, std::vector<bool>& recStack, std::vector<size_t>& parent, Graph& g, std::vector<size_t>& cycle);

    public:
        static bool isConnected(Graph g);
        static std::string shortestPath(Graph g, size_t src, size_t dest);
        static bool isContainsCycle(Graph g);
        static std::string isBipartite(Graph g);
        static std::string negativeCycle(Graph g);
    };
}
