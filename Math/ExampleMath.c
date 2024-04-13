#include "ExampleMath.h"
#include <math.h>

double root(double x)
{
    double n = x;
    double epsilon = 0.000001; // The desired precision
    while ((n - x / n) > epsilon)
    {
        n = (n + x / n) / 2;
    }
    return n;
}
double square(double x)
{
    return x * x;
}
double sin(double x)
{
    return sin(x);
}
