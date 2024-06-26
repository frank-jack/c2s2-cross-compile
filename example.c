// An example program that computes certain mathematical functions
#include "ExampleMath.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) // no arguments were passed
    {
        printf("We working?\n");
        return 0;
    }
    const double inVal = strtod(argv[1], NULL);
    double outVal = inVal;
    if (strcmp(argv[2], "root") == 0)
    {
        outVal = root(inVal);
    }
    else if (strcmp(argv[2], "square") == 0)
    {
        outVal = square(inVal);
    }
    else if (strcmp(argv[2], "sin") == 0)
    {
        outVal = sin(inVal);
    }
    else
    {
        outVal = inVal;
    }
    printf("The %s of %f is %f\n", argv[2], inVal, outVal);

    return 0;
}
