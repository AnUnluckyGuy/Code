#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6;
int n,m,num[maxn],Cut[maxn],Br[maxn];
struct X
{
    int x,y;
    bool del;
}edge[maxn];
vector<int> a[maxn];

void START()
{
    cin>>n>>m;

    for(int i=1;i<=m;++i)
    {
        cin>>edge[i].x>>edge[i].y;

        edge[i].del=0;

        a[edge[i].x].push_back(i);
        a[edge[i].y].push_back(i);
    }
}

void Visit(int u)
{
    int Root=(num[u]==-2);

    static int time=0;

    num[u]=time++;

    low[u]=maxn;

    int branch=0;//dem so nhanh con cua u

    for(int i:a[u])
    {
        if(edge[i].del)continue;

        edge[i].del=1;

        int v=edge[i].x+edge[i].y-u;//dinh noi voi u qua edge[i]

        if(num[v]==-1)
        {
            Visit(v);

            low[u]=min(low[u],low[v]);

            Br[i]=(low[v]>=num[v]);

            if(!Cut[u])Cut[u]=(low[v]>=num[u]);

            ++branch;
        }

        else low[u]=min(low[u],num[v]);
    }

    if(Root && branch<2)Cut[u]=0;
}

void NEXT()
{
    memset(num,-1,sizeof(num));
    memset(Br,0,sizeof(Br));
    memset(Cut,0,sizeof(Cut));

    for(int i=1;i<=n;++i)
    {
        if(num[i]==-1)
        {
            num[i]=-2;//danh dau la goc
            Visit(i);
        }
    }

    for(int i=1;i<=n;++i)
        if(Cut[i])cout<<i;//Khop

    for(int i=1;i<=m;++i)
        if(Br[i])cout<<i;//Cau
}

int main()
{
    START();
    NEXT();
}
