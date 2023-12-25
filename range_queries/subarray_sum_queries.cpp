#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

struct node
{
    ll r_mss, r_sum, r_pref, r_suf;
};
vector<node> segtree;

node combine(node a, node b)
{
    node comb;
    comb.r_mss = max(max(a.r_mss, b.r_mss), a.r_suf + b.r_pref);
    comb.r_sum = a.r_sum + b.r_sum;
    comb.r_pref = max(a.r_pref, a.r_sum + b.r_pref);
    comb.r_suf = max(b.r_suf, b.r_sum + a.r_suf);
    return comb;
}

void build_seg(vl &a, ll v, ll tl, ll tr)
{
    if (tl == tr)
    {
        node new_node = {max(0LL, a[tl]), a[tl], max(0LL, a[tl]), max(0LL, a[tl])};
        segtree[v] = new_node;
    }
    else
    {
        ll tm = (tl + tr) / 2;
        build_seg(a, v * 2, tl, tm);
        build_seg(a, v * 2 + 1, tm + 1, tr);
        segtree[v] = combine(segtree[v * 2], segtree[v * 2 + 1]);
    }
}

// node queryseg(ll v, ll tl, ll tr, ll l, ll r)
// {
//     if (l > r)
//     {
//         node new_node = {-1, 0, -1, -1};
//         return new_node;
//     }
//     if (l == tl && r == tr)
//         return segtree[v];
//     ll tm = (tl + tr) / 2;
//     return combine(queryseg(v * 2, tl, tm, l, min(r, tm)), queryseg(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
// }

void update_pt(ll v, ll tl, ll tr, ll pos, ll new_val)
{
    if (tl == tr)
    {
        node new_node = {max(0LL, new_val), new_val, max(0LL, new_val), max(0LL, new_val)};
        segtree[v] = new_node;
    }
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
    ll a, b;
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        update_pt(1, 0, n - 1, a - 1, b);
        cout << segtree[1].r_mss << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}