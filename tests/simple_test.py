#!/usr/bin/python

import os
import sys
import subprocess
import difflib

def test(target, args, head=None, expect_fail=False):
    test_name = os.path.basename(sys.argv[0])[:-3]
    example_dir = os.path.normpath(
        os.path.join(os.path.dirname(sys.argv[0]),
                     '..',
                     'examples'))
    test_bin = os.path.join(example_dir, target)
    
    test = subprocess.Popen([test_bin] + args,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT)
    (stdout, _) = test.communicate()
    got = stdout.split('\n')[:head]
    
    with open(test_name + '.out') as inp:
        want = inp.read().split('\n')

    if got == want:
        print 'OK'
        sys.exit(0)
        
    diff = difflib.unified_diff(got, want, fromfile='got', tofile='want')
    result = '\n'.join(diff)
    print 'FAIL'
    print result
    sys.exit(1)
