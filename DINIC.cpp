#include<bits/stdc++.h>
using namespace std;

const int maxx=(int)1e6+50;
const int maxn=(int)1e5+50;
const int oo=(int)1e9+7;
int n,m,s,t,h[maxn],FlowVal;
struct X
{
    int x,y,cf;
}ed[maxx];
vector<int> L[maxn];
vector<int> :: iterator cur[maxn];

void GetH()
{
    for(int i=s;i<=t;++i)h[i]=t;

    queue<int> q;

    h[t]=0;
    q.push(t);

    while(!q.empty())
    {
        int u=q.front();
        q.pop();

        for(int i:L[u])
        {
            i^=1;

            int v=ed[i].x;

            if(ed[i].cf==0 || h[v]<t)continue;

            h[v]=h[u]+1;

            if(v==t)return;

            q.push(v);
        }
    }
}

int DFS(int u,int flowIn)
{
    if(u==t)return flowIn;

    int flowOut=0;

    for(;cur[u]!=L[u].end();++cur[u])
    {
        int i=*cur[u];

        int v=ed[i].y;

        if(ed[i].cf==0||h[v]!=h[u]-1)continue;

        int q=DFS(v,min(flowIn,ed[i].cf));

        flowIn-=q;
        flowOut+=q;
        ed[i].cf-=q;
        ed[i^1].cf+=q;
        if(flowIn==0)break;
    }

    return flowOut;
}

void BlockingFlow()
{
    for(int i=s;i<=t;++i)cur[i]=L[i].begin();

    FlowVal+=DFS(s,oo);
}

int main()
{
    cin>>n>>m;

    int cnt=0;

    for(int i=1;i<=m;++i)
    {
        int u,v;
        cin>>u>>v;

        ed[cnt]={u,v,1};
        L[u].push_back(cnt);
        ed[cnt+1]={v,u,0};
        L[v].push_back(cnt+1);
        cnt+=2;
    }

    while(GetH(),h[s]<t)
        BlockingFlow();
}
