// Write a multithreaded program for generating prime numbers from a given starting number to the given ending number.

// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct threadAttributes
// {
//     int start;
//     int end;
// } Attributes;

// void *prime(void *args)
// {
//     Attributes *att = (Attributes *)args;

//     int start = att->start;
//     int end = att->end;

//     int *prim = (int *)malloc(sizeof(int) * n);

//     for (int i = start; i < end; i++)
//     {
//         for(int j = 2; j < i/2; j++)
//         {
//             if(i % j == 0)
//             {
//                 break;
//             }
//         }

//     }

//     return (void *)prim;
// }
// int main()
// {
//     pthread_t thread;
//     int s;
//     printf("Enter the start numer");
//     scanf("%d", &s);
//     int e;
//     printf("Enter the end number");
//     scanf("%d", &e);

//     Attributes attr;

//     attr.start = s;
//     attr.end = e;

//     pthread_create(&thread, 0, &prime, (void *)&attr);
//     int sum;
//     pthread_join(thread, (void **)&sum);

//     printf(" %d", sum);
// }

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct threadAttribute
{
    int start, end;
} Attributes;

int isPrime(int num)
{
    int count = 0;

    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
            count++;
    }

    if (count == 2)
        return 1;
    return 0;
}

void *displayPrime(void *arg)
{
    Attributes *attr = (Attributes *)arg;

    int *result;
    int k = 0;

    for (int i = attr->start; i <= attr->end; i++)
    {
        printf("%d ", i);
        if (isPrime(i))
            *(result + k) = i;
    }

    for (int i = attr->start; i <= attr->end; i++)
    {
        printf("%d ", result[i]);
    }

    // return (void*)result;
}

void main(int argc, char *argv[])
{
    int a, b;
    printf("Enter starting and ending numbers : ");
    scanf("%d%d", &a, &b);

    Attributes attr;
    attr.start = a;
    attr.end = b;

    int *res;

    pthread_t thread;
    pthread_create(&thread, 0, displayPrime, (void *)&attr);

    // pthread_join(thread,(void**)&res);
    pthread_join(thread, 0);

    // for(int i=attr.start;i<=attr.end;i++)
    // {
    // 	printf("%d ",res[i]);
    // }
}