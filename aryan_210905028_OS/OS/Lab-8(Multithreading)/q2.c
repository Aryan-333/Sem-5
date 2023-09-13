// Write a multithreaded program that calculates the summation of non-negative
// integers in a separate thread and passes the result to the main thread.

#include <pthread.h>
#include <stdio.h>

typedef struct threadAttributes
{
    int size;
    int *array;
} Attributes;

void *sum(void *args)
{
    Attributes *att = (Attributes *)args;
    int i;
    int n = att->size;
    int sum = 0;

    for (i = 0; i < n; i++)
    {
        if (att->array[i] > 0)
        {
            sum = sum + att->array[i];
        }
    }

    return (void *)sum;
}
int main()
{
    pthread_t thread;
    int n;
    printf("Enter the size of the array");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Attributes attr;

    attr.size = n;
    attr.array = arr;

    pthread_create(&thread, 0, &sum, (void *)&attr);
    int sum;
    pthread_join(thread, (void **)&sum);

    printf(" %d", sum);
}