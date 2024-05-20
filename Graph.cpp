 #include "Graph.hpp"
#include <iostream>
#include <vector>
using std::vector;
using std::invalid_argument;
using namespace ariel;

void Graph::loadGraph(const vector<vector<int>>& matrix) {
    // Check if the graph is empty
    if (matrix.empty()) {
        throw invalid_argument("The graph cannot be empty");
    }
    // Check if the matrix is square
    size_t s = matrix.size();
    for (size_t i = 0; i < s; i++) {
        if (matrix[i].size() != s) {
            throw invalid_argument("The matrix must be square");
        }
    }
    // If all good, load the graph
    this->matrix = matrix;
}
void Graph::printGraph() {
    //Vertex
    int v= this->matrix.size();

    //Edges
    size_t e=0;
    for(size_t i=0;i<v;i++){
        for(size_t j=0;j<v;j++){
            if(this->matrix[i][j]==1)
                e++;
        }
    }

    //Print the details for the user
    std::cout<<"Graph with "<<v<<" vertices and "<<e<<" edges." << std::endl;
}
size_t Graph::getVertexNum()const {
    return this->matrix.size();
}
int Graph::getEdge(size_t i, size_t j)const {
    if ((i<0) && (i>=getVertexNum()) && (j < 0) && (j>=getVertexNum())){
            return -1;
        }
        return matrix[i][j]; 
}
int Graph::getEdgeNum() {
    //Vertex
    int v= this->matrix.size();

    //Edges
    int e=0;
    for(size_t i=0;i<v;i++){
        for(size_t j=0;j<v;j++){
            if(this->matrix[i][j]!=0)
                e++;
        }
    }
    //If the graph is not directed, divide by 2
    if(!isDirected())
        e/=2;
    return e;
}
bool Graph::isDirected(){
    int n = this->matrix.size();
    for(size_t i=0;i<n;i++){
        for(size_t j=0;j<n;j++){
            if(this->matrix[i][j]!=this->matrix[j][i])
                return true;
        }
    }
    return false;
}
vector<size_t> Graph::getNeighbors(size_t node) {
    vector<size_t> neighbors;
    for (size_t i = 0; i < this->matrix.size(); i++) {//Iterate over the row of the node
        if (this->matrix[node][i] == 1) {
            neighbors.push_back(i);//Add the neighbor to the vector
        }
    }
    return neighbors;
}

//Overloading operators

//Addition
Graph Graph::operator+(const Graph& other) {
    //Check if the graphs have the same size
    if (this->matrix.size() != other.matrix.size()) {
        throw invalid_argument("The graphs must have the same size");
    }
    //Create a new graph
    Graph newGraph;
    newGraph.matrix = this->matrix;
    //Add the values of the other graph to the new graph
    for (size_t i = 0; i < this->matrix.size(); i++) {
        for (size_t j = 0; j < this->matrix.size(); j++) {
            newGraph.matrix[i][j] += other.matrix[i][j];
        }
    }
    return newGraph;
}

//Addition assignment
Graph Graph::operator+=(const Graph& other){
    //Check if the graphs have the same size
    if (this->matrix.size() != other.matrix.size()) {
        throw invalid_argument("The graphs must have the same size");
    }
    //Add the values of the other graph to the new graph
    for (size_t i = 0; i < this->matrix.size(); i++) {
        for (size_t j = 0; j < this->matrix.size(); j++) {
            this->matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

//Unary plus
Graph Graph::operator+()const {
    return *this;
}

//Subtraction
Graph Graph:: operator-(const Graph& other){
    //Check if the matrix are in the same size
    int n=this->getVertexNum();
    if(other.matrix.size()!=n)
        throw invalid_argument("The graphs must have the same size");

    //Create a new graph
    Graph ans;
    ans.matrix = this->matrix;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans.matrix[i][j]-=other.matrix[i][j];
        }
    }
    return ans;
}

//Subtraction assignment
Graph Graph::operator-=(const Graph& other){
    //check if the graphs are in the same size
    int n= this->getVertexNum();
    if(n!=other.matrix.size())
        throw invalid_argument("The graphs must have the same size");   
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            this->matrix[i][j]-=other.matrix[i][j];
        }
    }
    return *this;
}

