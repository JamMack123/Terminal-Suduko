#ifndef _ALGX_H_
#define _ALGX_H_
#include <vector>
using namespace std;

struct cell{
    struct cell *up;
    struct cell *down;
    struct cell *left;
    struct cell *right;
    struct cell *column;
    int rowID;
    int colID;
    int count = 0;
};

void createLinkedMatrix(vector<vector<bool>> probMatrix, int MaxRow, int MaxColumn);

void search(cell *header, int depth, vector<int> soln);

void cover(cell *c);

void uncover(cell *c);

vector<int> solve(vector<vector<bool>>);

#endif
