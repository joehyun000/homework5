#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 행렬의 행과 열의 개수를 입력받는 함수
void input_matrix(int *rows, int *cols) {
    printf("행과 열의 개수 입력: ");
    scanf("%d %d", rows, cols);
}

// 행렬에 메모리를 동적으로 할당하는 함수
int** allocate_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));   // 행렬의 행에 대한 메모리 할당 -> 이중 포인터로 할당
    for (int i=0; i<rows; i++)
        matrix[i] = (int *)malloc(cols * sizeof(int));    // 행렬의 열에 대한 메모리 할당 -> 포인터로 할당
    return matrix;
}

// 행렬의 값을 랜덤으로 생성하는 함수
void fill_matrix(int **matrix, int rows, int cols) {
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            matrix[i][j] = rand() % 100;  // 행렬의 값을 0~99의 랜덤 숫자로 채움
}

// 행렬을 출력하는 함수
void print_matrix(int **matrix, int rows, int cols) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++)
            printf("%d ", matrix[i][j]);        // 행렬의 값을 출력
        printf("\n");
    }
}

// 두 행렬을 더하는 함수
int** addition_matrix(int **A, int **B, int rows, int cols) {    
    int **result = allocate_matrix(rows, cols);       // 결과 행렬에 메모리를 동적으로 할당
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            result[i][j] = A[i][j] + B[i][j];         // A+B의 결과를 result 행렬에 저장
    return result;
}

// 두 행렬을 빼는 함수
int** subtraction_matrix(int **A, int **B, int rows, int cols) {
    int **result = allocate_matrix(rows, cols);       // 결과 행렬에 메모리를 동적으로 할당
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            result[i][j] = A[i][j] - B[i][j];         // A-B의 결과를 result 행렬에 저장
    return result;
}

// 행렬을 전치하는 함수
int** transpose_matrix(int **A, int rows, int cols) {
    int **result = allocate_matrix(cols, rows);       // 전치 행렬에 메모리를 동적으로 할당
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            result[j][i] = A[i][j];                   // 전치 행렬은 원래 행렬의 행과 열을 바꿔주는 것이므로, A[i][j] -> result[j][i]
    return result;
}

// 두 행렬을 곱하는 함수
int** multiply_matrix(int **A, int **B, int rowsA, int colsA, int rowsB, int colsB) {
    if(colsA != rowsB) {                                      // 행렬 곱셈이 불가능한 경우 : colsA와 rowsB가 같지 않을 때
        printf("행렬 곱셈이 불가능합니다.\n");                 
        return NULL;
    }
    int **result = allocate_matrix(rowsA, colsB);             // 결과 행렬에 메모리를 동적으로 할당
    for(int i=0; i<rowsA; i++)
        for(int j=0; j<colsB; j++) {
            result[i][j] = 0;
            for(int k=0; k<colsA; k++)
                result[i][j] += A[i][k] * B[k][j];           // AXB의 결과를 result 행렬에 저장
        }
    return result;
}

// 행렬을 해제하는 함수
void free_matrix(int **matrix, int rows) {
    for(int i=0; i<rows; i++)
        free(matrix[i]);
    free(matrix);
}

int main() {
    printf("[----- [박조현] [2021053017] -----]\n");
    int rowsA, colsA, rowsB, colsB;
    
    // 첫 번째 행렬의 행과 열의 개수 입력
    input_matrix(&rowsA, &colsA);
    // 두 번째 행렬의 행과 열의 개수 입력
    input_matrix(&rowsB, &colsB);
    
    // 행렬의 메모리를 동적으로 할당
    int **matrixA = allocate_matrix(rowsA, colsA);
    int **matrixB = allocate_matrix(rowsB, colsB);
    
    // 두 행렬의 값을 랜덤으로 채우기
    srand(time(0));         // 랜덤 시드 설정 : 실행할 때마다 다른 랜덤 값이 나오도록 함
    fill_matrix(matrixA, rowsA, colsA);
    fill_matrix(matrixB, rowsB, colsB);
    
    // 첫 번째 행렬 출력
    printf("첫 번째 행렬:\n");                    
    print_matrix(matrixA, rowsA, colsA);       

    // 두 번째 행렬 출력
    printf("\n두 번째 행렬:\n");
    print_matrix(matrixB, rowsB, colsB);         
    
    // 행렬 덧셈 : A+B
    printf("\n두 행렬의 합:\n");
    int **sum = addition_matrix(matrixA, matrixB, rowsA, colsA);
    print_matrix(sum, rowsA, colsA);
    
    // 행렬 뺄셈 : A-B
    printf("\n두 행렬의 차:\n");
    int **difference = subtraction_matrix(matrixA, matrixB, rowsA, colsA);
    print_matrix(difference, rowsA, colsA);
    
    // 행렬 전치 : A^T
    printf("\n첫 번째 행렬의 전치:\n");
    int **transposeA = transpose_matrix(matrixA, rowsA, colsA);
    print_matrix(transposeA, colsA, rowsA);
    
    // 행렬 곱셈 : AxB
    printf("\n두 행렬의 곱:\n");
    int **product = multiply_matrix(matrixA, matrixB, rowsA, colsA, rowsB, colsB);
    if (product != NULL)
        print_matrix(product, rowsA, colsB);
    
    // 메모리 해제
    free_matrix(matrixA, rowsA); // 첫 번째 행렬A 메모리 해제
    free_matrix(matrixB, rowsB); // 두 번째 행렬B 메모리 해제
    free_matrix(sum, rowsA); // 합 행렬 A+B 메모리 해제
    free_matrix(difference, rowsA); // 차 행렬 A-B 메모리 해제
    free_matrix(transposeA, colsA); // 전치 행렬 A^T 메모리 해제
    if (product != NULL)
        free_matrix(product, rowsA); // 곱 행렬 메모리 해제
    
    return 0;
}
