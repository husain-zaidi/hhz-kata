#include <stdio.h>

// extern void stats(int[], int, int *, int *);
extern void sort(int [] ,int);

int main(){
    int i, len, lst[50], sum, ave;
    printf("Enter the length of array");
    scanf("%d", &len);
    printf("Please Enter the numbers");
    for(i = 0; i < len; i++)
    {
        scanf("%d", &lst[i]);

    }
    printf("length= %d\n",len);
    printf("TEST");
    for(i = 0; i < len; i++)
    {
        printf("%d\t",lst[i]);
    }
printf("TEST");
    // stats(lst, len, &sum, &ave);
    sort(&lst,len);
    // printf("\nStats:\n");
    // printf("Sum=%d\n",sum);
    // printf("Ave=%d\n",ave);
    printf("After sorting=\n");
     for(i = 0; i < len; i++)
    {
        printf("%d\t",lst[i]);
    }
    return 0;
}