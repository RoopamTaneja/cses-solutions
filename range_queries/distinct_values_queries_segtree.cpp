#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vl segtree;
ll queryseg(ll v, ll tl, ll tr, ll l, ll r)
{
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return segtree[v];
    ll tm = (tl + tr) / 2;
    return queryseg(v * 2, tl, tm, l, min(r, tm)) + queryseg(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update_pt(ll v, ll tl, ll tr, ll pos, ll new_val)
{
    if (tl == tr)
        segtree[v] = new_val;
    else
    {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update_pt(v * 2, tl, tm, pos, new_val);
        else
            update_pt(v * 2 + 1, tm + 1, tr, pos, new_val);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1]; 
    }
}

void solve()
{
    ll n, q;
    cin >> n >> q;
    vl v(n);
    for (ll i = 0; i < n; i++)
        cin >> v[i];
    vector<vector<pll>> queries(n);
    ll a, b;
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        a--, b--;
        queries[a].emplace_back(mp(b, i));
    }
    segtree.resize(4 * n, 0);
    map<ll, ll> last_ind;
    vl soln(q, -1);
    for (ll i = n - 1; i >= 0; i--)
    {
        ll val = v[i];
        if (last_ind.count(val) > 0)
            update_pt(1, 0, n - 1, last_ind[val], 0);
        last_ind[val] = i;
        update_pt(1, 0, n - 1, last_ind[val], 1);
        for (auto &x : queries[i])
            soln[x.second] = queryseg(1, 0, n - 1, i, x.first); // queryseg(1, 0, n - 1, 0, x.first) is also fine
    }
    for (auto &i : soln)
        cout << i << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
