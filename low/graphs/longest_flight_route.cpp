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

void topoSort(ll node, vector<ll> adj[], ll vis[], stack<ll> &st)
{
    vis[node] = 1;
    for (auto it : adj[node])
        if (!vis[it])
            topoSort(it, adj, vis, st);

    st.push(node);
}

void shortestPath(ll V, vector<ll> adj[])
{
    ll vis[V] = {0};
    stack<ll> st;
    for (ll i = 1; i < V; i++)
        if (!vis[i])
            topoSort(i, adj, vis, st);

    vl dist(V, 1e9), parent(V, -1);
    dist[1] = 0;
    while (!st.empty())
    {
        ll node = st.top();
        st.pop();
        for (auto it : adj[node])
        {
            if (dist[node] != 1e9 && dist[node] - 1 < dist[it])
                dist[it] = dist[node] - 1, parent[it] = node;
        }
    }
    if (dist[V - 1] > 0)
        cout << "IMPOSSIBLE\n";
    else
    {
        vl path;
        ll temp = V - 1;
        while (temp != 1)
        {
            path.eb(temp);
            temp = parent[temp];
        }
        path.eb(1);
        reverse(all(path));
        ll val = path.size();
        cout << val << "\n";
        for (ll i = 0; i < val; i++)
            cout << path[i] << " ";

        cout << "\n";
    }
}

void solve()
{
    ll n, a, b, m;
    cin >> n >> m;
    vector<ll> adj[n + 1];
    for (ll i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].eb(b);
    }
    shortestPath(n + 1, adj);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}