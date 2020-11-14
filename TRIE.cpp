#include<bits/stdc++.h>
using namespace std;

const int maxn=1000000;
int n,m,num[maxn],child[maxn][15],cnt=0;
string s,t;

void GetTrie(string s)
{
    int node=0;

    for(int i=0;i<s.length();++i)
    {
        int k=s[i]-'a';

        if(!child[node][k])child[node][k]=++cnt;

        node=child[node][k];

        num[node]++;
    }
}

void START()
{
    fi>>n;

    for(int i=1;i<=n;++i)
    {
        fi>>s;
        GetTrie(s);
    }
}

int GetRes(string t)
{
    int node=0;

    for(int i=0;i<t.length();++i)
    {
        int k=t[i]-'a';

        if(!child[node][k])return 0;

        node=child[node][k];
    }
    return num[node];
}

void NEXT()
{
    fi>>m;

    for(int i=1;i<=m;++i)
    {
        fi>>t;
        fo<<GetRes(t)<<'\n';
    }
}

int main()
{
    START();
    NEXT();
}

