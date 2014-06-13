#ifndef TREE_H
#define TREE_H
#include<string>
#include<iostream>
#include<vector>
#include<stack>
using namespace std;


struct Node
{
    float data;                 //holds the score of each node
    string id;                  //holds the name assoicated with each data
    Node *left;
    Node *right;
};

class bTree
{
public:
    bTree();
    ~bTree();

    void insert(float,string);              //inserts a node given a name and score pair
    void destroy_tree();                    //destroys the tree at destructor
    void print(queue<string>&);                           //prints the tree side of the tree then the right side
    void sortTreeData();                    //sorts the tree by taking average of two nodes close to each other

private:
    void destroy_tree(Node* leaf);              //destroys the tree after being called
    void insert( Node* leaf, string, float);        //inserts a name score pair
    void printTree(Node *head, queue<string>&);                     //stores levels of tree into a stack
    void sortTreeData(Node*&, Node*, Node*);        //sorts the tree based on value
    void merge_trees();                             //merges two trees together
    Node* root;                             //root of the smaller node
    Node* root2;                            //root of the larger node
    int count;                              //keeps track of the number of nodes
};

#endif // TREE_H
