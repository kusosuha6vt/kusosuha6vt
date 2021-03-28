#include <bits/stdc++.h>

using namespace std;
typedef unsigned int ui;
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

const int N = 50000;
vector<int> g[N];
int h[N];
int d[N];
ui ans[N];
const int MEM = N * 100;
ui mem[MEM];
ui *ptr = mem;

ui *get_mem(int k) {
	ptr += k;
	assert(ptr <= mem + MEM);
	return ptr - k;
}

struct MyVector {
	int sz = 0;
	int cap = 0;
	ui *ptr = 0;
	ui &operator[](int i) const {
		return ptr[i];
	}

	ui &get_rev(int i) const {
		return ptr[sz - i - 1];
	}

	void push_back(ui val) {
		if (sz) {
			if (cap > sz) {
				ptr[sz++] = val;
			} else {
				cap *= 3;
				ui *new_ptr = get_mem(cap);
				memcpy(new_ptr, ptr, sizeof(ptr[0]) * sz);
				ptr = new_ptr;
				new_ptr = 0;
				ptr[sz++] = val;
			}
		} else {
			ptr = get_mem(1);
			cap = 1;
			ptr[sz++] = val;
		}
	}

	void reserve(int val) {
		if (cap < val) {
			cap = val;
			ui *new_ptr = get_mem(cap);
			memcpy(new_ptr, ptr, sizeof(ptr[0]) * sz);
			ptr = new_ptr;
			new_ptr = 0;
			ptr[sz++] = val;
		}
	}
};

ostream &operator << (ostream &out, MyVector mv) {
	cout << "{";
	cout << mv.sz << ", ";
	cout << "{";
	for (int i = 0; i < mv.sz; ++i) {
		cout << mv.get_rev(i) << ' ';
	}
	cout << "}}";
	return out;
}

const int LOG = 18, M = 1 << LOG;
cmx a[M], b[M], fa[M], fb[M];
ui res[M];
void merge_h(MyVector fs, MyVector sc) {
	// memset(a, 0, sizeof(a));
	// memset(b, 0, sizeof(b));
	// memset(fa, 0, sizeof(fa));
	// memset(fb, 0, sizeof(fb));
	// cout << "multiply:\n";
	// cout << fs << endl << sc << endl;
	int h = 32 - __builtin_clz(fs.sz + sc.sz);
	memset(a, 0, sizeof(a[0]) * (1 << h));
	memset(b, 0, sizeof(b[0]) * (1 << h));
	for (int i = 0; i < fs.sz; ++i) {
		a[i] = {fs.get_rev(i), 0};
	}
	for (int j = 0; j < sc.sz; ++j) {
		b[j] = {sc.get_rev(j), 0};
	}
	fft(a, (1 << h), 1, fa, get_root(1 << h));
	fft(b, (1 << h), 1, fb, get_root(1 << h));
	for (int i = 0; i < (1 << h); ++i) {
		fa[i] = fa[i] * fb[i];
	}
	fft(fa, (1 << h), 1, a, conjugate(get_root(1 << h)));
	// cout << "res = ";
	for (int i = 0; i < fs.sz + sc.sz - 1; ++i) {
		res[i] = ll(a[i].r / (1 << h) + 0.5);
		// cout << res[i] << ' ';
	}
	// cout << endl;
}

MyVector cnt[N];
ui scan[N];

void dfs(int v, int p) {
	// for (int i = 1; i <= d[v]; ++i) {
		// cout << "from " << v << " of len " << i << endl;
		// ans[i]++;
	scan[d[v]]++;
	// }
	for (int i = 0; i < g[v].size(); ++i) {
		if (g[v][i] == p) {
			swap(g[v][i], g[v].back());
			g[v].pop_back();
			break;
		}
	}
	h[v] = 1;
	if (g[v].empty()) {
		cnt[v].push_back(1);
		return;
	}
	for (int u : g[v]) {
		d[u] = d[v] + 1;
		dfs(u, v);
		h[v] = max(h[v], h[u] + 1);
	}
	for (int &u : g[v]) {
		if (h[u] > h[g[v][0]]) {
			swap(u, g[v][0]);
		}
	}
	cnt[v] = cnt[g[v][0]];
	// cnt[v].push_back(1);
	// cout << "lca " << v << endl;
	for (int u : g[v]) {
		if (u == g[v][0])
			continue;
		// for (int i = 0; i < cnt[v].sz; ++i) {
		// 	for (int j = 0; j < cnt[u].sz; ++j) {
		// 		ans[i + j + 2] += cnt[v].get_rev(i) * cnt[u].get_rev(j);
		// 		cout << cnt[v].get_rev(i) * cnt[u].get_rev(j) << " of len " << i + j + 2 << endl;
		// 	}
		// }
		merge_h(cnt[v], cnt[u]);
		for (int i = 0; i < cnt[u].sz + cnt[v].sz - 1; i++) {
			ans[i + 2] += res[i];
		}
		for (int i = 0; i < cnt[u].sz; ++i) {
			cnt[v].get_rev(i) += cnt[u].get_rev(i);
		}
	}
	cnt[v].push_back(1);
	// cout << "--" << v << endl;
	// for (int i = 0; i < h[v]; ++i) {
	// 	cout << cnt[v][i] << ' ';
	// }
	// cout << endl;
}

mt19937 gen(101010);
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 0; i < n; ++i) {
		shuffle(g[i].begin(), g[i].end(), gen);
	}
	int root = uniform_int_distribution<int>(0, n - 1)(gen);
	// cout << root << '\n';
	dfs(root, -1);
	for (int i = n - 1; i >= 2; --i) {
		scan[i - 1] += scan[i];
	}
	for (int i = 1; i < n; ++i) {
		cout << ans[i] + scan[i] << '\n';
	}
	return 0;
}
