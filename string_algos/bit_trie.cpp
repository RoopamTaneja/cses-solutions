// Includes Qs : max XOR of two elements of array, max XOR subarray, max XOR queries

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

// Bit trie : Prefix of bits of elements of array from MSB to LSB
struct trie_node
{
    ll next[2];
    trie_node()
    {
        for (ll i = 0; i < 2; i++)
            next[i] = -1;
    }
};

vector<trie_node> tri;
// initialise with empty root inside driver (emplace_back)

// insert nos in trie starting from MSB till LSB
const int max_bits = 32;
void insert_num(ll num)
{
    // TC : O(max_bits)
    ll v = 0;
    for (ll i = max_bits - 1; i >= 0; i--)
    {
        ll bit = 0;
        if ((1LL << i) & num)
            bit = 1;
        if (tri[v].next[bit] == -1)
        {
            tri[v].next[bit] = tri.size();
            tri.emplace_back();
        }
        v = tri[v].next[bit];
    }
}

// returns max xor of num with any no present in trie
// looks for opposite bit at higher index and follows its branch (even if no more
// opposite bits since an opposite bit at higher index overpowers opposite bits at
// all lower indices)
// follows no in trie giving most opposite bits at high indices => gives max XOR
ll max_xr(ll num)
{
    // TC : O(max_bits)
    ll mx_xr = 0;
    ll v = 0;
    for (ll i = max_bits - 1; i >= 0; i--)
    {
        ll bit = 0;
        if ((1LL << i) & num)
            bit = 1;
        if (tri[v].next[1 - bit] != -1)
        {
            mx_xr |= (1LL << i);
            v = tri[v].next[1 - bit];
        }
        else
            v = tri[v].next[bit];
    }
    return mx_xr;
}

// for finding max XOR b/w two elements of array
ll findMaximumXORbwTwoNosOfArray(vl &v)
{
    // TC : O(n * max_bits)
    // SC : O(n * max_bits)
    tri.clear();
    tri.emplace_back();
    ll n = v.size();
    insert_num(v[0]);
    ll ans = 0;
    for (ll i = 1; i < n; i++)
    {
        ans = max(ans, max_xr(v[i]));
        insert_num(v[i]);
    }
    return ans;
}

// for finding max XOR sum of any subarray
// XOR[L..R] = XOR[0..R] ^ XOR[0..L-1] or if L = 0, XOR[0..R]
// or in other words = pref[R] ^ pref[L-1] or pref[R] ^ 0
// For each i from 0 to n, we need to find max XOR it can give with any no present in trie
// the max xor we get is best xor for any subarray ending at i, then add v[i] also to trie
// take max of all these values and that is your ans.
ll maxXORsubarray(vl &v)
{
    // TC : O(n * max_bits)
    // SC : O(n * max_bits)
    tri.clear();
    tri.emplace_back();
    ll n = v.size();
    vl pref_xr(n);
    pref_xr[0] = v[0];
    for (ll i = 1; i < n; i++)
        pref_xr[i] = v[i] ^ pref_xr[i - 1];
    ll ans = 0;
    insert_num(0);
    for (ll i = 0; i < n; i++)
    {
        ans = max(ans, max_xr(pref_xr[i]));
        insert_num(pref_xr[i]);
    }
    return ans;
}



// https://leetcode.com/problems/maximum-xor-with-an-element-from-array/
// Offline Queries is the hint
bool comp(vector<ll> v1, vector<ll> v2)
{
    if (v1[1] < v2[1])
        return true;
    return false;
}

vector<ll> maximizeXor(vector<ll> &v, vector<vector<ll>> &q)
{
    // TC : O( nlgn + mlgm + n*max_bits + m*max_bits )
    // SC : O( n * max_bits )
    ll n = v.size();
    ll m = q.size();
    tri.clear();
    tri.emplace_back();
    sort(v.begin(), v.end());
    for (ll i = 0; i < m; i++)
        q[i].emplace_back(i);
    sort(q.begin(), q.end(), comp);
    vector<ll> ans(m);
    ll j = 0;
    for (ll i = 0; i < m; i++)
    {
        ll x = q[i][0];
        ll m = q[i][1];
        while (j < n && v[j] <= m)
        {
            // only valid nos are in trie
            insert_num(v[j]);
            j++;
        }
        if (j == 0)
            ans[q[i][2]] = -1;
        else
            ans[q[i][2]] = max_xr(x);
    }
    return ans;
}