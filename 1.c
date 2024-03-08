#include<stdio.h>

unsigned int sum (unsigned int a)
{
    if (a == 0) return a;
    return (a%10+sum(a/10));
}

int main()
{
    printf("%u",sum(125));
    return 0;
}