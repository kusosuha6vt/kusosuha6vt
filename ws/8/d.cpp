#include <bits/stdc++.h>
#include "message.h"
#include "rps.h"

using namespace std;
typedef long long ll;

int main() {
    if (MyNodeId() == 0) {
        ll n = GetN();
        ll m = NumberOfNodes();
        int len = (1 << 28) / 32;
        int hlen = 22;
        for (int j = 1; j < m; ++j) {

        }
    } else {
        Receive(0);
        int l = GetInt(0);
        int r = GetInt(0);
        for (int i = l; i < r; ++i) {
            
        }
    }
    return 0;
}
