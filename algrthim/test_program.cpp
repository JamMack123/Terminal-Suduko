#include "algx.h"
#include <vector>
#include <iostream>

int main(){
    cell *h = new cell; 
    vector<vector<bool>> prob;
    for(int i = 0; i < 10; i++){
        vector<bool> temp;
        for(int j=0; j < 10; j++){
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
    cell test =  createLinkedMatrix(prob, 10,10);
    
    return 0;
}
