#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

// M-1 : KMP : O(n^2)

vl prefix_function(string &s)
{
    ll n = s.length();
    vl pi(n);
    for (ll i = 1; i < n; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

ll countDistinctSubstrings(string &s)
{
    ll ans = 0;
    string t = "";
    for (char c : s)
    {
        t.push_back(c);
        string tmp = t;
        reverse(t.begin(), t.end());
        vl temp = prefix_function(t);
        t = tmp;
        ll mx = *max_element(temp.begin(), temp.end());
        ans += t.size() - mx;
    }
    return ans + 1; // + 1 for counting empty string also
}

/*
We take the string t = s + c and reverse it.
Now the task is transformed into computing how many prefixes there are that don't appear anywhere else.
If we compute the maximal value of the prefix function of the reversed string, then the longest prefix that appears in s is  
pi_max long. Clearly also all prefixes of smaller length appear in it.

Therefore the number of new substrings appearing when we add a new character is (t - pi_max).

So for each character appended we can compute the number of new substrings in O(n) time, which gives a time complexity of O(n^2) in total.

It is worth noting, that we can also compute the number of different substrings by appending the characters at the beginning, or by deleting characters from the beginning or the end.
*/

// M-2 : Trie : O(n^2)

// Every substring is a prefix of some suffix of the string. Insert all O(n) suffixes in a trie. 
// Each node of a trie denotes a distinct prefix of some member of trie => Each node indicates a distinct substring
// Empty root indicates empty substring, if that has to be included, ans = tri.size() else tri.size()-1
// TC is O(sum of lengths) or O(n^2)

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

bool search_string(string const &s)
{
    ll v = 0;
    for (char c : s)
    {
        if (tri[v].next[c - 'a'] == -1)
            return false;
        v = tri[v].next[c - 'a'];
    }
    return tri[v].flag;
}

int trieDistinctSubstrings(string &s)
{
    tri.clear();
    tri.emplace_back();
    ll n = s.size();
    for (ll i = 0; i < n; i++)
        insert_string(s.substr(i, n - i));
    return tri.size(); // since empty string is included
}

// Other methods include suffix automata with better TC but beyond our scope at this point.