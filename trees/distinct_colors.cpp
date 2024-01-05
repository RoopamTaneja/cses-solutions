#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<ll, ll> pll;
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
{
    start[node] = timer;
    timer++;
    for (auto x : children[node])
    {
        if (x == parent[node])
            continue;
        parent[x] = node;
        Traversal(x);
    }
    ending[node] = timer;
}

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
    ll n, a, b;
    cin >> n;
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
    vl v(n);
    vector<pll> queries(n);
    for (ll i = 1; i <= n; i++)
    {
        v[start[i]] = val[i];
        queries[start[i]] = mp((ending[i] - 1), i - 1);
    }
    segtree.resize(4 * n, 0);
    map<ll, ll> last_ind;
    vl soln(n, -1);
    for (ll i = n - 1; i >= 0; i--)
    {
        ll val = v[i];
        if (last_ind.count(val) > 0)
            update_pt(1, 0, n - 1, last_ind[val], 0);
        last_ind[val] = i;
        update_pt(1, 0, n - 1, last_ind[val], 1);
        soln[queries[i].second] = queryseg(1, 0, n - 1, i, queries[i].first);
    }
    for (auto &i : soln)
        cout << i << " ";
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
