#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "utils.h"

#include <sys/resource.h>
#include <sys/time.h>

typedef struct {
    long utime;  // user time in microseconds
    long stime;  // system time in microseconds
    size_t vmPeak; // peak memory in KB
} TmStat;

void getPeriodUsage(TmStat* stat) {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        stat->utime = usage.ru_utime.tv_sec * 1000000 + usage.ru_utime.tv_usec;
        stat->stime = usage.ru_stime.tv_sec * 1000000 + usage.ru_stime.tv_usec;
        stat->vmPeak = usage.ru_maxrss; // KB on Linux
    }
}

// Alternative using /proc for more accurate memory measurement on Linux
void getPeriodUsageProc(TmStat* stat) {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        stat->utime = usage.ru_utime.tv_sec * 1000000 + usage.ru_utime.tv_usec;
        stat->stime = usage.ru_stime.tv_sec * 1000000 + usage.ru_stime.tv_usec;
    }
    
    // Get peak memory from /proc
    FILE* file = fopen("/proc/self/status", "r");
    if (file) {
        char line[128];
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "VmPeak:", 7) == 0) {
                sscanf(line + 7, "%lu", &stat->vmPeak);
                break;
            }
        }
        fclose(file);
    }
}


void help_message() {
    printf("Usage: mps --method=<method> <input_file> <output_file>\n");
    printf("options:\n");
    printf("   bu - bottom-up DP\n");
    printf("   td - top-down DP\n");
}

int main(int argc, char *argv[]) {
    // start timing 
    // clock_t start = clock();
    // === memory ====
    struct timeval start, end;
    TmStat stat;
    
    gettimeofday(&start, NULL);

    //=====


    // Check command line arguments
    if (argc != 4 && argc != 3) {
        help_message();
        return 1;
    }

    // ===== Parse method flag =======
    char *method;
    FILE *input;
    FILE *output;
    bool print_order = false;
    if (argc == 4) {
        if (strncmp(argv[1], "--method=", 9) != 0) {
            printf("Invalid method flag\n");
            return 1;
        }
        method = argv[1] + 9;  // Skip "--method="
        // Open input and output files
        input = fopen(argv[2], "r");
        output = fopen(argv[3], "w");
        print_order = true;
    }
    else {
        // Open input and output files
        method = "td"; // default method
        input = fopen(argv[1], "r");
        output = fopen(argv[2], "w");
    }
 
    if (!input || !output) {
        printf("Error opening files\n");
        return 1;
    }

    // ===== Read input =====
    int n, N;
    fscanf(input, "%d", &n);
    printf("Number of chords: %d\n", n); // debug

    N = n/2; 
    int *chord = malloc(sizeof(int) * n);
    bool *is_head = calloc(n, sizeof(bool)); 
    // read the chord data
    for(int i = 0; i < N; i++){
        int a, b;
        fscanf(input, "%d %d", &a, &b);
        // printf("Read chord: %d - %d\n", a, b); // Debug
        chord[a] = b; chord[b] = a;
        is_head[a] = true; is_head[b] = false;
    }    
    // initialize M and record tables
    int **M = malloc(sizeof(int*) * (2*N));
    for (int i = 0; i < 2*N; i++) {
        M[i] = calloc(2*N - i, sizeof(int)); // only need upper triangle
    }
    Subproblem sub;
    sub.curr_len = 0;
    sub.i_arr = malloc(sizeof(char) * 4);
    sub.j_arr = malloc(sizeof(char) * 4);
    // =========== Choose method ===========
    if (strcmp(method, "bu") == 0) {
        // Bottom-up DP implementation
        // printf("Running bottom-up DP\n");
        MPS_BU(chord, N, M, &sub);
        int result = M[0][2*N - 1];
        fprintf(output, "%d\n", result);
        // ======== print the subproblem visited ======
        if (print_order){
            for (int i = 0; i < 5; i++) {
                if (i == 3) printf("..., ");
                else if (i == 4) printf("(%d, %d)\n", sub.i_arr[3], sub.j_arr[3]);
                else printf("(%d, %d), ", sub.i_arr[i], sub.j_arr[i]);
            }
        }
        free(sub.i_arr); free(sub.j_arr);
        // ======== traceback to get solution ========
        int *solution = malloc(sizeof(int) * result);
        int sol_len = 0;
        traceback(0, 2*N - 1, M, chord, solution, &sol_len, is_head);

        // ========== output the solution =========
        QSort(solution, 0, sol_len - 1);
        for (int i = 0; i < sol_len; i++) {
            // printf("%d %d\n", solution[i], chord[solution[i]]);
            fprintf(output, "%d %d\n", solution[i], chord[solution[i]]);
        }

        // ========== free memory ==========
        for (int i = 0; i < n; i++) {
            free(M[i]);
        }
        free(M);
        free(solution);
    }
    else if (strcmp(method, "td") == 0) {
        // printf("Running top-down DP\n");
        // initialize M with -1
        for (int i = 0; i < 2*N; i++) {
            for (int j = 0; j < 2*N - i; j++) {
                M[i][j] = -1;
            }
        }

        int result = MPS_TD(0, 2*N - 1, chord, M, &sub);
        fprintf(output, "%d\n", result);

        // ======== print the subproblem visited ======
        if (print_order){
            for (int i = 0; i < 5; i++) {
                if (i == 3) printf("..., ");
                else if (i == 4) printf("(%d, %d)\n", sub.i_arr[3], sub.j_arr[3]);
                else printf("(%d, %d), ", sub.i_arr[i], sub.j_arr[i]);
            }
        }
        free(sub.i_arr); free(sub.j_arr);
        // ======== traceback to get solution ========
        int *solution = malloc(sizeof(int) * result);
        int sol_len = 0;
        traceback(0, 2*N - 1, M, chord, solution, &sol_len, is_head);
        // ========== output the solution =========
        QSort(solution, 0, sol_len - 1);
        for (int i = 0; i < sol_len; i++) {
            // printf("%d %d\n", solution[i], chord[solution[i]]);
            fprintf(output, "%d %d\n", solution[i], chord[solution[i]]);
        }

        // ========== free memory ==========
        for (int i = 0; i < n; i++) {
            free(M[i]);
        }
        free(M);
        free(solution);
    } 
    else {
        help_message();
        return 1;
    }
    // End timing and calculate duration
    // clock_t end = clock();
    // double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // printf("Execution time: %f seconds\n", cpu_time_used);
    gettimeofday(&end, NULL);
    getPeriodUsageProc(&stat);
    
    long elapsed = (end.tv_sec - start.tv_sec) * 1000000 + 
                   (end.tv_usec - start.tv_usec);
    
    printf("The total CPU time: %.3f s\n", (stat.utime + stat.stime) / 1000000.0);
    printf("memory: %lf GB\n", stat.vmPeak/1048576.0);
    // ============= Clean up =============
    free(chord);
    free(is_head);

    fclose(input);
    fclose(output);
    return 0;
}