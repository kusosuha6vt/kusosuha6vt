#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	int i = 0;
	string j;
	while (cin >> j) {
		if (!i) {
			i = 1;
			continue;
		}
		cout << j << '\n';
		i = 0;
	}
	return 0;
}
