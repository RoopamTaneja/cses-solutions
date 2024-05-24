// https://leetcode.com/problems/shortest-palindrome/

// Obs 1 : Longest prefix of string which is also a palindrome 
// need not be touched, rather the rest of the suffix can be reversed
// and attached to the front.
// Obs 2 : Longest prefix which is also palindrome is same as 
// longest prefix which is also a suffix of (s + "#" + reverse(s))
// (# to avoid length of prefix from exceeding length of string)
// Now longest such prefix can be found using KMP array.

// TC : O(n)
// SC : O(n)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

vl prefix_function(string s)
{
    ll n = s.length();
    vl pi(n);
    for (ll i = 1; i < n; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

string shortestPalindrome(string s)
{
    string t = s;
    reverse(s.begin(), s.end());
    string tmp = t + "#" + s;
    vl pref = prefix_function(tmp);
    ll n = t.size();
    ll val = pref[2 * n];
    if (val == n)
        return t;
    string rep = t.substr(val);
    reverse(rep.begin(), rep.end());
    return rep + t.substr(0, val) + t.substr(val);
}