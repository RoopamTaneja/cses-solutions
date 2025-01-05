#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
#define eb emplace_back
#define all(v) v.begin(), v.end()
typedef vector<ll> vl;
#define mp make_pair
typedef pair<ll, ll> pll;

void solve()
{
    ll n, entry, k;
    vl v;
    cin >> n >> k;
    for (ll i = 0; i < n; i++)
    {
        cin >> entry;
        v.eb(entry);
    }
    ordered_set<ll> s;
    for (ll i = 0; i < k; i++)
        s.insert(v[i]);
    cout << *s.find_by_order((k - 1) / 2) << " ";
    for (ll i = 1; i < n - k + 1; i++)
    {
        s.erase(s.upper_bound(v[i - 1]));
        s.insert(v[i + k - 1]);
        cout << *s.find_by_order((k - 1) / 2) << " ";
    }
    cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

// ALITER : #pragma GCC optimize("O3,unroll-loops")

// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// void solve()
// {
//     ll n, entry, k;
//     vl v;
//     cin >> n >> k;
//     for (ll i = 0; i < n; i++)
//     {
//         cin >> entry;
//         v.eb(entry);
//     }
//     ordered_set<pll> s;
//     for (ll i = 0; i < k; i++)
//         s.insert(mp(v[i], i));
//     cout << s.find_by_order((k - 1) / 2)->first << " ";
//     for (ll i = 1; i < n - k + 1; i++)
//     {
//         s.erase(mp(v[i - 1], i - 1));
//         s.insert(mp(v[i + k - 1], i + k - 1));
//         cout << s.find_by_order((k - 1) / 2)->first << " ";
//     }
//     cout << "\n";
// }

// ALITER :
// #pragma GCC optimize("O3,unroll-loops")

// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// #define eb emplace_back
// #define all(v) v.begin(), v.end()
// typedef vector<ll> vl;
// #define mp make_pair
// typedef pair<ll, ll> pll;

// void solve()
// {
//     ll n, entry, k;
//     vl v;
//     cin >> n >> k;
//     for (ll i = 0; i < n; i++)
//     {
//         cin >> entry;
//         v.eb(entry);
//     }
//     multiset<ll> low, upp;
//     if (k == 1)
//     {
//         for (auto &i : v)
//             cout << i << " ";
//         cout << "\n";
//     }
//     else if (k == 2)
//     {
//         for (ll i = 0; i < n - 1; i++)
//             cout << min(v[i], v[i + 1]) << " ";
//         cout << "\n";
//     }
//     else
//     {
//         vl st;
//         for (ll i = 0; i < k; i++) // initializing the sets
//             st.eb(v[i]);
//         sort(all(st));
//         for (ll i = 0; i < (k + 1) / 2; i++)
//             low.insert(st[i]);
//         for (ll i = (k + 1) / 2; i < k; i++)
//             upp.insert(st[i]);
//         cout << *low.rbegin() << " ";
//         // shifting windows
//         ll low_sz = (k + 1) / 2;
//         for (ll i = k; i < n; i++)
//         {
//             auto lit = low.find(v[i - k]);
//             if (lit != low.end())
//                 low.erase(lit);
//             else
//                 upp.erase(upp.find(v[i - k]));
//             if (v[i] <= *low.rbegin())
//                 low.insert(v[i]);
//             else
//                 upp.insert(v[i]);
//             while (low.size() > low_sz)
//             {
//                 ll val = *low.rbegin();
//                 low.erase(low.find(val));
//                 upp.insert(val);
//             }
//             while (low.size() < low_sz)
//             {
//                 auto it = upp.begin();
//                 ll val = *it;
//                 upp.erase(it);
//                 low.insert(val);
//             }
//             cout << *low.rbegin() << " ";
//         }
//         cout << "\n";
//     }
// }

// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     solve();
//     return 0;
// }