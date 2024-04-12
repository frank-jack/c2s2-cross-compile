// An example program that computes certain mathematical functions
#include "ExampleMath.h"

int main(int argc, char *argv[])
{
    const double inVal = stod(argv[1]);
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
    printf("The %s of %d is %d", argv[2], inVal, outVal);

    return 0;
}
