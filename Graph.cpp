/*
ID: 207192246
Email: ShayNamir@gmail.com
*/

#include "Graph.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

// Load the graph to the object.
void Graph::loadGraph(vector<vector<int>> adjMatrix) 
{
    // Check if the graph is empty.
    if (adjMatrix.empty()) { throw invalid_argument("The graph is empty, please enter a new graph."); } 

    // Check if the graph is a square matrix.
    int size = adjMatrix.size();
    for (const auto& row : adjMatrix) 
    {
        if (row.size() != size) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }

    // Edge from a vertex to itself.
    for (size_t i = 0; i < adjMatrix.size(); ++i) 
    {
        if (adjMatrix[i][i] != 0) 
        {
            throw std::invalid_argument("Invalid graph: The graph has an edge from a vertex to itself.");
        }
    }

    //load the graph and check if it is directed
    this->matrix = adjMatrix;
    this->directed = isDirected();
}

// Print the number of vertices and edges in the graph and the graph itself.
string Graph::printGraph() 
{
    // Print the matrix like this: [1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]
    string result = "";
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        if (i == 0) 
        {
            result += "[";
        } 
        else 
        {
            ///pass to the next line
            result += "\n[";
        }
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (j == matrix[i].size() - 1) 
            {
                result += to_string(matrix[i][j]);
            } 
            else 
            {
                result += to_string(matrix[i][j]) + ", ";
            }
        }
        result += "]";
    }
    return result;

}

// Check if the graph is directed.
bool Graph::isDirected() 
{
    // Check if the graph is directed by checking if the adjacency matrix is symmetric.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (matrix[i][j] != matrix[j][i])
            {
                return true;
            }
        }
    }
    return false;
}

// Get the number of edges in the graph.
size_t Graph::getNumberOfEdges()  
{
    size_t countOfEdge = 0;

    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (matrix[i][j] != 0) // Check if there is an edge between two vertices.
            {
                countOfEdge++;
            }
        }
    }
    return countOfEdge;
}

// Get the neighbors of a vertex.
vector<size_t> Graph::getNeighbors(size_t vertex) 
{
    vector<size_t> neighbors;
    for (size_t i = 0; i < matrix[vertex].size(); ++i) 
    {
        if (matrix[vertex][i] != 0) // Check if there is an edge between two vertices.
        {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

// Get the number of nodes in the graph.
size_t Graph::getNumberOfVertices() { return matrix.size();}

// Get the weight of an edge.
int Graph::getWeight(int start, int end) 
{
    // Check if the node index is out of range.
    if (start < 0 || static_cast<size_t>(start) >= matrix.size() || end < 0 || static_cast<size_t>(end) >= matrix.size()) 
    {
        throw std::out_of_range("Node index out of range");
    }
    return matrix[static_cast<size_t>(start)][static_cast<size_t>(end)]; // Return the weight of the edge. 
}

// this function return the edges of the graph
vector<pair<int,pair<int, int>>> Graph::getEdges() const {
    vector<pair<int,pair<int, int>>> edges;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != 0) {
                edges.push_back({i, {j, matrix[i][j]}});
            }
        }
    }
    return edges;
}

// Check if the graph has a negative weight.
bool Graph::hasNegativeWeight() 
{
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (matrix[i][j] < 0) // Check if the weight of the edge is negative.
            {
                return true;
            }
        }
    }
    return false;
}


// Get the weight of an edge.
int Graph::getEdge(unsigned int s, unsigned int t)
{   
        // Check if the node index is out of range.
        if (s<0 && s>=getNumV() && t < 0 && t>=getNumV())
        {
            return -1;
        }
        return matrix[s][t]; 
}

// Set the graph to be directed or not.
void Graph::setDirect(bool directed)
    {
        directed = directed;
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = i; j < matrix[i].size(); j++)
            {
                if (!directed) // if not directed need to make the matrix symmetric
                {
                    if (matrix[i][j] != matrix[j][i])
                    {
                        if (matrix[i][j] == 0)
                        {
                            matrix[i][j] = matrix[j][i];
                        }
                        else if (matrix[j][i] == 0)
                        {
                            matrix[j][i] = matrix[i][j];
                        }
                        else
                        {
                            throw invalid_argument("Invalid graph: The graph is not symmetric.");
                        }
                    }
                }
            }
        }
    }

