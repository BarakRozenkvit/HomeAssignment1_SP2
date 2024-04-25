#include "Algorithms.hpp"
#include <iostream>
#include <queue>
#include <stack>
using namespace ariel;
using namespace std;

// ----------------- Public ---------------------

bool Algorithms::isConnected(Graph g) {
    //// Theorem 1: Kosaraju algorithm detects strongly connected components in graph
    //// Theorem 2: After the second DFS every tree in the forset will be different strongly connected component
    //// Conclusion: After the second DFS if only one root in the forest -> the entire graph is strongly connected
    // Create stack of vertices by order {v,v-1,v-2,...,0}
    stack<int> orderOfVertices;
    for (int i = g.getAdjMatrix().size() - 1; i > -1; i--) {
        orderOfVertices.push(i);
    }

    // 1. Run first DFS
    pair<pair<stack<int>,vector<int>>,pair<int,int>> DFSResult = Algorithms::DFS(g, orderOfVertices);
    // Results of first DFS:
    // Pie Array of vertices, -1 means null therefor root
    vector<int> vTrees = DFSResult.first.second;
    // finished time of vertices in order of highest to lowest (highest will pop first)
    stack<int> vStack = DFSResult.first.first;

    if (g.isDirected()) {
        // if graph is directed reverse edges, run second DFS in order of finishing times
        Graph gT = Algorithms::Transpose(g);
        DFSResult = Algorithms::DFS(gT, vStack);
        // Results of second DFS:
        vTrees = DFSResult.first.second;
    }

    // check if only one root exist in Pie Array, if not, more than one strongly connected components
    int root_num = 0;
    for (int i = 0; i < vTrees.size(); i++) {
        if (vTrees[i] == -1) {
            root_num++;
        }
    }
    return root_num == 1;
}

string Algorithms::shortestPath(Graph g, int src, int dest) {
    /// Theorem: BellmanFord calculates shortestPath from src to any v in V while weight are negative and non negative
    // Running BF in g from src
    pair<pair<vector<int>,vector<int>>,pair<bool,int>> BellmanFordResult = Algorithms::BellmanFord(g, src);
    // Results of DF:
    // Pie Array:
    vector<int> pieVertice = BellmanFordResult.first.first;
    // Distance from src Array
    vector<int> dVertices = BellmanFordResult.first.second;
    // Is there negative cycle
    bool isNegativeCycle = BellmanFordResult.second.first;
    if(isNegativeCycle){
        // If there is negative cycle, no shortest path
        return "-1";
    }
    // return the shortest path
    return pathString(pieVertice,src,dest);
}

string Algorithms::isContainsCycle(Graph g) {
    /// Theorem: DFS can detect cycle with detection of Back Edge
    // Create stack of vertices by order {v,v-1,v-2,...,0}
    stack<int> orderOfVertices;
    for(int i=g.getAdjMatrix().size()-1;i>-1;i--){
        orderOfVertices.push(i);
    }
    // Run DFS
    pair<pair<stack<int>,vector<int>>,pair<int,int>> DFSResult = Algorithms::DFS(g,orderOfVertices);
    // Results of DFS:
    // Pie Array
    vector<int> pieVertices = DFSResult.first.second;
    // v of the cycle
    int vStartCycle = DFSResult.second.first;
    // u of the cycle
    int vEndCycle = DFSResult.second.second;
    // if v == -1 there is no cycle found
    if(vStartCycle != -1){
        // return the path of cycle
        return pathString(pieVertices,vStartCycle,vEndCycle) + "->" + to_string(vStartCycle);
    }
    return "0";
}

string Algorithms::isBipartite(Graph g) {
    //// Theorem: Graph is Bipartite if and only if it is 2-Coloring-Graph
    // Run 2-Coloring Graph
    pair<bool,vector<int>> twoColoringResult = Algorithms::twoColoringGraph(g);
    // Results of 2-Coloring Graph:
    // if its possible
    bool possible = twoColoringResult.first;
    // the diviation of coloring
    vector<int> coloring = twoColoringResult.second;

    if(possible){
        // if its possible return the strings of groups
        string A = "{";
        string B = "{";
        for(int i =0;i<coloring.size();i++) {
            if (coloring[i] == 1) {
                A += to_string(i) + ", ";
            } else {
                B += to_string(i) + ", ";
            }
        }
        A.pop_back();A.pop_back();
        B.pop_back();B.pop_back();
        A += "}";
        B += "}";

        return "The graph is bipartite: A=" + A +", B="+B;

    }
    return "0";
}

string Algorithms::negativeCycle(Graph g) {
    //// Theorem: BellmanFord can detect negative cycle
    // Run BF
    pair<pair<vector<int>,vector<int>>,pair<bool,int>> BellmanFordResult = Algorithms::BellmanFord(g, 0);
    // Pie array of vertices
    vector<int> pieVertices = BellmanFordResult.first.first;
    // if is negative cycle
    bool isNegativeCycle = BellmanFordResult.second.first;
    if(isNegativeCycle){
        // if there is return the cycle
        int vStartCycle = BellmanFordResult.second.second;
        return pathString(pieVertices,vStartCycle,vStartCycle);
    }
    return "0";
}


