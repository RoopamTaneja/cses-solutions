#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

vl segtree;
vl lzAdd, lzSet;
void build_seg(vl &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
        segtree[v] = a[tl];
    else
    {
        ll tm = (tl + tr) / 2;
        build_seg(a, v * 2, tl, tm);
        build_seg(a, v * 2 + 1, tm + 1, tr);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1]; // combine fn for sum query
    }
}

void update_lz(ll ind, ll val, bool f)
{ // Most imp part of soln
    if (f)
    { // lzAdd update
        if (lzSet[ind] == 0)
            lzAdd[ind] += val;
        else
        {
            lzSet[ind] += val;
            lzAdd[ind] = 0;
        }
    }
    else
    { // lzSet update
        lzSet[ind] = val;
        lzAdd[ind] = 0;
    }
}

void push(ll v, ll tl, ll tr)
{
    ll tm = (tl + tr) / 2;
    if (lzAdd[v] != 0)
    {
        segtree[2 * v] += (tm - tl + 1) * lzAdd[v];
        segtree[2 * v + 1] += (tr - tm) * lzAdd[v];
        update_lz(2 * v, lzAdd[v], 1);
        update_lz(2 * v + 1, lzAdd[v], 1);
        lzAdd[v] = 0;
    }
    else if (lzSet[v] != 0)
    {
        segtree[2 * v] = (tm - tl + 1) * lzSet[v];
        segtree[2 * v + 1] = (tr - tm) * lzSet[v];
        update_lz(2 * v, lzSet[v], 0);
        update_lz(2 * v + 1, lzSet[v], 0);
        lzSet[v] = 0;
    }
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

void add_rng(ll v, ll tl, ll tr, ll l, ll r, ll addend)
{
    if (l > r)
        return;
    if (l == tl && tr == r)
    {
        segtree[v] += (tr - tl + 1) * addend;
        update_lz(v, addend, 1);
    }
    else
    {
        push(v, tl, tr);
        ll tm = (tl + tr) / 2;
        add_rng(v * 2, tl, tm, l, min(r, tm), addend);
        add_rng(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1];
    }
}

void set_rng(ll v, ll tl, ll tr, ll l, ll r, ll val)
{
    if (l > r)
        return;
    if (l == tl && tr == r)
    {
        segtree[v] = (tr - tl + 1) * val;
        update_lz(v, val, 0);
    }
    else
    {
        push(v, tl, tr);
        ll tm = (tl + tr) / 2;
        set_rng(v * 2, tl, tm, l, min(r, tm), val);
        set_rng(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
        segtree[v] = segtree[v * 2] + segtree[v * 2 + 1];
    }
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
    lzAdd.resize(4 * n, 0);
    lzSet.resize(4 * n, 0);
    build_seg(v, 1, 0, n - 1);
    ll num, a, b, x;
    for (ll i = 0; i < q; i++)
    {
        cin >> num >> a >> b;
        a--, b--; // 0-indexed
        if (num == 1)
        {
            cin >> x;
            add_rng(1, 0, n - 1, a, b, x);
        }
        else if (num == 2)
        {
            cin >> x;
            set_rng(1, 0, n - 1, a, b, x);
        }
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