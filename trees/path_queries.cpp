#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
vvl children;
vl parent, start, ending;

void treeinit(ll n)
{
    children.assign(n + 1, vl(0));
    parent.assign(n + 1, -1);
    start.assign(n + 1, 0);
    ending.assign(n + 1, 0);
}

ll timer = 0;
void Traversal(ll node)
{ // euler tour
    start[node] = timer;
    for (auto x : children[node])
    {
        if (x == parent[node])
            continue;
        parent[x] = node;
        timer++;
        Traversal(x);
    }
    timer++;
    ending[node] = timer;
}

vl segtree; // dynamic rsq
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
    ll n, q, a, b;
    cin >> n >> q;
    treeinit(n);
    vl val(n + 1, 0);
    for (ll i = 1; i <= n; i++)
        cin >> val[i];
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b;
        children[a].emplace_back(b);
        children[b].emplace_back(a);
    }
    Traversal(1);
    // for (auto &i : start)
    //     cout << i << " ";
    // cout << "\n";
    // for (auto &i : ending)
    //     cout << i << " ";
    // cout << "\n";
    vl v(2 * n);
    for (ll i = 1; i <= n; i++)
    {
        v[start[i]] = val[i];
        v[ending[i]] = -val[i];
    }
    n *= 2;
    segtree.resize(4 * n, 0);
    build_seg(v, 1, 0, n - 1);
    // for (auto &i : v)
    //     cout << i << " ";
    // cout << "\n";
    ll num, s, x;
    for (ll i = 0; i < q; i++)
    {
        cin >> num >> s;
        if (num == 1)
        {
            cin >> x;
            update_pt(1, 0, n - 1, start[s], x);
            update_pt(1, 0, n - 1, ending[s], -x);
        }
        else
            cout << queryseg(1, 0, n - 1, 0, start[s]) << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}