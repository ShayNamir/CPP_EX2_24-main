# Graph Class and Algorithms

This project comprises a robust `Graph` class and an assortment of advanced graph algorithms. It's developed in C++ and supports both directed and undirected graphs, accommodating weighted and unweighted edges seamlessly.

## Graph Class

### Overview

The Graph module manages graphs represented by adjacency matrices. It facilitates a range of operations including graph loading, graph representation display, and manipulation of graph properties.

### Functions

- **loadGraph(vector<vector<int>> graph)**: Loads a graph, verifying its square matrix nature and assessing its directedness.
- **printGraph()**: Renders the adjacency matrix of the graph as a string.
- **getNumberOfEdges()**: Retrieves the count of edges, accounting for graph directionality.
- **getNumberOfVertices()**: Obtains the vertex count, equivalent to the adjacency matrix's dimension.
- **haveNegativeWeight()**: Determines if any edges possess negative weights.
- **getNeighbors(size_t vertex)**: Lists vertices directly connected to a specified vertex via an edge.
- **isDirected()**: Indicates whether the graph is directed.
- **getWeight(size_t src, size_t dest)**: Fetches the weight of the edge connecting specified vertices.
- **setDirect(bool directed)**: Adjusts the graph's directedness, ensuring adjacency matrix symmetry for undirected graphs.

### Operator Overloading

- **operator+( Graph &g1,  Graph &g2)**: Combines the weights of corresponding edges from two graphs.
- **operator+=( Graph &g)**: Adds the weights of corresponding edges from another graph to the current graph.
- **operator-( Graph &g1,  Graph &g2)**: Subtracts the weights of corresponding edges from one graph to another.
- **operator-=( Graph &g)**: Deducts the weights of corresponding edges from the current graph.
- **operator *(int scalar)**: Scales the weights of the graph by a scalar.
- **operator/(int scalar)**: Divides the weights of the graph by a scalar.
- **operator*=(int scalar)**: Multiplies the weights of the graph by a scalar.
- **operator/=(int scalar)**: Divides the weights of the graph by a scalar.
- **operator>( Graph &g1,  Graph &g2)**: Compares two graphs based on edge or vertex count.
- **operator>=( Graph &g1,  Graph &g2)**: Compares two graphs based on edge or vertex count.
- **operator<( Graph &g1,  Graph &g2)**: Compares two graphs based on edge or vertex count.
- **operator<=( Graph &g1,  Graph &g2)**: Compares two graphs based on edge or vertex count.
- **operator==( Graph &g1,  Graph &g2)**: Checks if two graphs are identical.
- **operator!=( Graph &g1,  Graph &g2)**: Checks if two graphs are distinct.
- **operator++()**: Prefix increment operator to increase all edge weights by 1.
- **operator++(int)**: Postfix increment operator to increase all edge weights by 1.
- **operator--()**: Prefix decrement operator to decrease all edge weights by 1.
- **operator--(int)**: Postfix decrement operator to decrease all edge weights by 1.
- **operator *( Graph &g)**: Multiplies the adjacency matrices of two graphs.
- **operator<<(ostream &out,  Graph &g)**: Outputs the adjacency matrix of the graph to an output stream.

## Graph Algorithms Library

### Features

#### Connectivity Functions

- **isConnected(Graph graph)**: Determines graph connectivity, leveraging DFS for undirected graphs and adapting for directed graphs.

#### Bipartiteness Check

- **isBipartite(Graph &graph)**: Utilizes BFS to ascertain graph bipartiteness, identifying vertex sets for each color.

#### Shortest Path Algorithms

- **shortestPath(Graph graph, size_t src, size_t dest)**: Computes shortest paths using various algorithms tailored to different graph characteristics.

#### Cycle Detection

- **isContainsCycle(Graph &graph)**: Employs DFS to detect graph cycles, potentially returning the cycle path if found.

#### Negative Cycle Detection

- **negativeCycle(Graph graph)**: Implements a modified Bellman-Ford algorithm to identify negative weight cycles.

For the detailed explanation of each function and its usage, refer to the inline documentation within the source files.

## Operators

For a detailed explanation of operator overloading and its applications, consult the inline documentation provided within the source files.

## Printing by << Operator

For printing the graph's adjacency matrix, utilize the provided `operator<<` function with an appropriate output stream.

```cpp
friend ostream &operator<<(ostream &out, Graph &g);
