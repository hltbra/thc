#include <assert.h>
#include <stdio.h>
#define ENSURE(expr) run_check((expr), #expr, __func__, __FILE__, __LINE__)

const char *RED = "\033[01;31m";
const char *GREEN = "\033[01;32m";
const char *GREY ="\033[01;33m";
const char *STOPCOLOR = "\033[m";

static long ntests = 0;
static long nfailures = 0;
static char verbose_tests = 0;
static void (*tests[1024])(void);


void add_success(const char *expr, const char *func, const char *filename, const int fileno) {
    if (verbose_tests) {
        printf("%s%s ... OK %s[%s, %s:%d]\n", GREEN, expr, STOPCOLOR, func, filename, fileno);
    } else {
        printf(".");
    }
}
void add_failure(const char *expr, const char *func, const char *filename, const int fileno) {
    if (verbose_tests) {
        printf("%s%s ... FAIL %s[%s, %s:%d]\n", RED, expr, STOPCOLOR, func, filename, fileno);
    } else {
        printf("F");
    }
    nfailures++;
}
void run_check(const int result, const char *expr, const char *func, const char *fname, const int fline) {
    if (result) {
        add_success(expr, func, fname, fline);
    }
    else {
        add_failure(expr, func, fname, fline);
    }
}
void addtest(void (*f)(void)) {
    tests[ntests++] = f;
}

void run_all_tests(void) {
    int i;
    for (i = 0 ; i < ntests ; i++) {
        tests[i]();
    }
}

void report_tests(void) {
    printf("\nRun %ld test%s with %ld failure%s\n", ntests, (ntests == 1 ? "" : "s"), nfailures, (nfailures == 1 ? "" : "s"));
}

void bar(void) {
    ENSURE(1 == 2);
}

int main(void) {
    verbose_tests = 0;
    addtest(bar);
    run_all_tests();
    report_tests();
}
