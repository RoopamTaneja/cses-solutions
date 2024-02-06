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

bool comp(pair<int, int> p1, pair<int, int> p2)
{
    if (p1.second < p2.second)
        return true;
    return false;
}

void solve()
{
    ll n, a, b;
    vector<pll> v;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        cin >> a >> b;
        pll p = mp(a, b);
        v.eb(p);
    }
    sort(v.begin(), v.end(), comp);
    ll cnt = 1;
    ll last = 0;
    for (ll i = 1; i < n; i++)
    {
        if (v[i].first >= v[last].second)
        {
            cnt++;
            last = i;
        }
    }
    cout << cnt << "\n";
}

int main()
{
    solve();
    return 0;
}