#include<bits/stdc++.h>
using namespace std;

int l,r,z[2000005];
string t,s,zz;

void START()
{
    cin>>t>>s;

    zz=s+t;
}

void NEXT()
{
    l=r=0;

    z[0]=zz.length();

    for(int i=1;i<zz.length();++i)
    {
        if(i>r)
        {
            l=r=i;

            while(r<zz.length() && zz[r]==zz[r-l])++r;

            z[i]=r-l;
            --r;
        }

        else
        {
            int k=i-l;

            if(z[k]<r-i+1)z[i]=z[k];

            else
            {
                l=i;

                while(r<zz.length() && zz[r]==zz[r-l])++r;

                z[i]=r-l;
                --r;
            }
        }

        if(i>=s.length() && z[i]>=s.length())cout<<i-s.length()+1<<' ';
    }
}

int main()
{
    START();
    NEXT();
}
