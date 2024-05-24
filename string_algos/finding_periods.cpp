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

void solve()
{
    string s;
    cin >> s;
    vl pi = prefix_function(s);
    ll n = s.size();
    vl ans;
    ll i = pi[n - 1];
    while (i)
    {
        ans.emplace_back(n - i);
        i = pi[i - 1];
    }
    ans.emplace_back(n);
    for (auto &x : ans)
        cout << x << " ";
    cout << "\n";
}

vl z_function(string s)
{
    ll n = s.size();
    vl z(n);
    ll l = 0, r = 0;
    for (ll i = 1; i < n; i++)
    {
        if (i < r)
            z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

void solve2()
{
    string s;
    cin >> s;
    vl z = z_function(s);
    ll n = s.size();
    vl ans;
    for (ll i = 0; i < n; i++)
    {
        if (i + z[i] >= n)
            ans.emplace_back(i);
    }
    ans.emplace_back(n);
    for (auto &x : ans)
        cout << x << " ";
    cout << "\n";
}

int main()
{
    solve();
    return 0;
}