// https://leetcode.com/problems/implement-trie-prefix-tree/ 

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct trie_node
{
    ll next[26];
    bool flag = false;
    trie_node()
    {
        for (ll i = 0; i < 26; i++)
            next[i] = -1;
    }
};

class Trie
{
private:
    vector<trie_node> tri;

public:
    Trie()
    {
        tri.emplace_back();
    }

    void insert(string word)
    {
        ll v = 0;
        for (char c : word)
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

    bool search(string word)
    {
        ll v = 0;
        for (char c : word)
        {
            if (tri[v].next[c - 'a'] == -1)
                return false;
            v = tri[v].next[c - 'a'];
        }
        return tri[v].flag;
    }

    bool startsWith(string prefix)
    {
        ll v = 0;
        for (char c : prefix)
        {
            if (tri[v].next[c - 'a'] == -1)
                return false;
            v = tri[v].next[c - 'a'];
        }
        return true;
    }
};