// Add two matrices.
Graph Graph::operator+( Graph &g) 
{
    // Check if the matrices on the same size.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Add the two matrices together using Graph object a
    Graph result;
    result.matrix = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            result.matrix[i][j] += g.matrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < result.matrix.size(); ++i) 
    {
        result.matrix[i][i] = 0;
    }

    return result;
}

// Add two matrices and assign the result to the first matrix.
Graph Graph::operator+=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Add the two matrices together.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            matrix[i][j] += g.matrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        matrix[i][i] = 0;
    }

    return *this;
}

// Unary plus operator.
Graph Graph::operator+() { return *this; }

// Subtract two matrices.
Graph Graph::operator-( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Subtract the two matrices.
    Graph result;
    result.matrix = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            result.matrix[i][j] -= g.matrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < result.matrix.size(); ++i) 
    {
        result.matrix[i][i] = 0;
    }

    return result;
}

// Subtract two matrices and assign the result to the first matrix.
Graph Graph::operator-=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Subtract the two matrices.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            matrix[i][j] -= g.matrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        matrix[i][i] = 0;
    }

    return *this;
}

// Unary minus operator.
Graph Graph::operator-()  
{
    Graph result;
    result.matrix = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            result.matrix[i][j] = -result.matrix[i][j];
        }
    }

    //resized the diagonal to 0
    for (size_t i = 0; i < result.matrix.size(); ++i) 
    {
        result.matrix[i][i] = 0;
    }

    return result;
}

// Check if two matrices are equal.
bool Graph::operator==( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        return false;
    }

    // Check if the two matrices are equal.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (matrix[i][j] != g.matrix[i][j]) 
            {
                return false;
            }
        }
    }
    return true;
}

// Check if two matrices are not equal.
bool Graph::operator!=( Graph &g) { return !(*this == g); }

// Check if the first matrix is less than the second matrix.
bool Graph::operator<( Graph &g) 
{
    // Check if the Graph object has more vertices than the other Graph object.
    if (getNumberOfVertices() > g.getNumberOfVertices())
    {
        return false;
    }

    // Check if the Graph object is contained in the other Graph object.
    if(getNumberOfVertices() < g.getNumberOfVertices())
    {
        for (size_t i = 0; i < matrix.size(); ++i) 
        {
            for (size_t j = 0; j < matrix[i].size(); ++j) 
            {
                if (matrix[i][j] != 0 && g.matrix[i][j] == 0) // Check if there is an edge between two vertices in the first graph and if there is no edge between two vertices in the second graph. 
                {
                    return false;
                }
            }
        }
    }

    // Check if the number of edges in the first graph is less than the number of edges in the second graph.
    if (getNumberOfEdges() > g.getNumberOfEdges()) 
    {
        return false;
    }

    return true;
}

// Check if the first matrix is less than or equal to the second matrix.
bool Graph::operator<=( Graph &g) { return *this < g || *this == g; }

// Check if the first matrix is greater than the second matrix.
bool Graph::operator>( Graph &g) { return !(*this <= g); }

// Check if the first matrix is greater than or equal to the second matrix.
bool Graph::operator>=( Graph &g) { return !(*this < g); }

// increment operator (before the variable)
Graph Graph::operator++() 
{
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (i != j && matrix[i][j] != 0) // Check if the edge is not from a vertex to itself and if there is an edge between two vertices.
            {
            matrix[i][j]++;
            }
        }
    }   
    return *this;
}

// increment operator (after the variable)
Graph Graph::operator++(int) 
{
    Graph temp = *this;
    ++*this;
    return temp;
}

// decrement operator (before the variable)
Graph Graph::operator--() 
{
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            if (i != j && matrix[i][j] != 0) // Check if the edge is not from a vertex to itself and if there is an edge between two vertices.
            {
            matrix[i][j]--;
            }
        }
    }
    return *this;
}

// decrement operator (after the variable)
Graph Graph::operator--(int) 
{
    Graph temp = *this;
    --*this;
    return temp;
}

// Multiply a matrix by a scalar.
Graph Graph::operator*(int scalar) 
{
    Graph result;
    result.matrix = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            result.matrix[i][j] *= scalar;
        }
    }
    return result;
}

// Multiply a matrix by a scalar and assign the result to the matrix.
Graph Graph::operator*=(int scalar) 
{
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            matrix[i][j] *= scalar;
        }
    }
    return *this;
}

