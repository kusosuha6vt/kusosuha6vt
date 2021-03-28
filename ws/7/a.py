from sympy.core.cache import cacheit
from sympy import binomial

@cacheit
def b(n, k, j):
	return 1 if j==n else sum([b(n - j, k, i)*sum([binomial(i, m)*binomial(j - 1, i - 1 - m) for m in range(max(0, i - j), min(k, i - 1) + 1)]) for i in range(1, min(j + k, n - j) + 1)])

@cacheit
def A(n, k):
	if n==0:
		return 1
	m=min(n, k)
	return sum([b(n, m , j) for j in range(1, m + 1)])


print([A(n, d - n) for n in range(d + 1)])
