#include<bits/stdc++.h>
using namespace std;

const int maxn=(int)1e5+50;
int n,q,vs[maxn],cntPos,child[maxn],parent[maxn],CHead[maxn],CChain,pos[maxn],posC[maxn],color[maxn];
vector<int> a[maxn];
int bit[maxn],ve[maxn];

void DFS(int u)
{
    vs[u]=1;

    for(int v:a[u])
    {
        if(!vs[v])
        {
            parent[v]=u;
            DFS(v);
            child[u]+=child[v]+1;
        }
    }
}

void START()
{
    cin>>n>>q;

    for(int i=1;i<n;++i)
    {
        int u,v;
        cin>>u>>v;

        a[u].push_back(v);
        a[v].push_back(u);
    }

    DFS(1);
}

void HLD(int u)
{
    if(!CHead[CChain])CHead[CChain]=u;

    posC[u]=CChain;

    ++cntPos;
    pos[u]=cntPos;
    ve[cntPos]=u;

    int spv=-1;

    for(int v:a[u])
    {
        if(v!=parent[u])
        {
            if((spv==-1)||(child[v]>child[spv]))spv=v;
        }
    }

    if(spv>-1)HLD(spv);

    for(int v:a[u])
    {
        if(v!=parent[u] && v!=spv)
        {
            ++CChain;
            HLD(v);
        }
    }
}

void Up(int id,int gt)
{
    for(;id<=n;id+=id&-id)bit[id]+=gt;
}

int Get(int id)
{
    int res=0;

    for(;id>=1;id-=id&-id)res+=bit[id];

    return res;
}

void NEXT()
{
    CChain=1;
    cntPos=0;
    HLD(1);

    for(int i=1;i<=q;++i)
    {
        int order,u;
        cin>>order>>u;

        if(!order)
        {
            if(!color[u])
            {
                Up(pos[u],1);
                color[u]=1;
            }

            else
            {
                Up(pos[u],-1);
                color[u]=0;
            }
        }

        else
        {
            int res=-1;

            int uChain=posC[u];

            while(true)
            {
                if(uChain==posC[1])
                {
                    int l=1;int r=pos[u];
                    int mid;

                    while(l<=r)
                    {
                        mid=(l+r)/2;

                        if(Get(mid)<1)l=mid+1;
                        else r=mid-1;
                    }

                    if(l<=pos[u] && Get(l)==1)res=ve[l];

                    cout<<res<<'\n';
                    break;
                }

                int l=pos[CHead[uChain]];int r=pos[u];
                int mid;

                int p=Get(l-1);

                while(l<=r)
                {
                    mid=(l+r)/2;

                    if(Get(mid)-p<1)l=mid+1;
                    else r=mid-1;
                }

                if(l<=pos[u] && Get(l)-p==1)res=ve[l];

                u=parent[CHead[uChain]];
                uChain=posC[u];
            }
        }
    }
}

int main()
{
    START();
    NEXT();
}

