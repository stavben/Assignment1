#ifndef AGENT_H_
#define AGENT_H_
#include "Session.h"
#include <vector>
#include "Tree.h"
class Agent{
public:
    Agent();
    virtual ~Agent();

    virtual void act(Session& session)=0;
    virtual Agent* clone()const=0;

};

class ContactTracer: public Agent{
public:

    ContactTracer();
    
    virtual void act(Session& session);
    virtual Agent* clone()const;

};

class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual void act(Session& session);
    virtual Agent* clone()const;//Agent*?
    int infNeighbor(Session session, int virus);
private:
    const int nodeInd;
};

#endif
