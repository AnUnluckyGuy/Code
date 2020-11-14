#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int maxn=(int)1e5+5;
int n,q,del[maxn],child[maxn],y,h[maxn],ans[maxn];
vector<int>a[maxn];
vector<pii>anc[maxn];

void DFS1(int x,int pre)
{
    child[x]=1;
    for(int j:a[x])
    {
        if (j!=pre && !del[j])
        {
            DFS1(j,x);
            child[x]+=child[j];
        }
    }
}

int Find_center(int x)
{
    int cap=child[x]/2;
    int pre=-1;
    while(true)
    {
        int Found=0;
        for(int j:a[x])
        {
            if(j!=pre && !del[j] && child[j]>cap)
            {
                pre=x;
                x=j;
                Found=1;
                break;
            }
        }
        if(!Found)return x;
    }
}

void DFS2(int x,int pre)
{
    anc[x].push_back(make_pair(y,h[x]));
    for(int j:a[x])
    {
        if(j!=pre && !del[j])
        {
            h[j]=h[x]+1;
            DFS2(j,x);
        }
    }
}

void Centroid (int x)
{
    DFS1(x,x);
    y=Find_center(x);
    del[y]=1;

    h[y]=0;DFS2(y,y);
    for(int j:a[y])
        if(!del[j])Centroid(j);
}

void Init()
{
    cin>>n>>q;
    for(int i=1;i<n;++i)
    {
        int u,v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    Centroid(1);
}

void Update(int x)
{
    for(auto j:anc[x])ans[j.first]=min(ans[j.first],j.second);
}

void Solve()
{
    for(int i=1;i<=n;++i)ans[i]=(int)1e9;
    Update(1);

    for(int i=1;i<=q;++i)
    {
        int kind,u;
        cin>>kind>>u;
        if(kind==1) Update(u);
        else
        {
            int res=ans[u];
            for(auto j:anc[u])res=min(res,j.second+ans[j.first]);
            cout<<res<<'\n';
        }
    }
}

int main()
{
	Init();
	Solve();
}
