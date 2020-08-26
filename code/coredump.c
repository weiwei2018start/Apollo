#include <stdio.h>

int square(int a, int b) {
    int ret = 1;
    int *p = NULL;//new int();
    *p = 666;
    return ret; 
}

int doCalc(int number1, int number2) {
    int ret = square(number1, number2);
    return ret;
}

int main() {
    int param1 = 1;
    int param2 = 2;
    int ret = doCalc(param1, param2);
    printf ("ret is %d\n", ret);
    
    return 0;
}
