#include <pthread.h>
#include <stdio.h>

struct question
{
    int a;
    int b;
};

void *add(void *ptr)
{
    struct question *q = (struct question *)ptr;
    printf("%d + %d = %d\n", q->a, q->b, q->a + q->b);
}

void *sub(void *ptr)
{
    struct question *q = (struct question *)ptr;
    printf("%d - %d = %d\n", q->a, q->b, q->a - q->b);
}

void *mul(void *ptr)
{
    struct question *q = (struct question *)ptr;
    printf("%d * %d = %d\n", q->a, q->b, q->a * q->b);
}

void *div(void *ptr)
{
    struct question *q = (struct question *)ptr;
    if (q->b == 0)
    {
        printf("Cannot divide by zero!\n");
        return NULL;
    }
    else if (q->a % q->b != 0)
    {
        printf("%d / %d = %d\n", q->a, q->b, q->a / q->b);
        printf("Remainder: %d\n", q->a % q->b);
        return NULL;
    }
    else if (q->a % q->b == 0)
    {
        printf("%d / %d = %d\n", q->a, q->b, q->a / q->b);
        return NULL;
    }
}

int main()
{
    int n = 2;
    struct question q[n];
    pthread_t thread[n];
    for (int i = 0; i < n; i++)
    {
        char c;
        scanf("%d %c %d", &q[i].a, &c, &q[i].b);
        if (c == '+')
        {
            pthread_create(&thread[i], NULL, add, (void *)&q[i]);
        }
        else if (c == '-')
        {
            pthread_create(&thread[i], NULL, sub, (void *)&q[i]);
        }
        else if (c == '*')
        {
            pthread_create(&thread[i], NULL, mul, (void *)&q[i]);
        }
        else if (c == '/')
        {
            pthread_create(&thread[i], NULL, div, (void *)&q[i]);
        }
        else
        {
            printf("Invalid operator!\n");
        }
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(thread[i], NULL);
    }
    return 0;
}