// ---------------- Private -----------------------

pair<pair<vector<int>,vector<int>>,pair<bool,int>> Algorithms::BellmanFord(Graph g, int src) {
    bool IsNegativeCycle = false;
    int vStartCycle = -1;
    int V = g.getAdjMatrix().size();
    vector<int> d(V, INF);
    vector<int> pie(V, -1);
    d[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if(!g.isDirected() && pie[u] == v){continue;}
                Algorithms::relax(g, u, v, &d, &pie);
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if(!g.isDirected() && pie[u] == v){continue;}
            if (Algorithms::relax(g, u, v, &d, &pie)) {
                IsNegativeCycle = true;
                vStartCycle = v;
                break;
            }
        }
    }
    return make_pair(make_pair(pie,d), make_pair(IsNegativeCycle,vStartCycle));
}

pair<pair<stack<int>,vector<int>>,pair<int,int>> Algorithms::DFS(Graph g,stack<int> orderOfVertices){
    int vStartCycle = -1;
    int vEndCycle = -1;
    int time = 0;
    vector<int> d(g.getAdjMatrix().size(),0);
    stack<int> f;
    vector<int> pie(g.getAdjMatrix().size(),-1);
    vector<string> color(g.getAdjMatrix().size(),"White");

    while(!orderOfVertices.empty()){
        int u = orderOfVertices.top();
        orderOfVertices.pop();
        if(color[u] == "White"){
            Algorithms::DFS_Visit(g,u,&d,&f,&pie,&color,&time,&vStartCycle,&vEndCycle);
        }
    }
    return make_pair(make_pair(f,pie), make_pair(vStartCycle,vEndCycle));
}

void Algorithms::DFS_Visit(Graph g,int u, vector<int>* d,stack<int>* f, vector<int>* pie,vector<string>* color, int* time,int* vStartCycle,int* vEndCycle){
    (*color)[u] = "Gray";
    (*time)++;
    (*d)[u] = *time;
    for(int v = 0;v<g.getAdjMatrix().size();v++){
        if(!g.isDirected() && (*pie)[u] == v){continue;}
        if(u != v && g.getAdjMatrix()[u][v] < INF){

            if((*color)[v] == "Gray"){
                (*vStartCycle) = v;
                (*vEndCycle) = u;
            }
            if((*color)[v] == "White"){
                (*pie)[v] = u;
                DFS_Visit(g,v,d,f,pie,color,time,vStartCycle,vEndCycle);
            }
        }

    }
    (*color)[u] = "Black";
    (*time)++;
    (*f).push(u);
}

bool Algorithms::relax(Graph g,int u, int v,vector<int>* d,vector<int>* pie){
   if(u==v || (*d)[u] == INF || g.getAdjMatrix()[u][v] == INF){
       return false;}

   if ((*d)[v] > (*d)[u] + g.getAdjMatrix()[u][v]) {
        (*d)[v] = (*d)[u] + g.getAdjMatrix()[u][v];
        (*pie)[v] = u;
       return true;
    }

    return false;
}

string Algorithms::pathString(vector<int> vertices ,int src,int dest){

    string result = "";
    result.insert(0,to_string(dest));
    int curr = vertices[dest];
    while(curr != src){
        if(curr == -1){return "-1";}
        result.insert(0, to_string(curr) + "->");
        curr=vertices[curr];
    }
    return result.insert(0, to_string(src) +"->");
}

Graph Algorithms::Transpose(Graph g){
    vector<vector<int>>matT(g.getAdjMatrix());
    for(int i=0;i<matT.size();i++){
        for(int j=i+1;j<matT[i].size();j++){
            matT[i][j] = g.getAdjMatrix()[j][i];
            matT[j][i] = g.getAdjMatrix()[i][j];
        }
    }
    Graph gT;
    gT.loadGraph(matT);
    return gT;
}

pair<bool,vector<int>> Algorithms::twoColoringGraph(Graph g){
    vector<int> color(g.getAdjMatrix().size(),-1);
    color[0] = 1;
    queue<int> Q;
    Q.push(0);

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (int v = 0; v < color.size(); ++v) {
            if (u == v) { continue; }

            else if ((g.getAdjMatrix()[u][v] < INF || g.getAdjMatrix()[v][u] < INF) && color[v] == -1) {
                color[v] = 1 - color[u];
                Q.push(v);
            } else if ((g.getAdjMatrix()[u][v] < INF || g.getAdjMatrix()[v][u] < INF) && color[v] == color[u]) {
                return make_pair(false,color);
            }
        }
        if (Q.empty()) {
            for (int i = 0; i < color.size(); i++) {
                if (color[i] == -1) {
                    color[i] = 1;
                    Q.push(i);
                    break;

                }
            }
        }
    }

    return make_pair(true,color);
}
