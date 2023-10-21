#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// Datatypes
typedef long long ll;
typedef long double ld;
typedef long int l;
typedef unsigned int ui;

// Vectors
#define pb push_back
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

// Pairs
#define mp make_pair
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Mathematical Constants
#define _USE_MATH_DEFINES
#define mpi M_PI
#define me M_E
#define mphi 1.618033933 // Golden Ratio

const int MOD = 1e9 + 7;

// safe_map bfsOfGraph dfsIterOfGraph dfsRecurOfGraph flood_fill dijkstra kruskal

bool comp(pair<int, int> p1, pair<int, int> p2)
{ // just a sample
    if (p1.second > p2.second)
        return true;
    if (p1.second < p2.second)
        return false;
    if (p1.second == p2.second && p1.first > p2.first)
        return true;
    return false;
}

ll bin_mul(ll a, ll b, ll m)
{
    a %= m;
    ll res = 0;
    while (b > 0)
    {
        if (b & 1)
            res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

ll bin_exp_iter(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

ll pow_no_mod(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

ll floor_sqrt(ll x)
{
    ll ans = 0;
    for (ll k = 1LL << 30; k != 0; k /= 2)
    {
        if ((ans + k) * (ans + k) <= x)
            ans += k;
    }
    return ans;
}

class dsu
{
public:
    vl parent, size;
    dsu(ll n)
    { // makes new set
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (ll i = 0; i <= n; i++)
            parent[i] = i;
    }
    ll find_set(ll v)
    {
        if (v == parent[v])
            return v;
        // path compression
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(ll a, ll b)
    {
        // union by size
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

bool dfs(ll node, vl &parent, ll vis[], vl adj[], vl &result)
{
    vis[node] = 1;
    for (auto adjacentNode : adj[node])
    {
        if (!vis[adjacentNode])
        {
            parent[adjacentNode] = node;
            if (dfs(adjacentNode, parent, vis, adj, result) == true)
                return true;
        }
        else if (adjacentNode != parent[node])
        {
            result.eb(adjacentNode);
            while (node != adjacentNode)
            {
                result.eb(node);
                node = parent[node];
            }
            result.eb(adjacentNode);
            return true;
        }
    }
    return false;
}

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    vl adj[n + 1];
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].eb(b);
        adj[b].eb(a);
    }

    ll vis[n + 1] = {0};
    vl parent(n + 1, -1), result;
    for (int i = 1; i < n + 1; i++)
    {
        if (!vis[i])
        {
            if (dfs(i, parent, vis, adj, result))
            {
                cout << result.size() << "\n";
                for (ll i = 0; i < result.size(); i++)
                    cout << result[i] << " ";

                cout << "\n";
                return; // return when u get any cycle
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main()
{
    solve();
    return 0;
}