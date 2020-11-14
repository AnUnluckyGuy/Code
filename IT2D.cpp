#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=(int)2e3+1;
const int inf=(int)1e9;
int n,k;
int maxx[maxn*4][maxn*4];
int sum[maxn*4][maxn*4];

int query_y(int Idx , int x , int l , int r , int L , int R)
{
    if(L>r||l>R)return -inf;

    if(L<=l && r<=R)return maxx[Idx][x];

    int mid=(l+r)/2;
    return max(query_y(Idx,x*2,l,mid,L,R),query_y(Idx,x*2+1,mid+1,r,L,R));
}


int query_x(int x , int lx , int rx , int Lx , int Rx , int Ly , int Ry)
{
    if(Lx>rx || lx>Rx)return -inf;
    if(Lx<=lx && rx<=Rx)
        return query_y(x,1,1,2003,Ly,Ry);

    int mid=(lx+rx)/2;
    return max(query_x(x*2,lx,mid,Lx,Rx,Ly,Ry),query_x(x*2+1,mid+1,rx,Lx,Rx,Ly,Ry));
}

int query_Sy(int Idx , int x , int l , int r , int L , int R)
{
    if(L>r||l>R)return 0;

    if(L<=l && r<=R)return sum[Idx][x];

    int mid=(l+r)/2;
    return query_Sy(Idx,x*2,l,mid,L,R)+query_Sy(Idx,x*2+1,mid+1,r,L,R);
}


int query_Sx(int x , int lx , int rx , int Lx , int Rx , int Ly , int Ry)
{
    if(Lx>rx || lx>Rx)return 0;
    if(Lx<=lx && rx<=Rx)
        return query_Sy(x,1,1,2003,Ly,Ry);

    int mid=(lx+rx)/2;
    return query_Sx(x*2,lx,mid,Lx,Rx,Ly,Ry)+query_Sx(x*2+1,mid+1,rx,Lx,Rx,Ly,Ry);
}

void update_y(int Idx , int x , int l , int r , int X , int  Y , int c)
{
    if(l==r)
    {
        maxx[Idx][x]=max(maxx[Idx][x],c);
        if(X==1)
        {
            maxx[Idx][x]=max(maxx[Idx][x],maxx[Idx*2][x]);
            maxx[Idx][x]=max(maxx[Idx][x],maxx[Idx*2+1][x]);
        }
    }

    else
    {
        int mid=(l+r)/2;
        if(mid>=Y) update_y(Idx,x*2,l,mid,X,Y,c);
        else update_y(Idx,x*2+1,mid+1,r,X,Y,c);

        maxx[Idx][x]=max(maxx[Idx][x*2],maxx[Idx][x*2+1]);
        sum[Idx][x]=sum[Idx][x*2]+sum[Idx][x*2+1];
    }
}

void update_x(int id , int l , int r , int X , int Y , int c)
{
    if(l==r)
    {
        update_y(id,1,1,2003,0,Y,c);
        return;
    }

    int mid=(l+r)/2;

    if(mid>=X)update_x(id*2,l,mid,X,Y,c);
    else update_x(id*2+1,mid+1,r,X,Y,c);

    update_y(id,1,1,2003,1,Y,c);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill_n(&maxx[0][0],maxn*maxn*4*4,-inf);
    fill_n(&sum[0][0],maxn*maxn*4*4,0);
}

