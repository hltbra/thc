#include "thc.h"

void foo(void) {
    ENSURE(1 == 1);
}

void bar(void) {
    ENSURE(1 == 2);
}


int main(void) {
    thc_addtest(foo);
    thc_addtest(bar);
    return thc_run(1);
}
