
#ifndef UTILS_H // if UTILS_H is not defined
#define UTILS_H // define UTILS_H

typedef struct subproblem{
    char curr_len;
    int *i_arr;
    int *j_arr; 
} Subproblem;

void MPS_BU(int *chord, int N, int **M, Subproblem *subproblem_arr);
int MPS_TD(int i, int j, int *chord, int **M, Subproblem *subproblem_arr);
void traceback(int i, int j, int **M, int *chord, int *solution, int *curr_len, bool *is_head);
int RandPartition(int *data, int low, int high);
void QSort(int *data, int low, int high);

#endif