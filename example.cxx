// An example program that computes certain mathematical functions
#include <iostream>
#include <cstring>
#include "ExampleMath.h"

int main(int argc, char *argv[])
{
    const double inVal = std::stod(argv[1]);
    double outVal = inVal;
    if (strcmp(argv[2], "root") == 0)
    {
        outVal = examplemath::root(inVal);
    }
    else if (strcmp(argv[2], "square") == 0)
    {
        outVal = examplemath::square(inVal);
    }
    else if (strcmp(argv[2], "sin") == 0)
    {
        outVal = examplemath::sin(inVal);
    }
    else
    {
        outVal = inVal;
    }
    std::cout << "The " << argv[2] << " of " << inVal << " is " << outVal
              << std::endl;
    return 0;
}
