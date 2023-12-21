#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;

vl segtree;
void build_seg(vl &a, ll v, ll tl, ll tr)
{
    // First resize segtree to 4*n and assign 0
    // segtree[v] gives ans for [tl,tr] 0-indexed
    // Start : v=1,tl=0,tr=n-1
    if (tl == tr)
        segtree[v] = a[tl];
    else
    {
        ll tm = (tl + tr) / 2;
        build_seg(a, v * 2, tl, tm);
        build_seg(a, v * 2 + 1, tm + 1, tr);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1]; // change function here
    }
}

ll queryseg(ll v, ll tl, ll tr, ll l, ll r)
{
    // Query for [l,r] 0-indexed
    // segtree[v] gives ans for [tl,tr]
    // Start : v=1,tl=0,tr=n-1
    if (l > r)
        return 0; // change identity here
    if (l == tl && r == tr)
        return segtree[v];
    ll tm = (tl + tr) / 2;
    return queryseg(v * 2, tl, tm, l, min(r, tm)) + queryseg(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r); // change function here
}

void update_pt(ll v, ll tl, ll tr, ll pos, ll new_val)
{
    // Update at index pos (0-indexed)
    // segtree[v] gives ans for [tl,tr]
    // Start : v=1,tl=0,tr=n-1
    if (tl == tr)
        segtree[v] = new_val;
    else
    {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update_pt(v * 2, tl, tm, pos, new_val);
        else
            update_pt(v * 2 + 1, tm + 1, tr, pos, new_val);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1]; // change function here
    }
}

void solve()
{
    ll n, entry, q;
    vl v;
    cin >> n >> q;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    segtree.resize(4 * n, 0);
    build_seg(v, 1, 0, n - 1);
    ll a, b, x;
    for (ll i = 0; i < q; i++)
    {
        cin >> x >> a >> b;
        a--; // 0-indexed
        if (x == 1)
            update_pt(1, 0, n - 1, a, b);
        else
        {
            b--; // 0-indexed
            cout << queryseg(1, 0, n - 1, a, b) << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}