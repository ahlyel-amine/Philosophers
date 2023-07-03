#include <stdio.h>


void print_shape(int num1, int num2) 
{
    int idx1, idx2;
    for (idx1 = 0; idx1 < num1; idx1++)
    {
        for (idx2 = 0; idx2 < num2; idx2++)
        {
            printf("#");
        }
        printf("\n");
    }
}


int main(void)
{
    // print_shape(4, 3);
    int c = (4 << 8) | 0b100;
    if (c & 0b100)
        printf("%d\n", c >> 8);
    return (0);
}