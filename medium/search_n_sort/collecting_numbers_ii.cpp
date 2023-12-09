#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve()
{
    ll n, entry, m;
    vl v;
    cin >> n >> m;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry - 1);
    }
    vl pos(n);
    for (ll i = 0; i < n; i++)
        pos[v[i]] = i;
    ll ans = 1;
    for (ll i = 1; i < n; i++)
    {
        if (pos[i] < pos[i - 1])
            ans++;
    }
    ll l, r, a, b;
    while (m--)
    {
        set<pll> s;
        cin >> l >> r;
        a = v[l - 1];
        b = v[r - 1];
        if (a > 0)
            s.insert(mp(a - 1, a));
        if (a < n - 1)
            s.insert(mp(a, a + 1));
        if (b > 0)
            s.insert(mp(b - 1, b));
        if (b < n - 1)
            s.insert(mp(b, b + 1));
        for (auto &p : s)
        {
            if (pos[p.second] < pos[p.first])
                ans--;
        }
        swap(pos[a], pos[b]);
        swap(v[l - 1], v[r - 1]);
        for (auto &p : s)
        {
            if (pos[p.second] < pos[p.first])
                ans++;
        }
        cout << ans << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}