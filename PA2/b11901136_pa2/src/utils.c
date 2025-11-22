#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

void MPS_BU(int *chord, int N, int **M, Subproblem *subproblem_arr) {
    // Bottom-up DP implementation
    // int first_3 = 0;
    for (int length = 1; length < 2*N; length++) {
        for (int i = 0; i < 2*N - length; i++) { // start point
            int j = i + length; // end point

            int k = chord[j];
            // printf("before options\n");
            int option1 = M[i][j-1-i];
            // printf("after options\n");
            if (k == i){
                M[i][j-i] = M[i+1][(j-1)-(i+1)] + 1;
            }
            else if (i < k && k < j && (M[i][k-1-i] + M[k+1][j-1-(k+1)] + 1 > option1)) {
                M[i][j-i] = M[i][k-1-i] + M[k+1][j-1-(k+1)] + 1;
            } else {
                M[i][j-i] = option1;
            }
            if (subproblem_arr->curr_len < 3) {
                subproblem_arr->i_arr[subproblem_arr->curr_len] = i;
                subproblem_arr->j_arr[subproblem_arr->curr_len] = j;
                (subproblem_arr->curr_len)++;
            }
            // printf("i=%d, j=%d, M[%d][%d]=%d\n", i, j, i, j - i, M[i][j - i]);
                // printf("M(%d, %d) = %d\n", i, j, M[i][j]);
            // if (print_order && first_3 < 3) {
                // printf("M(%d, %d) = %d\n", i, j, M[i][j]);
                
                // first_3++;
            // }
        }
    }
    subproblem_arr->i_arr[3] = 0;
    subproblem_arr->j_arr[3] = 2*N - 1;
    (subproblem_arr->curr_len) = 4;
    // printf("M(%d, %d) = %d\n", 0, 2*N - 1, M[0][2*N - 1]);// last subproblem
}

int MPS_TD(int i, int j, int *chord, int **M, Subproblem *subproblem_arr) {
    // Top-down DP implementation with memoization
    if (M[i][j-i] != -1) {
        return M[i][j-i];
    }

    int k = chord[j];
    // record the subproblem
    if (subproblem_arr->curr_len == 4) {
        subproblem_arr->i_arr[3] = i;
        subproblem_arr->j_arr[3] = j;
    }
    else {
        subproblem_arr->i_arr[subproblem_arr->curr_len] = i;
        subproblem_arr->j_arr[subproblem_arr->curr_len] = j;
        (subproblem_arr->curr_len)++;
    }

    if (j <= i) {
        M[i][j-i] = 0;
        return 0;
    }

    if (k == i) {
        M[i][j-i] = 1 + MPS_TD(i + 1, j - 1, chord, M, subproblem_arr);
    } 
    else {
        int option1 = MPS_TD(i, j - 1, chord, M, subproblem_arr);
        M[i][j-i] = option1;
        if (i < k && k < j) {
            int option2 = 1 + MPS_TD(i, k - 1, chord, M, subproblem_arr)
                    + MPS_TD(k + 1, j - 1, chord, M, subproblem_arr);
            if (option2 > option1) {
                M[i][j-i] = option2;
            }
        }
    }

    return M[i][j-i];
}

void traceback(int i, int j, int **M, int *chord, int *solution, int *curr_len, bool *is_head) {
    if (M[i][j-i] == 0) return;

    int k = chord[j];
    if (k == i) {
        if (is_head[i]) solution[(*curr_len)++] = i;
        else solution[(*curr_len)++] = j;
        traceback(i+1, j-1, M, chord, solution, curr_len, is_head);
    }
    else if (M[i][j-i] > M[i][j-1-i]) { // take this edge
        if (is_head[j]) solution[(*curr_len)++] = j;
        else solution[(*curr_len)++] = k;
        traceback(i, k-1, M, chord, solution, curr_len, is_head);
        traceback(k+1, j-1, M, chord, solution, curr_len, is_head);
    }
    else {
        traceback(i, j-1, M, chord, solution, curr_len, is_head);
        return;
    }
}

int RandPartition(int *data, int low, int high) {
    int random_index = low + rand() % (high - low);
    int temp = data[low];
    data[low] = data[random_index];
    data[random_index] = temp;

    int pivot = data[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        while (data[--j] > pivot);
        while (data[++i] < pivot);
        if (i < j) {
            // swap data[i] and data[j]
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        } else {
            return j;
        }
    }
}

void QSort(int *data, int low, int high) {
    if (low < high) {
        int pivotIndex = RandPartition(data, low, high);
        QSort(data, low, pivotIndex);
        QSort(data, pivotIndex + 1, high);
    }
}

