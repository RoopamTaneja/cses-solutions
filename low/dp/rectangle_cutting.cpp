#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

void solve()
{
    ll a, b;
    cin >> a >> b;
    vvl dp(a + 10, vl(b + 10, 1e10));
    for (ll i = 1; i < a + 1; i++)
    {
        for (ll j = 1; j < b + 1; j++)
        {
            if (i == j)
                dp[i][j] = 0;
            else
            {
                for (ll k = 1; k < j; k++)
                    dp[i][j] = min(dp[i][j], (dp[i][k] + dp[i][j - k] + 1));
                for (ll k = 1; k < i; k++)
                    dp[i][j] = min(dp[i][j], (dp[k][j] + dp[i - k][j] + 1));
            }
        }
    }
    cout << dp[a][b] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}