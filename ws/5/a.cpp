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

cmx a[N], fa[N], b[N], fb[N], c[N], fc[N];
ll ic[N];

int main() {
	string sa, sb;
	cin >> sa >> sb;
	int sg = 1;
	if (sa == "0" || sb == "0") {
		cout << "0";
		return 0;
	}
	if (sa[0] == '-') {
		sg *= -1;
		sa = sa.substr(1);
	}
	if (sb[0] == '-') {
		sg *= -1;
		sb = sb.substr(1);
	}
	reverse(sa.begin(), sa.end());
	reverse(sb.begin(), sb.end());
	for (int i = 0; i < sa.size(); ++i) {
		a[i] = sa[i] - '0';
	}
	for (int i = 0; i < sb.size(); ++i) {
		b[i] = sb[i] - '0';
	}
	fft(a, N, 1, fa, get_root(N));
	fft(b, N, 1, fb, get_root(N));
	for (int i = 0; i < N; ++i) {
		fc[i] = fa[i] * fb[i];
	}
	fft(fc, N, 1, c, conjugate(get_root(N)));
	for (int i = 0; i < N; ++i) {
		ic[i] = ll(c[i].r / N + 0.5);
	}
	for (int i = 0; i < N - 1; ++i) {
		ic[i + 1] += ic[i] / 10;
		ic[i] %= 10;
	}
	if (sg < 0) {
		cout << '-';
	}
	bool ok = 0;
	for (int i = N - 1; i >= 0; --i) {
		if (ic[i])
			ok = 1;
		if (ok)
			cout << ic[i];
	}
	return 0;
}
