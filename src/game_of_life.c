#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NMAX 80
#define NMIN 25
void input(int matrix[NMIN][NMAX]);
void draw(int matrix[NMIN][NMAX]);
int n_of_neighbours(int matrix[NMIN][NMAX], int i, int j);
int new_i_height(int i);
int new_j_width(int j);
void update_matrix(int matrix[NMIN][NMAX], int new_matrix[NMIN][NMAX]);
int update_cell(int value, int n_of_nei);

int main() {
    int matrix[NMIN][NMAX];
    int new_matrix[NMIN][NMAX];
    input(matrix);
    int count = 0;
    while (1) {
        count++;
        printf("\33[0d\33[2J");
        draw(matrix);
        usleep(300000);
        update_matrix(matrix, new_matrix);
        for (int i = 0; i < NMIN; i++) {
            for (int j = 0; j < NMAX; j++) {
                matrix[i][j] = new_matrix[i][j];
            }
        }
        if (count == 100) {
            break;
        }
    }
    return 0;
}

void input(int matrix[NMIN][NMAX]) {
    for (int i = 0; i < NMIN; i++) {
        for (int j = 0; j < NMAX; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void draw(int matrix[NMIN][NMAX]) {
    for (int i = 0; i < NMIN; i++) {
        for (int j = 0; j < NMAX; j++) {
            if (matrix[i][j] == 0) {
                printf(" ");
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}

void update_matrix(int matrix[NMIN][NMAX], int new_matrix[NMIN][NMAX]) {
    int n_of_n;
    for (int i = 0; i < NMIN; i++) {
        for (int j = 0; j < NMAX; j++) {
            n_of_n = n_of_neighbours(matrix, i, j);
            new_matrix[i][j] = update_cell(matrix[i][j], n_of_n);
        }
    }
}

int update_cell(int value, int n_of_n) {
    int i = value;
    if (value == 0 && n_of_n == 3) i = 1;
    if (value == 1 && (n_of_n < 2 || n_of_n > 3)) i = 0;
    return i;
}

int new_i_height(int i) {
    if (i == -1)
        i = 25;
    else if (i == 26)
        i = 0;
    return i;
}

int new_j_width(int j) {
    if (j == -1)
        j = 25;
    else if (j == 26)
        j = 0;
    return j;
}

int n_of_neighbours(int matrix[NMIN][NMAX], int i, int j) {
    int calc = 0;
    calc -= matrix[new_i_height(i)][new_j_width(j)];
    for (int i_delt = -1; i_delt < 2; i_delt++)
        for (int j_delt = -1; j_delt < 2; j_delt++)
            calc += matrix[new_i_height(i + i_delt)][new_j_width(j + j_delt)];
    return calc;
}