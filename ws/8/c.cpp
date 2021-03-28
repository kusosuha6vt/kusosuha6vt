#include "message.h"
// #include "crates.h"
#include "crates1.h"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll l, r;
ll non, n, len, sum_all, ans;

void receive() {
	Receive(0);
	l = GetLL(0);
	r = GetLL(0);
	n = GetNumStacks();
	len = n / (NumberOfNodes() - 1);
}

void send() {
	ll i = 0;
	for (int j = 0; j < non; ++j) {
		PutLL(j + 1, min(i, n));
		PutLL(j + 1, min(n, i + len));
		Send(j + 1);
		i += len;
	}
}

void send_empty() {
	for (int j = 0; j < non; ++j) {
		Send(j + 1);
	}
}

ll real(ll l0, ll r0) {
	return (r0 - l0) * (sum_all / n) + (min(r0, sum_all % n) - l0);
}

void calc_sum1() {
	Receive(0);
	ll res = 0;
	for (ll i = l; i < r; ++i) {
		res += GetStackHeight(i);
	}
	PutLL(0, res);
	Send(0);
}

int sg(ll x) {
	return (x < 0 ? -1 : (x == 0 ? 0 : 1));
}

const ll mod = 1e9 + 7;

void calc_ans1() {
	Receive(0);
	ll extraL = GetLL(0);
	ll res = 0;
	for (ll i = l; i < r; ++i) {
		ll x = GetStackHeight(i);
		res = (res + abs(extraL)) % mod;
		if (sg(x) * sg(extraL) <= 0) {
			ll g = min(abs(x), abs(extraL));
			extraL += (extraL < 0 ? g : -g);
			x += (x < 0 ? g : -g);
		} else {
			extraL += x; 
		}
	}
	PutLL(0, res);
	Send(0);
}

int main() {
	if (MyNodeId() == 0) {
		n = GetNumStacks();
		non = NumberOfNodes() - 1;
		assert(non > 0);
		len = (n + non - 1) / non;
		send();
		
		send_empty();
		ll pref = 0;
		ll i = 0;
		for (int j = 0; j < non; ++j) {
			Receive(j + 1);
			PutLL(j + 1, pref - real(0, i));
			pref += GetLL(j + 1);
			i += len;
			Send(j + 1);
		}
		ans = 0;
		for (int j = 0; j < non; ++j) {
			Receive(j + 1);
			ans = (ans + GetLL(j + 1)) % mod;
		}

		cout << ans;
	} else {
		receive();
		calc_sum1();
		calc_ans1();
	}
	return 0;
}
