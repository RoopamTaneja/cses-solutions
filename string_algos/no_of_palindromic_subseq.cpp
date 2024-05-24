// See strings.md
// incl repeated subseq
// TC : O(n^2)
// SC : O(n^2)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

ll countPS(string s)
{
    ll n = s.size();
    vector<vector<ll>> dp(n + 5, vector<ll>(n + 5));
    for (ll i = 0; i < n; i++)
        dp[i][1] = 1;
    for (ll i = 0; i < n - 1; i++)
    {
        if (s[i] == s[i + 1])
            dp[i][2] = 3;
        else
            dp[i][2] = 2;
    }
    for (ll l = 3; l <= n; l++)
    {
        for (ll i = 0; i < n - l + 1; i++)
        {
            dp[i][l] = (dp[i][l - 1] + dp[i + 1][l - 1]) % MOD;
            if (s[i] == s[i + l - 1])
                dp[i][l] = (dp[i][l] + 1) % MOD;
            else
                dp[i][l] = (dp[i][l] - dp[i + 1][l - 2] + MOD) % MOD;
        }
    }
    return dp[0][n];
}