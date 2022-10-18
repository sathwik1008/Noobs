#include <stdio.h>
#include <stdbool.h>

bool Stack(int pushed[], int popped[])
{
    int i = 0, j = 0;
    int stack[100];
    int top = -1;
    while (i < 5)
    {
        if (pushed[i] == popped[j])
        {
            i++;
            j++;
        }
        else
        {
            stack[++top] = pushed[i++];
        }
    }

    while (j < 5)
    {
        if (stack[top] != popped[j])
        {
            return false;
            top--;
            j++;
        }
        return true;
    }
    return 0;
};

int main()
{

    // test case 1
    int pushed[] = {5, 10, 15, 20, 25};
    int popped[] = {20, 25, 15, 10, 5};

    // test case 2
    // int pushed[] = {5, 10, 15, 20, 25};
    // int popped[] = {20, 15, 25, 5, 10};

    printf("%d\n", Stack(pushed, popped));
}
