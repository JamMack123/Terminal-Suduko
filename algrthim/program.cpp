/*
Name: Justn MacKenzie, Paige Lekach
ID #: 1572034 , 1573266
CMPUT 275 
WINTER 2020
Final Project: Algorithm X and COver Problems
*/
#include <iostream>
#include <vector>
#include "algx.h"
#define matrixThing vector<vector<int>>
#define  theThing vector<vector<bool>>
//probmatrix must be made out of vector for the 
//algortim to work 


using namespace std;

vector<int> solve(vector<vector<bool>> probMatrix);

int main() {
    // Reading in the input for the col and row #'s of the matrix
    int rows, col;
    cin >> rows;
    cin >> col;
    matrixThing probMatrix;
    //creating the problem matrix using vectors from the input
    for(int j = 0; j <= rows; j++){
        vector<int> temp;
        for(int i = 0; i < col; i++){
            int val = 0;
            cin >> val;
            temp.push_back(val);
        }
        probMatrix.push_back(temp);
    }
    theThing output;
    for(int i = 0; i <= rows; i++){
        vector<bool> temp;
        for(int j = 0; j < col;j++){
            if(probMatrix[i][j] != 0){
                temp.push_back(true);
            }
            else{
                temp.push_back(false);
            }
        }
        output.push_back(temp);
    }
    
    // Solving the matrix and outputing the result
    // Either has a solution of rows or doesn'y
    vector<int> soln; 
    soln = solve(output);
    if(soln.size() > 0){
        cout<<"The ROWS that solve the problem matrix are: ";
        for(auto i = soln.begin(); i!= soln.end(); i++){
            cout << *i << " ";
        }
    } else{
        cout<<"No solution to the problem matrix inputed!"<<endl;
    }
    return 0;
}
