#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

struct Hash {
    static const int HASH_LENGTH = (int) 2e5 + 10;
    static const ull MOD1 = (ull) 1e9 + 7, MOD2 = 998244353ull, p = 29ull;
    static array<ull, HASH_LENGTH> h1, h2;
    static void hfill() {
        h1[0] = h2[0] = 1ull;
        for (int i = 1; i < HASH_LENGTH; ++i) {
            h1[i] = p * h1[i - 1] % MOD1;
            h2[i] = p * h2[i - 1] % MOD2;
        }
    }
    ull val1, val2;
    int len;
    Hash(ull val1 = 0, ull val2 = 0, int len = 0) : val1(val1), val2(val2), len(len) {}
    bool operator == (const Hash& other) const {
        return val1 == other.val1 && val2 == other.val2 && len == other.len;
    }
    void add_back(char c) {
        val1 = (val1 * p + c - 'a' + 1) % MOD1;
        val2 = (val2 * p + c - 'a' + 1) % MOD2;
        ++len;
    }
    Hash operator - (const Hash& other) const {
        return Hash(
                (MOD1 + val1 - other.val1 * h1[len - other.len] % MOD1) % MOD1,
                (MOD2 + val2 - other.val2 * h2[len - other.len] % MOD2) % MOD2,
                len - other.len
                );
    }
};

array<ull, Hash::HASH_LENGTH> Hash::h1, Hash::h2;

struct Prefix_hashes {
    const string& s;
    int n;
    vector<Hash> prefix;
    Prefix_hashes(const string& s) : s(s), n(s.size()) {
        prefix.resize(n + 1);
        Hash hs;
        for (int i = 1; i <= n; ++i) {
            hs.add_back(s[i - 1]);
            prefix[i] = hs;
        }
    }

    Hash substr(int l, int cnt) {
        ++l;
        return prefix[l + cnt - 1] - prefix[l - 1];
    }

};

int main() {

    string s;
    cin >> s;
    int n = s.size();
    string rev_s(s.rbegin(), s.rend());
    Hash::hfill();
    Prefix_hashes ph(s);
    Prefix_hashes rev_ph(rev_s);
    long long ans = 0;

    for (int i = 0; i < n; ++i) {
        int rev_i = n - i - 1;
        int l = 0, r = min(i, rev_i) + 1;
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (ph.substr(i + 1, m) == rev_ph.substr(rev_i + 1, m))
                l = m;
            else
                r = m;
        }
        ans += l + 1;
        if (i + 1 == n) continue;
        l = 0, r = min(i + 1, rev_i) + 1;
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (ph.substr(i + 1, m) == rev_ph.substr(rev_i, m))
                l = m;
            else
                r = m;
        }
        ans += l;
    }

    cout << ans;

    return 0;
}
