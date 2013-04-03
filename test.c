#include "thc.h"

void ensure_not_high() {
    ENSURE(2 + 2 == 4);
}

int main() {
    thc_addtest(ensure_not_high);
    return thc_run(THC_VERBOSE);
}