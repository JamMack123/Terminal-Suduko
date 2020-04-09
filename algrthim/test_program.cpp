/*
Name: Justn MacKenzie, Paige Lekach
ID #: 1572034 , 1573266
CMPUT 275 
WINTER 2020
Final Project: Algorithm X and COver Problems
*/

#include "algx.h"
#include <vector>
#include <iostream>

int main(){
    cell *h = new cell; 
    vector<vector<bool>> prob;
    for(int i = 0; i < 5; i++){
        vector<bool> temp;
        for(int j=0; j < 5; j++){
            if(i == 0){
                temp.push_back(true);
            }else
            {
            temp.push_back(false);
            }
        }
        prob.push_back(temp);
    }
    prob[1][1] = true;
    prob[2][2] = true;
    prob[3][3] = true;
    prob[4][4] = true;
    // prob[6][4] = true;
    // prob[9][2] = true;
    // prob[2][8] = true;
    solve(prob);
    return 0;
}
