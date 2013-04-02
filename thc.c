#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "thc.h"
#define PRIVATE static
#define PUBLIC

enum {
    THC_MAX_TESTS = 1024
};

PRIVATE struct timeval start, stop;
PRIVATE double time_elapsed = 0;

PRIVATE const char *RED = "\033[01;31m";
PRIVATE const char *GREEN = "\033[01;32m";
PRIVATE const char *STOPCOLOR = "\033[m";
PRIVATE char verbose_tests = 0;

PRIVATE long ntests = 0;
PRIVATE long nfailures = 0;
PRIVATE long nsegfaults = 0;
PRIVATE void (*tests[THC_MAX_TESTS])(void);

PRIVATE void thc_add_success(const char *expr, const char *func, const char *filename, const int fileno);
PRIVATE void thc_add_failure(const char *expr, const char *func, const char *filename, const int fileno);
PRIVATE void thc_report_tests(void);

PRIVATE void thc_calc_time(struct timeval start, struct timeval stop, double *time_elapsed){
    *time_elapsed = stop.tv_sec - start.tv_sec + (stop.tv_usec - start.tv_usec)/1000000.0;
}


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
    gettimeofday(&stop, NULL);
    thc_calc_time(start, stop, &time_elapsed);
    printf("\n%sRun %ld test%s with %ld failure%s and %ld segfault%s in %.4fs\n %s\n",
            color, ntests, (ntests == 1 ? "" : "s"),
            nfailures, (nfailures == 1 ? "" : "s"),
            nsegfaults, (nsegfaults == 1 ? "" : "s"),
            time_elapsed, STOPCOLOR);
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

PUBLIC int thc_run(int options) {
    gettimeofday(&start, NULL);

    int i;
    int child_status;
    int no_fork;
    pid_t pid;
    if ((options & THC_QUIET) && (options & THC_VERBOSE)) {
        printf("Invalid Test Option\n");
        printf("You can't mix THC_QUIET and THC_VERBOSE\n");
        exit(-1);
    }

    verbose_tests = options & THC_VERBOSE;
    no_fork = options & THC_NOFORK;

    for (i = 0 ; i < ntests ; i++) {
        if (no_fork) {
            tests[i]();
        } else {
            pid = fork();
            if (pid == 0) {
                nfailures = 0;
                tests[i]();
                exit(nfailures);
            } else {
                wait(&child_status);
                if (child_status > 0) {
                    if (WIFEXITED(child_status)) {
                        nfailures++;
                    } else{
                        nsegfaults++;
                        printf("\n%sSEVERAL TEST ERROR\n%s", (char*)RED,
                                                             (char*)STOPCOLOR);
                    }
                }
            }
        }
    }
    thc_report_tests();
    return nfailures;
}