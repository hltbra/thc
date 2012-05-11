THC
===

THC (Testing High C) is a set of macros and small functions aimed
to help C developers write their tests.

gcc test_thc.c thc.c -o htest.out && ./htest.out


Usage
-----

Create a test.c file:

	#include "thc.h"

	void ensure_not_high() {
	    ENSURE(2 + 2 == 4);
	}

	int main() {
	    thc_addtest(ensure_not_high);
	    return thc_run(THC_VERBOSE);
	}

Compile with:

	$ gcc -o test.out test.c  -Ipath/to/thc/ path/to/thc/thc.c
	$ ./test.out

See it run:

	$ ./test.out
	2 + 2 == 4 ... OK [ensure_not_high, test.c:4]

	Run 1 test with 0 failures

I can haz colors:

![usage](http://cloud.github.com/downloads/hltbra/thc/thc_usage.png)
