#include<bits/stdc++.h>
using namespace std;

typedef pair<double,double> pdd;//bieu dien vector,diem,...

pdd operator +(pdd a,pdd b)
{
    return pdd(a.first+b.first,a.second+b.second);
}

pdd operator -(pdd a,pdd b)
{
    return pdd(a.first-b.first,a.second-b.second);
}

pdd operator *(double k,pdd a)
{
    return pdd(a.first*k,a.second*k);
}

double operator *(pdd a,pdd b)//cross product
{
    return a.first*b.second-a.second*b.first;
}

double operator ^(pdd a,pdd b)//dot product
{
    return a.first*b.first+a.second*b.second;
}

int ccw(pdd x,pdd y,pdd z)//vi tri cua diem z so voi dt xy
{
    pdd xy=y-x;//vector chi phuong dt xy

    pdd yz=z-y;//vector chi phuong dt yz

    if(xy*yz==0)return 0;//z thuoc xy

    if(xy*yz>0)return 1;//z nam tren
    return -1;//z nam duoi
}

double S(pdd convex[],int n)//dien tich polygon
{
    //convex da dc sort

    convex[n+1]=convex[1];

    double res=0.0;

    for(int i=1;i<=n;++i)
        res+=(convex[i].first-convex[i+1].first)*(convex[i].second+convex[i+1].second);

    if(res>0)return res;//cac convex dc sap xep ccw;
    else return -res;//cac convex dc dap xep cw;
}

const double oo=(double)1e8;

//giao 2 dt lan luot co PTTQ la a1*x+b1*y+c1=0 va a2*x+b2*y+c2=0
pdd Intersect(double a1,double b1,double c1,double a2,double b2,double c2)
{
    pdd u=pdd(a1,a2);
    pdd v=pdd(b1,b2);
    pdd w=pdd(-c1,-c2);

    double D=u*v;

    if(D!=0)return pdd(w*v/D,u*w/D);
    if(u*w==0)return pdd(oo,oo);//2 dt trung nhau
    return pdd(-oo,-oo);//2 dt song song
}

//tim giao 2 duong thang lan luot di qua A va co vector chi phuong u
//va di B co vector chi phuong v
pdd Intersect(pdd A,pdd u,pdd B,pdd v)
{
    pdd w=B-A;
    double D=u*v;
    if (D!=0)
    {
        pdd t=pdd(w*v/D,u*w/D);
        return A+t.first*u;
    }
    if(u*w==0) return pdd(oo,oo);
    return pdd(-oo,-oo);
}

double Distance(pdd a,pdd b)
{
    return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

const double PI=acos(-1);

double Angle(pdd x,pdd y,pdd z)
{
    long double dot=(x-y)^(z-y);
    long double cross=(x-y)*(z-y);
    if(cross==0)
    {
        if(x.first <= y.first && x.second <= y.second && y.first <= z.first && y.second <= z.second)return 0;
        return PI;
    }
    return PI-acos(dot/(Distance(x,y)*Distance(y,z)));
}
