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

void method1(vector<pll> v, ll n, ll x)
{
    sort(all(v));
    for (ll i = 0; i < n; i++)
    {
        for (ll j = i + 1; j < n; j++)
        {
            ll k = j + 1;
            ll l = n - 1;
            while (k < l)
            {
                ll sum = v[i].first;
                sum += v[j].first;
                sum += v[k].first;
                sum += v[l].first;
                if (sum == x)
                {
                    cout << v[i].second << " " << v[j].second << " " << v[k].second << " " << v[l].second << "\n";
                    return;
                }
                else if (sum < x)
                    k++;
                else
                    l--;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

void method2(vl v, ll n, ll x)
{
    unordered_map<ll, pll> hm;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            int idx = x - v[i] - v[j];
            if (hm.find(idx) != hm.end())
            {
                cout << i + 1 << " " << j + 1 << " " << hm[idx].first + 1 << " " << hm[idx].second + 1;
                return;
            }
        }
        for (int j = i + 1; j < n; j++)
            hm[v[i] + v[j]] = {i, j};
    }
    cout << "IMPOSSIBLE\n";
}

void solve()
{
    ll n, entry, x;
    vector<pll> v;
    cin >> n >> x;
    vl vec;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        vec.eb(entry);
        v.eb(mp(entry, i + 1));
    }
    // method1(v, n, x);
    method2(vec, n, x);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}