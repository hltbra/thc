#include <stdio.h>
#include "thc.h"
#define PRIVATE static
#define PUBLIC

enum {
    THC_MAX_TESTS = 1024
};

PRIVATE const char *RED = "\033[01;31m";
PRIVATE const char *GREEN = "\033[01;32m";
PRIVATE const char *STOPCOLOR = "\033[m";
PRIVATE char verbose_tests = 0;

PRIVATE long ntests = 0;
PRIVATE long nfailures = 0;
PRIVATE void (*tests[THC_MAX_TESTS])(void);

PRIVATE void thc_add_success(const char *expr, const char *func, const char *filename, const int fileno);
PRIVATE void thc_add_failure(const char *expr, const char *func, const char *filename, const int fileno);
PRIVATE void thc_report_tests(void);


PRIVATE void thc_add_success(const char *expr, const char *func, const char *filename, const int fileno) {
    if (verbose_tests) {
        printf("%s%s ... OK %s[%s, %s:%d]\n", GREEN, expr, STOPCOLOR, func, filename, fileno);
    } else {
        printf(".");
    }
}

PRIVATE void thc_add_failure(const char *expr, const char *func, const char *filename, const int fileno) {
    if (verbose_tests) {
        printf("%s%s ... FAIL %s[%s, %s:%d]\n", RED, expr, STOPCOLOR, func, filename, fileno);
    } else {
        printf("F");
    }
    nfailures++;
}

PRIVATE void thc_report_tests(void) {
    char *color = (char *)GREEN;
    if (nfailures) {
        color = (char *)RED;
    }
    printf("\n%sRun %ld test%s with %ld failure%s%s\n", color, ntests, (ntests == 1 ? "" : "s"), nfailures, (nfailures == 1 ? "" : "s"), STOPCOLOR);
}

PUBLIC void thc_run_check(const int result, const char *expr, const char *func, const char *fname, const int fline) {
    if (result) {
        thc_add_success(expr, func, fname, fline);
    } else {
        thc_add_failure(expr, func, fname, fline);
    }
}

PUBLIC void thc_addtest(void (*f)(void)) {
    tests[ntests++] = f;
}

PUBLIC int thc_run(int verbose) {
    int i;
    verbose_tests = verbose;
    for (i = 0 ; i < ntests ; i++) {
        tests[i]();
    }
    thc_report_tests();
    return nfailures;
}

