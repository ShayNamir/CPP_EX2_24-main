/*
ID: 207192246
Email: ShayNamir@gmail.com
*/
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>

using namespace std;
TEST_CASE("Test graph addition")
{

    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);
    CHECK((g3 == g4) == true);
    CHECK((&g3 != &g1) == true);

    SUBCASE("Test graph addition with assignment")
    {
        g1 += g2;
        CHECK((g1 == g4) == true);
        CHECK((g1 != g3) == false);
    }

    SUBCASE("Test unary +")
    {
        ariel::Graph g5 = +g1;
        CHECK((g5 == g1) == true);
    }

    SUBCASE("Addition of two graphs with different dimensions")
    {
        ariel::Graph g6;
        vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
        g6.loadGraph(graph2);
        CHECK_THROWS(g1 + g6);
        CHECK_THROWS(g1 += g6);
    }

    SUBCASE("Test algorithms")
    {
        CHECK(g3.isDirected() == false);
        CHECK(ariel::Algorithms::isConnected(g3) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g3) == true);
        CHECK(ariel::Algorithms::isBipartite(g3) == "0");
        CHECK(ariel::Algorithms::shortestPath(g3, 1, 2) == "1->2");
    }
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;

    vector<vector<int>> expectedGraph = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);
    CHECK((g3 == g4) == true);

    SUBCASE("Test graph subtraction with assignment")
    {
        g1 -= g2;
        CHECK((g1 == g4) == true);
        CHECK((g1 != g3) == false);
    }

    SUBCASE("Test unary -")
    {
        g1 -= g2;
        ariel::Graph g5 = -g1;
        g4 = -g4;
        CHECK((g5 == g4) == true);

        g5 = -g5;
        vector<vector<int>> unsignedGraph = {
            {0, 0, 1},
            {0, 0, 1},
            {1, 1, 0}};
        ariel::Graph g6;
        g6.loadGraph(unsignedGraph);
        CHECK((g5 == g1) == true);
    }

    SUBCASE("Subtraction of two graphs with different dimensions")
    {
        ariel::Graph g6;
        vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
        g6.loadGraph(graph2);
        CHECK_THROWS(g1 - g6);
        CHECK_THROWS(g1 -= g6);
    }
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    ariel::Graph g5;
    g5.loadGraph(expectedGraph);
    CHECK((g4 == g5) == true);

    SUBCASE("Test graph multiplication by scalar")
    {
        g2 *= 2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 2},
            {2, 0, 4},
            {2, 4, 0}};
        ariel::Graph g6;
        g6.loadGraph(expectedGraph);
        CHECK((g2 == g6) == true);

        g2 /= 2;

        ariel::Graph g7 = 2 * g2;
        CHECK((g7 == g6) == true);

        ariel::Graph g8 = g2 * 2;
        CHECK((g8 == g6) == true);
    }

    SUBCASE("Test a big weighted graphs multiplication")
    {
        ariel::Graph g9;
        vector<vector<int>> weightedGraph2 = {
            {0, 1, 1, -1, 1},
            {1, 0, -7, 1, 4},
            {-25, 1, 0, 2, 1},
            {1, 5, 1, 0, 1},
            {9, 1, 1, 3, 0}};
        g9.loadGraph(weightedGraph2);

        vector<vector<int>> weightedGraph3 = {
            {0, -8, 1, -1, 0},
            {1, 0, -7, 1, 4},
            {-10, 1, 0, 6, 0},
            {1, 0, 4, 0, 2},
            {9, 1, -2, 3, 0}};
        ariel::Graph g10;
        g10.loadGraph(weightedGraph3);
        ariel::Graph g11 = g9 * g10;
        vector<vector<int>> expectedGraph2 = {
            {0, 2, -13, 10, 2},
            {107, 0, -3, -31, 2},
            {12, 201, 0, 29, 8},
            {4, -6, -36, 0, 20},
            {-6, -71, 14, -2, 0}};
        ariel::Graph g12;
        g12.loadGraph(expectedGraph2);
        CHECK((g11 == g12) == true);
    }
}

TEST_CASE("Invalid operations")
{
    //Loading a graph with different dimensions
    vector<vector<int>> loadMat = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    ariel::Graph gLoad;
    CHECK_THROWS(gLoad.loadGraph(loadMat));

    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
    CHECK_THROWS(g1 - g6);
}

