#include "math.h"

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

static int _lcm(int a, int b, int i) {
    if (a % b == 0) return a;
    return _lcm(a + i, b, i);
}

int lcm(int a, int b) {
    return _lcm(a, b, a);
}
