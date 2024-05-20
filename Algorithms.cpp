/*
207192246
ShayNamir@gmail.com
*/
#define WHITE -1
#define GRAY 0
#define BLACK 1

#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <algorithm>
#include <climits>

using namespace ariel;
using namespace std;

static bool isPartOfC(size_t vertex, vector<bool>& visited, vector<bool>& recStack, vector<size_t>& parent, ariel::Graph& g, vector<size_t>& cycle);


bool Algorithms::isConnected(Graph g){
    if(g.getVertexNum()==0)
        return false;//Error

    vector<bool> visited(g.getVertexNum(), false);
    DFS(g, 0, visited);

    for (size_t i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;//The graph is connected
}
/*
This function will return the shortest path between two vertices in the graph.
Example:
    0 1 0
    1 0 1
    0 1 0
    shortestPath(g, 0, 2) -> 0->1->2
*/
string Algorithms::shortestPath(Graph g, size_t src, size_t dest) {
    size_t numNodes = g.getVertexNum(); // Get the number of nodes in the graph
    vector<int> dist(numNodes, INT_MAX); // Initialize all distances as infinity
    vector<size_t> parent(numNodes, SIZE_MAX); // Initialize all parents as not visited
    dist[src] = 0; // Set the distance of the source node as 0
    queue<size_t> q; // Initialize the queue
    q.push(src); // Push the source node to the queue
    while (!q.empty()) {
        size_t node = q.front(); // Get the front of the queue
        q.pop(); // Pop the front of the queue
        vector<size_t> neighbors = g.getNeighbors(node); // Get the neighbors of the current node
        for (size_t i = 0; i < neighbors.size(); i++) {
            if (dist[neighbors[i]] == INT_MAX) { // If the neighbor is not visited
                dist[neighbors[i]] = dist[node] + 1; // Update the distance of the neighbor
                parent[neighbors[i]] = node; // Update the parent of the neighbor
                q.push(neighbors[i]); // Push the neighbor to the queue
            }
        }
    }
    if (dist[dest] == INT_MAX) { // If the destination node is not visited
        return "-1"; // There is no path between the source and destination nodes
    }
    vector<size_t> path; // Initialize the path vector
    size_t current = dest;
    while (current != SIZE_MAX) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end()); // Reverse the path vector
    string result = "";
    for (size_t i = 0; i < path.size(); i++) {
        result += to_string(path[i]);
        if (i < path.size() - 1) {
            result += "->";
        }
    }
    return result;
}


