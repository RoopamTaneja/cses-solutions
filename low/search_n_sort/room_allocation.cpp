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

void solve()
{
    ll a, b, n;
    cin >> n;
    vector<pair<pll, ll>> v; // entry , exit, original index
    for (ll i = 0; i < n; i++)
    {
        cin >> a >> b;
        v.eb(mp(mp(a, b), i));
    }
    sort(all(v));
    ll room_no = 0;
    vl rooms(n, -1);
    set<pll> s;
    s.insert(mp(v[0].first.second, 1));
    rooms[v[0].second] = 1;
    ll last_room = 1;
    for (ll i = 1; i < n; i++)
    {
        auto min_dep = *s.begin();
        if (min_dep.first < v[i].first.first)
        {
            s.erase(s.begin());
            s.insert(mp(v[i].first.second, min_dep.second));
            rooms[v[i].second] = min_dep.second;
        }
        else
        {
            last_room++;
            s.insert(mp(v[i].first.second, last_room));
            rooms[v[i].second] = last_room;
        }
    }
    for (auto &i : rooms)
        room_no = max(i, room_no);
    cout << room_no << "\n";
    for (auto &i : rooms)
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