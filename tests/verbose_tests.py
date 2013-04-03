import unittest
from . import THCTestCase

class THCVerboseTestCase(THCTestCase):

    def test_no_tests(self):
        self.assertNoDiff("""\
            #include "thc.h"
            int main() {
                return thc_run(THC_VERBOSE);
            }
            """,
            """Run 0 tests with 0 failures and 0 segfaults""")

    def test_simple_successful_ensure(self):
        self.assertNoDiff("""\
            #include "thc.h"
            void one_should_equal_to_one() {
                ENSURE(1 == 1);
            }
            int main() {
                thc_addtest(one_should_equal_to_one);
                return thc_run(THC_VERBOSE);
            }
            """,
            """\
1 == 1 ... OK [one_should_equal_to_one, FNAME:3]

Run 1 test with 0 failures and 0 segfaults""")

    def test_simple_unsuccessful_ensure(self):
        self.assertNoDiff("""\
            #include "thc.h"
            void one_should_equal_to_two() {
                ENSURE(1 == 2);
            }
            int main() {
                thc_addtest(one_should_equal_to_two);
                return thc_run(THC_VERBOSE);
            }
            """, """\
1 == 2 ... FAIL [one_should_equal_to_two, FNAME:3]

Run 1 test with 1 failure and 0 segfaults""")

    def test_segfault(self):
        self.assertNoDiff("""\
            #include "thc.h"
            #include <stdlib.h>
            void should_segfault() {
                char *p;
                free(p);
            }
            int main() {
                thc_addtest(should_segfault);
                return thc_run(THC_VERBOSE);
            }
            """, """\
THC FOUND A SEGFAULT!!!

Run 1 test with 0 failures and 1 segfault""")


if __name__ == '__main__':
    unittest.main()