#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    double a = LONG_MAX  - 100;
	a += 0.12;
    printf("%lu %f %ld\n", sizeof(a), a, LONG_MAX);
    return 0;
}