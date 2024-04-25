#include "Algorithms.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

Graph::Graph() {}

void Graph::loadGraph(vector <vector<int>> graph) {
    if (graph.size() != graph[0].size()){
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }

    _adjMatrix = graph;
    _edges = 0;

    for(int i=0; i < _adjMatrix.size(); i++) {
        for (int j = 0; j < _adjMatrix[i].size(); j++) {
            if(i==j && _adjMatrix[i][j] !=0){
                throw invalid_argument("Invalid graph: i -> i has edge.");
            }
            if(_adjMatrix[i][j] != _adjMatrix[j][i]){
                _isDirected = true;
            }
            if (_adjMatrix[i][j] != 0) {
                _edges++;
            }
        }
    }

    for(int i=0; i < _adjMatrix.size(); i++) {
        for (int j = 0; j < _adjMatrix[i].size(); j++) {
            if(i!=j && _adjMatrix[i][j] == 0){
                _adjMatrix[i][j] = INF;
            }
        }
    }
}

void Graph::printGraph() {
    cout << "Graph with " << _adjMatrix.size() << " vertices and " << _edges << " edges." << endl;
}

