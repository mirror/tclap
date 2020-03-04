#!/usr/bin/python3

import os
import subprocess
import argparse

def build(build_dir, config):
    os.chdir(build_dir)
    cpu_count = os.cpu_count() or 1
    ret = subprocess.run(['cmake', '-DCMAKE_BUILD_TYPE=' + config,
                          '..']).returncode
    return ret or subprocess.run(['cmake', '--build', '.', '--config',
                                  config, '-j', str(cpu_count)])

def run_tests(build_dir, config):
    test_dir = os.path.join(build_dir, 'tests')
    os.chdir(test_dir)
    subprocess.run(['ctest', '-C', config])

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Execute tests (and optionally builds)')
    parser.add_argument('--build', dest='build', action='store_true',
                        help='Build target before testing')
    parser.add_argument('--build_dir', dest='build_dir', action='store',
                        default='build', type=str, metavar='PATH',
                        help='CMake build directory')
    parser.add_argument('--config', dest='config', action='store',
                        default='Debug', type=str,
                        help='CMake build config (Debug, Release, etc)')
    args = parser.parse_args()
    cwd = os.getcwd()
    if args.build:
        build(os.path.normpath(args.build_dir), args.config)

    os.chdir(cwd)
    run_tests(os.path.normpath(args.build_dir), args.config)
