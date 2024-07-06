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
    ll l = 0, r = 0;
    ll ans = 0;
    ll sum = 0;
    while (r < n)
    {
        sum += v[r];
        while (l < n && sum >= x)
        {
            if (sum == x)
                ans++;
            sum -= v[l];
            l++;
        }
        r++;
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