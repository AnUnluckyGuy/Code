#include<bits/stdc++.h>
using namespace std;
typedef pair<long long,long long> line;

const long long oo=(long long)2e18;
const int maxn=(int)3e5;
int n,m;
struct X
{
    int l,r;
    line L;
}tree[maxn*4];

void BuildTree(int id,int le,int ri)
{
    tree[id].l=le;
    tree[id].r=ri;
    tree[id].L={(long long)0,(long long)0};

    if(le==ri)return;

    int mid=(le+ri)/2;
    BuildTree(id*2,le,mid);
    BuildTree(id*2+1,mid+1,ri);
}

long long Val(line LL,long long x)
{
    return x*LL.first+LL.second;
}

void Up(int id,int le,int ri,line newline)
{
    if(tree[id].l>ri || tree[id].r<le)return;

    if(tree[id].l>=le && tree[id].r<=ri)
    {
        line oldline=tree[id].L;

        int idl=tree[id].l;
        int idr=tree[id].r;

        if(Val(newline,idl)<=Val(oldline,idl) && Val(newline,idr)<=Val(oldline,idr))
        {
            return;
        }

        if(Val(newline,idl)>=Val(oldline,idl) && Val(newline,idr)>=Val(oldline,idr))
        {
            tree[id].L=newline;
            return;
        }

        int mid=(idl+idr)/2;
        if(Val(newline,idl)<=Val(oldline,idl) && Val(newline,mid)<=Val(oldline,mid))
        {
            Up(id*2+1,le,ri,newline);
            return;
        }

        if(Val(newline,idl)>=Val(oldline,idl) && Val(newline,mid)>=Val(oldline,mid))
        {
            Up(id*2+1,le,ri,oldline);
            tree[id].L=newline;
            return;
        }

        ++mid;
        if(Val(newline,mid)<=Val(oldline,mid) && Val(newline,idr)<=Val(oldline,idr))
        {
            Up(id*2,le,ri,newline);
            return;
        }

        if(Val(newline,mid)>=Val(oldline,mid) && Val(newline,idr)>=Val(oldline,idr))
        {
            Up(id*2,le,ri,oldline);
            tree[id].L=newline;
            return;
        }
    }

    Up(id*2,le,ri,newline);
    Up(id*2+1,le,ri,newline);
}

long long Get(int id,int pos)
{
    if(tree[id].l>pos || tree[id].r<pos)return 0;

    long long res=Val(tree[id].L,pos);
    if(tree[id].l==tree[id].r)return res;

    res=max(res,Get(id*2,pos));
    res=max(res,Get(id*2+1,pos));

    return res;
}

int main()
{
    ios_base::sync_with_stdio(NULL);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    BuildTree(1,1,n);

    for(int i=1;i<=m;++i)
    {
        long long s,e,v,d;
        cin>>s>>e>>v>>d;

        Up(1,s,e,{d,v-s*d});
    }

    for(int i=1;i<=n;++i)
        cout<<Get(1,i)<<'\n';
}
