#include <bits/stdc++.h>

using namespace std;

const int N = 1 + 13 * 50;
const int A = 26;
int to[N][A];
int tp[N];
int sz = 1;
int lk[N];
int id[N];
int pt[13];
typedef unsigned int ui;
ui msk[N];

int add_string(const string &s) {
	int v = 0;
	for (char c : s) {
		if (to[v][c - 'A'] == 0) {
			to[v][c - 'A'] = sz++;
			while (sz >= N)
				{}
		}
		v = to[v][c - 'A'];
	}
	return v;
}

int q[N];
void bfs() {
	int l = 0, r = 1;
	q[0] = 0;
	while (r - l) {
		int v = q[l++];
		int l = lk[v];
		msk[v] = msk[v] | msk[l];
		for (int i = 0; i < A; ++i) {
			if (to[v][i]) {
				lk[to[v][i]] = (v ? to[l][i] : 0);
				q[r++] = to[v][i];
			} else {
				to[v][i] = to[l][i];
			}
		}
	}
}

int d[13][13];
char c[13][13];
int pr[13][13];
int d_all[13][N];
int p_all[13][N];
char c_all[13][N];
bool used[N];
bool u[13];

Нужно, чтобы a->b->c->d->e->f
msk[a] | msk[b] | msk[c] | msk[d] = 0b11111111
2^13 = 8000
Всего вершин - 12 * 50 + 1 = 601
От вершины до Всех масок - 4_800_000
сохранить можно 67_000_000 of int
2^26 = 6e7


void calc(int S_i) {
	memset(used, 0, sizeof(used));
	memset(u, 0, sizeof(u));
	int S = pt[S_i];
	q[0] = S;
	int l = 0, r = 1;
	d_all[S_i][S] = 0;
	used[S] = 1;
	u[S_i] = 1;
	d[S_i][S_i] = 0;
	while (l < r) {
		int v = q[l++];
		for (int i = 0; i < A; ++i) {
			if (!used[to[v][i]]) {
				used[to[v][i]] = 1;
				q[r++] = to[v][i];
				c_all[S_i][to[v][i]] = i + 'A';
				p_all[S_i][to[v][i]] = v;
				d_all[S_i][to[v][i]] = d_all[S_i][v] + 1;
				for (int j = 0; j < 13; ++j) {
					if (!u[j] && ((msk[j] >> j) & 1)) {
						u[j] = 1;
						d[S_i][j] = d_all[S_i][]
					}
				}
			}
		}
	}
}

char tmp[N];
void output(int a, int b) {
	// pt[a] -> -> -> -> ... -> pt[b]
	int sz_ = 0;
	while (b != a) {
		tmp[sz_++] = c[a][b];
		b = pr[a][b];
	}
	for (int i = sz_ - 1; i >= 0; --i) {
		cout << tmp[i];
	}
}

int p[13];
int main() {
	freopen("in", "r", stdin);
	int n;
	cin >> n;
	set<string> st;
	id[(pt[0] = 0)] = 0;
	msk[0] = 1;
	for (int i = 0; i < n; ++i) {
		string s;
		assert(st.count(s) == 0);
		cin >> s;
		st.insert(s);
		id[(pt[i + 1] = add_string(s))] = i + 1;
		msk[pt[i + 1]] = msk[pt[i + 1]] | (1 << (i + 1));
	}
	bfs();

	for (int i = 0; i < n + 1; ++i) {
		calc(i);
	}

	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			cout << d[i][j] << ' ';
		}
		cout << endl;
	}

	int ans = INT_MAX;
	int pos = -1;
	iota(p, p + n + 1, 0);
	int j = 0;
	do {
		int cur = 0;
		for (int i = 0; i < n; ++i) {
			cur += d[p[i]][p[i + 1]];
		}
		if (ans > cur) {
			ans = cur;
			pos = j;
		}
		j++;
	} while (next_permutation(p + 1, p + n + 1));

	j = 0;
	while (j < pos) {
		next_permutation(p + 1, p + n + 1);
		j++;
	}
	cout << ans << '\n';
	for (int i = 0; i < n; ++i) {
		output(p[i], p[i + 1]);
	}
	return 0;
}
