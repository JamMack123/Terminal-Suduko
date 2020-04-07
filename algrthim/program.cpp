#include <iostream>
#include "algx.h"
#define matrix vector<vector<int>>
#define boolMatrix vector<vector<bool>>
//probmatrix must be made out of vector for the 
//algortim to work 


using namespace std;

int main() {
    int m, n;
    cin >> n;
    cin >> m;
    cout << n <<" " << m << endl;
    matrix probMatrix;
    for(int j = 0; j<= m; j++){
        vector<int> temp;
        for(int i = 0; i < n; i++){
            int val = 0;
            cin >> val;
            temp.push_back(val);
        }
        probMatrix.push_back(temp);
    }
    boolMatrix output;
    for(int i = 0; i <= m; i++){
        vector<bool> temp;
        for(int j = 0; j < n;j++){
            if(probMatrix[i][j] != 0){
                temp.push_back(true);
            }
            else{
                temp.push_back(false);
            }
        }
        output.push_back(temp);
    }



    for(int i = 0; i<= m; i++){
        for(int j = 0; j<n; j++){
            cout << output[i][j] <<" ";
        }
        cout << endl;
    }

    vector<int> soln; 
    soln  = solve(output);
    return 0;
}
