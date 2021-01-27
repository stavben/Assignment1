#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    const std::vector<Tree*>& getChildren() const;
    const int getRoot() const;
    const int getChildrenSize() const;
    static Tree* createTree(const Session& session, int rootLabel);
    virtual Tree* clone()const=0;
    virtual int traceTree()=0;
    //copy constructor
    Tree (const Tree& other);
    //assignment operator
    Tree& operator=(const Tree &other);
    //distructor
    virtual ~Tree();
    //move assignment
    Tree& operator=(Tree&& other);
    //move constructor
    Tree(Tree&& other);



protected:
    int node;
    std::vector<Tree*> children;
    void clear();
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;

};
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif
