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
        segtree[v] = min(segtree[v * 2], segtree[v * 2 + 1]);
    }
}

ll queryseg(ll v, ll tl, ll tr, ll l, ll r)
{
    if (l > r)
        return 1e10;
    if (l == tl && r == tr)
        return segtree[v];
    ll tm = (tl + tr) / 2;
    return min(queryseg(v * 2, tl, tm, l, min(r, tm)), queryseg(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
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
        segtree[v] = min(segtree[v * 2], segtree[v * 2 + 1]);
    }
}

vl seg2;
void build2(vl &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
        seg2[v] = a[tl];
    else
    {
        ll tm = (tl + tr) / 2;
        build2(a, v * 2, tl, tm);
        build2(a, v * 2 + 1, tm + 1, tr);
        seg2[v] = min(seg2[v * 2], seg2[v * 2 + 1]);
    }
}

ll query2(ll v, ll tl, ll tr, ll l, ll r)
{
    if (l > r)
        return 1e10;
    if (l == tl && r == tr)
        return seg2[v];
    ll tm = (tl + tr) / 2;
    return min(query2(v * 2, tl, tm, l, min(r, tm)), query2(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

void update2(ll v, ll tl, ll tr, ll pos, ll new_val)
{
    if (tl == tr)
        seg2[v] = new_val;
    else
    {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update2(v * 2, tl, tm, pos, new_val);
        else
            update2(v * 2 + 1, tm + 1, tr, pos, new_val);
        seg2[v] = min(seg2[v * 2], seg2[v * 2 + 1]);
    }
}

void solve()
{
    ll n, q;
    cin >> n >> q;
    vl v(n), s1(n), s2(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
        s1[i] = v[i] - i;
        s2[i] = v[i] + i;
    }
    segtree.resize(4 * n, 0);
    seg2.resize(4 * n, 0);
    build_seg(s1, 1, 0, n - 1);
    build2(s2, 1, 0, n - 1);
    ll a, k, x;
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> k;
        k--; // 0-based
        if (a == 1)
        {
            cin >> x;
            update_pt(1, 0, n - 1, k, x - k);
            update2(1, 0, n - 1, k, x + k);
        }
        else
        {
            ll val1 = queryseg(1, 0, n - 1, 0, k);
            ll val2 = query2(1, 0, n - 1, k + 1, n - 1);
            cout << min(val1 + k, val2 - k) << "\n";
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