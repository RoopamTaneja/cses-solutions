#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
typedef vector<ll> vl;

// Longest subarray having unique elements from array
// O(n lgn)
void solve()
{
    ll n, entry;
    vl v;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    ll start = 0;
    ll ans = 0;
    map<ll, ll> m;
    for (ll i = 0; i < n; i++)
    {
        if (m.find(v[i]) == m.end() || m[v[i]] < start)
            m[v[i]] = i;
        else
        {
            ans = max(ans, i - start);
            start = m[v[i]] + 1;
            m[v[i]] = i;
        }
    }
    ans = max(ans, n - start);
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}