/*
ID: 207192246
Email: ShayNamir@gmail.com
*/

#include "Algorithms.hpp"
#include <queue>
#include <limits>
#include <climits>
#include <algorithm>


using namespace ariel;
using namespace std;

// Perform a depth-first search (DFS) traversal of the graph starting from the given vertex
void Algorithms::dfs(Graph graph, size_t vertex, vector<bool>& visited)
{
    // Mark the current vertex as visited
    visited[vertex] = true;

    // Get the neighbors of the current vertex
    vector<size_t> neighbors = graph.getNeighbors(vertex);

    // Recursively visit all unvisited neighbors
    for (size_t neighbor : neighbors)
    {
        if (!visited[neighbor])
        {
            dfs(graph, neighbor, visited);
        }
    }
}

// Check if the graph is connected by check directed or undirected graph and return true if the graph is connected
bool Algorithms::isConnected(Graph graph)
        {
            // Get the number of vertices in the graph
            size_t numVertices = graph.getNumberOfVertices();

            if (!graph.isDirected())
            {
                // Create a visited array to keep track of visited vertices
                vector<bool> visited(numVertices, false);

                // Perform DFS starting from the first vertex
                dfs(graph, 0, visited);

                // Check if all vertices have been visited
                for (bool v : visited)
                {
                    if (!v)
                        return false;
                }

                return true;
            }
            else
            {
                // Create a visited array to keep track of visited vertices
                vector<bool> visited(numVertices, false);

                // Perform DFS on all vertices
                for (size_t i = 0; i < numVertices; i++)
                {
                    dfs(graph, i, visited);
                    for (bool v : visited)
                    {
                        if (!v)
                        {
                            // maybe its weakly connected
                            graph.setDirect(false);
                            if (isConnected(graph) == false)
                            {
                                return false;
                            }
                            return true;
                        }
                    }
                    visited.assign(numVertices, false); // Reset the visited array
                }
                return true;
            }
        }

// Check if the graph is bipartite by using the Breadth-First Search (BFS) algorithm
string Algorithms::isBipartite(Graph grp) 
{

    size_t numNodes = grp.getNumberOfVertices(); // Get the number of nodes in the graph
    vector<int> colorArr(numNodes, -1); // Initialize all nodes as not colored
    vector<size_t> setA, setB; // Initialize the two sets A and B  to store the nodes

    for (size_t i = 0; i < numNodes; i++) 
    {
        if (colorArr[i] == -1) // If the node is not colored
         {
            queue<size_t> q; // Initialize a queue to store the nodes
            q.push(i);
            colorArr[i] = 1; // Color the node with color 1

            while (!q.empty()) 
            {
                size_t u = q.front(); // Get the first node in the queue
                q.pop(); // Remove the first node from the queue
                vector<size_t> neighbors = grp.getNeighbors(u); // Get the neighbors of the current node

                for (size_t v: neighbors)  // Loop through the neighbors of the current node
                {
                    if (colorArr[v] == -1) // If the neighbor is not colored
                    {
                        colorArr[v] = 1 - colorArr[u]; // Color the neighbor with the opposite color of the current node
                        q.push(v); 
                    } 
                    else if (colorArr[v] == colorArr[u]) // If the neighbor has the same color as the current node
                    {
                        return "0"; // The graph is not bipartite
                    }
                }
            }
        }
    }

    // The graph is bipartite and we need to store the nodes in the two sets A and B
    for (size_t i = 0; i < numNodes; i++) // Loop through all the nodes
    {
        if (colorArr[i] == 1) // If the node is colored with color 1
        {
            setA.push_back(i);
        } 
        else // If the node is colored with color 0
        {
            setB.push_back(i);
        }
    }

    // Create a string representation of the two sets A and B
    string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); i++) 
    {
        result += std::to_string(setA[i]);
        if (i != setA.size() - 1) 
        {
            result += ", ";
        }
    }

    result += "}, B={";
    for (size_t i = 0; i < setB.size(); i++) 
    {
        result += std::to_string(setB[i]);
        if (i != setB.size() - 1) 
        {
            result += ", ";
        }
    }
    result += "}";

    return result; // Return the result string representation of the two sets A and B
}

