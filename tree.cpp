#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<stack>
#include "tree.h"
using namespace std;

bTree::bTree()
{
    root = NULL;                        //left tree is empty
    root2 = NULL;                       //right tree is empty
    count = 0;                          //there are no nodes
}
bTree::~bTree()
{
    destroy_tree();
}

void bTree::destroy_tree(Node *leaf)        //uses recursion to delete tree
{
    if(leaf != NULL)
    {
        destroy_tree(leaf->left);           //deletes all childs to the left of root
        destroy_tree(leaf->right);          //then deletes all childs to the right of root
        delete leaf;                        //deletes the node
    }
}


void bTree::insert(Node *leaf, string species1, float num1)
{

        if(leaf->data > num1)                           //checks as long as the data is greater than the score provided
        {
            if(leaf->left != NULL)                      //traverses left until finds the right position for the value
            {
                insert(leaf->left, species1, num1);         //recursive call to function until the right position is found
            }
            else
            {
                leaf->left = new Node;              //creates a new node on the left of position
                leaf->left->data = num1;            //assigns a data to the new node
                leaf->left->id = species1;          //asssigns a unique id to the new node matching the name of the file
                leaf->left->left = NULL;            //makes the left pointer point to NULL
                leaf->left->right = NULL;           //makes the right pointer point to NULL
                count++;

            }
        }
        else if(leaf->data < num1)              //traverses the right of the tree
        {
            if(leaf->right != NULL)                 //calls recursively until null space was found
            {
                insert(leaf->right, species1, num1);
            }

            else
            {
                leaf->right = new Node;             //creates a new node
                leaf->right->data = num1;           //stores the score into the new node
                leaf->right->id = species1;         //stores the name in the new node
                leaf->right->right = NULL;          //makes the right pointer point to null
                leaf->right->left = NULL;           //makes the left pointer point to null
                count++;

            }
        }


}


void bTree::insert(float key1, string animal1)
{
    if(root == NULL)
    {
        root = new Node;            //if the root is not pointing to null creates a new node to point to it
        root->data = key1;          //stores the data into the root
        root->id = animal1;         //stores the name into the root
        root->left = NULL;          //points the right and left pointer to null
        root->right = NULL;
        count++;
    }
    else
    {
        insert(root, animal1, key1);
    }
}


void bTree::destroy_tree()      //destorys the tree to be called in the destructor
{
    destroy_tree(root);
}

void bTree::printTree(Node *head, queue<string>& order)
{
    if(head != NULL)
    {
        //cout << "(";
        order.push("(");                            //pushes a ( for each level to the left
        printTree(head->left, order);
        printTree(head->right, order);
        order.push(")");                               //pushes a ) for each time we move to the right of a node
        //cout << ")";
        if(head->id != "average")
        {
            order.push(head->id + " ");             //checks for data with a name and adds that to the queue
            //cout << head->id << " ";
        }
    }
}

void bTree::print(queue<string>& order_print)
{
    cout << "Printing the tree: " << endl;
    printTree(root, order_print);
    string open, close;
    while(!order_print.empty())                     //uses queue loops through it until empty
    {
        open = order_print.front();                     //stores a string variable to check if there is a opening followed by a closing parenthesis
        order_print.pop();
        if(!order_print.empty())
        {
            close = order_print.front();
            if(close == ")" && open== "(")         //if there is a closing follwing a opening parenthesis followed by a closing on pops stack an extra time
            {
                order_print.pop();
            }
            else
            {
                cout <<open;                //prints the stack value
            }
        }
    }
    cout << open;                   //prints the last value in the stack
}

void bTree::sortTreeData(Node*&leaf, Node*next_node, Node*prev_node)
{
    if(abs(leaf->data - next_node->data) < 24)          //checks if the root and the next node is within a certain range
    {
        Node* created = new Node;                               //creates a new node to average two nodes
        created->data = (leaf->data + next_node->data)/2.0;     //stores the average of the two nodes
        created->id = "average";                                //stores the combined name of the two nodes
        created->left = leaf;                                   //new node point to the lesser node
        created->right = next_node;                             //new node points to the greater node value
        leaf = created;                                         //leaf becomes the root of the node
        prev_node->right = NULL;                                //the greater node points to null from the right to create a leaf
        prev_node = next_node;                                  //previous takes the value of next_node
        next_node= next_node->right;                            //next node becomes the next on the right of tree
        if(next_node != NULL)
        {
            sortTreeData(leaf, next_node, prev_node);   //recursive call if next_node is not null
        }
    }
    else
    {
        if(next_node ->right != NULL)                   //when two nodes arent close to each other
        {
            root2 = next_node;
            prev_node->right = NULL;                //makes a new tree where the greater part of the tree points to it
            prev_node = next_node;
            next_node= next_node->right;
            sortTreeData(root2, next_node, prev_node);
        }
    }
}

void bTree::sortTreeData()
{
    sortTreeData(root, root->right, root);
    merge_trees();
}

void bTree::merge_trees()
{
    Node* head = new Node;                  //creates a new root to make the left and right pointers point to root and root2
    head->data = (root->data + root2->data)/2.0;
    head->id = "average";
    head->left = root;
    head->right = root2;
    root = head;
}


