#include <stdio.h>

void star()
{
    printf("\xE2\xAD\x90 ");
}

void marker()
{
    printf("\033[1;31m");
}

void reset()
{
    printf("\033[0m");
}

void notick()
{
    printf("\xE2\x9D\x8C");
}

void tick()
{
    printf("\xE2\x9C\x85 ");
}

void exclamation()
{
    printf("\xE2\x9D\x97 ");
}

void placeholder()
{
    printf(" - ");
}

void bold()
{
    printf("\033[1m\033[37m");
}