//Unary minus
Graph Graph:: operator-(){
    int n=this->getVertexNum();
    for(int i=0;i<n;i++){
        for( int j=0;j<n;j++){
            this->matrix[i][j]*=(-1);
        }
    }
    return *this;
}
//Equality operators
bool Graph::operator==(const Graph& other){
    //case one
    bool caseOne=true;
    int n= other.matrix.size();
    caseOne=n==this->getVertexNum();
    if(caseOne){// No need if are not in the same size
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(this->matrix[i][j]!=other.matrix[i][j])
                caseOne=false;
            }
        }
    }
    if(caseOne)
        return caseOne;

    //Case two
    Graph temp=(*this>other);
    bool caseTwo = temp!=*this;
    temp = (*this<other);
    caseTwo = caseTwo&&(temp!=other);
    return caseTwo;
}
bool Graph::operator!=(const Graph& other){
    bool ans = *this==other;
    return !ans;
}
Graph Graph::operator>(const Graph& other){
    //If one graph is contained in another
    int smallN=std::min(this->getVertexNum(),other.matrix.size());
    int bigN=std::max(this->getVertexNum(),other.matrix.size());
    bool contained=true;
    for (int i=0;i<smallN;i++){
        for (int j=0;j<smallN;j++){
            if(this->matrix[i][j]!=other.matrix[i][j])
                contained=false;
        }
    }

    //By number of edges
    if(this->getEdgeNum()>other.getVertexNum())
        return *this;
    if(this->getEdgeNum()>other.getVertexNum())
        return other;

    //By the matrix size
    if(this->matrix.size()>other.matrix.size())
        return *this;

    return other;
}
Graph Graph::operator<=(const Graph& other){
    Graph ans = *this>other;
}
Graph Graph::operator<(const Graph& other){
    //If one graph is contained in another
    int smallN=std::min(this->getVertexNum(),other.matrix.size());
    int bigN=std::max(this->getVertexNum(),other.matrix.size());
    bool contained=true;
    for (int i=0;i<smallN;i++){
        for (int j=0;j<smallN;j++){
            if(this->matrix[i][j]!=other.matrix[i][j])
                contained=false;
        }
    }

    //By number of edges
    if(this->getEdgeNum()<other.getVertexNum())
        return *this;
    if(this->getEdgeNum()<other.getVertexNum())
        return other;

    //By the matrix size
    if(this->matrix.size()<other.matrix.size())
        return *this;

    return other;
}
Graph Graph::operator>=(const Graph& other){
    Graph ans = *this<other;
}

//Increment
Graph Graph::operator++(){
    int n=this->getVertexNum();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            this->matrix[i][j]++;
        }
    }
    return *this;
}
Graph Graph::operator++(int){
    //Use the pre-increment operator
    Graph ans = *this;
    ++*this;
    return ans;
}
//Decrement
Graph Graph::operator--(){
    int n=this->getVertexNum();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            this->matrix[i][j]--;
        }
    }
    return *this;
}
Graph Graph::operator--(int){
    //Use the pre-decrement operator
    Graph ans = *this;
    --*this;
    return ans;
}

//Multiplication operators
Graph Graph::operator*(const Graph& other){
    //Matrix multiplication
    int n=this->getVertexNum();
    if(n!=other.matrix.size())
        throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    Graph ans;
    //No need to resize the matrix because the matrix is square
    for(int i=0;i<n;i++){
        ans.matrix[i].resize(n);
        for(int j=0;j<n;j++){
            ans.matrix[i][j]=0;
            for(int k=0;k<n;k++){
                ans.matrix[i][j]+=this->matrix[i][k]*other.matrix[k][j];
            }
        }
    }
    return ans;
}
Graph Graph::operator*=(const Graph& other){
    //Use the multiplication operator
    *this = *this * other;
    return *this;
}
Graph Graph::operator*(int scalar){
    //Multiply the matrix by a scalar
    int n=this->getVertexNum();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            this->matrix[i][j]*=scalar;
        }
    }
    return *this;
}
Graph Graph::operator*=(int scalar){
    //Use the multiplication operator
    *this = *this * scalar;
    return *this;
}
//Division
Graph Graph::operator/(int scalar){
    //Divide the matrix by a scalar
    int n=this->getVertexNum();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            this->matrix[i][j]/=scalar;
        }
    }
    return *this;
}
Graph Graph::operator/=(int scalar){
    //Use the division operator
    *this = *this / scalar;
    return *this;
}

//Print the graph
#include <iostream> // Include the necessary header file

std::ostream& operator<<(std::ostream& os, const Graph& g){
    /*
    the matrix:
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0}};
    will print: [0, 1, 0], [1, 0, 1], [0, 1, 0]
    */
   int n=g.getVertexNum();
    os << "[";
    for (size_t i = 0; i < n; i++) {
        os << "[";
        for (size_t j = 0; j < n; j++) {
            os << g.getEdge(i, j);
            if (j != n - 1) {
                os << ", ";
            }
        }
        os << "]";
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
