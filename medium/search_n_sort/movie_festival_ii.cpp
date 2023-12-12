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

bool comp(pll p1, pll p2)
{
    if (p1.second < p2.second)
        return true;
    return false;
}

void solve()
{
    ll n, a, b, k;
    vector<pll> v;
    cin >> n >> k;
    for (ll i = 0; i < n; i++)
    {
        cin >> a >> b;
        pll p = mp(a, b);
        v.eb(p);
    }
    sort(v.begin(), v.end(), comp);
    // The first step is the same as that of Movie Festival;
    // sort the movies in increasing order of end time.
    ll cnt = 1;
    k--;
    multiset<ll> ms;
    ms.insert(v[0].second);
    // ending times of different people in multiset
    // For each movie in order, we can assign a member to watch it
    // if there exists an element in ms less than or equal
    // to the start time of the movie. If there are multiple
    // such elements, choose the greatest one V. IMP !!!
    // for greatest => (--upper_bound)
    for (ll i = 1; i < n; i++)
    {
        auto it = ms.upper_bound(v[i].first);
        if (it != ms.begin())
        {
            cnt++;
            ms.erase(--it);
            ms.insert(v[i].second);
        }
        else if (k > 0)
        {
            k--;
            cnt++;
            ms.insert(v[i].second);
        }
    }
    cout << cnt << "\n";
}

int main()
{
    solve();
    return 0;
}