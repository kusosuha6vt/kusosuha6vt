#include "message.h"
#include "pancakes.h"


#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll count_actions(ll i, ll e) {
	ll ans = 0;
	ll cur = GetStackItem(i);
	for (i++; i <= e; ++i) {
		ll nxt = GetStackItem(i);
		if (cur > nxt) {
			ans++;
		}
		cur = nxt;
	}
	// cout << ans << ' ';
	return ans;
}

int main() {
	if (MyNodeId() == 0) {
		ll n = GetStackSize();
		ll non = NumberOfNodes();
		assert(non > 1);
		ll w = n / non;
		ll i = 0;
		for (int j = 1; j < non; ++j) {
			PutLL(j, min(i, n - 1));
			PutLL(j, min(i + w, n - 1));
			Send(j);
			i += w;
		}
		ll ans = 1 + count_actions(min(i, n - 1), n - 1);
		for (int j = 1; j < non; ++j) {
			Receive(j);
			ans += GetLL(j);
		}
		cout << ans;
	} else {
		Receive(0);
		ll s, f;
		s = GetLL(0);
		f = GetLL(0);
		PutLL(0, count_actions(s, f));
		Send(0);
	}
	return 0;
}
