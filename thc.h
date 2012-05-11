#ifndef _THC_INCLUDE
#define _THC_INCLUDE

#define ENSURE(expr) thc_run_check((expr), #expr, __func__, __FILE__, __LINE__)

enum {
	THC_QUIET = 0,
	THC_VERBOSE = 1
};

void thc_run_check(const int result, const char *expr, const char *func, const char *fname, const int fline);
void thc_addtest(void (*f)(void));
int thc_run(int verbose);

#endif
