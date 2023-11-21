#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int procNum;
int resourceNum = 3;

void display(int m, int n, int arr[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int checkAvailability(int need[], int resourceAvailable[])
{
    int flag = 1;
    for (int i = 0; i < resourceNum; i++)
    {
        if (!(need[i] <= resourceAvailable[i]))
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

void updatedAvailableResource(int available[], int allocated[])
{
    for (int i = 0; i < resourceNum; i++)
    {
        available[i] += allocated[i];
    }
}

int checkSafeState(int resourceAvail[], int resources[], int satisfied[])
{
    for (int i = 0; i < resourceNum; i++)
    {
        if (!(resourceAvail[i] == resources[i] && satisfied[i]))
        {
            return 0;
        }
        return 1;
    }
}

void main()
{
    printf("Enter number of processes");
    scanf("%d", &procNum);

    int processMax[procNum][resourceNum];
    int processAlloc[procNum][resourceNum];
    int processNeed[procNum][resourceNum];

    int resourceAvail[resourceNum];
    int resources[resourceNum];
    int satisfied[procNum];

    for (int i = 0; i < procNum; i++)
    {
        satisfied[i] = 0;
    }

    resources[0] = 10;
    resources[1] = 5;
    resources[2] = 7;

    // Maximum Resources
    for (int i = 0; i < procNum; i++)
    {
        printf("Maximum resources for process %d\n", i + 1);
        for (int j = 0; j < resourceNum; j++)
        {
            printf("Resource %d \n", j + 1);
            scanf("%d", &processMax[i][j]);
        }
        printf("\n");
    }

    // Resource allocated
    for (int i = 0; i < procNum; i++)
    {
        printf("Resources allocated for process %d\n", i + 1);
        for (int j = 0; j < resourceNum; j++)
        {
            printf("Resource %d \n", j + 1);
            scanf("%d", &processAlloc[i][j]);
        }
        printf("\n");
    }

    // Remaining need
    for (int i = 0; i < procNum; i++)
    {
        for (int j = 0; j < resourceNum; j++)
        {
            processNeed[i][j] = processMax[i][j] - processAlloc[i][j];
        }
    }

    // Available Resources       ------HERE CHANGE IN FOR LOOP
    for (int i = 0; i < resourceNum; i++)
    {
        int sum = 0;
        for (int j = 0; j < procNum; j++)
        {
            sum += processAlloc[j][i];
        }
        resourceAvail[i] = resources[i] - sum;
    }

    printf("Available");
    for (int i = 0; i < resourceNum; i++)
    {
        printf("%d ", resourceAvail[i]);
    }

    printf("\n\nNEED : \n");
    display(procNum, resourceNum, processNeed);

    // SAFE STATE
    for (int i = 0; i < procNum; i = (i + 1) % procNum)
    {
        if (!(satisfied[i]) && checkAvailability(processNeed[i], resourceAvail))
        {
            satisfied[i] = 1;

            updatedAvailableResource(resourceAvail, processAlloc[i]);

            printf("Available %d : ", i + 1);
            for (int j = 0; j < resourceNum; j++)
            {
                printf("%d ", resourceAvail[j]);
            }
            printf("\n");

            if (checkSafeState(resourceAvail, resources, satisfied))
            {
                printf("Safe State\n");
                break;
            }
        }
    }

    if (!checkSafeState(resourceAvail, resources, satisfied))
        printf("Unsafe system\n");
}