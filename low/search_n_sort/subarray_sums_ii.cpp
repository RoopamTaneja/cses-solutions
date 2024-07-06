#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;

void solve()
{
    ll n, entry, x;
    vl v;
    cin >> n >> x;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    vl pref(n, 0);
    pref[0] = v[0];
    for (ll i = 1; i < n; i++)
    {
        pref[i] = pref[i - 1] + v[i];
    }
    ll ans = 0;
    unordered_map<ll, ll> freq;
    freq[0] = 1;
    for (ll i = 0; i < n; i++)
    {
        if (freq.find(pref[i] - x) != freq.end())
            ans += freq[pref[i] - x];
        freq[pref[i]]++;
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