#include "algx.h"
#include "algx.h"
#include <vector>

#include <iostream>
// I KNOW THIS IS BAD STYLE I COULDN'T come up with any
//other names that wouldn't error with already cded thing
//therfore theThing exists purely because I got tired of typing
//the decleration for it multiple times
#define  theThing vector<vector<bool>>

using namespace std;

cell *header = new cell;

void cover(){
    int x = 7;
};

void search(cell *header, int depth, vector<int> soln){
    int X = 7;
};

void createLinkedMatrix(theThing probMatrix, int maxRow, int maxColumn){
    cell matrix[maxRow][maxColumn];

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
    header->right = &matrix[0][0];
    header->left = &matrix[0][maxColumn-1];
    matrix[0][0].left = header;
    matrix[0][maxColumn-1].right = header;
}

void solve(theThing probMatrix){

}
