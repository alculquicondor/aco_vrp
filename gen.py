#!/usr/bin/env python3

from random import randint
from sys import argv

n = int(argv[1])
print(n)
print(400, 250, 0)
for _ in range(n - 1):
    print (randint(5, 795), randint(5, 495), randint(1, 5))