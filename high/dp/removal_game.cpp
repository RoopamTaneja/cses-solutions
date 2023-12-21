#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<ll, ll> pll;

void solve()
{
    ll n, entry;
    cin >> n;
    vl v;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    ll sum = 0;
    for (ll i = 0; i < n; i++)
        sum += v[i];
    vvl dp(n, vl(n, -1 * 1e14));
    for (ll j = 0; j < n; j++)
    {
        for (ll i = n - 1; i >= 0; i--)
        {
            if (i == j)
                dp[i][j] = v[i];
            else
            {
                if (i < n - 1 && i < j)
                    dp[i][j] = max((v[i] - dp[i + 1][j]), dp[i][j]);
                if (j > 0 && i < j)
                    dp[i][j] = max((v[j] - dp[i][j - 1]), dp[i][j]);
            }
        }
    }
    cout << (dp[0][n - 1] + sum) / 2 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}