/*
This function will return true if the graph contains a cycle, and false otherwise.
for example:
    0 1 0
    1 0 1
    0 1 0
    isContainsCycle(g) -> false
*/
bool Algorithms::isContainsCycle(Graph g){
    
    if(g.getVertexNum()==0)
        return false;//Error

    size_t numNodes = g.getVertexNum(); // Get the number of nodes in the graph
    vector<bool> visited(numNodes, false); // Initialize all nodes as not visited
    vector<bool> recStack(numNodes, false); // Initialize all nodes as not part of the recursion stack
    vector<size_t> parent(numNodes, SIZE_MAX); // Initialize all parents as not visited
    vector<size_t> cycle; // Initialize the cycle vector
    for (size_t i = 0; i < numNodes; i++) {
        if (!visited[i] && isPartOfC(i, visited, recStack, parent, g, cycle)) {
            return true;
        }
    }
    return false;
}
/*
Function isPartOfC
This function will return true if the vertex is part of the cycle, and false otherwise.
For example:
    0 1 1 0 0
    1 0 1 0 0
    1 1 0 1 0
    0 0 1 0 0
    0 0 0 0 0
    isPartOfC(0, visited, recStack, parent, g, cycle) -> true
*/
bool Algorithms::isPartOfC(size_t vertex, vector<bool>& visited, vector<bool>& recStack, vector<size_t>& parent, Graph& g, vector<size_t>& cycle){
    if (!visited[vertex]) {
        visited[vertex] = true;
        recStack[vertex] = true;
        vector<size_t> neighbors = g.getNeighbors(vertex);
        for (size_t i = 0; i < neighbors.size(); i++) {
            if (!visited[neighbors[i]] && isPartOfC(neighbors[i], visited, recStack, parent, g, cycle)) {
                parent[neighbors[i]] = vertex;
                return true;
            } else if (recStack[neighbors[i]]) {
                parent[neighbors[i]] = vertex;
                size_t current = vertex;
                cycle.push_back(current);
                current = parent[current];
                while (current != vertex) {
                    cycle.push_back(current);
                    current = parent[current];
                }
                cycle.push_back(vertex);
                return true;
            }
        }
    }
    recStack[vertex] = false;
    return false;
}
void Algorithms::DFS(Graph g, size_t src, vector<bool>& visited) {
    if(g.getVertexNum()==0)
        return;//Error

    // Mark the current node as visited
    visited[src] = true;
    vector<size_t> neighbors = g.getNeighbors(src);
    for (size_t i = 0; i < neighbors.size(); i++) {
        if (!visited[neighbors[i]]) {
            DFS(g, neighbors[i], visited);//Recursively visit the neighbors
        }
    }
}
/*
This function will check if the graph is bipartite and return the string representation of the bipartite graph.
Example:
    0 1 2 0 0
    1 0 3 0 0
    2 3 0 4 0
    0 0 4 0 5
    0 0 0 5 0
    isBipartite(g) -> The graph is bipartite: A={0, 2, 4}, B={1, 3}
*/
string Algorithms::isBipartite(Graph g){
    size_t numV = g.getVertexNum();
    queue<unsigned int> q;
     vector<int> a(numV, -1);
    vector<int> b(numV, WHITE);//colors
    for(unsigned int i=0; i<numV; i++){
        if(b[i] == WHITE){
            a[i] = 0;
            q.push(i);
            b[i] = GRAY;
            while(!q.empty()){
                size_t u = q.front();
                q.pop();
                for(size_t v=0; v<numV; v++){
                    if(g.getEdge(u,v) != 0){
                        if(b[v] == WHITE){
                            a[v] = !a[u];
                            b[v] = GRAY;
                            q.push(v);
                        } 
                        else if(v != u && a[v] == a[u]){
                             return "0";// Not bipartite
                        } 
                    }
                }
                b[u] = BLACK;
            }
        }
    }
    string A = "";
    string B = "";
    for(unsigned int i=0; i<numV; i++){
        if(a[i] == 0){ 
            if (A.empty()) { A += to_string(i); }
            else{ A += ", " + to_string(i); }
        }
        else{ 
            if (B.empty()) { B += to_string(i); }
            else{ B += ", " + to_string(i); }
        }
    }
    return "The graph is bipartite: A={"+A+"}, B={"+B+"}";
}
/*
Function to detect negative cycles in the graph by using the Bellman-Ford algorithm
and return the string representation of the negative cycle
*/
string Algorithms::negativeCycle(Graph g) {
    size_t numNodes = g.getVertexNum(); // Get the number of nodes in the graph
    vector<int> dist(numNodes, numeric_limits<int>::max()); // Initialize all distances as infinity
    dist[0] = 0; // Set the distance of the first node as 0
    vector<size_t> parent(numNodes, SIZE_MAX); // Initialize all parents as not visited
    size_t lastUpdated = SIZE_MAX; // Initialize the last updated node as not visited

    // Relax edges for (numNodes - 1) iterations
    for (size_t i = 0; i < numNodes - 1; i++) {
        for (size_t j = 0; j < numNodes; j++) {
            vector<size_t> neighbors = g.getNeighbors(j); // Get the neighbors of the current node
            for (size_t k = 0; k < neighbors.size(); k++) {
                if (dist[j] != numeric_limits<int>::max() && 
                    dist[j] + g.getEdge(j, neighbors[k]) < dist[neighbors[k]]) {
                    
                    dist[neighbors[k]] = dist[j] + g.getEdge(j, neighbors[k]); // Update the distance of the neighbor
                    parent[neighbors[k]] = j; // Update the parent of the neighbor
                    lastUpdated = neighbors[k]; // Update the last updated node
                }
            }
        }
    }

    // Detect negative cycle by checking for further relaxation
    for (size_t j = 0; j < numNodes; j++) {
        vector<size_t> neighbors = g.getNeighbors(j);
        for (size_t k = 0; k < neighbors.size(); k++) {
            if (dist[j] != numeric_limits<int>::max() && 
                dist[j] + g.getEdge(j, neighbors[k]) < dist[neighbors[k]]) {
                
                // Negative cycle detected, reconstruct cycle
                vector<size_t> cycle;
                size_t current = neighbors[k];
                cycle.push_back(current);
                current = parent[current];
                while (current != neighbors[k]) {
                    cycle.push_back(current);
                    current = parent[current];
                }
                cycle.push_back(neighbors[k]);

                // Construct result string
                string result = "";
                for (size_t i = cycle.size(); i > 0; i--) {
                    result += to_string(cycle[i - 1]);
                    if (i > 1) {
                        result += "->";
                    }
                }
                return result;
            }
        }
    }

    return "The graph does not contain a negative cycle";
}