//// @author:314638669, Barak10101998@gmail.com
#include <vector>
#pragma once
#define INF INT32_MAX

using namespace std;

namespace ariel {

    class Graph {

        vector<vector<int>> _adjMatrix;
        int _edges = 0;
        bool _isDirected = false;
        bool _isNegativeEdges = false;


    public:

        Graph();

        void loadGraph(vector<vector<int>> graph);

        void printGraph();

        vector<vector<int>> getAdjMatrix(){
            return _adjMatrix;
        }

        bool isDirected(){
            return _isDirected;
        }
        int getEdges(){
            return _edges;
        }
        bool getisNegativeEdges(){
            return _isNegativeEdges;
        }
        void addS();
    };
}
