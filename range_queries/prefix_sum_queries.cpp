#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

vector<pll> segtree;
pll combine(pll a, pll b)
{
    return mp((a.first + b.first), max(a.second, a.first + b.second));
}

void build_seg(vl &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
        segtree[v] = mp(a[tl], max(0LL, a[tl]));
    else
    {
        ll tm = (tl + tr) / 2;
        build_seg(a, v * 2, tl, tm);
        build_seg(a, v * 2 + 1, tm + 1, tr);
        segtree[v] = combine(segtree[v * 2], segtree[v * 2 + 1]);
    }
}

pll queryseg(ll v, ll tl, ll tr, ll l, ll r)
{
    if (l > r)
        return mp(0, -1);
    if (l == tl && r == tr)
        return segtree[v];
    ll tm = (tl + tr) / 2;
    return combine(queryseg(v * 2, tl, tm, l, min(r, tm)), queryseg(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

void update_pt(ll v, ll tl, ll tr, ll pos, ll new_val)
{
    if (tl == tr)
        segtree[v] = mp(new_val, max(0LL, new_val));
    else
    {
        ll tm = (tl + tr) / 2;
        if (pos <= tm)
            update_pt(v * 2, tl, tm, pos, new_val);
        else
            update_pt(v * 2 + 1, tm + 1, tr, pos, new_val);
        segtree[v] = combine(segtree[v * 2], segtree[v * 2 + 1]);
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
    segtree.resize(4 * n);
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
            cout << queryseg(1, 0, n - 1, a, b).second << "\n";
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