// the function return the shortest path between two nodes in the graph by using the Bellman-Ford algorithm
string Algorithms::shortestPath(Graph grp, size_t start, size_t end) 
{
    size_t numNodes = grp.getNumberOfVertices(); // Get the number of nodes in the graph
    vector<int> dist(numNodes, numeric_limits<int>::max()); // Initialize all nodes with infinite distance
    vector<size_t> pred(numNodes, numeric_limits<size_t>::max()); // Initialize all parents of the nodes as max value
    dist[start] = 0;

    // Relax all edges |V| - 1 times
    bool updated = false;
    for (size_t i = 0; i < numNodes - 1; i++) 
    {
        updated = false;
        for (auto edge : grp.getEdges()) 
        {
            size_t u = static_cast<size_t>(edge.first); // Get the first node of the edge
            size_t v = static_cast<size_t>(edge.second.first); // Get the second node of the edge
            int weight = edge.second.second;
            if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) // If there is a shorter path
            {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                updated = true; // bool variable to check if there is an update
            }
        }
        if (!updated) break; // If there is no update, then break the loop 
    }

    // Check for negative-weight cycles in the last iteration
    if (updated) 
    {
        for (auto edge : grp.getEdges()) 
        {
            size_t u = static_cast<size_t>(edge.first); // Get the first node of the edge
            size_t v = static_cast<size_t>(edge.second.first); // Get the second node of the edge
            int weight = edge.second.second;
            if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) // If there is a negative cycle
            {
                return "The graph contains a negative cycle"; // Return if a negative cycle is found
            }
        }
    }

    // If there is no path between the two nodes
    if (dist[end] == numeric_limits<int>::max()) 
    {
        return "-1";  // No path found
    }

    vector<size_t> path;
    for (size_t at = end; at != start; at = pred[at]) 
    {
        if (at == numeric_limits<size_t>::max()) // If there is no path between the two nodes
        {
            return "-1";  
        }
        path.push_back(at);
    }
    path.push_back(start); // Add the start node at the end

    reverse(path.begin(), path.end()); // Reverse the path vector to get the correct order

    // Create a string representation of the path
    string pathStr = to_string(path[0]);
    for (size_t i = 1; i < path.size(); ++i) 
    {
        pathStr += "->" + to_string(path[i]);
    }

    return pathStr;
}

// Function to detect cycles in the graph by using the Depth-First Search (DFS) algorithm
bool Algorithms::isCyclicUtil(size_t vertex, vector<bool>& visited, vector<bool>& recStack, vector<size_t >& parent,Graph graph, vector<size_t>& cycle)
{
    visited[vertex] = true; // Mark the current node as visited
    recStack[vertex] = true; // Mark the current node as part of the recursion stack
    bool isDirected = graph.isDirected(); // check if the graph is directed
    size_t numNodes = graph.getNumberOfVertices(); // Get the number of nodes in the graph

    // Recursively visit all unvisited neighbors
    for (size_t i = 0; i < numNodes; i++) 
    {
        if (graph.isEdge(vertex, i)) // If there is an edge between the current node and its neighbor
        {  
            if (!visited[i]) // If the neighbor is not visited 
            {
                parent[i] = vertex; // Set the parent of the neighbor to the current node
                if (isCyclicUtil(i, visited, recStack, parent, graph, cycle))  // Check if the neighbor is part of a cycle
                {
                    return true;
                }
            } 
            // If the neighbor is visited and part of the recursion stack
            else if ((isDirected && recStack[i]) || (!isDirected && recStack[i] && parent[vertex] != i)) 
            {
                // If a cycle is detected, trace back to print the cycle
                cycle.push_back(i);
                for (size_t p = vertex; p != i; p = parent[p]) 
                {
                    cycle.push_back(p);
                }
                cycle.push_back(i);  // Complete the cycle by adding the start node again
                reverse(cycle.begin(), cycle.end());

                // Print the cycle 
                //cout << "The cycle is: ";
                for (size_t j = 0; j < cycle.size(); j++) {
                    //cout << cycle[j];
                    //if (j < cycle.size() - 1) cout << "->";
                }
                //cout << endl;
                return true;
            }
        }
    }

    // Remove the current node from the recursion stack after visiting all neighbors
    recStack[vertex] = false;
    return false;
}

