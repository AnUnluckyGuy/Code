#include<bits/stdc++.h>
#define pdb pair<double,double>
#define x first
#define y second
using namespace std;

int n;
pdb a[1000000];
pdb Convex[1000000];
double res;

pdb operator +(pdb A,pdb B)
{
    return pdb(A.x+B.x,A.y+B.y);
}

pdb operator -(pdb A,pdb B)
{
    return pdb(A.x-B.x,A.y-B.y);
}

pdb operator *(int k,pdb A)
{
    return pdb(k*A.x,k*A.y);
}

double operator *(pdb A,pdb B)
{
    return A.x*B.y-A.y*B.x;
}

bool cmpY(pdb u,pdb v)
{
    if(u.y==v.y)return u.x<v.x;

    return u.y<v.y;
}

void START()
{
    fi>>n;

    for(int i=1;i<=n;++i)fi>>a[i].x>>a[i].y;

    sort(a+1,a+n+1,cmpY);
}

int ccw(pdb p1,pdb p2,pdb p3)
{
     long double t=(p2-p1)*(p3-p1);
     if (t>0) return 1;
     if (t<0) return -1;
     return 0;
}

void NEXT()
{
    int m=0;

    for(int i=1;i<=n;++i)
    {
        if(m<2)Convex[++m]=a[i];
        else
        {
            while(m>1&&ccw(Convex[m-1],Convex[m],a[i])<0)--m;

            Convex[++m]=a[i];
        }
    }

    for(int i=n-1;i>=1;--i)
    {
        if(m<2)Convex[++m]=a[i];
        else
        {
            while(m>1&&ccw(Convex[m-1],Convex[m],a[i])<0)--m;

            Convex[++m]=a[i];
        }
    }

    --m;

    Convex[m+1]=Convex[1];

    res=0;

    for(int i=1;i<=m;++i)
    {
        res+=sqrt((Convex[i+1].x-Convex[i].x)*(Convex[i+1].x-Convex[i].x)+(Convex[i+1].y-Convex[i].y)*(Convex[i+1].y-Convex[i].y));
    }

    fo<<fixed<<setprecision(2)<<res;
}

int main()
{
    START();
    NEXT();
}

