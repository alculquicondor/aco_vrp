#!/usr/bin/env python3

from random import randint
from sys import argv

n = int(argv[1])
print(n)
print(500, 300, 0)
for _ in range(n - 1):
    print (randint(5, 995), randint(5, 595), randint(1, 10))
m = int(argv[2])
print(m)
for _ in range(m):
    print(randint(10, 60))