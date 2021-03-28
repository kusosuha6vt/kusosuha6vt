#include "message.h"
// #include "max.h"
#include <max.h>

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
// Количество совпадающих строк на префиксе s[0..i]: s[i-len..i] == s[i1..i1+len]
int main() {
	if (MyNodeId() == 0) {
		ll non = NumberOfNodes();
		ll n = GetN();
		ll mx = -1;
		ll i;
		ll WORK = n / non;
		int j = 1;
		for (i = 0; j < non; i += WORK, j++) {
			PutLL(j, i);
			PutLL(j, WORK);
			Send(j);
		}
		j = 1;
		for (i = 0; j < non; i += WORK, j++) {
			Receive(j);
			mx = max(mx, GetLL(j));
		}
		for (; i < n; i++) {
			mx = max(mx, GetElement(i));
		}
		cout << mx << endl;
		return 0;
	} else {
		Receive(0);
		ll i = GetLL(0);
		ll sz = GetLL(0);
		ll mx = -1;
		for (ll e = i + sz; i < e; ++i) {
			mx = max(mx, GetElement(i));
		}
		PutLL(0, mx);
		Send(0);
	}
	// if (MyNodeId() != 0) {
	// 	return 0;
	// }

	// ll n = GetN();
	// ll mx = -1;
	// for (int i = 0; i < n; ++i) {
	// 	ll a = GetElement(i);
	// 	mx = (mx < a ? a : mx);
	// }
	// cout << mx << endl;
	return 0;
}
