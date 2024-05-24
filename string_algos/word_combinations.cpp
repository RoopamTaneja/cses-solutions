#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

const int alpha = 26;
struct trie_node
{
    ll next[alpha];
    bool flag = false;
    trie_node()
    {
        for (ll i = 0; i < alpha; i++)
            next[i] = -1;
    }
};

vector<trie_node> tri;

void insert_string(string const &s)
{
    ll v = 0;
    for (char c : s)
    {
        if (tri[v].next[c - 'a'] == -1)
        {
            tri[v].next[c - 'a'] = tri.size();
            tri.emplace_back();
        }
        v = tri[v].next[c - 'a'];
    }
    tri[v].flag = true;
}

const int MOD = 1e9 + 7;

int main()
{
    tri.emplace_back();
    string s;
    cin >> s;
    ll k;
    cin >> k;
    string t;
    for (ll i = 0; i < k; i++)
    {
        cin >> t;
        insert_string(t);
    }
    ll n = s.size();
    vl dp(n);
    // dp[i] = no of ways to make s[i : n-1] from trie
    // Start from i and search for every prefix from i till n-1 in trie
    // If prefix ending at j (or s[i : j] ) is found => Ways of s[i : n-1] are incremented by ways 
    // of s[j+1 : n-1] or dp[i] += dp[j+1]
    // If the whole ending at n-1 is found => 1 more way of dp[i] is to get it whole from trie => 
    // dp[i] += 1
    // Since dp[i] needs dp values at higher indices precomputed => i goes reverse from n-1 to 0
    // Ans : dp[0]
    for (ll i = n - 1; i >= 0; i--)
    {
        ll v = 0;
        for (ll j = i; j < n; j++)
        {
            if (tri[v].next[s[j] - 'a'] == -1)
                break; // s[j] not found => rest of prefixes can't be made
            v = tri[v].next[s[j] - 'a'];
            if (tri[v].flag)
            {
                if (j == n - 1)
                    dp[i] = (dp[i] + 1) % MOD;
                else
                    dp[i] = (dp[i] + dp[j + 1]) % MOD;
            }
        }
    }
    cout << dp[0] << "\n";
    return 0;
}

// TC : O(sum of lengths of trie strings) + O(n ^ 2)
// SC : O(sum of lengths * size(alphabet))