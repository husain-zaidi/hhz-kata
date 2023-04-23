#include <pthread.h>
#include <stdio.h>

int m, n, p, a[50][50], b[50][50], c[50][50];

void display(int matrixNo)
{
    int i, j;
    if(matrixNo==1)
    {
        printf("\nFirst Matrix: ");
        for(i=0; i<m; i++)
        {
            printf("\n|\t");
            for(j=0; j<n; j++)
                printf("%d\t|\t", a[i][j]);
        }
    }
    else if(matrixNo==2)
    {
        printf("\nSecond Matrix: ");
        for(i=0; i<n; i++)
        {
            printf("\n|\t");
            for(j=0; j<p; j++)
                printf("%d\t|\t", b[i][j]);
        }
    }
    else if(matrixNo==3)
    {
        printf("\nThird Matrix: ");
        for(i=0; i<m; i++)
        {
            printf("\n|\t");
            for(j=0; j<p; j++)
                printf("%d\t|\t", c[i][j]);
        }
    }
}

void addColumn(int row, int column)
{
    c[row][column]=0;
    for(int i=0; i<n; i++)
    {
        printf("\nMultiplying value %d at [%d][%d] of the first matrix and value %d at [%d][%d] of the second matrix.", a[row][i], row, i, b[i][column], i, column);
        c[row][column] += a[row][i]*b[i][column];
    }
    printf("\nPlacing value %d at [%d][%d] of the resultant matrix.", c[row][column], row, column);
    display(3);
}

void* MatMultiplication(void* num)
{
    int* val=num;
    for (int i=0; i<p; i++)
        addColumn(*val, i);
}

int main()
{

    int i, j;
    printf("\nEnter the number of rows and columns of the first matrix: ");
    scanf("%d%d", &m, &n);
    pthread_t thread_id[m];
    printf("\nEnter the number of columns of the second matrix: ");
    scanf("%d", &p);
    printf("\nEnter the values of the first matrix: ");
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            scanf("%d", &a[i][j]);
    printf("\nEnter the values of the second matrix: ");
    for(i=0; i<n; i++)
        for(j=0; j<p; j++)
            scanf("%d", &b[i][j]);
    display(1);
    display(2);
    for(i=0; i<m; i++) {
        pthread_create(&thread_id[i], NULL, MatMultiplication, &i);
    }

    for(i=0; i<m; i++)
        pthread_join(thread_id[i], NULL);
}
