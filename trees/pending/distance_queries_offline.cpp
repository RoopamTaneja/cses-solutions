#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define mp make_pair
typedef pair<ll, ll> pll;

class dsu_rank
{
public:
    vl parent, rank;
    void dsu_init(ll n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (ll i = 0; i <= n; i++)
            parent[i] = i;
    }
    ll find_set(ll v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_rank(ll a, ll b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};


vvl children;
vl highest, level;
vector<vector<pll>> queries;
vl soln;
vector<bool> vis;
dsu_rank ds;

void treeinit(ll n, ll q)
{
    children.assign(n + 1, vl(0));
    vis.assign(n + 1, 0);
    highest.assign(n + 1, 0);
    level.assign(n + 1, 0);
    queries.resize(n + 1, vector<pll>(0));
    soln.resize(q);
    ds.dsu_init(n);
}

void Traversal(ll node)
{
    highest[node] = node;
    vis[node] = true;
    for (auto x : children[node])
    {
        if (vis[x])
            continue;
        level[x] = level[node] + 1;
        Traversal(x);
        ds.union_rank(node, x);
        highest[ds.find_set(node)] = node;
    }
    for (auto y : queries[node])
    {
        if (vis[y.first])
            soln[y.second] = highest[ds.find_set(y.first)];
    }
    // for (auto &other_node : queries[node])
    // {
    //     if (vis[other_node.first])
    //         cout << "LCA of " << node << " and " << other_node.first
    //              << " is " << highest[ds.find_set(other_node.first)] << ".\n";
    // }
}

void solve()
{
    ll n, q, a, b;
    vl v;
    cin >> n >> q;
    treeinit(n, q);
    for (ll i = 2; i <= n; i++)
    {
        cin >> a >> b;
        children[a].emplace_back(b);
        children[b].emplace_back(a);
    }
    vector<pll> store_query;
    for (ll i = 0; i < q; i++)
    {
        cin >> a >> b;
        store_query.emplace_back(mp(a, b));
        queries[a].emplace_back(mp(b, i));
    }
    Traversal(1);
    for (ll i = 0; i < q; i++)
    {
        ll l = store_query[i].first, r = store_query[i].second;
        ll lca = soln[i];
        cout << lca << "\n";
        // cout << level[l] + level[r] - 2 * level[lca] << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}