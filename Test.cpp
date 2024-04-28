#include "doctest.h"
#include "Algorithms.hpp"
//#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}
TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->2->0");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
            {0, 1, 2, 0, 0},
            {1, 0, 3, 0, 0},
            {2, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}
TEST_CASE("Test Negative Cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, -9, 0, 0},
            {0, 0, -8, 0},
             {0, 0, 0, -10},
              {-7, 0, 0, 0},

    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "0->1->2->3->0");
}
TEST_CASE("TestAll Directed - No Weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,2,6) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g,7,2) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g,4,5) == "-1");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
    CHECK(ariel::Algorithms::negativeCycle(g) == "0");
}
TEST_CASE("TestAll Directed - Non Negative Weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 0, 5, 0, 0},
            {6, 0, 0, 0, 0},
            {0, 8, 0, 4, 0},
            {1, 0, 0, 0, 0},
            {2, 0, 2, 0, 0},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,0,3) == "0->2->3");
    CHECK(ariel::Algorithms::shortestPath(g,2,3) == "2->3");
    CHECK(ariel::Algorithms::shortestPath(g,1,4) == "-1");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->2->3->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
    CHECK(ariel::Algorithms::negativeCycle(g) == "0");
}
TEST_CASE("TestAll Directed - Negative Weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {

            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 6, 0},
            {0, 0, 0, 0, 5, 0},
            {1, 0, 0, 0, 8, -8},
            {0, 6, 0, -8, 0, 0},
            {4, 0, 0, 0, 0, 0},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,0,4) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g,1,5) == "1->4->3->5");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "2->4->3->5->0");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "4->3->4");
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
    CHECK(ariel::Algorithms::negativeCycle(g) == "0");

}
TEST_CASE("TestAll Directed - No Weights")
{}
TEST_CASE("TestAll Directed - Non Negative Weights")
{}
TEST_CASE("TestAll Directed - Negative Weights")
{}
