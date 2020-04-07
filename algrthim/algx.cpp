#include "algx.h"
#include <vector>

#include <iostream>
// I KNOW THIS IS BAD STYLE I COULDN'T come up with any
//other names that wouldn't error with already cded thing
//therfore theThing exists purely because I got tired of typing
//the decleration for it multiple times
#define  theThing vector<vector<bool>>

using namespace std;

vector<int> soln;
cell *header = new cell;
// static int maxRow = 0;
// static int maxCol = 0;

void cover(cell *c){
    c->right->left = c->left;
    c->left->right = c->right;
    cell *i = c->down;
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

void uncover(cell *c){
    cell *i = c->up;
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
    c->right->left = c;
    c->left->right = c;
    return;
}

cell* findStartColumn(){
    cell *i = header->right;
    cell *key;
    //The exact max value for an int in C++ this way there is no possible
    //way that the number of 1s in any column is greater then this
    //unless yu are using larger data types
    int max = 2147483647;
    while(i != header){
        int temp = i->count;
        if(temp < max){
            max = temp;
            key = i;
        }
        i = i->right;
    }
    // cout << "Finished " << endl;
    return key;

}

void search(vector<int> &ans){
    if(header->right == header){
        //Have to save values to external vector
        //due to recursive nature of the function
        for(auto i = soln.begin(); i != soln.end(); i++){
            ans.push_back(*i);
        }
        return;
    } else {
        cell *c = findStartColumn();
        cell *r = c->down;
        while(c != r){
            int temp = r->rowID;
            soln.push_back(temp);
            cell *j = r;
            do{
                cover(j->column);
                j = j->right;
            }while(j != r);
            search(ans);
            soln.pop_back();
            c = r->column;
            j = r->left;
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
void createLinkedMatrix(theThing probMatrix,int maxRow, int maxColumn, cell *matrix[]){
    for(int i =0; i< maxRow; i++){
        cout << i <<": ";
        for(int j = 0; j < maxColumn; j++){
            cout<< probMatrix[i][j] << " ";
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
                // cerr <<"Up: " << i <<" " << j << " " << matrix[i][j].up << endl << endl;
            }
        }
        cout << endl;
    }
    //Pointer fixing for header node
    //This allows for a single obect to reference the whole array
    header->right = &matrix[0][0];
    header->left = &matrix[0][maxColumn-1];
    matrix[0][0].left = header;
    matrix[0][maxColumn-1].right = header;
}

void solve(theThing probMatrix){
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
    createLinkedMatrix(probMatrix, maxRow, maxCol, matrix);
    

    cell *temp = header->right;
  
    vector<int> ans;
    search(ans);
    cerr << ans.size() << endl;
    cout << ans[0] << endl;
    // cout << soln[0] << endl;
}