// Function to detect cycles in the graph by using the Depth-First Search (DFS) algorithm
bool Algorithms::isContainsCycle(Graph graph)
{
    
    size_t numNodes = graph.getNumberOfVertices(); // Get the number of nodes in the graph

    vector<bool> visited(numNodes, false); // Initialize all nodes as not visited

    vector<bool> recStack(numNodes, false); // Initialize all nodes as not part of the recursion stack

    vector<size_t> parent(numNodes, SIZE_MAX); // Initialize all parents as not visited

    vector<size_t> cycle; // Initialize the cycle vector

    for (size_t i = 0; i < numNodes; i++) 
    {
        if (!visited[i])  // If the node is not visited that means it is not part of the cycle
        {
            if (isCyclicUtil(i, visited, recStack, parent, graph, cycle)) // Check if the node is part of a cycle
            {
                return true;
            }
        }
    }
    return false;
}

// Function to detect negative cycles in the graph by using the Bellman-Ford algorithm
 string Algorithms::negativeCycle(Graph graph)
 {

    // if the graph is empty
    if (graph.getNumberOfEdges() == 0)
    {
        return "the graph does not contain a negative cycle"; // An empty graph is considered not to contain a negative cycle
    }

    //if the graph dont have a negative weight
    if (!graph.hasNegativeWeight())
    {
        return "the graph does not contain a negative cycle"; // A graph without negative weights is considered not to contain a negative cycle
    }

        unsigned int numV = graph.getNumberOfVertices(); // Get the number of vertices in the graph
        
        vector<int> dist(numV, INT_MAX); // Initialize all nodes with infinite distance
        vector<unsigned int> parent(numV, INT_MAX); // Initialize all parents of the nodes as max value

        // Relax all edges |V| - 1 times
        for(unsigned int v=0; v<numV; v++)
        {
            if(dist[v] == INT_MAX){
                dist[v] = 0;
                for(unsigned int u=0; u<numV-1; u++)
                {
                    for(unsigned int i=0; i<numV; i++)
                    {
                        for(unsigned int j=0; j<numV; j++)
                        {   
                            // if there is an edge that update the distance
                            if(graph.getEdge(i,j)!=0 && dist[j]>dist[i]+graph.getEdge(i,j)) 
                            {
                                if(!graph.isDirected() && parent[i] == j){ continue; }
                                dist[j] = dist[i] + graph.getEdge(i,j);
                                parent[j] = i;
                            }
                        }
                    }
                }

                // Check for negative-weight cycles in the last iteration
                for(unsigned int i=0; i<numV; i++)
                {
                    for(unsigned int j=0; j<numV; j++)
                    {
                        if(!graph.isDirected() && parent[i] == j){ continue; } // if the graph is not directed and the parent is the same as the child

                        // if there is a edge that update the distance
                        if(graph.getEdge(i,j)!=0 && dist[i]!=INT_MAX && dist[j]>dist[i]+graph.getEdge(i,j))
                        {
                            vector<int> visited(numV, 0);
                            dist[j] = dist[i] + graph.getEdge(i,j);
                            parent[j] = i;
                            string path = to_string(i); // start from end
                            unsigned int cur = parent[i];
                            int for_2nd_visit =0;

                            // trace back to print the cycle
                            while(cur != i)
                            {  
                                path = to_string(cur) + "->" + path;  
                                visited[cur] = 1;
                                cur = parent[cur];
                                if(visited[cur] && !for_2nd_visit){
                                    for_2nd_visit = 1;
                                    path = to_string(parent[cur]);
                                    i = parent[cur];
                                }
                            }
                            path = to_string(i) + "->" + path;
                            return "The cycle is: " + path;
                        }
                    }
                }
            }
        }
        return "the graph does not contain a negative cycle"; // Return if no negative cycle is found
    }


