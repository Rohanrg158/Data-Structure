#include<stdio.h>
#define MAX 100

void sumSparseMatrices(int mat1[MAX][3], int mat2[MAX][3], int result[MAX][3], int *r1, int *r2)
{
  int i=0, j=0, k=0;
  while (i<*r1 && j<*r2)
  {
    if (mat1[i][0]==mat2[j][0] && mat1[i][1]==mat2[j][1])
    {
      result[k][0]=mat1[i][0];
      result[k][1]=mat1[i][1];
      result[k][2]=mat1[i][2]+mat2[j][2];
      i++;
      j++;
    }
    else if (mat1[i][0] < mat2[j][0] || (mat1[i][0] == mat2[j][0] && mat1[i][1]<mat2[j][1]))
    {
      result[k][0]=mat1[i][0];
      result[k][1]=mat1[i][1];
      result[k][2]=mat1[i][2];
      i++;
      j++;
    }
    else
    {
      result[k][0]=mat1[i][0];
      result[k][1]=mat1[i][1];
      result[k][2]=mat2[j][2];
      i++;
      j++;
    }
  }
  while (i < *r1)
  {
      result[k][0]=mat1[i][0];
      result[k][1]=mat1[i][1];
      result[k][2]=mat1[i][2];
      i++;
      j++;
  }
  while (j < *r2) 
  {
     result[k][0]=mat1[i][0];
      result[k][1]=mat1[i][1];
      result[k][2]=mat2[j][2];
      i++;
      j++;
  }
  *r1 = k;
}
void printSparseMatrix(int matrix[MAX][3], int rows) 
{
   printf("\nRow Column Value\n");
   for(int i=0; i<rows; i++)
    {
      printf("%d    %d    %d\n", matrix[i][0], matrix[i][1], matrix[i][2]);
    }
}
void inputSparseMatrix(int matrix[MAX][3], int *rows) 
{
  int i;
  printf("Enter the number of non-zero elements in the matrix: ");
  scanf("%d", &*rows);
  for (int i = 0; i < *rows; i++) 
  {
      printf("Enter row index, column index and value for element %d: ", i + 1);
      scanf("%d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2]);
  }
}
void transposeSparseMatrix(int matrix[MAX][3], int result[MAX][3], int rows) {
    int k = 0;
    for (int col = 0; col < MAX; col++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][1] == col) {
                result[k][0] = matrix[i][1]; 
                result[k][1] = matrix[i][0]; 
                result[k][2] = matrix[i][2];
                k++;
            }
        }
    }
}
int main()
{
    int mat1[MAX][3], mat2[MAX][3], result[MAX][3], transpose[MAX][3];
    int rows1, rows2;

    printf("Enter details for the first sparse matrix:\n");
    inputSparseMatrix(mat1, &rows1);

    printf("Enter details for the second sparse matrix:\n");
    inputSparseMatrix(mat2, &rows2);

    sumSparseMatrices(mat1, mat2, result, &rows1, &rows2);

    printf("\nResultant Sparse Matrix after Addition:\n");
    printSparseMatrix(result, rows1);

    transposeSparseMatrix(result, transpose, rows1);

    printf("\nTranspose of the Resultant Sparse Matrix:\n");
    printSparseMatrix(transpose, rows1);

    return 0;
}
