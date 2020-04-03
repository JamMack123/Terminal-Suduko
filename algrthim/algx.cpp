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
    int col = 999999999999999999999;
    while(i != header){
        int temp = i->count;
        if(temp < col){
            col = temp;
            key = i;
        }
        i = i->right;
    }
    return key;
    /*
    struct cell *h = header;
    struct cell *first = h->right;
    h = h->right->right;
    do
    {
        if(h->nodeCount < first->nodeCount){
            first = h;
        }
        h = h->right;
    }while(h != header);
    */

}

void search(int depth, vector <int> soln){
    if(header->right == header){
        // print_solutions(soln);
        return;
    } else {
        cell *c = findStartColumn();
        cell *r = c->down;
        while(c != r){
            soln.push_back(r->rowID);
            cell *j = r->right;
            while(j != r){
                cover(j->column);
                j = j->right;
            }
            search(depth+1, soln);
            soln.pop_back();
            //r = s[k]; ?????????
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
    //Pointer fixing for header node
    //This allows for a single obect to reference the whole array
    header->right = &matrix[0][0];
    header->left = &matrix[0][maxColumn-1];
    matrix[0][0].left = header;
    matrix[0][maxColumn-1].right = header;
}

void solve(theThing probMatrix){
    int maxCol, maxRow;
    maxCol = probMatrix[0].size();
    maxRow = probMatrix.size();
    createLinkedMatrix(probMatrix, maxRow,maxCol);
    


    cout << header->right << endl;
    cell *temp = header->right;
    cover(temp);
    cout << header->right << endl;
    uncover(temp);
    cout << header->right << endl;
    temp = findStartColumn();
    cout << temp << endl;
}
