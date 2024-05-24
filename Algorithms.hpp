/*
ID: 207192246
Email: ShayNamir@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp" 
#include <string>
#include <vector>
using namespace std; 


namespace ariel
{
        class Algorithms
        {
                public:
                static bool isConnected(Graph graph); // Check if the graph is connected
                static string shortestPath(Graph graph, size_t start, size_t end); // Find the shortest path between two vertices
                static bool isContainsCycle(Graph graph); // Check if the graph contains a cycle
                static string isBipartite(Graph graph); // Check if the graph is bipartite
                static string negativeCycle(Graph graph); // Check if the graph contains a negative cycle

                static void dfs(Graph graph, size_t vertex, vector<bool>& visited); // Depth First Search
                static bool isCyclicUtil(size_t vertex, vector<bool>& visited, vector<bool>& recStack, vector<size_t >& parent, const Graph graph, vector<size_t>& cycle); // Check if the graph contains a cycle
         };
               
}

#endif // ALGORITHMS_HPP