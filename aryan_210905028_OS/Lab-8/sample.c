#include <pthread.h>
#include <stdio.h>
void *child_thread(void *param)
{
    int id = (int)param; //to convert the void * parameter param back to an integer value 
    printf("Start thread %i\n", id);
    return (void *)id;
}
int main()
{
    pthread_t thread[10];
    int return_value[10];
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&thread[i], 0, &child_thread, (void *)i); // as 4th parameter expect a pointer to pass integer i to a void * pointer using (void *)i
        // expects a void * argument.
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(thread[i], (void **)&return_value[i]); //it is address to pointer of void 
        // expects a void ** argument ,,  to provide the address where the return value should be stored.
        // To pass the address of the return_value[i] we use &
        printf("End thread %i\n", return_value[i]);
    }
}