// Multiply two matrices.
Graph Graph::operator*( Graph &g) 
{
    size_t adj_length = matrix.size();
    size_t adj_width = matrix[0].size();
    size_t g_length = g.matrix.size();
    size_t g_width = g.matrix[0].size();
    
    // Check if the number of columns in the first matrix is equal to the number of rows in the second matrix.
    if (adj_width != g_length) 
    {
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }

    // Multiply the two matrices.
    Graph result;
    result.matrix.resize(adj_length, vector<int>(g_width, 0));

    for (size_t i = 0; i < adj_length; ++i) 
    {
        for (size_t j = 0; j < g_width; ++j) 
        {
            for (size_t k = 0; k < adj_width; ++k) 
            {
                result.matrix[i][j] += matrix[i][k] * g.matrix[k][j];
            }
        }
    }

    // put 0 in the diagonal
    for (size_t i = 0; i < result.matrix.size(); ++i) 
    {
        result.matrix[i][i] = 0;
    }

    return result;

}

// Multiply two matrices.
Graph Graph::operator*=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Multiply the two matrices.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            matrix[i][j] *= g.matrix[i][j];
        }
    }
    return *this;
}

// Divide a matrix by a scalar.
Graph Graph::operator/(int scalar) 
{
    // Check if the scalar is zero.
    if (scalar == 0) 
    {
        throw invalid_argument("Invalid operation: Division by zero.");
    }

    // Divide the matrix by the scalar.
    Graph result;
    result.matrix = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            result.matrix[i][j] /= scalar;
        }
    }
    return result;
}

// Divide a matrix by a scalar and assign the result to the matrix.
Graph Graph::operator/=(int scalar) 
{
    // Check if the scalar is zero.
    if (scalar == 0) 
    {
        throw invalid_argument("Invalid operation: Division by zero.");
    }

    // Divide the matrix by the scalar.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            matrix[i][j] /= scalar;
        }
    }
    return *this;
}

// Divide two matrices.
Graph Graph::operator/( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Divide the two matrices.
    Graph result;
    result.matrix = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            // Check if the scalar is zero.
            if (g.matrix[i][j] == 0) 
            {
                throw invalid_argument("Invalid operation: Division by zero.");
            }
            result.matrix[i][j] /= g.matrix[i][j];
        }
    }
    return result;
}

// Divide two matrices and assign the result to the matrix.
Graph Graph::operator/=( Graph &g) 
{
    // Check if the dimensions of the two matrices are equal.
    if (matrix.size() != g.matrix.size()) 
    {
        throw invalid_argument("Invalid operation: The dimensions of the two matrices are not equal.");
    }

    // Divide the two matrices.
    for (size_t i = 0; i < matrix.size(); ++i) 
    {
        for (size_t j = 0; j < matrix[i].size(); ++j) 
        {
            // Check if the scalar is zero.
            if (g.matrix[i][j] == 0) 
            {
                throw invalid_argument("Invalid operation: Division by zero.");
            }
            matrix[i][j] /= g.matrix[i][j];
        }
    }
    return *this;
}


// friend functions
namespace ariel
{

    // Print the matrix using the << operator (friend function).
    ostream& operator<<(ostream& out, Graph& g) 
    {
        for (size_t i = 0; i < g.getMatrix().size(); ++i) 
        {
            if (i == 0) 
            {
                out << "[";
            } 
            else 
            {
                out << ", [";
            }
            for (size_t j = 0; j < g.getMatrix()[i].size(); ++j) 
            {
                if (j == g.getMatrix()[i].size() - 1) 
                {
                    out << g.getMatrix()[i][j];
                } 
                else 
                {
                    out << g.getMatrix()[i][j] << ", ";
                }
            }
            out << "]";
        }
        out << endl;
        return out;
    }

// Read the matrix using the >> operator (friend function).
istream& operator>>(istream &in, Graph &g) 
{
    for (size_t i = 0; i < g.getMatrix().size(); ++i) 
    {
        for (size_t j = 0; j < g.getMatrix()[i].size(); ++j) 
        {
            in >> g.getMatrix()[i][j];
        }
    }
    return in;
}

// Multiply a matrix by a scalar outside the class(friend function).
Graph operator*(int scalar, Graph &g) { return g * scalar; }

// Divide a matrix by a scalar outside the class(friend function).
//Graph operator/(int scalar, Graph &g) { return g / scalar; }

}





