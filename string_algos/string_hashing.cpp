#include <bits/stdc++.h>
using namespace std;
typedef ll ll;
typedef vector<ll> vl;

// USACO orz
class HashedString
{
private:
    // change m and p if you want
    static const ll m = 1e9 + 9;
    static const ll p = 9973;

    // pw[i] contains p^i % m
    static vector<ll> pw;

    // p_hash[i] is the hash of the first i characters of the given string
    vector<ll> p_hash;

public:
    HashedString(const string &s) : p_hash(s.size() + 1)
    {
        while (pw.size() < s.size())
        {
            pw.push_back((pw.back() * p) % m);
        }

        p_hash[0] = 0;
        for (int i = 0; i < s.size(); i++)
        {
            p_hash[i + 1] = ((p_hash[i] * p) % m + s[i]) % m;
        }
    }

    ll get_hash(int start, int end)
    {
        ll raw_val = (p_hash[end + 1] - (p_hash[start] * pw[end - start + 1]));
        return (raw_val % m + m) % m;
    }
};
vector<ll> HashedString::pw = {1};

// Simplified impl :
const ll m = 1e9 + 9;
const ll p = 9973;
void init(string &s, vl &pw, vl &pref)
{
    ll n = s.length();
    pw.push_back(1);
    while (pw.size() < n)
        pw.push_back((pw.back() * p) % m);
    pref.assign(n + 1, 0);
    for (ll i = 0; i < n; i++)
        pref[i + 1] = ((pref[i] * p) % m + s[i]) % m;
}

ll get_hash(ll i, ll j, vl &pw, vl &pref) // returns hash of s[i..j]
{                                         // i and j 0-indexed
    ll val = pref[j + 1] - (pref[i] * pw[j - i + 1]) % m;
    return (val + m) % m;
}

// sample caller
void solve()
{
    string s = "abc";
    vl pw, pref;
    init(s, pw, pref);
    ll ans = get_hash(0, 1, pw, pref);
}

int main()
{
    return 0;
}