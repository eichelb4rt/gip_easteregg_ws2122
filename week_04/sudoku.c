#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BOX_SIZE 3
#define N BOX_SIZE * BOX_SIZE
#define MAXCHAR 1024

bool is_present_in_column(int col, int num, int** grid) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
bool is_present_in_row(int row, int num, int** grid) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
bool is_present_in_box(int boxStartRow, int boxStartCol, int num, int** grid) {
    for (int row = 0; row < BOX_SIZE; row++)
        for (int col = 0; col < BOX_SIZE; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}
void print_sudoku(int** grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col % BOX_SIZE == 0 && col != 0) {
                printf("| ");
            }
            if (col == 0) {
                printf(" ");
            }
            printf("%d ", grid[row][col]);
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
bool find_empty_place(int* row, int* col, int** grid) {
    for (*row = 0; *row < N; ++ * row)
        for (*col = 0; *col < N; ++ * col)
            if (grid[*row][*col] == 0)
                return true;
    return false;
}
bool is_valid(int row, int col, int num, int** grid) {
    return !is_present_in_row(row, num, grid)
        && !is_present_in_column(col, num, grid)
        && !is_present_in_box(row - row % BOX_SIZE, col - col % BOX_SIZE, num, grid);
}
bool solve_sudoku(int** grid) {
    int row, col;
    if (!find_empty_place(&row, &col, grid))
        return true;
    for (int num = 1; num <= N; num++) {
        if (is_valid(row, col, num, grid)) {
            grid[row][col] = num;
            if (solve_sudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
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

int** read_grid(char* filename) {
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

int main() {
    int** grid = read_grid("grid.csv");
    if (solve_sudoku(grid))
        print_sudoku(grid);
    else
        printf("No solution exists\n");
}