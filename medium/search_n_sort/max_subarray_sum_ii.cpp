#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<ll, ll> pll;

void solve()
{
    ll n, entry, a, b;
    vl v;
    cin >> n >> a >> b;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    vl pref(n, 0);
    pref[0] = v[0];
    for (ll i = 1; i < n; i++)
        pref[i] = pref[i - 1] + v[i];
    set<pll> s; // can also use multiset
    s.insert(mp(0, -1));
    ll ans = -2 * 1e15;
    for (ll i = a - 1; i < n; i++)
    { // kind of sliding window
        ans = max(ans, pref[i] - s.begin()->first);
        s.insert(mp(pref[i - a + 1], i - a + 1));
        if (s.size() > b - a + 1)
        {
            ll ind = i - b;
            ll key;
            if (i - b < 0)
                key = 0;
            else
                key = pref[i - b];
            s.erase(mp(key, ind));
        }
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