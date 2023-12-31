#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

vl segtree;
vl lazy;
vl lzop_ct;
void build_seg(vl &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
        segtree[v] = a[tl];
    else
    {
        ll tm = (tl + tr) / 2;
        build_seg(a, v * 2, tl, tm);
        build_seg(a, v * 2 + 1, tm + 1, tr);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1];
    }
}

void lz_upd(ll i, ll x, ll y, ll a, ll b)
{
    ll len = b - a + 1;
    segtree[i] += (len * x) + (b * (b + 1) / 2 - a * (a - 1) / 2) * y;
    lazy[i] += x;
    lzop_ct[i] += y;
}

void push(ll v, ll tl, ll tr)
{
    ll tm = (tl + tr) / 2;
    lz_upd(2 * v, lazy[v], lzop_ct[v], tl, tm);
    lz_upd(2 * v + 1, lazy[v], lzop_ct[v], tm + 1, tr);
    lazy[v] = 0;
    lzop_ct[v] = 0;
}

ll queryseg(ll v, ll tl, ll tr, ll l, ll r)
{
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return segtree[v];
    push(v, tl, tr);
    ll tm = (tl + tr) / 2;
    return queryseg(v * 2, tl, tm, l, min(r, tm)) + queryseg(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update_rng(ll v, ll tl, ll tr, ll l, ll r, ll x, ll y)
{
    if (l > r)
        return;
    if (l == tl && tr == r)
    {
        lz_upd(v, x, y, tl, tr);
        return;
    }
    push(v, tl, tr);
    ll tm = (tl + tr) / 2;
    update_rng(v * 2, tl, tm, l, min(r, tm), x, y);
    update_rng(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x, y);
    segtree[v] = segtree[v * 2] + segtree[v * 2 + 1];
}

void solve()
{
    ll n, q, entry;
    cin >> n >> q;
    vl v;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.emplace_back(entry);
    }
    segtree.resize(4 * n, 0);
    lazy.resize(4 * n, 0);
    lzop_ct.resize(4 * n, 0);
    build_seg(v, 1, 0, n - 1);
    ll num, a, b;
    for (ll i = 0; i < q; i++)
    {
        cin >> num >> a >> b;
        a--, b--; // 0-indexed
        if (num == 1)
            update_rng(1, 0, n - 1, a, b, 1 - a, 1);
        else
            cout << queryseg(1, 0, n - 1, a, b) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}