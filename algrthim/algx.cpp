/*
Name: Justn MacKenzie, Paige Lekach
ID #: 1572034 , 1573266
CMPUT 275 
WINTER 2020
Final Project: Algorithm X and COver Problems
*/
//Including outside files and libraries
#include "algx.h"
#include <vector>

#include <iostream>
// I KNOW THIS IS BAD STYLE I COULDN'T come up with any
//other names that wouldn't error with already cded thing
//therfore theThing exists purely because I got tired of typing
//the decleration for it multiple times
#define  theThing vector<vector<bool>>

using namespace std;
// Our global vectors
vector<int> soln;
cell *header = new cell;

/*
 This function is used in the search function to be able to cover a column in our problem
 matrix to figure out if it is a solution.
 Inputs: cell *c (column to cover)
 Outputs: NONE 
*/
void cover(cell *c){
    // Re-assigning whats to the left and right of the passed in column
    c->right->left = c->left;
    c->left->right = c->right;
    cell *i = c->down;
    // Going through the rest of the columns and figure out which other elements
    // that are connected to c and reassigning those up and down values
    while(i != c){
        cell *j = i->right;
        while(j != i){
            j->down->up = j->up;
            j->up->down = j->down;
            j->count = j->column->count-1;
            j = j->right;
        }
        i = i -> down;
    }
    return;
};

/*
    This function uncovers a given column, which is used in the search function
    Inputs: cell *c (the column to uncover)
    Outputs: NONE
*/
void uncover(cell *c){
    cell *i = c->up;
    // Re-assigning the columns so that c can be re inserted into the matrix
    while(i != c){
        cell *j = i->left;
        while(j!= i){
            j->column->count--;
            j->down->up = j;
            j->up->down = j;
            j = j->left;
        }
        i = i->up;
    }
    // Re-assignming the c values
    c->right->left = c;
    c->left->right = c;
    return;
}

/*
    This function searches the given matrix for the column with the lowest amount
    of 1's and this in turn is the column that will be started with in search
    Inputs: NONE
    Outputs: cell* (the column that will be started with in search)
*/
cell* findStartColumn(){
    cell *i = header->right;
    cell *key;
    //The exact max value for an int in C++ this way there is no possible
    //way that the number of 1s in any column is greater then this
    //unless yu are using larger data types
    int max = 2147483647;
    while(i != header){
        // Comparing the values of the column count of each column to determine the
        // smallest value, then setting the key to be that column
        
        int temp = i->count;
        if(temp < max){
            max = temp;
            key = i;
        }
        i = i->right;
    }
    // Returning the start column
    return key;

}

/*
    This function is where algorithm x is implemented and the matrix is searched
    for the rows that solve the matrix. The Solution is saved as a vector and the rowID;s
    are added as they are found as solutions. The uncover, cover, findFirstColumn function are utilised here
*/
void search(vector<int> &ans){
    // Case where all the solutions have been found and the solution is added to the ans vector
    if(header->right == header){
        //Have to save values to external vector
        //due to recursive nature of the function
        for(auto i = soln.begin(); i != soln.end(); i++){
            ans.push_back(*i);
        }
        return;
    } else {
        // Initializing our variables
        cell *c = findStartColumn();
        cell *r = c->down;
        
        //While we're not back at the start
        while(c != r){
            // adding the rowID of r to the soln
            int temp = r->rowID;
            soln.push_back(temp);
            cell *j = r;
            // Covering all the adjacent elements until we're back at r
            do{
                cover(j->column);
                j = j->right;
            }while(j != r);
            // recursively calling the function to find other solutions
            search(ans);
            // if the rowID added ends up not being a solution to the matrix
            // the ID is popped off the soln vector
            soln.pop_back();
            c = r->column;
            j = r->left;
            
            // uncovering the adjacent columns since r is no longer a solution
            while(j!=r){
                uncover(j->column);
                j = j->left;
            }
            r = r->down;
        }
        uncover(c);
        return;
    }
}

/*
    This function takes the inputed problem matrix and converts it to a matrix that is columns
    and rows of 0's and 1's that are all connected right, left, up, and down. The matrix is a cell 
    pointer instance and has all the attributes of the cell struct.
    Inputs: theThing probMatrix
            int maxRow
            int maxColumn
            cell *matrix[]
    Outputs: NONE
*/
void createLinkedMatrix(theThing probMatrix,int maxRow, int maxColumn, cell *matrix[]){
    for(int i =0; i< maxRow; i++){
        for(int j = 0; j < maxColumn; j++){
            if(probMatrix[i][j]){
                //Assigns ids to matrix
                matrix[i][j].rowID = i;
                matrix[i][j].colID = j;
                matrix[i][j].column = &matrix[0][j];
                //If not the first row adds to count 
                //This allows for determing the column with the least
                //number of elemnts
                if(i !=0){
                    matrix[0][j].count +=1;
                }
                //Assigning right pointer
                int temp = j;
                do{
                    temp++;
                    //Confirms wrap around
                    temp = temp%(maxColumn);
                }while(!probMatrix[i][temp] && j != temp);
                matrix[i][j].right = &matrix[i][temp];
                //Assigning left pointer
                temp = j;
                do{
                    temp--;
                    if(temp <0){
                        //Confirms wrap around
                        temp = maxColumn-1;
                    }
                }while(!probMatrix[i][temp] && j != temp);
                matrix[i][j].left = &matrix[i][temp];
                //Assigning down pointer
                temp = i;
                do{
                    temp++;
                    
                    //Confirms wrap around
                    temp = temp%(maxRow);
                }while(!probMatrix[temp][j] && i != temp);
                matrix[i][j].down = &matrix[temp][j];
                //Assigning up pointer
                temp = i;
                do{
                    temp--;
                    if(temp <0){
                        //Confirms wrap around
                        temp = maxRow-1;
                    }
                }while(!probMatrix[temp][j] && i != temp);
                matrix[i][j].up = &matrix[temp][j];
            }
        }
    }
    //Pointer fixing for header node
    //This allows for a single obect to reference the whole array
    header->right = &matrix[0][0];
    header->left = &matrix[0][maxColumn-1];
    matrix[0][0].left = header;
    matrix[0][maxColumn-1].right = header;
}

/*
    This function calls on all the other functions in this file to be able to solve the problem
    and return the solution vector of the rowID's
    Inputs: theThing probMatrix
    Ouutputs: vector<int> (the solution vector)
*/
vector<int> solve(theThing probMatrix){
    // Getting the variable values from the probMatrix
    int maxRow, maxCol;
    maxCol = probMatrix[0].size();
    maxRow = probMatrix.size();
    cell *matrix[maxCol];
    //Reserves space for the matrix so the pointers
    //organized within the create linked matrix function do
    //not get destroyed
    for(int i = 0; i < maxCol; i++){
        matrix[i] = new cell[maxRow];
    }
    // Creating out Linked Matrix 
    createLinkedMatrix(probMatrix, maxRow, maxCol, matrix);
    
    cell *temp = header->right;
    
    // Searching the matrix for the row answers and returning the ans vector 
    vector<int> ans;
    search(ans);
    
    return ans;
    
}
