import difflib
import os
import re
import tempfile
import subprocess
import unittest

cwd = os.path.dirname(os.path.abspath(__file__))
root_dir = os.path.dirname(cwd)
THC_C = os.path.join(root_dir, "thc.c")


def green(msg):
    return "\033[01;32m" + msg + "\033[m"


def red(msg):
    return "\033[01;31m" + msg + "\033[m"


def remove_colors(msg):
    return (msg.replace("\033[01;31m", "")
               .replace("\033[01;32m", "")
               .replace("\033[m", ""))


def normalize_output(msg, fname):
    result = remove_colors(msg).strip().replace(fname, "FNAME")
    return re.sub(r'\d+\.\d+s$', 'SECONDS', result)


class THCTestCase(unittest.TestCase):

    def assertNoDiff(self, program, expected_output):
        source_fd, source_file = tempfile.mkstemp(suffix='.c')
        try:
            executable = gcc(program, source=source_file)
            try:
                output = run(executable)
                normalized_output = normalize_output(output, fname=source_file)
                diff = difflib.ndiff(
                    normalized_output.splitlines(True),
                    expected_output.splitlines(True))
                assert_msg = self.build_assert_msg(diff)
                self.assertEquals(expected_output, normalized_output, assert_msg)
            finally:
                os.remove(executable)
        finally:
            os.close(source_fd)
            os.remove(source_file)

    def build_assert_msg(self, diff):
        result = []
        for line in diff:
            if line.startswith('-'):
                result.append(red(line))
            elif line.startswith('+'):
                result.append(green(line))
            else:
                result.append(line)
        return '\n' + '\n'.join(result)


def gcc(program, source):
    with open(source, "w") as f:
        f.write(program)
    output_file = source + ".out"
    proc = subprocess.Popen(["gcc", source, THC_C, "-I", root_dir, "-o", output_file])
    stdout, stderr = proc.communicate()
    assert proc.returncode == 0, "gcc failed to compile.\nStdout:\n%s\n=====\nStderr:\n%s" % (stdout, stderr)
    return output_file


def run(executable):
    proc = subprocess.Popen([executable], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate()
    return stdout

