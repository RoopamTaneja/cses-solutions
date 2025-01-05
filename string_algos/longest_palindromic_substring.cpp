// See no_of_palindromic_substrings.cpp first
// TC : O(n^2)
// SC : O(n^2)

// Faster : 
// Manacher's : TC and SC both O(n) -> See manacher.cpp

// Just compute dp table to find which substrings are palindromes
// and return the longest among those

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string longestPalindrome(string s)
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
    for (ll l = n; l >= 2; l--)
    {
        for (ll i = 0; i < n; i++)
        {
            if (dp[i][l])
                return s.substr(i, l);
        }
    }
    return string(1, s[0]);
}