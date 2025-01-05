#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

vl manacher_odd(string s)
{
    ll n = s.length();
    s = "$" + s + "^";
    ll l = 1, r = 1;
    vl ans(n + 2);
    for (ll i = 1; i <= n; i++)
    {
        ans[i] = max(0LL, min(r - i, ans[l + r - i]));
        while (s[i - ans[i]] == s[i + ans[i]])
            ans[i]++;
        if (i + ans[i] > r)
            l = i - ans[i], r = i + ans[i];
    }
    return vl(++ans.begin(), --ans.end());
}

vl manacher(string s)
{
    string t = "#";
    for (auto &c : s)
    {
        t.push_back(c);
        t.push_back('#');
    }
    vl ans = manacher_odd(t);
    return ans;
}

int main()
{
    string s;
    cin >> s;
    vl d = manacher(s);
    ll sz = d.size();
    // Using manacher array to find longest palindromic substring
    ll mx = 0, ind = -1;
    for (ll i = 0; i < sz; i++)
    {
        if (d[i] > mx)
        {
            mx = d[i];
            ind = i;
        }
    }
    string ans = s.substr((ind / 2) - (d[ind] / 2) + (ind % 2), d[ind] - 1);
    cout << ans << "\n";

    // For no of palindromic substrings
    // ll cnt = 0;
    // for (auto &x : d)
        // cnt += x / 2;
    return 0;
}