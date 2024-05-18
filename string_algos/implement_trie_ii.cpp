// https://www.naukri.com/code360/problems/implement-trie_1387095

#include <bits/stdc++.h>
using namespace std;

const int alpha = 26;
struct trie_node
{
    int next[alpha];
    int cnt_pref = 0;
    int cnt_word = 0;
    trie_node()
    {
        for (int i = 0; i < alpha; i++)
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

    void insert(string &word)
    {
        int v = 0;
        for (char c : word)
        {
            if (tri[v].next[c - 'a'] == -1)
            {
                tri[v].next[c - 'a'] = tri.size();
                tri.emplace_back();
            }
            v = tri[v].next[c - 'a'];
            tri[v].cnt_pref++;
        }
        tri[v].cnt_word++;
    }

    int countWordsEqualTo(string &word)
    {
        int v = 0;
        for (char c : word)
        {
            if (tri[v].next[c - 'a'] == -1)
                return 0;
            v = tri[v].next[c - 'a'];
        }
        return tri[v].cnt_word;
    }

    int countWordsStartingWith(string &word)
    {
        int v = 0;
        for (char c : word)
        {
            if (tri[v].next[c - 'a'] == -1)
                return 0;
            v = tri[v].next[c - 'a'];
        }
        return tri[v].cnt_pref;
    }

    void erase(string &word)
    {
        int v = 0;
        for (char c : word)
        {
            if (tri[v].next[c - 'a'] == -1)
                return;
            v = tri[v].next[c - 'a'];
            tri[v].cnt_pref--;
        }
        if (tri[v].cnt_word)
            tri[v].cnt_word--;
    }
};