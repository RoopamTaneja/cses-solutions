// See strings.md
// incl repeated substrings
// TC : O(n^2)
// SC : O(n^2)
// Faster algorithm -> manacher.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int countSubstrings(string s)
{
    ll n = s.size();
    vector<vector<bool>> dp(n + 5, vector<bool>(n + 5));
    for (ll i = 0; i < n; i++)
    {
        dp[i][1] = 1;
        if (i < n - 1)
            dp[i][2] = (s[i] == s[i + 1]);
    }
    for (ll l = 3; l <= n; l++)
        for (ll i = 0; i <= n - l; i++)
            dp[i][l] = (dp[i + 1][l - 2] && (s[i] == s[i + l - 1]));
    ll ans = 0;
    for (ll i = 0; i < n; i++)
        for (ll l = 1; l <= n; l++)
            ans += dp[i][l];
    return ans;
}