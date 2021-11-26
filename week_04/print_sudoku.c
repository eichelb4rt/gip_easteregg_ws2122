#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BOX_SIZE 3
#define N BOX_SIZE * BOX_SIZE
#define MAXCHAR 1024

void print_sudoku(int** grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col % BOX_SIZE == 0 && col != 0) {
                printf("| ");
            }
            if (col == 0) {
                printf(" ");
            }
            if (grid[row][col] == 0) {
                printf("  ");
            } else {
                printf("%d ", grid[row][col]);
            }
        }
        if (row % BOX_SIZE == BOX_SIZE - 1 && row != N - 1) {
            printf("\n");
            for (int i = 0; i < N / BOX_SIZE; ++i) {
                if (i != 0) {
                    printf("+");
                }
                printf("-------");
            }
        }
        printf("\n");
    }
}

int** init_matrix(const int rows, const int columns) {
    int** matrix = (int**) malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (int*) malloc(columns * sizeof(int));
    }
    return matrix;
}

void del_matrix(const int rows, const int columns, int** matrix) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

const char* get_field(char* line, int num) {
    const char* tok;
    for (tok = strtok(line, ",");
        tok && *tok;
        tok = strtok(NULL, ",")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

int** read_grid(const char* filename) {
    FILE* f = fopen(filename, "r");

    int** grid = init_matrix(N, N);
    char line[MAXCHAR];
    int line_number = 0;
    for (int row = 0; row < N; ++row) {
        if (!fgets(line, MAXCHAR, f)) {
            printf("Something went wrong while reading sudoku grid.");
            exit(1);
        }
        char* dup;
        for (int col = 0; col < N; ++col) {
            dup = strdup(line);
            grid[row][col] = atoi(get_field(dup, col + 1));
        }
    }
    return grid;
}

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Please pass the .csv where the sudoku is stored.\n");
        exit(1);
    }
    int** grid = read_grid(argv[1]);
    print_sudoku(grid);
    return 0;
}
