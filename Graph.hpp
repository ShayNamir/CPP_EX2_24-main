/*
ID: 207192246
Email: ShayNamir@gmail.com
*/
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <utility>
using namespace std;

namespace ariel
{
    class Graph
    {
       private:
        vector<vector<int>> matrix;
        bool directed;

       public:

        void loadGraph(vector<vector<int>> adjMatrix);
        string printGraph(); // Print the graph.
        size_t getNumberOfEdges();
        int getWeight(int start, int end); // Get the value of an edge.
        vector<size_t> getNeighbors(size_t vertex);
        bool isDirected(); 
        size_t getNumberOfVertices();
        vector<vector<int>> getMatrix() const {return matrix;}
        vector<pair<int,pair<int, int>>> getEdges() const;
        bool isEdge(size_t from, size_t to) { return matrix[from][to] != 0;} // Check if there is an edge between two vertices.
        bool hasNegativeWeight(); 
        void setDirect(bool directed); 
        int getEdge(unsigned int s, unsigned int t);
        unsigned int getNumV() const{ return matrix.size(); }

        // Arithmetic operators
        Graph operator+( Graph &g); 
        Graph operator+=( Graph &g);
        Graph operator+() ; // Unary plus operator. 
        Graph operator-( Graph &g); 
        Graph operator-=( Graph &g); 
        Graph operator-() ; // Unary minus operator.

        //comparison operators
        bool operator==( Graph &g); 
        bool operator!=( Graph &g); 
        bool operator<( Graph &g); 
        bool operator<=( Graph &g); 
        bool operator>( Graph &g);
        bool operator>=( Graph &g); 

        // Assignment operators
        Graph operator++(); //i ++
        Graph operator++(int); //++ i
        Graph operator--(); // i --
        Graph operator--(int); // -- i

        // Multiplication operators
        Graph operator*(int scalar); 
        Graph operator*=( int scalar); 
        Graph operator*( Graph &g); 
        Graph operator*=( Graph &g); 

        // Division operators
        Graph operator/(int scalar); 
        Graph operator/=(int scalar); 
        Graph operator/( Graph &g); 
        Graph operator/=( Graph &g); 

        friend ostream& operator<<(ostream &out,Graph &g); // Print the matrix.
        friend Graph operator*(int scalar, Graph &g); // Multiply a acalar by a matrix.
    };    
}

#endif