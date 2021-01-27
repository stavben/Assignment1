//
// Created by spl211 on 08/11/2020.
//
#include "../include/Session.h"
#include "../include/Agent.h"
#include "fstream"
#include "../include/json.hpp"
using namespace std;
using json = nlohmann::json;

Session::Session(const std::string &path):g(vector<vector<int>>()),treeType(),agents(),infected(),carry(vector<int>()),cycle(0){
    ifstream temp(path);
    json jin;
    temp>>jin ;
    g= Graph(jin["graph"]);

    //tree type:
    json type = (jin["tree"]);
    if (type == "C")
        treeType=Cycle;
    if(type=="M")
        treeType=MaxRank;
    if(type=="R")
        treeType=Root;

    // agents
    json agent= (jin["agents"]);
    for (auto& elem: agent){
       if(elem[0]=="V") {
            agents.push_back(new Virus(elem[1]));
            carry.push_back(elem[1]);
        }
        else if (elem[0]=="C") {
           agents.push_back(new ContactTracer);
       }
    }

}

const Graph& Session::getGraph() const {
    return g;
}

bool Session::isInfected(int i) {
    return g.isInfected(i);
}
void Session::setGraph(const Graph &graph) {
    g = graph;
}

TreeType Session::getTreeType() const {
    return treeType;
}

 void Session::enqueueInfected(int i) {
    infected.push(i);
     g.infectNode(i);
}

int Session::getCycle() const{
    return cycle;
}
int Session::dequeueInfected() {
    int r= infected.front();
    infected.pop();
    return r;
}
void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}
bool Session::hasInfected() const {
    return !infected.empty();
}

void Session::disconnect(int v) {
    g.disconnect(v);
}

void Session::simulate() {
        bool ok= true;
        while (ok){

            int a=agents.size();
            for(int i=0;i<a;i++){
                agents[i]->act(*this);
            }
            cycle++;
            ok= endCheckSimulate();
        }
    ofstream o("output.json");
    json j;
    j["graph"] = g.getMatrixs();
    j["infected"] = carry;
    o<<j;
}
bool Session::endCheckSimulate() {
    bool ans=true;
    int carrySize=carry.size();
    for(int i=0;(i<carrySize)&(ans);i++)
        if((g.isInfected(carry[i]))== false)
            ans= false;
    return !ans;

}

std::vector<int> Session::getCarry() {
    return carry;
}
void Session::pushCarry(int i) {
    carry.push_back(i);
}

//Session copy constructor
Session::Session(const Session &other):g(other.getGraph()),treeType(other.getTreeType()),agents(),infected(other.infected),carry(other.carry),cycle(other.getCycle()){
   for (auto agent:other.agents){
        Agent* cloned = agent->clone();
        agents.push_back(cloned);
    }
}
//session move operator
Session::Session(Session &&other):g(other.g),treeType(other.treeType),agents(other.agents),infected(other.infected),carry(other.carry),cycle(other.cycle) {
    int otherSize=other.agents.size();
    for (int i=0;i<otherSize;i++){
        agents[i]= nullptr;
    }
}
//move op
Session & Session::operator=(Session &&other) {
    if(this!=&other){
        clear();
        agents.clear();
        g=other.g;
        treeType=other.treeType;
        agents=std::move(other.agents);
        infected=other.infected;
        carry=other.carry;
        cycle=other.cycle;

    }
    return *this;
}

//Session ass op
Session& Session::operator=(const Session &other) {
    if(this!=&other){
        g=other.g;
        treeType=other.getTreeType();
        int otAgSize = other.agents.size();
        for(int i =0;i<otAgSize;++i){
            this->addAgent(*other.agents[i]);
        }
        infected=other.infected;
        carry=other.carry;
        cycle=other.getCycle();
        clear();

    }
    return *this;
}
void Session::clear() {
    for(auto &agent : agents){
        if (agent!= nullptr){
            delete (agent);
            agent= nullptr;
        }
    }

}
//distructor

Session::~Session() {clear();}
