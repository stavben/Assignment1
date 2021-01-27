//
// Created by spl211 on 08/11/2020.
//
#include "../include/Agent.h"
#include "../include/Tree.h"
#include "vector"
using namespace std;

Agent::Agent(){}
Agent::~Agent() noexcept {}

ContactTracer::ContactTracer() : Agent() {}


void ContactTracer::act(Session& session) {
    if(session.hasInfected()){
        int inf = session.dequeueInfected();
        Tree* bfs =Graph::Bfs(inf,session);
        int toRemove = bfs->traceTree();
        session.disconnect(toRemove);
        delete (bfs);
    }
}

Virus::Virus(int nodeInd): Agent(), nodeInd(nodeInd) {
    }

void Virus::act(Session& session) {
    if (!session.isInfected(nodeInd))
        session.enqueueInfected(nodeInd);
    int i = infNeighbor(session,nodeInd);
 if (i!=-1){
     session.addAgent(Virus(i));
     session.pushCarry(i);
 }
    }

int Virus::infNeighbor(Session session, int virus) {
    int b= -1;
    bool flog1= true;
    bool flog2= true;
    Graph curr = session.getGraph();
    std::vector<std::vector<int>> myMatrixs=curr.getMatrixs();
    int matrixSize=myMatrixs.size();
    for(int j=0;(j<matrixSize)&flog2;j++){
        if(myMatrixs[virus][j]==1){
            std::vector<int> a= session.getCarry();
            int aSize =a.size();
            for(int i=0;(i<aSize)&flog1;i++){
                if(a[i]==j)
                    flog1= false;
            }
            if(flog1) {
                b = j;
                flog2= false;
            }
            flog1= true;

        }
    }
    return b;
}

Agent * Virus::clone() const {
    return new Virus(*this);
}
Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}



