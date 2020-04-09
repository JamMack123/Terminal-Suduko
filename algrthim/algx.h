/*
Name: Justn MacKenzie, Paige Lekach
ID #: 1572034 , 1573266
CMPUT 275 
WINTER 2020
Final Project: Algorithm X and COver Problems
*/

#ifndef _ALGX_H_
#define _ALGX_H_
#include <vector>
using namespace std;

// Initializiation of the cell struct that will help us creat our linked matrix 
// by defining each cell to be connected to another cell upwards, downwards, to the left and right

struct cell{
    // Connected up, down, left, right cells
    struct cell *up;
    struct cell *down;
    struct cell *left;
    struct cell *right;
    
    // the column the cell belongs to
    struct cell *column;
    
    // Which row and column it is
    int rowID;
    int colID;
    
    //The amount of 1's present in teh cell's column
    int count = 0;
};

//Forward declerations of the functions in algx.cpp
void createLinkedMatrix(vector<vector<bool>> probMatrix, int MaxRow, int MaxColumn);

void search(cell *header, int depth, vector<int> soln);

void cover(cell *c);

void uncover(cell *c);

vector<int> solve(vector<vector<bool>>);

#endif
