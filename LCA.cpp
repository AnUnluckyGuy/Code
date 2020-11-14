#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6;
int n,k,u,v,h[maxn]/*do cao*/,T[maxn]/*cha truc tiep*/,p[maxn][20];
vector<int> a[maxn];

void DFS(int u)
{
    for(int v:a[u])
    {
        if(T[v]==-1)
        {
            T[v]=u;
            h[v]=h[u]+1;
            DFS(v);
        }
    }
}

void START()
{
    fi>>n>>k;

    for(int i=1;i<n;++i)
    {
        fi>>u>>v;

        a[u].push_back(v);

        a[v].push_back(u);
    }
}

void Prepare()
{
    memset(T,-1,sizeof(T));
    T[1]=0;h[1]=1;
    DFS(1);

    memset(p,-1,sizeof(p));

    for(int i=1;i<=n;++i)p[i][0]=T[i];//cha thu 2^0 cua i(cha truc tiep)

    for(int j=1;1<<j<=n;++j)
    {
        for(int i=1;i<=n;++i)
        {
            if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
            //cha thu 2^j cua i
        }
    }
}

void NEXT()
{
    for(int i=1;i<=k;++i)
    {
        cin>>u>>v;

        if(h[u]<h[v])swap(u,v);

        int log=log2(h[u]);

        for(int j=log;j>=0;--j)
        {
            if((h[u]-(1<<j))>=h[v])u=p[u][j];
        }

        if(u==v)fo<<u<<'\n';

        else
        {
            for(int j=log;j>=0;--j)
            {
                if(p[u][j]!=-1 && p[u][j]!=p[v][j])
                {
                    u=p[u][j];
                    v=p[v][j];
                }
            }

            fo<<T[u]<<'\n';
        }
    }
}

int main()
{
    cin>>n>>k;

    //nhap cac dg di

    Prepare();
    NEXT();
}
