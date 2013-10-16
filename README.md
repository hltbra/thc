THC
===

[![Build Status](https://travis-ci.org/hltbra/thc.png)](https://travis-ci.org/hltbra/thc)
[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/hltbra/thc/trend.png)](https://bitdeli.com/free "Bitdeli Badge")
<img src="https://instanc.es/bin/hltbra/thc.png" width="95" height="18" />

THC (Testing High C) is a set of macros and small functions aimed
to help C developers write their tests.


Usage
-----

Create a C test file (let's say test.c):

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

See it running:

	$ ./test.out
	2 + 2 == 4 ... OK [ensure_not_high, test.c:4]

	Run 1 test with 0 failures


Samples
-------

There are some samples at [samples/](https://github.com/hltbra/thc/tree/master/samples).



Colors
------

I CAN HAZ COLORS!

![usage](http://cloud.github.com/downloads/hltbra/thc/thc_usage.png)



