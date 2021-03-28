from random import *
import sys
_, i = sys.argv
random.seed(i)
n = randint(1, 5)
print(n)
for i in range(n):
    print(randint(-15, 15), randint(-15, 15), randint(-15, 15))
