
#include <stdio.h>

int main(void)
{
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        j += i;
        printf("%d\n", j);
    }
    return 0;
}