TEST_CASE("Testing increment prefix and postfix")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g2++; // will be equal to g2 before increment
    ariel::Graph g4;
    ariel::Graph g5;
    vector<vector<int>> expectedGraph = {
        {0, 2, 2},
        {2, 0, 3},
        {2, 3, 0}};
    g4.loadGraph(expectedGraph);
    g5.loadGraph(weightedGraph);
    
    CHECK((g4 == g2) == true);
    CHECK((g3 == g5) == true);
    CHECK((g3 != g2) == true);

    SUBCASE("Comparing between g2 and g3 algorithms")
    {
        // suppose to be the same

        bool g2Connected = ariel::Algorithms::isConnected(g2);
        bool g3Connected = ariel::Algorithms::isConnected(g3);

        CHECK(g2Connected == g3Connected);

        bool g2Cycle = ariel::Algorithms::isContainsCycle(g2);
        bool g3Cycle = ariel::Algorithms::isContainsCycle(g3);

        CHECK(g2Cycle == g3Cycle);

        string g2Bipartite = ariel::Algorithms::isBipartite(g2);
        string g3Bipartite = ariel::Algorithms::isBipartite(g3);

        CHECK(g2Bipartite == g3Bipartite);

        string g2ShortestPath = ariel::Algorithms::shortestPath(g2, 1, 2);
        string g3ShortestPath = ariel::Algorithms::shortestPath(g3, 1, 2);

        CHECK(g2ShortestPath == g3ShortestPath);
    }

    ariel::Graph g6 = ++g1; // will be equal to g1 after increment
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};

    ariel::Graph g7;
    g7.loadGraph(graph2);

    ariel::Graph g8;
    g8.loadGraph(graph);
    
    CHECK((g6 == g7) == true);
    CHECK((g1 != g8) == true);

    SUBCASE("Incrementing zero matrix")
    {
        vector<vector<int>> zeroMatrix = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        ariel::Graph g3;
        g3.loadGraph(zeroMatrix);
        // Not supposed to change the graph
        g3++;
        ++g3;
        ariel::Graph g4;
        g4.loadGraph(zeroMatrix);
        CHECK((g3 == g4) == true);
        CHECK((g3 != g4) == false);
    }
}

TEST_CASE("Testing devrement prefix and postfix")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, -8, 1, -1, 0},
        {1, 0, -7, 1, 4},
        {-10, 1, 0, 6, 0},
        {1, 0, 4, 0, 2},
        {9, 1, -2, 3, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1--;

    CHECK(ariel::Algorithms::isConnected(g2) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g2) == true);
    CHECK(ariel::Algorithms::isBipartite(g2) == "0");
    CHECK(ariel::Algorithms::shortestPath(g2, 4, 2) == "The graph contains a negative cycle");
    CHECK(ariel::Algorithms::negativeCycle(g2) == "The cycle is: 0->1->2->0");

    vector<vector<int>> graph2 = {
        {0, -9, 0, -2, 0},
        {0, 0, -8, 0, 3},
        {-11, 0, 0, 5, 0},
        {0, 0, 3, 0, 1},
        {8, 0, -3, 2, 0}};
    ariel::Graph g3;
    g3.loadGraph(graph2);
    ariel::Graph g4;
    g4.loadGraph(graph);

    CHECK((g3 == g1) == true);
    CHECK((g2 == g4) == true);

    ariel::Graph g5 = --g1;
    vector<vector<int>> graph3 = {
        {0, -10, 0, -3, 0},
        {0, 0, -9, 0, 2},
        {-12, 0, 0, 4, 0},
        {0, 0, 2, 0, 0},
        {7, 0, -4, 1, 0}};
    ariel::Graph g6;
    g6.loadGraph(graph3);

    CHECK((g5 == g6) == true);
    CHECK((g1 != g3) == true); // g1 changed

    CHECK(ariel::Algorithms::isConnected(g5) == true);
    CHECK(ariel::Algorithms::isContainsCycle(g5) == true);
    CHECK(ariel::Algorithms::isBipartite(g5) == "0");
    CHECK(ariel::Algorithms::shortestPath(g5, 1, 2) == "The graph contains a negative cycle");
    CHECK(ariel::Algorithms::shortestPath(g5, 4, 2) == "The graph contains a negative cycle");
    CHECK(ariel::Algorithms::negativeCycle(g5) == "The cycle is: 0->1->2->0");

    SUBCASE("Decrementing zero matrix")
    {
        vector<vector<int>> zeroMatrix = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        ariel::Graph g3;
        g3.loadGraph(zeroMatrix);
        // Not supposed to change the graph
        g3--;
        --g3;
        ariel::Graph g4;
        g4.loadGraph(zeroMatrix);
        CHECK((g3 == g4) == true);
        CHECK((g3 != g4) == false);
    }
}

TEST_CASE("Checking comparison operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 2, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    CHECK((g1 < g2) == true); // graph 1 is contained in graph 2
    CHECK((g1 > g2) == false);
    CHECK((g1 <= g2) == true);
    CHECK((g1 >= g2) == false);

    SUBCASE("Checking bigger graph")
    {
        ariel::Graph g3;
        vector<vector<int>> weightedGraph2 = {
            {0, 1, 1, -1, 1},
            {1, 0, -7, 1, 4},
            {-25, 1, 0, 2, 1},
            {1, 5, 1, 0, 1},
            {9, 1, 1, 3, 0}};
        g3.loadGraph(weightedGraph2);

        CHECK((g3 < g2) == false);
        CHECK((g3 > g2) == true);
        CHECK((g3 <= g2) == false);
        CHECK((g3 >= g2) == true);
    }
}