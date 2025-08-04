#include <stdio.h>

#define MAX 100

void addSparseMatrices(int matrix1[MAX][3], int matrix2[MAX][3], int result[MAX][3], int *r1, int *r2) {
    int i = 0, j = 0, k = 0;

    while (i < *r1 && j < *r2) {
        if (matrix1[i][0] == matrix2[j][0] && matrix1[i][1] == matrix2[j][1]) {
            result[k][0] = matrix1[i][0];
            result[k][1] = matrix1[i][1];
            result[k][2] = matrix1[i][2] + matrix2[j][2];
            i++;
            j++;
            k++;
        }
        else if (matrix1[i][0] < matrix2[j][0] || (matrix1[i][0] == matrix2[j][0] && matrix1[i][1] < matrix2[j][1])) {
            result[k][0] = matrix1[i][0];
            result[k][1] = matrix1[i][1];
            result[k][2] = matrix1[i][2];
            i++;
            k++;
        }
        else {
            result[k][0] = matrix2[j][0];
            result[k][1] = matrix2[j][1];
            result[k][2] = matrix2[j][2];
            j++;
            k++;
        }
    }
    
    while (i < *r1) {
        result[k][0] = matrix1[i][0];
        result[k][1] = matrix1[i][1];
        result[k][2] = matrix1[i][2];
        i++;
        k++;
    }

    while (j < *r2) {
        result[k][0] = matrix2[j][0];
        result[k][1] = matrix2[j][1];
        result[k][2] = matrix2[j][2];
        j++;
        k++;
    }

    *r1 = k; 
}

void inputMatrix(int matrix[MAX][3], int *rows) {
    int i;
    printf("Enter the number of non-zero elements: ");
    scanf("%d", rows);

    for (i = 0; i < *rows; i++) {
        printf("Enter row, column, and value for element %d: ", i + 1);
        scanf("%d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2]);
    }
}

void printMatrix(int matrix[MAX][3], int rows) {
    printf("\nRow  Column  Value\n");
    for (int i = 0; i < rows; i++) {
        printf("%d    %d      %d\n", matrix[i][0], matrix[i][1], matrix[i][2]);
    }
}
void transposeSparseMatrix(int matrix[MAX][3], int *rows) {
    int i;
    int transposed[MAX][3];
    int k = 0;

    // Transposing the sparse matrix (swap rows and columns)
    for (i = 0; i < *rows; i++) {
        transposed[k][0] = matrix[i][1];  // Swap row and column
        transposed[k][1] = matrix[i][0];  // Swap row and column
        transposed[k][2] = matrix[i][2];  // Value remains the same
        k++;
    }
    for (i = 0; i < k; i++) {
        matrix[i][0] = transposed[i][0];
        matrix[i][1] = transposed[i][1];
        matrix[i][2] = transposed[i][2];
    }

    *rows = k;  // Update the number of rows (non-zero elements)
}

int main() {
    int matrix1[MAX][3], matrix2[MAX][3], result[MAX][3];
    int rows1, rows2;

    printf("Enter details for the first sparse matrix:\n");
    inputMatrix(matrix1, &rows1);

    printf("\nEnter details for the second sparse matrix:\n");
    inputMatrix(matrix2, &rows2);

    addSparseMatrices(matrix1, matrix2, result, &rows1, &rows2);

    printf("\nResultant Sparse Matrix after Addition:\n");
    printMatrix(result, rows1);
    printf("\nTransposing the Resultant Sparse Matrix:\n");
    transposeSparseMatrix(result, &rows1);

    printMatrix(result, rows1);

    return 0;
}
