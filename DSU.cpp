#include<bits/stdc++.h>
using namespace std;

int lab[100000];

void MakeSet()
{
    for(int i=1;i<=n;++i)lab[i]=-1;
}

int FndSet(int e)
{
    return lab[e]<0? e:lab[e]=FindSet(lab[e]);
}

void Union(int e,int f)
{
    if(lab[e]<lab[f])swap(e,f);

    lab[e]+=lab[f];

    lab[f]=e;
}

int main()
{
    int n;
    cin>>n;

    MakeSet();
}
