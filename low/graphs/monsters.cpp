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
typedef vector<char> vc;
typedef vector<vc> vvc;
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

// 0 = up, 1 = right, 2 = down, 3 = left
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
string stepDir = "URDL";
char grid[1000][1000];

void flood_fill_bfs(ll n, ll m, pll src, vector<pll> mons)
{
    ll x = src.first, y = src.second;
    vector<vector<bool>> vis(n, vector<bool>(m, 0));
    vvl prevStep(n, vl(m, -1)); // for backtracking from end (if needed)
    vvl steps(n, vl(m, INT_MAX));
    queue<pll> q;
    for (auto &mon : mons)
    {
        q.push(mon);
        steps[mon.first][mon.second] = 0;
        vis[mon.first][mon.second] = 1;
    }

    while (!q.empty())
    {
        ll top_x = q.front().first;
        ll top_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            ll adj_x = top_x + dx[i];
            ll adj_y = top_y + dy[i];
            if (adj_x < 0 || adj_x >= n || adj_y < 0 || adj_y >= m)
                continue;
            if (grid[adj_x][adj_y] == '#') // characters to be ignored
                continue;
            if (vis[adj_x][adj_y]) // ignore if already visited
                continue;
            vis[adj_x][adj_y] = 1;
            steps[adj_x][adj_y] = steps[top_x][top_y] + 1;
            q.push({adj_x, adj_y});
        }
    }
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < m; j++)
            vis[i][j] = false;

    queue<pair<pll, ll>> newq;
    newq.push({{x, y}, 0});
    vis[x][y] = 1;
    pll end;
    bool won = false;
    while (!newq.empty())
    {
        ll top_x = newq.front().first.first;
        ll top_y = newq.front().first.second;
        ll mySteps = newq.front().second;
        newq.pop();

        for (int i = 0; i < 4; i++)
        {
            ll adj_x = top_x + dx[i];
            ll adj_y = top_y + dy[i];
            if (adj_x < 0 || adj_x >= n || adj_y < 0 || adj_y >= m)
            {
                won = true;
                end = {top_x, top_y};
                break;
            }

            if (grid[adj_x][adj_y] == '#') // characters to be ignored
                continue;
            if (vis[adj_x][adj_y]) // ignore if already visited
                continue;
            if (mySteps + 1 >= steps[adj_x][adj_y])
                continue;
            vis[adj_x][adj_y] = 1;
            prevStep[adj_x][adj_y] = i;
            newq.push({{adj_x, adj_y}, mySteps + 1});
        }
        if (won)
            break;
    }
    if (won)
    {
        cout << "YES\n";
        vl path;
        while (end != src)
        {
            ll p = prevStep[end.first][end.second];
            path.eb(p);
            end = mp(end.first - dx[p], end.second - dy[p]);
        }
        reverse(path.begin(), path.end());
        cout << path.size() << "\n";
        for (ll c : path)
            cout << stepDir[c];

        cout << "\n";
    }
    else
        cout << "NO\n";
}

void solve()
{
    ll n, m, entry;
    cin >> n >> m;
    pll src;
    vector<pll> mons;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            cin >> grid[i][j];
            entry = grid[i][j];
            if (entry == 'A')
                src = mp(i, j);
            else if (entry == 'M')
                mons.eb(mp(i, j));
        }
    }
    flood_fill_bfs(n, m, src, mons);
}

/*Because the monsters move optimally, if a monster can reach a location in the
maze before A, then A may never move to that spot. Thus, for A to enter a spot,
the distance from that location to A must be less than the distance from that
location to the nearest monster. Knowing this, we may BFS to find all locations
that are visitable by A. This will run in N*M time because each location will
be visited a constant amount of times.

While conducting the bfs, store the previous location of every location. This way, once A reaches the edge, we can retrace A's
path, following the path of previous locations and storing the direction
traveled.*/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}