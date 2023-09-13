// Write a multithreaded program that performs the sum of even numbers and odd numbers in an input array.
//  Create a separate thread to perform the sum of even numbers and odd numbers. The parent thread has to wait
// until both the threads are done.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct threadAttributes
{
    int size;
    int *array;
} Attributes;

void *even(void *args)
{
    Attributes *att = (Attributes *)args;
    int i;
    int n = att->size;
    int esum = 0;

    for (i = 0; i < n; i++)
    {
        if (att->array[i] % 2 == 0)
        {
            esum = esum + att->array[i];
        }
    }

    return (void *)(intptr_t)esum;
}
void *odd(void *args)
{
    Attributes *att = (Attributes *)args;
    int i;
    int n = att->size;
    int osum = 0;

    for (i = 0; i < n; i++)
    {
        if (att->array[i] % 2 != 0)
        {
            osum = osum + att->array[i];
        }
    }

    return (void *)(intptr_t)osum;
}
int main()
{
    pthread_t even_thread, odd_thread; // two different threads
    int n;
    printf("Enter the size of the array");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Attributes even_attr, odd_attr;

    even_attr.size = n;
    even_attr.array = arr;

    odd_attr.size = n;
    odd_attr.array = arr;

    pthread_create(&even_thread, NULL, even, (void *)&even_attr);
    pthread_create(&odd_thread, NULL, odd, (void *)&odd_attr);

    int esum, osum;
    pthread_join(even_thread, (void **)&esum);
    pthread_join(odd_thread, (void **)&osum);

    printf("Even Sum %d\n", esum);
    printf("Odd Sum %d\n", osum);
}
