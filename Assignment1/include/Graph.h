#ifndef GRAPH_H_
#define GRAPH_H_
#include "Tree.h"
#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    const std::vector<std::vector<int>> getMatrixs();
    static Tree* Bfs (int v,Session& session);
    void disconnect(int v);
    int numOfChild(int i);
private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infected;
};

#endif
