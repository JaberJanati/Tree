/******************************************************************************************************************************
Title: Tree Program
Author: Jaber Janati
Date Created On: May 15, 2014
Description: Program asks user for a file to read. The programs checks if the file exists and then reads from it, the data is later
sorted based on the score value then put into a tree. The tree is then sorted by checking if two nodes are close to each other in
value then creating a new node that stores the average value of the two scores and so forth. Tree is then printed.
*******************************************************************************************************************************/
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<queue>
#include<string>
#include "tree.h"
#include "tree.cpp"
using namespace std;

void sort_tree(vector<float>, vector<string>, int);         //sorts the numbers in ascending order
bool checkFile(string& file);



int main()
{
    ifstream theFile;                                   //varaible for opening file for reading
    string filename;                                    //holds the name of the file to open at command prompt
    queue<string> ordered;                              //queue holds the string version of the tree to be printed

    vector<string> name;                          //stores the name in an array
    vector<float> score;                            //stores the score in an array of float
    string next_name;
    float next_num;
    int size=0;                                             //size at beginning is set to zero of the queue

    cout << "Enter a filename: " << endl;
    cin >> filename;
    checkFile(filename);
    theFile.open(filename.c_str());

    if(theFile.fail())                                      //checks if the file exists or can be opened
    {
        exit(1);
    }
    while(!theFile.eof())
    {
        theFile >> next_name;
        name.push_back(next_name);
        theFile >> next_num;
        score.push_back(next_num);
        size++;

    }
    theFile.close();
    sort_tree(score, name, size);                       //sorts the vector by score in ascending order


    bTree tree;

    for(int i = 0; i < size;i++)
    {
        tree.insert(score[i], name[i]);                     //inserts each names score pair into the tree
    }

    tree.sortTreeData();                                //sorts the tree to get desired output
    tree.print(ordered);                                //prints the tree using queue to store name of each pair as well as ( and ) for tree level
    cout << endl;




    return 0;
}

void sort_tree(vector<float> data, vector<string> name, int size)
{
    for(int i = 0; i <size-1; i++)              //uses bubble sort to sort an array in ascending order
    {
        for(int j= i; j < size-1; j++)
        {
            if(data[i] > data[j])
            {
                std::swap(data[i], data[j]);
                std::swap(name[i], name[j]);
            }
        }
    }
}

bool checkFile(string& file)                                            //adds the txt extenstion if not found
{
   int size = file.length();                       //holds the file name's legnth
    string ending = "";
    if(size >= 5)                                       //checks if the length >= 5 for minimum length for a name that includes .txt
    {
        for(int i = size-4; i < size; i++)              //starts at the last 4 characters and adds value to ending variable
        {
            ending += file[i];
        }
        if(ending != ".txt")                        //checks if the variable is .txt if not then adds it to the string file_name
        {
            file = file + ".txt";
            cout << file << endl;
            return true;
        }
        else
            return true;
    }
    else
        cerr << "Not a valid choice " << endl;
        return false;

    }


