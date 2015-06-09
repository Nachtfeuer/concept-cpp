#!/usr/bin/python
"""
License
=======
Copyright (c) 2015 Thomas Lehmann

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""
import os
import re
import click

def test_primes(max_number, sieve):
    command = "examples/primes --max-number=%d --sieve=%s" % (max_number, sieve)
    primes = 0
    for line in os.popen(command):
        line = line[0: len(line)-1]
        if line.find("primes found") >= 0:
            match = re.search("(?P<primes>[0-9]+)", line)
            if match:
                primes = int(match.group("primes"))

        if line.find("calculation took") >= 0:
            match = re.search("(?P<duration>[0-9]+\.[0-9]+)", line)
            if match:
                return primes, float(match.group("duration"))
    return None, None

@click.command()
@click.option("--max-number", type=click.INT, default=10000, help="maximum prime number")
@click.option("--tests", type=click.INT, default=10, help="maximum prime number")
@click.option("--sieve", default="default", help="sieve short name, one of: default, optimized")
def main(max_number, tests, sieve):
    durations = []
    primes = 0
    for test in range(tests):
        primes, duration = test_primes(max_number, sieve)
        durations.append(duration)

    print("max. number is %d" % max_number)
    print("primes found: %d" % primes)
    print("%d measurements" % len(durations))
    print("avg duration: %fms" % (sum(durations)/len(durations)))

if __name__ == "__main__":
    main()
