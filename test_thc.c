#include <stdlib.h>
#include "thc.h"

void foo(void) {
    ENSURE(1 == 1);
}

void bar(void) {
    ENSURE(1 == 2);
}

void segfault(void) {
    int *a;
    free(a);
}


int main(void) {
    thc_addtest(foo);
    thc_addtest(bar);
    thc_addtest(segfault);
    return thc_run(1);
}
