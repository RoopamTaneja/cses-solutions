#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// Datatypes
typedef long long ll;
typedef long double ld;
typedef long int l;
typedef unsigned int ui;

// Vectors
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
const int MOD = 1e9 + 7;
void solve()
{
    ll n, entry, m;
    vl v;
    cin >> n >> m;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    vvl dp(n + 10, vl(m + 10, 0));
    dp[0][v[0]] = 1;
    if (v[0] == 0)
    {
        for (ll i = 0; i <= m; i++)
        {
            dp[0][i] = 1;
        }
    }
    for (ll i = 1; i < n; i++)
    {
        if (v[i] == 0)
        {
            for (ll j = 1; j <= m; j++)
            {
                if (j > 1)
                    dp[i][j] += dp[i - 1][j - 1];
                dp[i][j] += dp[i - 1][j];
                if (j <= m)
                    dp[i][j] += dp[i - 1][j + 1];
                dp[i][j] %= MOD;
            }
        }
        else
        {
            ll j = v[i];
            if (j > 1)
                dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] += dp[i - 1][j];
            if (j <= m)
                dp[i][j] += dp[i - 1][j + 1];
            dp[i][j] %= MOD;
        }
    }
    ll ans = 0;
    for (ll i = 1; i <= m; i++)
    {
        ans += dp[n - 1][i];
        ans %= MOD;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}