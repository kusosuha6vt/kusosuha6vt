#include <iostream>
#include <cmath>
#include <algorithm>
// #include <complex>

using namespace std;
typedef long double ld;
typedef long long ll;
// typedef complex<ld> cmx;

struct cmx {
	ld r, i;
	cmx(ld r = 0, ld i = 0) : r(r), i(i) {}
};

cmx operator * (const cmx &a, const cmx &b) {
	return {a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}

cmx operator + (const cmx &a, const cmx &b) {
	return {a.r + b.r, a.i + b.i};
}

cmx operator - (const cmx &a, const cmx &b) {
	return {a.r - b.r, a.i - b.i};
}

cmx get_root(int n) {
	return {cos(2L * M_PI / n), sin(2L * M_PI / n)};
}

cmx conjugate(const cmx &a) {
	return {a.r, -a.i};
}

const int LOG = 20;
const int N = 1 << LOG;
void fft(cmx *a, int n, int s, cmx *res, cmx w) {
	if (n == 1) {
		res[0] = a[0];
		return;
	}
	cmx w2 = w * w;
	fft(a,     n >> 1, s << 1, res,            w2);
	fft(a + s, n >> 1, s << 1, res + (n >> 1), w2);
	cmx x = 1;
	for (int i = 0; i < (n >> 1); ++i) {
		cmx b = res[i];
		cmx c = res[i + (n >> 1)];
		cmx tmp = x * c;
		res[i           ] = b + tmp;
		res[i + (n >> 1)] = b - tmp;
		x = x * w;
	}
}

cmx a[N], a2[N], fa[N], fa2[N];

int main() {
	string s;
	cin >> s;
	int n = s.size();
	for (int i = 0; i < s.size(); ++i) {
		a[i] = s[i] - '0';
		a2[n * 2 - 1 - i * 2] = a[i];
	}
	// ans = sum(a * a * a2) / 2
	cmx w = get_root(N);
	cmx wr = conjugate(w);
	fft(a, N, 1, fa, w);
	for (int i = 0; i < N; ++i) {
		fa[i] = fa[i] * fa[i];
	}
	fft(fa, N, 1, a, wr);
	ll sum = 0;
	for (int i = 0; i < 2 * n; i += 2) {
		ll cur = ll(a[i].r / N + 0.5);
		if (s[i >> 1] - '0') {
			sum += cur - 1;
		}
	}
	cout << sum / 2;
	return 0;
}
