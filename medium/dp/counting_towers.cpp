#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;

const int MOD = 1e9 + 7;

void solve()
{
    ll t, n;
    cin >> t;
    vl w1(1000005, 0), w2(1000005, 0);
    w1[1] = 1;
    w2[1] = 1;
    for (ll i = 2; i <= 1000000; i++)
    {
        w1[i] = (w1[i] + w2[i - 1]) % MOD;
        w1[i] = ((w1[i] % MOD) + ((4 * w1[i - 1]) % MOD)) % MOD;
        w2[i] = ((w2[i] % MOD) + ((2 * w2[i - 1]) % MOD)) % MOD;
        w2[i] = (w2[i] + w1[i - 1]) % MOD;
    }
    while (t--)
    {
        cin >> n;
        cout << (w1[n] + w2[n]) % MOD << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}