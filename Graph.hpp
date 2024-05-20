/*
This class is a template class that represents a graph. It is implemented using an matrix of vertices.
*/
#include <iostream>
#include <vector>
using namespace std;
namespace ariel{
    class Graph{
        private:
            vector<vector<int>> matrix;
        public:
            void loadGraph(const vector<vector<int>>& matrix);// Function to load a graph from a matrix
            void printGraph();// Function to print the adjacency matrix of the graph
            size_t getVertexNum()const;//return the number of vertices in the graph
            bool isDirected();//return true if the graph is directed, otherwise return false
            int getEdgeNum();//return the number of edges in the graph
            int getEdge(size_t i, size_t j)const;//return the value of the edge between vertex i and vertex j
            vector<size_t> getNeighbors(size_t node);
            
            //Overloading operators
            Graph operator+(const Graph& other);//+
            Graph operator+=(const Graph& other);//+=
            Graph operator+()const;//Unary +
            Graph operator-(const Graph& other);//-
            Graph operator-=(const Graph& other);//-=
            Graph operator-();//Unary -

            //Equality operators
            bool operator==(const Graph& other);//==
            bool operator!=(const Graph& other);//!=
            Graph operator>(const Graph& other);//>
            Graph operator>=(const Graph& other);//>=
            Graph operator<(const Graph& other);//<
            Graph operator<=(const Graph& other);//<=

            //++
            Graph operator++();//Pre-increment
            Graph operator++(int);//Post-increment
            //--
            Graph operator--();//Pre-decrement
            Graph operator--(int);//Post-decrement

            //Multiplication operators
            Graph operator*(const Graph& other);//* vector multiplication
            Graph operator*=(const Graph& other);//*= vector multiplication
            Graph operator*(int scalar);//* scalar multiplication
            Graph operator*=(int scalar);//*= scalar multiplication
            Graph operator/(int scalar);// / scalar division
            Graph operator/=(int scalar);// /= scalar division

            //Print the graph
            friend ostream& operator<<(ostream& os, const Graph& g);

    };
}