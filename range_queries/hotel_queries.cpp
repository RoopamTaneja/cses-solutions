#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

vl segtree;
void build_seg(vl &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
        segtree[v] = a[tl];
    else
    {
        ll tm = (tl + tr) / 2;
        build_seg(a, v * 2, tl, tm);
        build_seg(a, v * 2 + 1, tm + 1, tr);
        segtree[v] = max(segtree[v * 2], segtree[v * 2 + 1]); // change function here
    }
}

ll queryseg(ll v, ll tl, ll tr, ll x)
{
    if (segtree[v] < x)
        return -1;
    if (tl == tr)
        return tl;
    ll tm = (tl + tr) / 2;
    ll val = queryseg(v * 2, tl, tm, x);
    if (val == -1)
        val = queryseg(v * 2 + 1, tm + 1, tr, x);
    return val;
}

void update_pt(ll v, ll tl, ll tr, ll pos, ll new_val)
{
    if (tl == tr)
        segtree[v] -= new_val;
    else
    {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update_pt(v * 2, tl, tm, pos, new_val);
        else
            update_pt(v * 2 + 1, tm + 1, tr, pos, new_val);
        segtree[v] = max(segtree[v * 2], segtree[v * 2 + 1]); // change function here
    }
}

void solve()
{
    ll n, entry, m;
    vl v;
    cin >> n >> m;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    segtree.resize(4 * n, 0);
    build_seg(v, 1, 0, n - 1);
    ll x;
    for (ll i = 0; i < m; i++)
    {
        cin >> x;
        ll ind = queryseg(1, 0, n - 1, x);
        if (ind != -1)
            update_pt(1, 0, n - 1, ind, x);
        cout << ind + 1 << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}