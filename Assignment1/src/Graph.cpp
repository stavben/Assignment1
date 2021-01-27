//
// Created by spl211 on 08/11/2020.
//
#include <vector>
#include "../include/Graph.h"
#include "../include/Session.h"
#include <queue>


using namespace std;

Graph::Graph(vector<vector<int>> matrix):edges(matrix),infected(vector<bool>(edges.size())) {
    for (int i:infected)
        infected[i]=false;

}
void Graph::infectNode(int nodeInd) {
infected[nodeInd]=true;
}

bool Graph::isInfected(int nodeInd) {
    return infected[nodeInd];
}
const std::vector<std::vector<int>> Graph::getMatrixs() {
    return edges;
}
void Graph::disconnect(int v) {
    int edgesSize= edges[v].size();
    for (int i = 0;i<edgesSize;++i){
        edges[v][i]=false;
        edges[i][v]=false;
    }
}
int Graph::numOfChild(int i) {
    int counter = 0;
    int edgesSize=edges.size();
    for(int j=0;j<edgesSize;j++){
        if (edges[i][j]==1)
            counter++;
    }
    return counter;
}

Tree* Graph::Bfs(int s,Session& session) {
    Graph myGraph=session.getGraph();
    int graphSize=myGraph.edges.size();
    std::vector<bool> vistied(graphSize);

    for(bool i:vistied)
        vistied[i]=false;

    std::queue<Tree*> ans;
    Tree* t = Tree::createTree(session,s);
    ans.push(t);
    vistied[s]=true;

    while (!ans.empty()) {
        Tree* k = ans.front();
        int root = k->getRoot();
        ans.pop();
        for (int i=0;i<graphSize;++i) {
            if ((myGraph.edges[root][i] == 1 )& !vistied[i]) {
                Tree* tmp = Tree::createTree(session,i);
                k->addChild(*tmp);
                vistied[i] = true;
                ans.push(k->getChildren().back());
                delete (tmp);

            }
        }

    }
    return t;
}


