//
// Created by spl211 on 08/11/2020.
//
#include "../include/Tree.h"
#include "../include/Session.h"

Tree::Tree(int rootLabel):node(rootLabel),children(){}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}
const std::vector<Tree *> & Tree::getChildren() const {
    return children;
}
const int Tree::getRoot() const {
    return node;
}
const int Tree::getChildrenSize() const {
    return children.size();
}
Tree * Tree::createTree(const Session &session, int rootLabel) {

Tree* t;
TreeType type = session.getTreeType();
if (type==Cycle) {
    t = new CycleTree(rootLabel, session.getCycle());
}
if (type==MaxRank) {
    t = new MaxRankTree(rootLabel);
}
if (type==Root){
    t= new RootTree(rootLabel);
}

    return t;
}
void Tree::clear() {
       for (Tree* c:children){
           if (c!= nullptr){
               delete c;
               c= nullptr;
           }
   }
     }
//rule of 5:
//copy constructor
Tree::Tree(const Tree &other):node(other.node),children(){
    int cSize=other.getChildrenSize();
    for (int i=0;i<cSize;++i)
        children.push_back(other.children[i]->clone());
}

//assignment operator
Tree & Tree::operator=(const Tree &other) {
    if(this!=&other) {
        node = other.getRoot();

        for (Tree *t:children)
            delete (t);
        for (Tree *t :other.children){
            children.push_back(t->clone());
        }

    }
    return *this;
}
//distructor
Tree::~Tree() {clear();}

//move assignment
Tree& Tree::operator=(Tree &&other){
    if(this!=&other){
        clear();
        children.clear();
        children=std::move(other.children);
        node=other.node;
    }
    return *this;
}
//move constructor
Tree::Tree(Tree &&other):node(other.node),children(std::move(other.children)){
}

// cycle
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){
}
int CycleTree::traceTree() {
    Tree* curr= this;
    bool done =false;
    for (int c=currCycle;!done&&c>0;--c){
        if (curr->getChildrenSize()>0){
          //  delete (curr);
            Tree* child = curr->getChildren()[0];
            curr=child;

        }
        else
            done=true;
        }
    int toDisconnect = curr->getRoot();
    return toDisconnect;

}
Tree * CycleTree::clone() const {
    return new CycleTree(*this);
}

// maxRank
MaxRankTree::MaxRankTree(int rootLabel) :Tree(rootLabel){}
int MaxRankTree::traceTree() {
    std::queue<MaxRankTree*>myTree;
    myTree.push(this);
    int a=0;
    int maxRankNode=-1;
    MaxRankTree ans= MaxRankTree(*this);
    while (!myTree.empty()) {
        MaxRankTree *nowTree = myTree.front();
        for (Tree *i:nowTree->children)
            myTree.push((MaxRankTree *) i);
        myTree.pop();
        if (nowTree->getChildrenSize() > a) {
            a = nowTree->getChildrenSize();
            maxRankNode=nowTree->node;
            MaxRankTree ans = *nowTree;
        }
    }
    if (maxRankNode==-1){
        return node;
    }
        else return maxRankNode;
}

Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
//root tree
RootTree::RootTree(int rootLabel) :Tree(rootLabel){}

int RootTree::traceTree() {
    return node;
}
Tree * RootTree::clone() const {
    return new RootTree(*this);
}
