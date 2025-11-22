#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void help_message() {
    printf("Usage: ./compare <input_file> <output_file>\n");
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        help_message();
        return 1;
    }
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    if (!file1 || !file2) {
        printf("Error opening files\n");
        return 1;
    }
    clock_t start = clock();
    // Compare the results
    int result1, result2;
    fscanf(file1, "%d", &result1);
    fscanf(file2, "%d", &result2);
    if (result1 != result2) {
        printf("Results are different\n");
        return 1;
    }
    printf("Results are the same\n");
    printf("Start comparing the edges\n");
    int pair1_1, pair1_2, pair2_1, pair2_2;
    int error_count = 0;
    for (int i = 0; i < result1; i++) {
        fscanf(file1, "%d %d", &pair1_1, &pair1_2);
        fscanf(file2, "%d %d", &pair2_1, &pair2_2);
        if (pair1_1 != pair2_1 || pair1_2 != pair2_2) {
            error_count++;
            printf("Edge %d is different\n", i);
            printf("pair1: (%d, %d), pair2: (%d, %d)\n", pair1_1, pair1_2, pair2_1, pair2_2);
        }
    }
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time for comparing edges: %f seconds\n", cpu_time_used);
    if (error_count > 0) {
        printf("Total %d edges are different\n", error_count);
    } else {
        printf("All edges are the same\n");
    }
    fclose(file1);
    fclose(file2); 
    return 0;
}