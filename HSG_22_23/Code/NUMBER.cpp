#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 5;

bool isPrime[mxN];

void sieve() {
    for (int i = 2; i < mxN; ++i) isPrime[i] = true;
    for (int i = 2; i * i < mxN; ++i) {
        for (int j = i * i; j < mxN; j += i) isPrime[j] = false;
    }
}

bool isPalin(int n) {
    int x = n;
    int num = 0;
    while (x > 0) {
        num = num * 10 + x % 10;
        x /= 10;
    }
    return (num == n);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("NUMBER.INP", "r", stdin);
    freopen("NUMBER.OUT", "w", stdout);

    int p, q;
    cin >> p >> q;
    sieve();

    int res = 0;
    for (int i = p; i <= q; ++i) {
        if (isPrime[i] && isPalin(i)) ++res;
    }
    cout << res;
    return 0;
}