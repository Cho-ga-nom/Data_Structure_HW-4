#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [조수현]  [2018038084] -----]\n");

    int row, col;
    srand(time(NULL));  // 난수 발생 함수

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);  // 행, 열을 입력받아 2차원 배열 생성
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}  // 배열 생성 실패 시 -1 리턴

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");  // 배열 초기화
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");  // 배열 출력
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n"); // 배열 덧셈
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");   //  배열 뺄셈
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");   // 배열 전치
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");  // 배열 곱셈
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':  
            printf("Free all matrices..\n");    // 배열 해제
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');   // 배열 해제 시 프로그램 종료

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0)    // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix = (int**)malloc(sizeof(int)*row);   // 2차원 배열 동적 할당

    for(int i = 0; i < row; i++) {
        matrix[i] = (int *)malloc(sizeof(int)*col);
    }

    return matrix;   // 동적할당한 배열 반환
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf(" %d ", matrix[i][j]);     // 초기화시킨 배열 출력
        }
        printf("\n");
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
        if(row <= 0 || col <= 0)  // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    for(int i = 0; i < row; i++) {
        free(matrix[row]);   // 배열 메모리 해제
    } 
    free(matrix);   // 동적할당 시에 배열의 행만큼 malloc 을 호출하고 그 이전에 한 번 더 호출했었으므로 row+1만틈 free 해준다
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
        if(row <= 0 || col <= 0)  // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
    
    for(int i = 0; i < row; i++) 
    {
        for(int j = 0; j < col; j++)
        {
            matrix[i][j] = rand()%20;   // 0~19 까지의 난수로 배열 초기화
        }
    }

    for(int i = 0; i <row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(matrix[i][j] == NULL)    // 제대로 초기화 되었는지 검사
            return -1;
        }
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
        if(row <= 0 || col <= 0)   // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix_sum = (int **)malloc(sizeof(int)*row);   // 덧셈 결과를 저장할 배열 동적할당
    
    for(int i = 0; i < row; i++) {
        matrix_sum[i] = (int*)malloc(sizeof(int)*col);
    }

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }

    print_matrix(matrix_sum, row, col);   // 결과 출력
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{ 
        if(row <= 0 || col <= 0)  // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int **matrix_sub = (int **)malloc(sizeof(int)*row);  // 뺄셈 결과를 저장할 배열 동적할당
    
    for(int i = 0; i < row; i++) {
        matrix_sub[i] = (int*)malloc(sizeof(int)*col);
    }

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];  
        }
    }

    print_matrix(matrix_sub, row, col);   // 결과 출력
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
        if(row <= 0 || col <= 0)  // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            matrix_t[i][j] = matrix[j][i];   // matrix를 전치한 배열을matrix_t에 대입
        }
    }

        for(int i = 0; i <row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(matrix[i][j] == NULL)  // 전치가 잘 이루어졌는지 검사
            return -1;
        }
    }
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
        if(row <= 0 || col <= 0)  // 잘못된 인자 전달 검사
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int sum = 0;  // 곱셈 중간 값을 저장할 변수 선언 및 초기화
    int **matrix_axt = (int **)malloc(sizeof(int)*row);   // 곱셈 결과를 저장할 배열 동적할당
    
    for(int i = 0; i < row; i++) {
        matrix_axt[i] = (int*)malloc(sizeof(int)*row);
    }

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < row; j++)   // matrix_t가 전치된 행렬이기 때문에 row 만큼 반복
        {
            for(int k = 0; k < col; k++)
            {
                sum += (matrix_a[i][k] * matrix_t[k][j]);  // 곱셈 결과를 sum에 누적
            }
            matrix_axt[i][j] = sum;   // matrix_axt에 sum 의 값 대입
            sum = 0;  // 다음 연산을 위해 sum 초기화
        }
    }
    print_matrix(matrix_axt, row, row);  // 결과 출력
}