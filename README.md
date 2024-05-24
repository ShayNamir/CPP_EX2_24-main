
# Graph Class and Algorithms

This project includes a comprehensive `Graph` class and several sophisticated graph algorithms. It is implemented in C++ and supports both directed and undirected graphs, with capabilities for handling weighted and unweighted edges.

## Graph Class

### Overview

The Graph library manages graphs represented as adjacency matrices. It supports operations such as loading graphs, printing graph details, and manipulating graph properties.

### Functions

- **loadGraph(vector<vector<int>> graph)**: Loads a graph and check if it squre matrix and directed ot not.
- **printGraph()**: Outputs the graph's adjacency matrix as a string.
- **getNumberOfEdges()**: Returns the number of edges, considering the graph's directed or undirected nature.
- **getNumberOfVertices()**: Returns the number of vertices, which corresponds to the dimension of the adjacency matrix.
- **haveNegativeWeight()**: Determines if any edges have negative weights.
- **getNeighbors(size_t vertex)**: Lists all vertices connected directly by an edge to the specified vertex.
- **isDirected()**: Indicates whether the graph is directed.
- **getWeight(size_t src, size_t dest)**: Retrieves the weight of the edge between specified vertices.
- **setDirect(bool directed)**: Adjusts the graph to be directed or undirected, ensuring symmetry in the adjacency matrix for undirected graphs.

### Operator Overloading

- **operator+( Graph &g1,  Graph &g2)**: Adds the weights of corresponding edges of two graphs.
- **operator+=( Graph &g)**: Adds the weights of corresponding edges to the current graph.
- **operator-( Graph &g1,  Graph &g2)**: Subtracts the weights of corresponding edges of two graphs.
- **operator-=( Graph &g)**: Subtracts the weights of corresponding edges from the current graph.
- **operator *(int scalar)**: Multiplies the weights of the graph by a scalar.
- **operator/(int scalar)**: Divides the weights of the graph by a scalar.
- **operator*=(int scalar)**: Multiplies the weights of the graph by a scalar.
- **operator/=(int scalar)**: Divides the weights of the graph by a scalar.
- **operator>( Graph &g1,  Graph &g2)**: Compares two graphs to check if the first graph has more edges or vertices than the second graph.
- **operator>=( Graph &g1,  Graph &g2)**: Compares two graphs to check if the first graph has more or equal edges or vertices than the second graph.
- **operator<( Graph &g1,  Graph &g2)**: Compares two graphs to check if the first graph has fewer edges or vertices than the second graph.
- **operator<=( Graph &g1,  Graph &g2)**: Compares two graphs to check if the first graph has fewer or equal edges or vertices than the second graph.
- **operator==( Graph &g1,  Graph &g2)**: Checks if two graphs are equal.
- **operator!=( Graph &g1,  Graph &g2)**: Checks if two graphs are not equal.
- **operator++()**: Prefix increment operator to increase all edge weights by 1.
- **operator++(int)**: Postfix increment operator to increase all edge weights by 1.
- **operator--()**: Prefix decrement operator to decrease all edge weights by 1.
- **operator--(int)**: Postfix decrement operator to decrease all edge weights by 1.
- **operator *( Graph &g)**: Multiplies the adjacency matrices of two graphs.
- **operator<<(ostream &out,  Graph &g)**: Outputs the graph's adjacency matrix to an output stream.

## Graph Algorithms Library

### Features

#### Connectivity Functions

- **isConnected(Graph graph)**:
  - For undirected graphs, checks connectivity using DFS to ensure all nodes are reachable from any node.
  - For directed graphs, assesses strong connectivity and weak connectivity by modifying edge directionality temporarily.

#### Bipartiteness Check

- **isBipartite(Graph &graph)**:
  - Uses BFS to determine if the graph can be two-colored, which would confirm it as bipartite, and identifies the vertex sets for each color.

#### Shortest Path Algorithms

- **shortestPath(Graph graph, size_t src, size_t dest)**:
  - Finds the shortest path using Dijkstra's algorithm for non-negative weight graphs, Bellman-Ford for negative weights, and BFS for unweighted graphs.

#### Cycle Detection

- **isContainsCycle(Graph &graph)**:
  - Utilizes DFS to detect the presence of any cycles in the graph, capable of returning the path of the cycle if found.

#### Negative Cycle Detection

- **negativeCycle(Graph graph)**:
  - Employs a modified Bellman-Ford algorithm to detect negative weight cycles, crucial for accurate application of certain shortest path algorithms.

and change the words` is represented as an adjacency matrix, where `[i][j] == 0` means no edge between vertices `i` and `j`.

## Operators

### Addition Operators (+, +=)

1. **`+`**: Adds two graphs only if they have the same number of vertices (same size). Allows us to do:  
   `g3 = g1 + g2`

2. **`+=`**: Adds another graph of the same size to the graph itself (otherwise throws an exception).  
   Example: `g1 += g2`

3. **`+g`**: Unary **`+`**, returns the graph itself.

### Subtraction Operators (-, -=)

1. **`-`**: Subtracts two graphs only if they have the same number of vertices (same size). Allows us to do:  
   `g3 = g1 - g2`

2. **`-=`**: Subtracts another graph of the same size from the graph itself (otherwise throws an exception).  
   Example: `g1 -= g2`

3. **`-g`**: Unary **`-`**, switches the sign (like multiplying by -1) of each non-zero element (i.e., where there is an edge).

### Multiplication Operators (*, *=)

We have two types of multiplication:

1. **Multiply two graphs `g1 * g2`**: Multiplies their adjacency matrices, applying rules of linear algebra, then initializes all diagonal elements to 0 to maintain the graph format.

2. **Multiply by a scalar**:  
   - `g * 2`
   - `2 * g`

   The first format will be a class function, and the second requires a function outside the class but within the namespace.  
   This is because the `operator*` function outside the class is needed for a binary operator where the left-hand operand is not of the class type.

### Division Operator (/=)

The division operator is defined only on a graph with a non-zero scalar. It traverses the matrix and divides each edge by this scalar.

### Increment and Decrement Operators (prefix ++, postfix ++)

- **Prefix ++**: Allows us to do `++g` or `--g`, increment or decrement by 1, only if the edge is not 0.  
  This means we're incrementing (or decreasing) `g` before we use it or perform a function on it.  
  Example: `g2 = ++g1` means `g2` will be equal to `g1` after it has been incremented.

- **Postfix ++**: Allows us to do `g++` or `g--`, increment or decrement by 1, only if the edge is not 0.  
  This means we're incrementing (or decreasing) `g` after we use it or perform a function on it.  
  Example: `g2 = g1++` means `g2` will be equal to `g1` before it has been incremented.

### Comparison Operators

Let's define what it means for one graph to be greater than (or less than) another graph:

1. If `g1` is contained in `g2`, then `g1 < g2`.
2. If not, `g1 < g2` if `g2` has more edges than `g1`.
3. If not, `g1 < g2` if `g2` has a greater order (more vertices).

For each other operator, such as `<=` or `>=`, we'll use logical rules to create them.  
For example, to do `g2 >= g1`, we need `!(g1 < g2)`.

### Equality Operators (==, !=)

Two graphs are considered equal if they have the same order (number of vertices) and the same edges and weights between each pair of vertices. Otherwise, they are not equal.

### Printing by << Operator

This operator is not an operation on the graph but allows us to have access to the graph's private members using the `friend` keyword.  
The function signature uses `ostream` from the standard library `std`:

```cpp
friend ostream &operator<<(ostream &out, Graph &g);
