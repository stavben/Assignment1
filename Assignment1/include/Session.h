#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include <queue>

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    const Graph& getGraph() const;
    void enqueueInfected(int i);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCycle() const;
    bool isInfected(int i);
    void pushCarry(int i);
    // session copy constructor
    Session (const Session& other);
    //session move constructor
    Session(Session&& other);
    //move op
    Session& operator=(Session&& other);
    //ass op
    Session& operator=(const Session& other);
    virtual ~Session();
    bool hasInfected() const;
    void disconnect(int v);
    bool endCheckSimulate();
    std::vector<int> getCarry();
    bool componentCheck();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infected;
    std::vector<int> carry;
    int cycle;
    void clear();
};

#endif
