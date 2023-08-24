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

// safe_map bfsOfGraph dfsIterOfGraph dfsRecurOfGraph

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

void bfs(ll n, vl adj[])
{
    vl dist(n + 1, INT_MAX);
    vl parent(n + 1, -1);
    vl result;
    dist[1] = 0;
    queue<ll> q;
    q.push(1);
    while (!q.empty())
    {
        ll node = q.front();
        q.pop();
        for (auto it : adj[node])
        {
            if (dist[it] == INT_MAX)
            {
                q.push(it);
                dist[it] = dist[node] + 1;
                parent[it] = node;
            }
            if (it == n)
                break;
        }
    }
    if (dist[n] == INT_MAX)
        cout << "IMPOSSIBLE\n";
    else
    {
        vl path;
        while (n != 1)
        {
            path.eb(n);
            n = parent[n];
        }
        path.eb(1);
        reverse(path.begin(), path.end());
        cout << path.size() << "\n";
        for (ll i = 0; i < path.size(); i++)
            cout << path[i] << " ";

        cout << "\n";
    }
}
// T. C. : BFS : O(V+E)

void solve()
{
    ll n, m;
    cin >> n >> m;

    vl adj[n + 1];
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs(n, adj);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}